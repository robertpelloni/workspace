import os
import logging
import sys
from .utils import retry_request

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

class MusicRemaker:
    def __init__(self, api_token=None):
        """Initialize the Music Remaker using Replicate."""
        self.api_token = api_token or os.environ.get("REPLICATE_API_TOKEN")
        self.client = None
        if self.api_token:
            logger.info("MusicRemaker initialized (lazy client).")
        else:
            logger.warning("REPLICATE_API_TOKEN not set.")

    def remake(self, audio_path, prompt):
        """Remix an audio file using Replicate MusicGen."""
        import replicate
        if not self.client and self.api_token:
             self.client = replicate.Client(api_token=self.api_token)

        if not self.client:
            raise RuntimeError("Replicate client not initialized.")

        with open(audio_path, "rb") as audio_file:
            # Create a 'file' object for Replicate
            # Use specific MusicGen Melody version
            output = replicate.run(
                "meta/musicgen:671ac645ce5e552cc63a54a2bbff63fcf798043055d2dac5fc9e36a837eedcfb",
                input={
                    "model_version": "melody",
                    "prompt": prompt,
                    "input_audio": audio_file,
                    "duration": 30,
                    "continuation": False
                }
            )

        if not output:
            raise RuntimeError("Music generation returned no output.")

        logger.info(f"Music remake generated: {output}")
        return output

if __name__ == "__main__":
    if len(sys.argv) > 2:
        remaker = MusicRemaker()
        print(remaker.remake(sys.argv[1], sys.argv[2]))
