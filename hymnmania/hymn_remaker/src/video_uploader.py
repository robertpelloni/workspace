import os
import shutil
import subprocess
import logging
import json
import time
import requests
from googleapiclient.discovery import build
from googleapiclient.http import MediaFileUpload
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from google.oauth2.credentials import Credentials

from hymn_remaker import settings

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

# Scopes required for YouTube Data API
SCOPES = ["https://www.googleapis.com/auth/youtube.upload"]


class VideoProducer:
    def __init__(self, client_secrets_file=None):
        """Initialize the VideoProducer."""
        self.client_secrets_file = (
            client_secrets_file
            or os.environ.get("GOOGLE_CLIENT_SECRETS_FILE")
            or "client_secrets.json"
        )
        self.youtube = None

    def _create_srt_file(self, lyrics, srt_path):
        """Convert list of lyric dicts into a standard SRT file."""
        if not lyrics:
            return False
        try:
            with open(srt_path, 'w', encoding='utf-8') as f:
                for i, line in enumerate(lyrics):
                    start = float(line.get('start', i * 5))
                    end = float(line.get('end', start + 4))
                    text = line.get('text', '')

                    def format_time(seconds):
                        hours = int(seconds // 3600)
                        minutes = int((seconds % 3600) // 60)
                        secs = int(seconds % 60)
                        millis = int((seconds - int(seconds)) * 1000)
                        return f"{hours:02d}:{minutes:02d}:{secs:02d},{millis:03d}"

                    f.write(f"{i+1}\n")
                    f.write(f"{format_time(start)} --> {format_time(end)}\n")
                    f.write(f"{text}\n\n")

            logger.info(f"SRT file created at {srt_path}")
            return True
        except Exception as e:
            logger.error(f"Failed to create SRT: {e}")
            return False

    def create_video(self, audio_path, image_url, output_path, lyrics=None,
                     video_format="Standard 16:9", sub_font_size=24,
                     sub_primary_color="#FFFFFF", sub_outline_color="#000000",
                     sub_back_color="#000000", sub_box=True,
                     enable_visualizer=False, visualizer_mode="cline"):
        """Create an MP4 video from an audio file, image, and optional lyrics."""
        logger.info(f"Creating video from {audio_path}...")

        import uuid
        unique_id = uuid.uuid4().hex
        temp_image_path = f"temp_art_{unique_id}.png"
        temp_srt_path = f"{output_path}.srt"

        try:
            # 1. Download or copy the image
            if image_url.startswith('http://') or image_url.startswith('https://'):
                response = requests.get(image_url)
                response.raise_for_status()
                with open(temp_image_path, 'wb') as f:
                    f.write(response.content)
            else:
                if not os.path.exists(image_url):
                    raise FileNotFoundError(f"Local image file not found: {image_url}")
                shutil.copy2(image_url, temp_image_path)

            # 2. Prepare SRT if lyrics are provided
            has_subtitles = False
            if lyrics:
                has_subtitles = self._create_srt_file(lyrics, temp_srt_path)

            # Helper: escape SRT path for FFmpeg subtitles filter
            def _escape_srt_path(path):
                p = path.replace('\\', '/')
                p = p.replace(':', '\\:')
                p = p.replace("'", "\\'")
                p = p.replace(' ', '\\ ')
                return p

            # Helper: convert hex color to ASS format
            def _to_ass_color(hex_str):
                h = hex_str.lstrip('#')
                if len(h) == 6:
                    return f"&H00{h[4:6]}{h[2:4]}{h[0:2]}&"
                return "&H00FFFFFF&"

            # Helper: run ffmpeg with or without subtitles
            def _run_ffmpeg(with_subtitles):
                cmd = [
                    settings.FFMPEG_BIN,
                    "-y",
                    "-loop", "1",
                    "-i", temp_image_path,
                    "-i", audio_path,
                ]

                # Build filter_complex chain
                filter_parts = []

                # Step 1: Scale and pad the image -> [v_base]
                if video_format == "Vertical 9:16 (TikTok/Reels)":
                    scale_filter = "[0:v]scale=1080:-1,pad=1080:1920:(ow-iw)/2:(oh-ih)/2:black[v_base]"
                else:
                    scale_filter = "[0:v]scale=-1:1080,pad=1920:1080:(ow-iw)/2:(oh-ih)/2:black[v_base]"
                filter_parts.append(scale_filter)

                # Step 2: Optional visualizer overlay -> [v]
                if enable_visualizer:
                    w, h = ("1080", "150") if video_format == "Vertical 9:16 (TikTok/Reels)" else ("1920", "200")
                    y_pos = "(H-h)/2"
                    if visualizer_mode == "avectorscope":
                        filter_parts.append(f"[1:a]avectorscope=s={h}x{h}:draw=line:color=white[wave]")
                        filter_parts.append(f"[v_base][wave]overlay=x=(W-w)/2:y={y_pos}[v]")
                    else:
                        filter_parts.append(f"[1:a]showwaves=s={w}x{h}:mode={visualizer_mode}:colors=white@0.5[wave]")
                        filter_parts.append(f"[v_base][wave]overlay=x=0:y={y_pos}[v]")
                    video_label = "[v]"
                else:
                    # No visualizer: rename [v_base] -> [v] using format filter
                    filter_parts.append("[v_base]format=yuv420p[v]")
                    video_label = "[v]"

                # Step 3: Optional subtitles burned in -> [v_sub]
                if with_subtitles and has_subtitles:
                    safe_srt = _escape_srt_path(temp_srt_path)
                    p_color = _to_ass_color(sub_primary_color)
                    o_color = _to_ass_color(sub_outline_color)
                    b_color = _to_ass_color(sub_back_color)
                    border_style = "3" if sub_box else "1"
                    force_style = (f"FontSize={sub_font_size},PrimaryColour={p_color},"
                                   f"OutlineColour={o_color},BackColour={b_color},"
                                   f"BorderStyle={border_style}")
                    filter_parts.append(
                        f"[v]subtitles={safe_srt}:force_style='{force_style}'[v_sub]"
                    )
                    video_label = "[v_sub]"

                filter_complex = ";".join(filter_parts)
                cmd.extend(["-filter_complex", filter_complex])
                cmd.extend(["-map", video_label, "-map", "1:a"])
                cmd.extend([
                    "-c:v", "libx264",
                    "-preset", "medium",
                    "-c:a", "aac",
                    "-b:a", "192k",
                    "-shortest",
                    output_path
                ])

                logger.info(f"Running ffmpeg: {' '.join(cmd)}")
                result = subprocess.run(cmd, capture_output=True, text=True)
                if result.returncode != 0:
                    logger.error(f"FFmpeg stderr: {result.stderr[:500]}")
                    raise subprocess.CalledProcessError(
                        result.returncode, cmd, result.stdout, result.stderr
                    )

            # Attempt 1: With subtitles (if available)
            # Attempt 2: With sanitized subtitles (ASCII only)
            # Attempt 3: Without subtitles
            success = False
            last_error = None

            if has_subtitles:
                try:
                    _run_ffmpeg(True)
                    logger.info(f"Video created at {output_path}")
                    success = True
                except subprocess.CalledProcessError as e:
                    last_error = e
                    logger.warning("FFmpeg with subtitles failed, trying sanitized...")
                    if lyrics:
                        sanitized = []
                        for line in lyrics:
                            nl = line.copy()
                            nl['text'] = "".join(c for c in line.get('text', '') if ord(c) < 128)
                            sanitized.append(nl)
                        self._create_srt_file(sanitized, temp_srt_path)
                    try:
                        _run_ffmpeg(True)
                        logger.info(f"Video created at {output_path} (sanitized subtitles)")
                        success = True
                    except subprocess.CalledProcessError as e2:
                        last_error = e2
                        logger.warning("FFmpeg with sanitized subtitles failed, trying without...")

            if not success:
                try:
                    _run_ffmpeg(False)
                    logger.info(f"Video created at {output_path} (no subtitles)")
                    success = True
                except subprocess.CalledProcessError as e:
                    raise RuntimeError(
                        f"FFmpeg failed to create video. Last error: {e.stderr[:300] if e.stderr else str(e)}"
                    )

        except Exception as e:
            logger.error(f"Failed to create video: {e}")
            raise
        finally:
            if os.path.exists(temp_image_path):
                os.remove(temp_image_path)
            if os.path.exists(temp_srt_path):
                os.remove(temp_srt_path)

    def _get_authenticated_service(self):
        """Authenticate and return the YouTube API service."""
        creds = None
        token_path = "token.json"

        if os.path.exists(token_path):
            creds = Credentials.from_authorized_user_file(token_path, SCOPES)

        if not creds or not creds.valid:
            if creds and creds.expired and creds.refresh_token:
                creds.refresh(Request())
            else:
                if not os.path.exists(self.client_secrets_file):
                    raise FileNotFoundError(
                        f"Client secrets file not found at {self.client_secrets_file}."
                    )
                flow = InstalledAppFlow.from_client_secrets_file(
                    self.client_secrets_file, SCOPES
                )
                creds = flow.run_local_server(port=0)
                with open(token_path, "w") as token:
                    token.write(creds.to_json())

        return build("youtube", "v3", credentials=creds)

    def create_shorts(self, video_path, output_dir):
        """Extract 15-second short clips from the main video using FFmpeg."""
        shorts_dir = os.path.join(output_dir, "shorts")
        os.makedirs(shorts_dir, exist_ok=True)
        logger.info(f"Extracting 15-second shorts from {video_path} into {shorts_dir}...")

        filename = os.path.basename(video_path)
        name_no_ext = os.path.splitext(filename)[0]
        output_pattern = os.path.join(shorts_dir, f"{name_no_ext}_short_%03d.mp4")

        cmd = [
            settings.FFMPEG_BIN,
            "-y",
            "-i", video_path,
            "-f", "segment",
            "-segment_time", "15",
            "-c", "copy",
            output_pattern
        ]

        try:
            logger.info(f"Running ffmpeg: {' '.join(cmd)}")
            subprocess.run(cmd, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            logger.info(f"Shorts generated successfully in {shorts_dir}")
        except subprocess.CalledProcessError as e:
            error_msg = e.stderr.decode() if e.stderr else str(e)
            logger.error(f"FFmpeg shorts extraction failed: {error_msg}")
            raise e

    def upload_to_youtube(self, video_path, metadata, progress_callback=None):
        """Upload the video to YouTube."""
        logger.info(f"Uploading {video_path} to YouTube...")

        if not self.youtube:
            self.youtube = self._get_authenticated_service()

        body = {
            "snippet": {
                "title": metadata.get("title", "My New Song"),
                "description": metadata.get("description", "Generated by AI"),
                "tags": metadata.get("tags", []),
                "categoryId": "10"  # Music
            },
            "status": {
                "privacyStatus": "private"
            }
        }

        media = MediaFileUpload(video_path, chunksize=-1, resumable=True)
        request = self.youtube.videos().insert(
            part="snippet,status",
            body=body,
            media_body=media
        )

        response = None
        while response is None:
            status, response = request.next_chunk()
            if status:
                pct = int(status.progress() * 100)
                logger.info(f"Uploaded {pct}%")
                if progress_callback:
                    progress_callback(pct)

        logger.info(f"Upload complete! Video ID: {response['id']}")
        return response['id']
