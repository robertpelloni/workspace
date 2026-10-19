import os
import logging
import uuid
from .utils import retry_request

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

class TTSGenerator:
    def __init__(self, api_key=None):
        """
        Initialize the TTS Generator with an ElevenLabs API key.

        Args:
            api_key (str): ElevenLabs API key. Defaults to ELEVENLABS_API_KEY env var.
        """
        self.api_key = api_key or os.environ.get("ELEVENLABS_API_KEY")
        self.client = None
        if not self.api_key:
            logger.warning("ELEVENLABS_API_KEY not set. TTSGenerator will not function.")

    def _get_client(self):
        if not self.client and self.api_key:
            from elevenlabs.client import ElevenLabs
            self.client = ElevenLabs(api_key=self.api_key)
        return self.client

    def _pitch_shift(self, sound, semitones):
        """
        High fidelity pitch-shift using pyrubberband to prevent altering audio speed.
        Converts the pydub AudioSegment to numpy, shifts, and converts back.
        """
        import numpy as np
        import pyrubberband as pyrb
        samples = np.array(sound.get_array_of_samples())
        if sound.channels == 2:
            samples = samples.reshape((-1, 2))

        max_val = 1 << (8 * sound.sample_width - 1)
        samples = samples.astype(np.float32) / max_val
        shifted_samples = pyrb.pitch_shift(samples, sound.frame_rate, semitones)
        shifted_samples = np.clip(shifted_samples, -1.0, 1.0)

        _SAMPLE_WIDTH_TO_DTYPE = {1: np.int8, 2: np.int16, 3: np.int32, 4: np.int32}
        dtype = _SAMPLE_WIDTH_TO_DTYPE.get(sound.sample_width, np.int16)
        shifted_samples = (shifted_samples * max_val).astype(dtype)

        shifted_sound = sound._spawn(shifted_samples.tobytes())
        return shifted_sound

    @retry_request(max_retries=3, delay=2, backoff=2)
    def generate_vocals(self, lyrics, output_path, voice_id="21m00Tcm4TlvDq8ikWAM", model="eleven_multilingual_v2", status_callback=None, **kwargs):
        """
        Generate a single synchronized vocal track from a list of lyrics and timestamps.
        """
        if not self.api_key:
            raise ValueError("ELEVENLABS_API_KEY is required to generate vocals.")

        from pydub import AudioSegment
        client = self._get_client()
        logger.info(f"Generating vocal track for {len(lyrics)} lines...")

        max_time_sec = 0
        if lyrics:
            max_time_sec = max([float(line.get('end', 0)) for line in lyrics] + [30])

        combined_audio = AudioSegment.silent(duration=int(max_time_sec * 1000) + 5000)

        voice_ids = [vid.strip() for vid in voice_id.split(',')]
        primary_voice = voice_ids[0]
        harmony_voices = voice_ids[1:] if len(voice_ids) > 1 else []

        total_lines = len(lyrics)

        for i, line in enumerate(lyrics):
            text = line.get('text', '').strip()
            if not text: continue

            start_ms = int(float(line.get('start', i * 5)) * 1000)
            logger.info(f"Synthesizing Vocal Line {i+1}/{total_lines}: '{text}' at {start_ms}ms")

            audio_generator = client.generate(text=text, voice=primary_voice, model=model)
            audio_data = b"".join(audio_generator)

            temp_filename = f"temp_tts_primary_{uuid.uuid4().hex}.mp3"
            try:
                with open(temp_filename, "wb") as f:
                    f.write(audio_data)
                line_audio = AudioSegment.from_file(temp_filename)

                if harmony_voices:
                    semitone_shifts = [4, 7, -5, -12]
                    for v_idx, h_voice in enumerate(harmony_voices):
                        h_generator = client.generate(text=text, voice=h_voice, model=model)
                        h_data = b"".join(h_generator)
                        h_temp = f"temp_tts_harm_{uuid.uuid4().hex}.mp3"
                        with open(h_temp, "wb") as hf: hf.write(h_data)
                        h_audio = AudioSegment.from_file(h_temp)
                        shift_amount = semitone_shifts[v_idx % len(semitone_shifts)]
                        h_audio = self._pitch_shift(h_audio, shift_amount)
                        h_audio = (h_audio - 6).pan(-0.5 if v_idx % 2 == 0 else 0.5)
                        line_audio = line_audio.overlay(h_audio)
                        if os.path.exists(h_temp): os.remove(h_temp)

                combined_audio = combined_audio.overlay(line_audio, position=start_ms)
            finally:
                if os.path.exists(temp_filename): os.remove(temp_filename)

        combined_audio.export(output_path, format="wav")
        return output_path

if __name__ == "__main__":
    import sys
    if os.environ.get("ELEVENLABS_API_KEY"):
        generator = TTSGenerator()
        if len(sys.argv) > 1:
            test_lyrics = [{"text": "Amazing grace", "start": 1.0, "end": 4.0}]
            generator.generate_vocals(test_lyrics, sys.argv[1])
