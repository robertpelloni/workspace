import os
import logging
import torch
from pathlib import Path
from diffusers import LTXImageToVideoPipeline, WanImageToVideoPipeline
from diffusers.utils import export_to_video

logger = logging.getLogger(__name__)

class LocalVideoGenerator:
    """
    Generates AI-powered video loops locally using GPU-accelerated diffusion models (LTX-Video, Wan 2.1).
    """

    def __init__(self, model_type="ltx-video", model_size="1.3b"):
        self.model_type = model_type.lower()
        self.model_size = model_size.lower()
        self.device = "cpu"
        try:
            import torch
            self.device = "cuda" if torch.cuda.is_available() else "cpu"
        except ImportError:
            pass
        self.pipeline = None

        if self.device == "cpu":
            logger.warning("No CUDA detected. Local video generation will be EXTREMELY slow.")

    def _load_pipeline(self):
        if self.pipeline:
            return

        import torch
        from diffusers import LTXImageToVideoPipeline, WanImageToVideoPipeline

        try:
            if self.model_type == "ltx-video":
                model_id = "Lightricks/LTX-Video"
                logger.info(f"Loading LTX-Video pipeline from {model_id}...")
                self.pipeline = LTXImageToVideoPipeline.from_pretrained(
                    model_id,
                    torch_dtype=torch.float16 if self.device == "cuda" else torch.float32
                ).to(self.device)
                # Optimization for 1080 Ti (11GB VRAM)
                self.pipeline.enable_model_cpu_offload()

            elif self.model_type == "wan":
                # For Wan 2.1, model size matters
                if self.model_size == "1.3b":
                    model_id = "Wan-AI/Wan2.1-T2V-1.3B-Diffusers"
                else:
                    model_id = "Wan-AI/Wan2.1-T2V-14B-Diffusers"

                logger.info(f"Loading Wan 2.1 ({self.model_size}) pipeline from {model_id}...")
                self.pipeline = WanImageToVideoPipeline.from_pretrained(
                    model_id,
                    torch_dtype=torch.float16 if self.device == "cuda" else torch.float32
                ).to(self.device)
                self.pipeline.enable_model_cpu_offload()

            logger.info(f"Pipeline {self.model_type} loaded successfully on {self.device}.")
        except Exception as e:
            logger.error(f"Failed to load video pipeline: {e}")
            raise

    def check_dependencies(self):
        """Check if all required AI video libraries are installed."""
        try:
            import torch
            import diffusers
            import transformers
            return True
        except ImportError:
            return False

    def generate_loop(self, prompt, output_path, image=None, num_frames=81):
        """
        Generate a single continuous high-quality video loop.
        """
        self._load_pipeline()
        logger.info(f"Generating {num_frames} frames for prompt: {prompt[:50]}...")

        try:
            enhanced_prompt = f"{prompt}, cinematic, high resolution, fluid motion, masterpiece."

            # Load and process image if provided
            input_image = None
            if image:
                from PIL import Image
                if isinstance(image, str) and os.path.exists(image):
                    input_image = Image.open(image).convert("RGB")
                elif isinstance(image, Image.Image):
                    input_image = image

            with torch.inference_mode():
                if self.model_type == "ltx-video":
                    video_frames = self.pipeline(
                        prompt=enhanced_prompt,
                        image=input_image,
                        num_frames=num_frames,
                        width=768,
                        height=512,
                        num_inference_steps=25,
                        guidance_scale=7.5
                    ).frames[0]
                else:
                    video_frames = self.pipeline(
                        prompt=enhanced_prompt,
                        image=input_image,
                        num_frames=num_frames,
                        width=832,
                        height=480,
                        num_inference_steps=30,
                        guidance_scale=6.0
                    ).frames[0]

            from diffusers.utils import export_to_video
            temp_video = "temp_generated_loop.mp4"
            export_to_video(video_frames, temp_video, fps=24)

            import subprocess
            from hymn_remaker import settings
            logger.info(f"Upscaling generated loop to 1080p: {output_path}")
            upscale_cmd = [
                settings.FFMPEG_BIN, "-y",
                "-i", temp_video,
                "-vf", "scale=1920:1080:force_original_aspect_ratio=increase,crop=1920:1080",
                "-c:v", "libx264", "-crf", "18", "-pix_fmt", "yuv420p",
                output_path
            ]
            subprocess.run(upscale_cmd, check=True, capture_output=True)
            if os.path.exists(temp_video):
                os.remove(temp_video)
            return output_path
        except Exception as e:
            logger.error(f"Video loop generation failed: {e}")
            return None

    def generate_beat_synced_video(self, audio_path, image_path, output_path, tempo_bpm=120.0, prompt=None, duration_sec=10.0, quotes=None):
        """
        Generates a continuous AI video loop that is upscaled and ready for composition.
        """
        loop_path = output_path.replace(".mp4", "_loop.mp4")
        active_prompt = prompt
        if quotes and len(quotes) > 0:
            active_prompt = f"{prompt}. Visual theme reflecting: '{quotes[0]['text']}'"

        res = self.generate_loop(active_prompt, loop_path, image=image_path)
        if res and os.path.exists(res):
            return res
        return None

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    gen = LocalVideoGenerator(model_type="wan", model_size="1.3b")
    # gen.generate_loop("Abstract deep house visuals", "test_loop.mp4")
