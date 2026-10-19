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

logging.basicConfig(level=logging.INFO)
from hymn_remaker import settings
logger = logging.getLogger(__name__)

# Scopes required for YouTube Data API
SCOPES = ["https://www.googleapis.com/auth/youtube.upload"]

class VideoProducer:
    def __init__(self, client_secrets_file=None):
        """
        Initialize the VideoProducer.

        Args:
            client_secrets_file (str): Path to client_secrets.json.
                                       Defaults to GOOGLE_CLIENT_SECRETS_FILE env var or 'client_secrets.json'.
        """
        self.client_secrets_file = (
            client_secrets_file or
            os.environ.get("GOOGLE_CLIENT_SECRETS_FILE") or
            "client_secrets.json"
        )
        self.youtube = None

    def _create_srt_file(self, lyrics, srt_path):
        """Convert list of lyric dicts into a standard SRT file."""
        if not lyrics:
            return False

        try:
            with open(srt_path, 'w') as f:
                for i, line in enumerate(lyrics):
                    start = float(line.get('start', i * 5))
                    end = float(line.get('end', start + 4))
                    text = line.get('text', '')

                    # Convert seconds to SRT timestamp: HH:MM:SS,mmm
                    def format_time(seconds):
                        hours = int(seconds // 3600)
                        minutes = int((seconds % 3600) // 60)
                        secs = int(seconds % 60)
                        millis = int((seconds - int(seconds)) * 1000)
                        return f"{hours:02d}:{minutes:02d}:{secs:02d},{millis:03d}"

                    start_str = format_time(start)
                    end_str = format_time(end)

                    f.write(f"{i+1}\n")
                    f.write(f"{start_str} --> {end_str}\n")
                    f.write(f"{text}\n\n")

            logger.info(f"SRT file created at {srt_path}")
            return True
        except Exception as e:
            logger.error(f"Failed to create SRT: {e}")
            return False

    def _create_ass_file(self, lyrics, ass_path, sub_font_name="Georgia", sub_font_size=24, sub_primary_color="#FFFFFF", sub_outline_color="#000000", sub_back_color="#000000", sub_alignment=5, tempo_bpm=None):
        """Convert list of lyric dicts into a stylized Advanced Substation Alpha (ASS) file."""
        if not lyrics:
            return False

        try:
            # Helper to convert hex colors (#RRGGBB) to ASS color format (&HBBGGRR&)
            # ASS alpha channel is inverted: 00 is opaque, FF is transparent. We default to 00 (opaque)
            def to_ass_color(hex_str, opacity_hex="00"):
                h = hex_str.lstrip('#')
                if len(h) == 6:
                    return f"&H{opacity_hex}{h[4:6]}{h[2:4]}{h[0:2]}"
                return f"&H{opacity_hex}FFFFFF"

            p_color = to_ass_color(sub_primary_color)      # Opaque primary
            # For karaoke: secondary color is the "unhighlighted" color.
            # We set secondary color to a translucent gray (&H80808080) so it highlights nicely.
            s_color = "&H80808080"
            o_color = to_ass_color(sub_outline_color)      # Outline
            b_color = to_ass_color(sub_back_color, "40")   # Translucent background shadow (~25% transparency)

            with open(ass_path, 'w', encoding='utf-8') as f:
                # 1. Script Info Section
                f.write("[Script Info]\n")
                f.write("Title: Hymnmania Soulful Lyrics\n")
                f.write("ScriptType: v4.00+\n")
                f.write("WrapStyle: 0\n")
                f.write("PlayResX: 1920\n")
                f.write("PlayResY: 1080\n")
                f.write("ScaledBorderAndShadow: yes\n\n")

                # 2. Styles Section
                f.write("[V4+ Styles]\n")
                f.write("Format: Name, Fontname, Fontsize, PrimaryColour, SecondaryColour, OutlineColour, BackColour, Bold, Italic, Underline, StrikeOut, ScaleX, ScaleY, Spacing, Angle, BorderStyle, Outline, Shadow, Alignment, MarginL, MarginR, MarginV, Encoding\n")
                # Style name: LyricStyle
                # BorderStyle: 1 (Outline + Shadow)
                f.write(f"Style: LyricStyle,{sub_font_name},{sub_font_size},{p_color},{s_color},{o_color},{b_color},-1,0,0,0,100,100,0,0,1,2,1,{sub_alignment},10,10,20,1\n\n")

                # 3. Events Section
                f.write("[Events]\n")
                f.write("Format: Layer, Start, End, Style, Name, MarginL, MarginR, MarginV, Effect, Text\n")

                # Format time as H:MM:SS.cs (hours:minutes:seconds.centiseconds)
                def format_ass_time(seconds):
                    hours = int(seconds // 3600)
                    minutes = int((seconds % 3600) // 60)
                    secs = int(seconds % 60)
                    centiseconds = int(round((seconds - int(seconds)) * 100))
                    if centiseconds == 100:
                        secs += 1
                        centiseconds = 0
                    return f"{hours}:{minutes:02d}:{secs:02d}.{centiseconds:02d}"

                for line in lyrics:
                    start = float(line.get('start', 0))
                    end = float(line.get('end', start + 4))
                    text = line.get('text', '')

                    start_str = format_ass_time(start)
                    end_str = format_ass_time(end)

                    # Dynamic Effects:
                    # - Add a subtle fade-in and fade-out transition: {\fad(300,300)}
                    # - If tempo is provided, we can add karaoke-style highlighting to the text!
                    # For karaoke, we can split text into words and highlight them matching the beats.
                    effect_prefix = "{\\fad(300,300)}"

                    if tempo_bpm and " " in text:
                        words = text.split()
                        num_words = len(words)
                        duration_cs = int((end - start) * 100)
                        word_duration_cs = max(1, duration_cs // num_words)

                        # Form karaoke string: {\kf25}Word1 {\kf30}Word2 ...
                        # AND add a pulsing pulse effect to the whole line!
                        # We add multiple \t tags to scale up and down on every beat.
                        beat_len_sec = 60.0 / tempo_bpm
                        beat_len_cs = int(beat_len_sec * 100)

                        pulse_tags = ""
                        curr_cs = 0
                        while curr_cs < duration_cs:
                            # Scale UP at start of beat (105%)
                            pulse_tags += f"{{\\t({curr_cs},{curr_cs+50},\\fscx105\\fscy105)}}"
                            # Scale DOWN shortly after (100%)
                            pulse_tags += f"{{\\t({curr_cs+50},{curr_cs+150},\\fscx100\\fscy100)}}"
                            curr_cs += beat_len_cs

                        karaoke_parts = []
                        for word in words:
                            karaoke_parts.append(f"{{\\kf{word_duration_cs}}}{word}")

                        formatted_text = f"{effect_prefix}{pulse_tags}" + " ".join(karaoke_parts)
                    else:
                        formatted_text = f"{effect_prefix}{text}"

                    f.write(f"Dialogue: 0,{start_str},{end_str},LyricStyle,,0,0,0,,{formatted_text}\n")

            logger.info(f"ASS subtitle file created at {ass_path}")
            return True
        except Exception as e:
            logger.error(f"Failed to create ASS subtitle file: {e}")
            return False

    def create_video(self, audio_path, image_url, output_path, lyrics=None, video_format="Standard 16:9", sub_font_size=24, sub_primary_color="#FFFFFF", sub_outline_color="#000000", sub_back_color="#000000", sub_box=True, enable_visualizer=False, visualizer_mode="cline", sub_alignment=2, sub_font_name="Arial", tempo_bpm=None):
        """
        Create an MP4 video from an audio file, image URL, and optional lyrics using ffmpeg.

        Args:
            audio_path (str): Path to the input audio file.
            image_url (str): URL of the album art image.
            output_path (str): Path to the output video file.
            lyrics (list): Optional list of synced lyrics dicts.
            video_format (str): The aspect ratio of the output video.
            sub_alignment (int): ASS subtitle alignment (e.g. 2 for bottom-center, 5 for middle-center).
            sub_font_name (str): Font name to use for subtitles.
            tempo_bpm (float): Tempo of the track in BPM for beat-synchronized visual pulsing.
        """
        logger.info(f"Creating video from {audio_path}...")

        import uuid
        unique_id = uuid.uuid4().hex
        temp_image_path = f"temp_art_{unique_id}.png"
        temp_subtitle_path = f"{output_path}.ass"
        # 1. Prepare Background (Image, URL, or Color)
        is_temp_image = False
        try:
            if isinstance(image_url, str) and image_url.lower() in ["black", "white", "blue", "red", "green"]:
                # Use solid color fallback via lavfi - we'll handle this in the ffmpeg command below
                temp_image_path = None
                logger.info(f"Using solid color background: {image_url}")
            elif image_url.startswith('http://') or image_url.startswith('https://'):
                response = requests.get(image_url)
                response.raise_for_status()
                with open(temp_image_path, 'wb') as f:
                    f.write(response.content)
                is_temp_image = True
            elif image_url.endswith(".mp4"):
                # Background is already a video
                temp_image_path = image_url
            else:
                # Assume it's a local file path
                if not os.path.exists(image_url):
                    raise FileNotFoundError(f"Local image file not found: {image_url}")
                shutil.copy2(image_url, temp_image_path)
                is_temp_image = True

            # 2. Prepare ASS Subtitles if lyrics are provided
            has_subtitles = False
            if lyrics:
                has_subtitles = self._create_ass_file(
                    lyrics, temp_subtitle_path,
                    sub_font_name=sub_font_name, sub_font_size=sub_font_size,
                    sub_primary_color=sub_primary_color, sub_outline_color=sub_outline_color,
                    sub_back_color=sub_back_color, sub_alignment=sub_alignment,
                    tempo_bpm=tempo_bpm
                )

            # 3. Use ffmpeg to combine background and audio
            base_cmd = [settings.FFMPEG_BIN, "-y"]

            if temp_image_path is None:
                # Solid color mode (lavfi color source doesn't use -loop)
                color_name = image_url.lower()
                base_cmd.extend(["-f", "lavfi", "-i", f"color=c={color_name}:s=1920x1080"])
            elif temp_image_path.lower().endswith(('.mp4', '.avi', '.mov', '.mkv')):
                # Loop video input infinitely using -stream_loop
                base_cmd.extend(["-stream_loop", "-1", "-i", temp_image_path])
            else:
                base_cmd.extend(["-loop", "1", "-i", temp_image_path])

            base_cmd.extend(["-i", audio_path])

            # Helper to execute ffmpeg
            def run_ffmpeg(subtitles_enabled):
                ffmpeg_cmd = base_cmd.copy()

                # Determine base filters depending on format
                base_vf = ""
                target_w, target_h = (1080, 1920) if video_format == "Vertical 9:16 (TikTok/Reels)" else (1920, 1080)

                if video_format == "Vertical 9:16 (TikTok/Reels)":
                    # Scale to 1080 width, then pad to 1080x1920, ensuring even dimensions
                    base_vf = f"[0:v]scale=1080:trunc(1080/a/2)*2,pad={target_w}:{target_h}:(ow-iw)/2:(oh-ih)/2:black[v_base]"
                else:
                    # Standard 16:9, scale to 1080 height, then pad to 1920x1080, ensuring even dimensions
                    base_vf = f"[0:v]scale=trunc(1080*a/2)*2:1080,pad={target_w}:{target_h}:(ow-iw)/2:(oh-ih)/2:black[v_base]"

                # Build filter complex
                filters = [base_vf]

                # Add Audio-Reactive Visualizer
                if enable_visualizer:
                    w_viz, h_viz = (1080, 150) if video_format == "Vertical 9:16 (TikTok/Reels)" else (1920, 200)
                    y_pos = "(H-h)/2" # Center vertically

                    if visualizer_mode == "kaleidoscope":
                        # Kaleidoscope: Split video into quadrants, flip and tile
                        # 1. Take top-left corner (960x540)
                        # 2. Duplicate and flip for symmetry
                        kaleido = (
                            f"[v_base]crop=iw/2:ih/2:0:0,split=4[q1][q2][q3][q4];"
                            f"[q2]hflip[q2h];[q3]vflip[q3v];[q4]hflip,vflip[q4hv];"
                            f"[q1][q2h]hstack[top];[q3v][q4hv]hstack[bottom];[top][bottom]vstack[v_kaleido];"
                            f"[1:a]showwaves=s={target_w}x{h_viz}:mode=cline:colors=white@0.4[wave];"
                            f"[v_kaleido][wave]overlay=x=0:y={y_pos}:format=yuv420[v_pre]"
                        )
                        filters.append(kaleido)
                    elif visualizer_mode == "avectorscope":
                        vis_filter = f"[1:a]avectorscope=s={h_viz}x{h_viz}:draw=line:color=white[wave];[v_base][wave]overlay=x=(W-w)/2:y={y_pos}:format=yuv420[v_pre]"
                        filters.append(vis_filter)
                    else:
                        vis_filter = f"[1:a]showwaves=s={w_viz}x{h_viz}:mode={visualizer_mode}:colors=white@0.5[wave];[v_base][wave]overlay=x=0:y={y_pos}:format=yuv420[v_pre]"
                        filters.append(vis_filter)

                    # Ensure the overlay result is exactly the target size
                    filters.append(f"[v_pre]scale={target_w}:{target_h}[v]")
                else:
                    # Just pass the base video through
                    filters.append("[v_base]null[v]")  # pass through without copy

                # Apply Beat-Synchronized Visual Pulsing (Brightness/Contrast) if tempo is provided
                if tempo_bpm and float(tempo_bpm) > 0:
                    bpm = float(tempo_bpm)
                    beat_len = 60.0 / bpm
                    bar_len = beat_len * 4.0
                    # Brightness and contrast formula that spikes at start of beat and decays
                    # Brightness max +0.05, Contrast max +0.06 (both double on downbeats)
                    pulse_expr = (
                        f"[v]eq="
                        f"brightness='0.05*exp(-15.0*mod(t,{beat_len}))+0.05*exp(-6.0*mod(t,{bar_len}))':"
                        f"contrast='1.0+0.06*exp(-15.0*mod(t,{beat_len}))+0.06*exp(-6.0*mod(t,{bar_len}))':"
                        f"eval=frame[v_pulsed]"
                    )

                    filters.append(pulse_expr)
                    video_stream_name = "[v_pulsed]"
                else:
                    video_stream_name = "[v]"

                if subtitles_enabled:
                    safe_subtitle_path = temp_subtitle_path.replace('\\', '/').replace(':', '\\:')
                    filters.append(f"{video_stream_name}subtitles={safe_subtitle_path}[v_sub]")
                    ffmpeg_cmd.extend(["-filter_complex", ";".join(filters), "-map", "[v_sub]", "-map", "1:a"])
                else:
                    ffmpeg_cmd.extend(["-filter_complex", ";".join(filters), "-map", video_stream_name, "-map", "1:a"])

                ffmpeg_cmd.extend([
                    "-c:v", "libx264",
                    "-c:a", "aac",
                    "-b:a", "192k",
                    "-pix_fmt", "yuv420p",
                    "-shortest",
                    output_path
                ])
                logger.info(f"Running ffmpeg: {' '.join(ffmpeg_cmd)}")
                subprocess.run(ffmpeg_cmd, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

            max_retries = 3
            success = False
            for attempt in range(max_retries):
                try:
                    # Try with subtitles first if they exist
                    run_ffmpeg(has_subtitles)
                    logger.info(f"Video created at {output_path}")
                    success = True
                    break
                except subprocess.CalledProcessError as e:
                    error_msg = e.stderr.decode()
                    logger.error(f"FFmpeg failed on attempt {attempt + 1}: {error_msg}")
                    if has_subtitles and attempt < max_retries - 1:
                        logger.warning("Sanitizing lyrics and retrying...")
                        # Basic sanitization: strip non-ascii
                        sanitized_lyrics = []
                        for line in lyrics:
                            new_line = line.copy()
                            new_line['text'] = "".join([c for c in line.get('text', '') if ord(c) < 128])
                            sanitized_lyrics.append(new_line)
                        self._create_ass_file(
                            sanitized_lyrics, temp_subtitle_path,
                            sub_font_name=sub_font_name, sub_font_size=sub_font_size,
                            sub_primary_color=sub_primary_color, sub_outline_color=sub_outline_color,
                            sub_back_color=sub_back_color, sub_alignment=sub_alignment,
                            tempo_bpm=tempo_bpm
                        )
                    else:
                        break

            if not success:
                if has_subtitles:
                    logger.warning("All subtitle retries failed. Retrying WITHOUT subtitles...")
                    run_ffmpeg(False)
                    logger.info(f"Video created at {output_path} (without subtitles fallback)")
                else:
                    raise RuntimeError("FFmpeg failed to create video after all retries.")

        except Exception as e:
            logger.error(f"Failed to create video: {e}")
            raise
        finally:
            if is_temp_image and temp_image_path and os.path.exists(temp_image_path):
                os.remove(temp_image_path)
            if os.path.exists(temp_subtitle_path):
                os.remove(temp_subtitle_path)

    def _get_authenticated_service(self):
        """Authenticate and return the YouTube API service."""
        creds = None
        # The file token.json stores the user's access and refresh tokens, and is
        # created automatically when the authorization flow completes for the first
        # time.
        token_path = "token.json"
        if os.path.exists(token_path):
            creds = Credentials.from_authorized_user_file(token_path, SCOPES)

        # If there are no (valid) credentials available, let the user log in.
        if not creds or not creds.valid:
            if creds and creds.expired and creds.refresh_token:
                creds.refresh(Request())
            else:
                if not os.path.exists(self.client_secrets_file):
                     raise FileNotFoundError(f"Client secrets file not found at {self.client_secrets_file}. Cannot authenticate.")

                flow = InstalledAppFlow.from_client_secrets_file(
                    self.client_secrets_file, SCOPES
                )
                creds = flow.run_local_server(port=0)

            # Save the credentials for the next run
            with open(token_path, "w") as token:
                token.write(creds.to_json())

        return build("youtube", "v3", credentials=creds)

    def create_shorts(self, video_path, output_dir):
        """
        Extract 15-second short clips from the main video using FFmpeg.

        Args:
            video_path (str): Path to the main output video.
            output_dir (str): Base output directory.
        """
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
            error_msg = e.stderr.decode()
            logger.error(f"FFmpeg shorts extraction failed: {error_msg}")
            raise e

    def upload_to_youtube(self, video_path, metadata, progress_callback=None):
        """
        Upload the video to YouTube.

        Args:
            video_path (str): Path to the video file.
            metadata (dict): Metadata dictionary (title, description, tags).
            progress_callback (callable): Optional callback function for upload progress (takes integer 0-100).

        Returns:
            str: ID of the uploaded video.
        """
        logger.info(f"Uploading {video_path} to YouTube...")

        if not self.youtube:
            self.youtube = self._get_authenticated_service()

        body = {
            "snippet": {
                "title": metadata.get("title", "My New Song"),
                "description": metadata.get("description", "Generated by AI"),
                "tags": metadata.get("tags", []),
                "categoryId": "10" # Music
            },
            "status": {
                "privacyStatus": "private" # Default to private for safety
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

if __name__ == "__main__":
    # Test video creation (requires dummy audio)
    producer = VideoProducer()

    # We need a dummy audio file for testing video creation
    test_audio = "hymn_remaker/output/test_hymn.wav" # created in step 2

    # Check if we have internet access or need to use a local file for testing
    test_image_url = "https://via.placeholder.com/1024.png"

    # For testing in an environment without internet/dummy purposes, we can write a local file
    # and bypass the download step if the URL is "file://..." or just handle it in the test block
    # But to keep the class clean, let's just mock the download if it's a local file path

    test_output = "hymn_remaker/output/test_video.mp4"

    if os.path.exists(test_audio):
        try:
            producer.create_video(test_audio, test_image_url, test_output)
        except Exception as e:
            logger.warning(f"Standard test failed (likely network): {e}")
            logger.info("Attempting local test...")
            # Create a dummy image
            from PIL import Image
            local_img = "hymn_remaker/output/test_art.png"
            Image.new('RGB', (1024, 1024), color='red').save(local_img)

            # Monkey patch requests.get to return file content
            class MockResponse:
                def __init__(self, content):
                    self.content = content
                def raise_for_status(self):
                    pass

            original_get = requests.get
            def mock_get(url):
                if url == "local_test_url":
                    with open(local_img, "rb") as f:
                        return MockResponse(f.read())
                return original_get(url)

            requests.get = mock_get
            producer.create_video(test_audio, "local_test_url", test_output)
            requests.get = original_get

    else:
        print(f"Test audio {test_audio} not found. Run step 2 first.")
