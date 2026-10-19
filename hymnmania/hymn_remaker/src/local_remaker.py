import os
import torch
import torchaudio
import logging
from transformers import MusicgenMelodyForConditionalGeneration, AutoProcessor
import numpy as np
from scipy.io import wavfile

logger = logging.getLogger(__name__)

class LocalMusicRemaker:
    def __init__(self, model_id="facebook/musicgen-melody", use_half=True):
        self.device = "cuda" if torch.cuda.is_available() else "cpu"
        logger.info(f"Loading Local MusicGen model ({model_id}) on {self.device}...")

        # Load model
        self.model = MusicgenMelodyForConditionalGeneration.from_pretrained(
            model_id,
            torch_dtype=torch.float16 if (use_half and self.device == "cuda") else torch.float32
        ).to(self.device)

        # Enable CPU offload or other optimizations if on CPU
        if self.device == "cpu":
            # Optional: dynamic quantization for CPU speedup
            # Note: MusicGen may have mixed results with standard dynamic quantization
            try:
                import intel_extension_for_pytorch as ipex
                self.model = ipex.optimize(self.model)
                logger.info("IPEX optimization applied for CPU inference.")
            except ImportError:
                pass

        self.processor = AutoProcessor.from_pretrained(model_id)

    def generate(self, prompt, melody_path=None, duration=30, output_path=None, guidance_scale=3.0, temperature=1.0):
        """
        Generate audio locally using MusicGen. Supports both melody-conditioned and text-to-audio.
        """
        if melody_path and os.path.exists(melody_path):
            logger.info(f"Local Generation (Melody): prompt='{prompt}', conditioning={melody_path}")
            melody, sr = torchaudio.load(melody_path)
            inputs = self.processor(
                audio=melody,
                sampling_rate=sr,
                text=[prompt],
                padding=True,
                return_tensors="pt",
            ).to(self.device)
        else:
            logger.info(f"Local Generation (Text-only): prompt='{prompt}'")
            inputs = self.processor(
                text=[prompt],
                padding=True,
                return_tensors="pt",
            ).to(self.device)

        # Generate
        # MusicGen uses 50 tokens per second
        max_tokens = int(duration * 50)

        with torch.no_grad():
            audio_values = self.model.generate(
                **inputs,
                max_new_tokens=max_tokens,
                guidance_scale=guidance_scale,
                do_sample=True,
                temperature=temperature
            )

        # Post-process
        sampling_rate = self.model.config.audio_encoder.sampling_rate
        audio_data = audio_values[0, 0].cpu().numpy()

        if output_path:
            # Normalize to 16-bit PCM
            max_val = np.max(np.abs(audio_data))
            if max_val > 0:
                audio_data = audio_data / max_val
            wavfile.write(output_path, sampling_rate, (audio_data * 32767).astype(np.int16))
            logger.info(f"Local generation saved to {output_path}")
            return output_path

        return audio_data, sampling_rate

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    # Basic test
    # remaker = LocalMusicRemaker()
