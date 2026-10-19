import os
import time
import logging

from hymn_remaker import settings
from hymn_remaker.src.local_video_generator import LocalVideoGenerator

logger = logging.getLogger(__name__)

class AIVideoGenerator:
    """
    Generates AI-powered videos using state-of-the-art diffusion models.
    Supports cloud models via Replicate and local beat-synced generation via LTX-Video/Wan2.1.
    """

    def __init__(self, api_token=None):
        """Initialize the AI Video Generator."""
        self.api_token = api_token or os.environ.get("REPLICATE_API_TOKEN")
        self.local_gen = None

        if self.api_token:
            logger.info("AIVideoGenerator initialized (lazy client).")
        else:
            logger.warning("REPLICATE_API_TOKEN not set.")

    def _get_local_gen(self):
        if not self.local_gen:
            from hymn_remaker.src.local_video_generator import LocalVideoGenerator
            self.local_gen = LocalVideoGenerator()
        return self.local_gen

    def generate_video(self, audio_path, image_url, output_path, prompt=None, tempo=120.0, force_local=False, model_type="ltx-video", model_size="1.3b", quotes=None):
        """High level dispatch for video generation."""
        if force_local:
            return self._get_local_gen().generate_video(audio_path, image_url, output_path, prompt=prompt, tempo=tempo, model_type=model_type, model_size=model_size, quotes=quotes)

        import requests
        import replicate
        # ... rest of method
        """
        Generate an audio-reactive AI video.
        Supports cloud models via Replicate or local GPU generation.

        Args:
            audio_path (str): Path to the rendered song WAV/MP3.
            image_url (str): URL or local path to the generated album art.
            output_path (str): Final MP4 destination.
            prompt (str): Text prompt describing the visual motion.
            tempo (float): Tempo of the audio in BPM for beat synchronization.
            force_local (bool): If True, skips Replicate and generates video locally.
            model_type (str): Local model type ('ltx-video' or 'wan').
            model_size (str): Local model size (e.g. '1.3b', '14b').
            quotes (list): Optional list of dicts representing beat-synced text quotes.

        Returns:
            str: Path to the generated video file.
        """
        # Default prompt if none provided
        if not prompt:
            prompt = "An abstract, evolving visual journey following the rhythm and mood of the music. Cinematic, high quality, vibrant."

        # Check if the audio file exists
        if not os.path.exists(audio_path):
            logger.error(f"Audio file not found for video generation: {audio_path}")
            return None

        # Fallback or forced local generation
        if force_local or not self.api_token:
            if force_local:
                logger.info(f"Local video generation forced. Model: {model_type} ({model_size})")
            else:
                logger.info("REPLICATE_API_TOKEN is missing. Attempting local programmatic video generation...")

            self.local_gen = LocalVideoGenerator(model_type=model_type, model_size=model_size)
            if self.local_gen.check_dependencies():
                local_image_path = image_url
                # If image_url is a web URL, download it locally first
                if image_url and (image_url.startswith("http://") or image_url.startswith("https://")):
                    try:
                        logger.info(f"Downloading cover art from URL for local video generator: {image_url}")
                        resp = requests.get(image_url, timeout=30)
                        resp.raise_for_status()
                        local_image_path = output_path.replace(".mp4", "_art_temp.png")
                        with open(local_image_path, "wb") as f:
                            f.write(resp.content)
                    except Exception as e:
                        logger.warning(f"Could not download image for local video generation: {e}")
                        local_image_path = None

                # Execute local beat-synchronized generation
                res = self.local_gen.generate_beat_synced_video(
                    audio_path=audio_path,
                    image_path=local_image_path,
                    output_path=output_path,
                    tempo_bpm=tempo,
                    prompt=prompt,
                    duration_sec=10.0,
                    quotes=quotes
                )

                # Cleanup temporary downloaded image
                if local_image_path and local_image_path != image_url and os.path.exists(local_image_path):
                    os.remove(local_image_path)
                return res
            else:
                logger.error("Local video generation dependencies (torch, diffusers) are missing. Cannot generate local video.")
                return None

        try:
            logger.info(f"Starting Replicate AI Video Generation (LTX-Video) for {os.path.basename(audio_path)}...")

            # Using lucataco/ltx-video on Replicate for higher reliability
            output = replicate.run(
                "lucataco/ltx-video:603957f6e07662c5e533b34479e09d5930e104e54884260908865f80b2a7576f",
                input={
                    "prompt": prompt,
                    "input_image": image_url,
                    "num_frames": 121,
                    "fps": 24,
                    "aspect_ratio": "16:9"
                }
            )

            if not output:
                raise RuntimeError("AI video generation returned no output.")

            video_url = output
            logger.info(f"AI Video generated! Downloading from {video_url}...")

            response = requests.get(video_url, timeout=120)
            response.raise_for_status()

            with open(output_path, "wb") as f:
                f.write(response.content)

            logger.info(f"AI Video saved to {output_path}")
            return output_path

        except Exception as e:
            logger.error(f"Replicate AI Video generation failed: {e}")
            return None

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    gen = AIVideoGenerator()
