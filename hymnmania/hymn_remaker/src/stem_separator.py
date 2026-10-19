import logging
import os
import subprocess

logger = logging.getLogger(__name__)

class StemSeparator:
    def __init__(self, model="htdemucs"):
        """
        Wrapper for Facebook's Demucs stem separation library.
        Defaults to the highly performant hybrid transformer model (htdemucs).
        """
        self.model = model

    def separate(self, audio_path, output_dir):
        """
        Separates an audio file into vocals, drums, bass, and other.

        Args:
            audio_path (str): Path to the input mixed audio file.
            output_dir (str): Directory where the output stems should be saved.

        Returns:
            dict: A dictionary mapping stem names to their respective file paths.
                  e.g., {'drums': 'path/to/drums.wav', 'bass': '...', 'other': '...', 'vocals': '...'}
        """
        if not os.path.exists(audio_path):
            raise FileNotFoundError(f"Audio file to separate not found: {audio_path}")

        logger.info(f"Running Demucs stem separation on {audio_path}...")

        # Ensure output directory exists
        os.makedirs(output_dir, exist_ok=True)

        # Demucs CLI: demucs -n <model> --out <output_dir> <input_file>
        # Outputs to <output_dir>/<model>/<filename_no_ext>/<stem>.wav
        cmd = [
            "python3", "-m", "demucs.separate",
            "-n", self.model,
            "-o", output_dir,
            audio_path
        ]

        try:
            subprocess.run(cmd, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

            # Locate the generated files
            filename = os.path.basename(audio_path)
            name_no_ext = os.path.splitext(filename)[0]
            stem_dir = os.path.join(output_dir, self.model, name_no_ext)

            if not os.path.exists(stem_dir):
                raise FileNotFoundError(f"Demucs output directory not found: {stem_dir}")

            stems = {}
            for stem_name in ["drums", "bass", "other", "vocals"]:
                expected_path = os.path.join(stem_dir, f"{stem_name}.wav")
                if os.path.exists(expected_path):
                    stems[stem_name] = expected_path
                else:
                    logger.warning(f"Expected stem not found: {expected_path}")

            logger.info("Stem separation complete.")
            return stems

        except subprocess.CalledProcessError as e:
            error_msg = e.stderr.decode()
            logger.error(f"Demucs failed: {error_msg}")
            raise RuntimeError(f"Stem separation failed: {error_msg}")
