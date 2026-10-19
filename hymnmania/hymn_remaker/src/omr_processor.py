import logging
import os
import subprocess

logger = logging.getLogger(__name__)

class OMRProcessor:
    def __init__(self):
        pass

    def is_available(self):
        """Check if the oemer CLI tool is installed and available."""
        try:
            subprocess.run(["oemer", "--help"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, check=True)
            return True
        except (subprocess.CalledProcessError, FileNotFoundError):
            return False

    def process(self, image_path, output_dir):
        """
        Run Optical Music Recognition on a given image/PDF file and output a MusicXML file.

        Args:
            image_path (str): Path to the input sheet music image (png, jpg, pdf).
            output_dir (str): Directory to place the generated MusicXML file.

        Returns:
            str: The path to the generated .mxl file.
        """
        if not os.path.exists(image_path):
            raise FileNotFoundError(f"OMR input file not found: {image_path}")

        filename = os.path.basename(image_path)
        name_no_ext = os.path.splitext(filename)[0]
        output_mxl_path = os.path.join(output_dir, f"{name_no_ext}.mxl")

        logger.info(f"Running OMR (oemer) on {image_path}...")

        # oemer usually outputs the file in the same directory as the input,
        # or takes an output path depending on its CLI options.
        # Its default behavior is `oemer <image_path>`, which produces `<image_path_no_ext>.musicxml`
        try:
            # We run oemer
            cmd = ["oemer", image_path]
            result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

            if result.returncode != 0:
                logger.error(f"oemer failed: {result.stderr}")
                raise RuntimeError(f"OMR processing failed: {result.stderr}")

            # Locate the output file. oemer typically generates a .musicxml file in the same directory as the input.
            input_dir = os.path.dirname(image_path)
            expected_output = os.path.join(input_dir, f"{name_no_ext}.musicxml")

            if os.path.exists(expected_output):
                # Move/Rename it to our output directory as .mxl so the rest of the pipeline picks it up
                import shutil
                shutil.move(expected_output, output_mxl_path)
                logger.info(f"OMR successful. Generated: {output_mxl_path}")
                return output_mxl_path
            else:
                logger.error(f"oemer succeeded but output file {expected_output} was not found.")
                raise FileNotFoundError(f"Expected OMR output not found: {expected_output}")

        except Exception as e:
            logger.error(f"OMR Processor encountered an error: {e}")
            raise e
