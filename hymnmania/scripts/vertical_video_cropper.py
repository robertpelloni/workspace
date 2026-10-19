"""
Vertical Video Cropper for TikTok/Shorts
==========================================
Crops 16:9 horizontal video to 9:16 vertical (1080x1920) by extracting
the center portion. Used for TikTok and YouTube Shorts distribution.

Usage:
    python vertical_video_cropper.py --input video.mp4 --output video_vertical.mp4
    python vertical_video_cropper.py --batch generated/ --outdir generated/vertical/

Output: 1080x1920 MP4, H.264+AAC, matching original duration and audio.
"""
import os
import subprocess
import argparse
import re

ROOT = os.path.dirname(os.path.abspath(__file__))
FFMPEG = os.path.join(ROOT, "..", "hymn_remaker", "bin", "ffmpeg.exe")
if not os.path.exists(FFMPEG):
    FFMPEG = "ffmpeg"


def crop_vertical(input_path, output_path, width=1080, height=1920):
    """Crop center of 16:9 video to 9:16 vertical."""
    cf = subprocess.CREATE_NO_WINDOW if hasattr(subprocess, "CREATE_NO_WINDOW") else 0
    
    try:
        probe = subprocess.run(
            [FFMPEG, "-i", input_path],
            capture_output=True, text=True, creationflags=cf
        )
        input_w, input_h = 640, 360
        for line in probe.stderr.split("\n"):
            if "Video:" in line and "x" in line:
                match = re.search(r'(\d{2,5})x(\d{2,5})', line)
                if match:
                    input_w, input_h = int(match.group(1)), int(match.group(2))
                    break
        
        crop_h = input_h
        crop_w = int(input_h * 9 / 16)
        if crop_w > input_w:
            crop_w = input_w
            crop_h = int(input_w * 16 / 9)
        x_offset = (input_w - crop_w) // 2
        y_offset = (input_h - crop_h) // 2
    except (subprocess.SubprocessError, ValueError, OSError):
        crop_w, crop_h, x_offset, y_offset = 202, 360, 219, 0
    
    vf = f"crop={crop_w}:{crop_h}:{x_offset}:{y_offset},scale={width}:{height}:flags=lanczos"
    
    cmd = [
        FFMPEG, "-y",
        "-i", input_path,
        "-vf", vf,
        "-c:v", "libx264", "-preset", "medium", "-crf", "23",
        "-c:a", "aac", "-b:a", "192k",
        "-pix_fmt", "yuv420p",
        "-movflags", "+faststart",
        output_path
    ]
    
    r = subprocess.run(cmd, capture_output=True, text=True, timeout=300, creationflags=cf)
    
    if os.path.exists(output_path) and os.path.getsize(output_path) > 10000:
        size_mb = os.path.getsize(output_path) / (1024 * 1024)
        return True, size_mb
    return False, 0


def main():
    parser = argparse.ArgumentParser(description="Crop 16:9 video to 9:16 vertical")
    parser.add_argument("--input", required=True, help="Input video file")
    parser.add_argument("--output", help="Output video file")
    parser.add_argument("--width", type=int, default=1080)
    parser.add_argument("--height", type=int, default=1920)
    args = parser.parse_args()
    
    out = args.output or args.input.replace(".mp4", "_vertical.mp4")
    print(f"Cropping: {args.input} -> {out}")
    ok, size = crop_vertical(args.input, out, args.width, args.height)
    if ok:
        print(f"OK ({size:.1f}MB)")
    else:
        print("FAILED")


if __name__ == "__main__":
    main()
