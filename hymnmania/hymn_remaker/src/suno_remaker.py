"""
Suno AI Music Remaker — High-level orchestration facade.

Re-exports the decomposed sub-modules:
    - suno_api:    HTTP client, auth, polling, download
    - suno_browser: Playwright browser automation & Turnstile harvesting

This module provides the ``SunoRemaker`` class that the pipeline imports,
preserving full backward compatibility with ``main.py`` and ``app.py``.
"""

import os
import glob
import time
import subprocess
import logging
from pathlib import Path

from hymn_remaker import settings
from hymn_remaker.src.suno_api import SunoAPIClient
from hymn_remaker.src import suno_browser
from hymn_remaker.src.suno_browser_automation import SunoBrowserAutomation

logger = logging.getLogger(__name__)


class SunoRemaker:
    """Generate Deep House remixes of hymn audio using Suno AI.

    Supports two modes:
        - API mode:   Direct HTTP requests with Turnstile token
        - Browser mode: CDP automation of the Suno web UI in Edge
    """

    def __init__(self, session_token=None, client_token=None, model_version=None):
        self.api = SunoAPIClient(
            session_token=session_token,
            client_token=client_token,
            model_version=model_version,
        )
        # Backward-compatible property access
        self.session_token = self.api.session_token
        self.client_token = self.api.client_token
        self.model_version = self.api.model_version
        self.browser_automation = SunoBrowserAutomation()

    def is_available(self):
        """Check if Suno API or Browser Automation is configured."""
        # Try API check first
        if self.api.is_available():
            return True

        # Fallback: check if Edge is listening on 9222 for browser automation
        try:
            import socket

            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.settimeout(1)
            result = sock.connect_ex(("127.0.0.1", 9222))
            sock.close()
            if result == 0:
                logger.info(
                    "SunoRemaker: API not available, but Edge debugging port 9222 is open. Enabling browser mode."
                )
                return True
        except Exception:
            pass

        return False

    def check_captcha(self):
        """Check if CAPTCHA is required for generation."""
        return self.api.check_captcha()

    def get_session_info(self):
        """Get current session info from Suno API."""
        return self.api.get_session_info()

    def get_feed(self, page=1):
        """Get user's song feed."""
        return self.api.get_feed(page)

    def get_turnstile_token(self, timeout=30):
        """Obtain a Cloudflare Turnstile token using Playwright."""
        return suno_browser.get_turnstile_token(
            session_token=self.session_token,
            client_token=self.client_token,
            timeout=timeout,
        )

    def remake(
        self,
        wav_path,
        prompt,
        duration=30,
        make_instrumental=True,
        tags="deep house, electronic, club",
        keep_mp3=False,
        mode="auto",
        turnstile_token=None,
        lyrics=None,
    ):
        """Generate a Deep House remake of a hymn using Suno AI."""
        if not os.path.exists(wav_path):
            raise FileNotFoundError(f"Input WAV not found: {wav_path}")

        hymn_name = Path(wav_path).stem.replace("_base", "")
        logger.info(f"=== Suno Remake: {hymn_name} ===")

        full_prompt = (
            f"Create a {prompt} version inspired by this hymn melody. "
            f"Transform it into a club-ready deep house track with "
            f"four-on-the-floor kick, deep bass, atmospheric pads, "
            f"and subtle references to the original hymn's melody."
        )

        clips = None

        # Try API mode first if session token is available
        if mode in ("auto", "api") and self.session_token:
            try:
                # 1. Upload audio influence first in API mode
                audio_influence_id = None
                if os.path.exists(wav_path):
                    # Prefer MP3 for upload efficiency if it exists
                    mp3_path = wav_path.rsplit("_base.wav", 1)[0] + "_base.mp3"
                    upload_path = mp3_path if os.path.exists(mp3_path) else wav_path

                    logger.info(
                        f"Uploading audio influence for API mode: {os.path.basename(upload_path)}"
                    )
                    # Use the api client's upload method
                    upload_result = self.api.upload_audio(upload_path)
                    if upload_result:
                        audio_influence_id = upload_result.get("id")
                        logger.info(f"Audio influence ID: {audio_influence_id}")

                # 2. Get Turnstile token if not provided
                if not turnstile_token:
                    captcha = self.check_captcha()
                    if captcha.get("required"):
                        logger.info("CAPTCHA required, obtaining Turnstile token...")
                        turnstile_token = self.get_turnstile_token()

                # 3. Submit generation with influence
                clips = self.api.generate_songs(
                    prompt=full_prompt,
                    turnstile_token=turnstile_token,
                    make_instrumental=make_instrumental,
                    tags=tags,
                    title=f"{hymn_name} (Deep House Remix)",
                    audio_influence_id=audio_influence_id,
                    audio_influence_weight=0.8,  # Force strict melody retention
                )
            except Exception as e:
                logger.warning(f"API mode failed: {e}")
                if mode == "auto":
                    logger.info("Falling back to browser mode...")
                else:
                    raise

        # Fall back to browser mode (CDP)
        if clips is None and mode in ("auto", "browser"):
            logger.info("Triggering Suno Browser Automation (CDP)...")
            # Prepare audio influence path (prefer MP3, fall back to WAV)
            audio_influence = None
            mp3_path = wav_path.rsplit("_base.wav", 1)[0] + "_base.mp3"
            if os.path.exists(mp3_path):
                audio_influence = mp3_path
            elif os.path.exists(wav_path):
                audio_influence = wav_path

            try:
                success = self.browser_automation.trigger_generation(
                    prompt=full_prompt,
                    audio_path=audio_influence,
                    make_instrumental=make_instrumental,
                    lyrics=lyrics,
                )
                if success:
                    logger.info(
                        "Suno: Browser automation triggered generation. Waiting for completion..."
                    )
                    if self.browser_automation.wait_for_completion_and_download():
                        # We don't have clip IDs from browser mode easily, but we can poll the feed via API
                        # to find the latest completed clips for this user.
                        time.sleep(10)
                        logger.info("Suno: Polling user feed for the new clips...")
                        feed = self.api.get_feed()
                        # Take the top 2 clips (Suno generates in pairs)
                        if feed:
                            clips = feed[:2]
                            logger.info(f"Suno: Found {len(clips)} new clips in feed.")
            except Exception as be:
                logger.error(f"Suno Browser Automation failed: {be}")

        if not clips:
            raise RuntimeError("No clips generated (Suno)")

        # Poll for completion
        clip_ids = [clip.get("id") for clip in clips if clip.get("id")]
        if not clip_ids:
            raise RuntimeError("Suno returned no clip IDs")

        completed_clips = self.api.poll_songs(clip_ids)

        # Filter out errored clips
        valid_clips = [
            c
            for c in completed_clips
            if c.get("status") not in ("error", "failed") and c.get("audio_url")
        ]
        if not valid_clips:
            raise RuntimeError("All Suno clips failed or have no audio_url")

        # Select best clip and download
        best_clip = self.api.select_best_clip(valid_clips)
        remake_wav = wav_path.rsplit("_base.wav", 1)[0] + "_remake.wav"
        self.api.download_audio(best_clip, remake_wav)

        logger.info(f"=== Suno Remake Complete: {remake_wav} ===")
        return remake_wav

    def batch_wav_to_mp3(self, output_dir, bitrate="192k"):
        """Convert all base WAV files in the output directory to MP3."""
        wav_files = glob.glob(os.path.join(output_dir, "*_base.wav"))
        logger.info(f"Found {len(wav_files)} base WAV files to convert to MP3")

        converted = 0
        failed = 0

        for wav_path in sorted(wav_files):
            mp3_path = wav_path.rsplit("_base.wav", 1)[0] + "_base.mp3"
            if os.path.exists(mp3_path):
                converted += 1
                continue
            try:
                self._wav_to_mp3(wav_path, mp3_path, bitrate=bitrate)
                converted += 1
            except Exception as e:
                logger.error(f"  FAILED: {os.path.basename(wav_path)}: {e}")
                failed += 1

        return converted, failed

    def _wav_to_mp3(self, wav_path, mp3_path=None, bitrate="192k"):
        """Convert a WAV file to MP3 using ffmpeg."""
        if not os.path.exists(wav_path):
            raise FileNotFoundError(f"WAV file not found: {wav_path}")
        if mp3_path is None:
            mp3_path = wav_path.rsplit(".", 1)[0] + ".mp3"

        cmd = [
            settings.FFMPEG_BIN,
            "-y",
            "-i",
            wav_path,
            "-codec:a",
            "libmp3lame",
            "-b:a",
            bitrate,
            mp3_path,
        ]
        subprocess.run(cmd, capture_output=True, text=True, timeout=60)
        return mp3_path
