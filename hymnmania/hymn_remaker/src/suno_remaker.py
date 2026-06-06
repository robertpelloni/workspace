"""
Suno AI Music Remaker - Deep House generation with audio influence.

Uses the Suno AI API (studio-api.suno.ai) to generate Deep House remixes
of hymn MIDI renders by uploading the original as "audio influence" data.

Authentication:
    Requires a SUNO_SESSION_TOKEN obtained from suno.com browser cookies.
    1. Go to https://suno.com in your browser
    2. Open DevTools > Application > Cookies > suno.com
    3. Copy the session token value
    4. Set SUNO_SESSION_TOKEN in .env or environment

Audio Influence:
    Suno v4 supports uploading audio as influence/reference material.
    The hymn's base WAV is converted to MP3 (via ffmpeg), base64-encoded,
    and sent as input_audio in the generate request.

Workflow:
    1. Convert base WAV to MP3 (ffmpeg)
    2. Base64 encode the MP3
    3. POST /api/generate/v2/ with audio influence + Deep House prompt
    4. Poll /api/get/?ids=... until songs are complete
    5. Download the best generated audio
    6. Save as remake WAV
"""

import os
import sys
import time
import json
import base64
import logging
import subprocess
import tempfile
import shutil
import requests
from pathlib import Path

from hymn_remaker import settings
from hymn_remaker.src.utils import retry_request

logger = logging.getLogger(__name__)

# Suno API endpoints
SUNO_BASE_URL = "https://studio-api.suno.ai"
GENERATE_URL = f"{SUNO_BASE_URL}/api/generate/v2/"
GET_SONG_URL = f"{SUNO_BASE_URL}/api/get/"
CLIP_URL = f"{SUNO_BASE_URL}/api/clip/"

# Default model version
DEFAULT_MODEL_VERSION = "chirp-v4"

# Polling settings
POLL_INTERVAL = 5        # seconds between status checks
POLL_TIMEOUT = 300       # max seconds to wait for generation (5 min)
MAX_RETRIES = 3


class SunoRemaker:
    """
    Generate Deep House remixes of hymn audio using Suno AI.

    Uses Suno's audio influence feature to take the original hymn
    as reference material and create a Deep House version.
    """

    def __init__(self, session_token=None, model_version=None):
        """
        Initialize the Suno Remaker.

        Args:
            session_token (str): Suno session token from browser cookies.
                                 Defaults to SUNO_SESSION_TOKEN env var.
            model_version (str): Suno model version. Defaults to chirp-v4.
        """
        self.session_token = session_token or os.environ.get("SUNO_SESSION_TOKEN", "")
        self.model_version = model_version or os.environ.get("SUNO_MODEL_VERSION", DEFAULT_MODEL_VERSION)
        self.base_url = os.environ.get("SUNO_BASE_URL", SUNO_BASE_URL)

        if not self.session_token:
            logger.warning("SUNO_SESSION_TOKEN not set. SunoRemaker will not function.")
            logger.warning("Get your token from suno.com browser cookies (DevTools > Application > Cookies)")
        else:
            logger.info(f"SunoRemaker initialized with model {self.model_version}")

        # FFmpeg path from settings
        self.ffmpeg_bin = settings.FFMPEG_BIN

    def is_available(self):
        """Check if Suno API is configured and available."""
        if not self.session_token:
            return False
        return True

    def _get_headers(self):
        """Build request headers with auth token."""
        return {
            "Accept": "*/*",
            "Accept-Language": "en-US,en;q=0.9",
            "Authorization": f"Bearer {self.session_token}",
            "Content-Type": "application/json",
            "Origin": "https://suno.com",
            "Referer": "https://suno.com/",
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/131.0.0.0 Safari/537.36",
            "sec-ch-ua": '"Google Chrome";v="131", "Chromium";v="131", "Not_A Brand";v="24"',
            "sec-ch-ua-mobile": "?0",
            "sec-ch-ua-platform": '"Windows"',
            "sec-fetch-dest": "empty",
            "sec-fetch-mode": "cors",
            "sec-fetch-site": "cross-site",
        }

    def _wav_to_mp3(self, wav_path, mp3_path=None, bitrate="192k"):
        """
        Convert a WAV file to MP3 using ffmpeg.

        Args:
            wav_path (str): Path to input WAV file.
            mp3_path (str): Path for output MP3. If None, creates temp file.
            bitrate (str): MP3 bitrate (default 192k).

        Returns:
            str: Path to the generated MP3 file.

        Raises:
            RuntimeError: If ffmpeg conversion fails.
        """
        if not os.path.exists(wav_path):
            raise FileNotFoundError(f"WAV file not found: {wav_path}")

        if mp3_path is None:
            mp3_path = wav_path.rsplit(".", 1)[0] + ".mp3"

        # Get file size for logging
        wav_size_mb = os.path.getsize(wav_path) / (1024 * 1024)
        logger.info(f"Converting {wav_path} ({wav_size_mb:.1f}MB WAV) to MP3 @ {bitrate}...")

        cmd = [
            self.ffmpeg_bin,
            "-y",                    # overwrite output
            "-i", wav_path,          # input
            "-codec:a", "libmp3lame",
            "-b:a", bitrate,
            "-joint_stereo", "1",
            mp3_path
        ]

        try:
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=60,
                creationflags=subprocess.CREATE_NO_WINDOW if os.name == "nt" else 0
            )
            if result.returncode != 0:
                raise RuntimeError(f"ffmpeg failed: {result.stderr[-500:]}")

            mp3_size_mb = os.path.getsize(mp3_path) / (1024 * 1024)
            logger.info(f"MP3 created: {mp3_path} ({mp3_size_mb:.1f}MB)")
            return mp3_path

        except subprocess.TimeoutExpired:
            raise RuntimeError(f"ffmpeg timed out converting {wav_path}")
        except FileNotFoundError:
            raise RuntimeError(f"ffmpeg not found at {self.ffmpeg_bin}")

    def _mp3_to_base64(self, mp3_path):
        """
        Read an MP3 file and return its base64-encoded content.

        Args:
            mp3_path (str): Path to MP3 file.

        Returns:
            str: Base64-encoded MP3 data (no prefix).
        """
        with open(mp3_path, "rb") as f:
            data = f.read()
        encoded = base64.b64encode(data).decode("utf-8")
        logger.info(f"Base64 encoded MP3: {len(encoded)} chars from {len(data)} bytes")
        return encoded

    def _build_audio_influence(self, mp3_base64, source_name="hymn"):
        """
        Build the audio influence payload for the Suno API.

        The Suno v4 API accepts audio influence via the 'input_audio' field.
        This contains the base64 MP3 data and metadata.

        Args:
            mp3_base64 (str): Base64-encoded MP3 audio data.
            source_name (str): Name/label for the audio source.

        Returns:
            dict: Audio influence payload.
        """
        return {
            "audio_source": "file",
            "file": mp3_base64,
            "source_name": source_name,
        }

    @retry_request(max_retries=2, delay=3, backoff=2)
    def _generate_songs(self, prompt, audio_influence=None, make_instrumental=True,
                         tags=None, title=None):
        """
        Submit a song generation request to Suno.

        Args:
            prompt (str): Text description of the song to generate.
            audio_influence (dict): Audio influence payload (from _build_audio_influence).
            make_instrumental (bool): Whether to generate instrumental only.
            tags (str): Genre tags (e.g., "deep house, electronic").
            title (str): Song title.

        Returns:
            list: List of clip dictionaries from the API response.

        Raises:
            RuntimeError: If the API request fails.
        """
        if not self.session_token:
            raise RuntimeError("SUNO_SESSION_TOKEN not configured")

        # Build the generation payload
        payload = {
            "gpt_description_prompt": prompt,
            "mv": self.model_version,
            "make_instrumental": make_instrumental,
        }

        # Add audio influence if provided
        if audio_influence:
            payload["input_audio"] = audio_influence

        # Add optional fields
        if tags:
            payload["tags"] = tags
        if title:
            payload["title"] = title

        logger.info(f"Submitting Suno generation request...")
        logger.info(f"  Prompt: {prompt[:100]}...")
        logger.info(f"  Model: {self.model_version}")
        logger.info(f"  Audio influence: {'Yes' if audio_influence else 'No'}")
        logger.info(f"  Instrumental: {make_instrumental}")

        headers = self._get_headers()

        try:
            response = requests.post(
                f"{self.base_url}/api/generate/v2/",
                json=payload,
                headers=headers,
                timeout=30
            )

            if response.status_code == 401:
                raise RuntimeError("SUNO_SESSION_TOKEN is invalid or expired. Get a new one from suno.com")
            if response.status_code == 402:
                raise RuntimeError("Suno credits exhausted. Wait for daily reset or upgrade plan.")
            if response.status_code == 429:
                raise RuntimeError("Suno rate limit hit. Waiting before retry.")
            if response.status_code == 503:
                raise RuntimeError("Suno API is temporarily unavailable (503). Try again later.")
            if response.status_code != 200:
                raise RuntimeError(f"Suno API error {response.status_code}: {response.text[:300]}")

            clips = response.json()
            if isinstance(clips, dict) and "clips" in clips:
                clips = clips["clips"]

            logger.info(f"Suno generation submitted: {len(clips)} clip(s)")
            for clip in clips:
                clip_id = clip.get("id", "unknown")
                logger.info(f"  Clip ID: {clip_id}")

            return clips

        except requests.exceptions.ConnectionError as e:
            raise RuntimeError(f"Cannot connect to Suno API: {e}")
        except requests.exceptions.Timeout:
            raise RuntimeError("Suno API request timed out")

    @retry_request(max_retries=2, delay=3, backoff=2)
    def _poll_songs(self, clip_ids):
        """
        Poll Suno API until songs are complete.

        Suno generates 2 clips per request. We poll until both are done,
        then return the one with the best quality score.

        Args:
            clip_ids (list): List of clip IDs to poll.

        Returns:
            list: List of completed clip dictionaries.

        Raises:
            RuntimeError: If polling times out.
        """
        if not clip_ids:
            raise RuntimeError("No clip IDs to poll")

        ids_param = ",".join(clip_ids)
        headers = self._get_headers()
        start_time = time.time()

        logger.info(f"Polling Suno for {len(clip_ids)} clip(s)...")

        while True:
            elapsed = time.time() - start_time
            if elapsed > POLL_TIMEOUT:
                raise RuntimeError(f"Suno generation timed out after {POLL_TIMEOUT}s")

            try:
                response = requests.get(
                    f"{self.base_url}/api/get/?ids={ids_param}",
                    headers=headers,
                    timeout=15
                )

                if response.status_code != 200:
                    logger.warning(f"Suno poll returned {response.status_code}, retrying...")
                    time.sleep(POLL_INTERVAL)
                    continue

                clips = response.json()
                if isinstance(clips, list):
                    all_done = all(
                        clip.get("status") in ("complete", "completed")
                        for clip in clips
                    )
                else:
                    all_done = False

                if all_done:
                    logger.info(f"All clips complete after {elapsed:.0f}s")
                    return clips

                # Log progress
                for clip in clips if isinstance(clips, list) else []:
                    status = clip.get("status", "unknown")
                    clip_id = clip.get("id", "?")
                    if status == "error":
                        error_msg = clip.get("error_message", "unknown error")
                        logger.error(f"  Clip {clip_id} failed: {error_msg}")
                    elif status not in ("complete", "completed"):
                        logger.info(f"  Clip {clip_id}: {status}...")

            except requests.exceptions.RequestException as e:
                logger.warning(f"Poll request failed: {e}")

            time.sleep(POLL_INTERVAL)

    def _download_audio(self, clip, output_path):
        """
        Download the generated audio from a completed Suno clip.

        Suno provides audio_url (MP3) and video_url (MP4 with visuals).
        We download the MP3 and convert to WAV for pipeline compatibility.

        Args:
            clip (dict): Completed clip dictionary from Suno.
            output_path (str): Path to save the output WAV file.

        Returns:
            str: Path to the downloaded WAV file.

        Raises:
            RuntimeError: If download fails.
        """
        audio_url = clip.get("audio_url")
        if not audio_url:
            raise RuntimeError("Clip has no audio_url")

        logger.info(f"Downloading Suno audio from {audio_url[:80]}...")

        try:
            response = requests.get(audio_url, timeout=60, stream=True)
            response.raise_for_status()

            # Save as MP3 first
            mp3_path = output_path.rsplit(".", 1)[0] + "_suno.mp3"
            with open(mp3_path, "wb") as f:
                for chunk in response.iter_content(chunk_size=8192):
                    f.write(chunk)

            mp3_size_mb = os.path.getsize(mp3_path) / (1024 * 1024)
            logger.info(f"Downloaded Suno MP3: {mp3_path} ({mp3_size_mb:.1f}MB)")

            # Convert MP3 to WAV for pipeline compatibility
            cmd = [
                self.ffmpeg_bin,
                "-y",
                "-i", mp3_path,
                "-codec:a", "pcm_s16le",
                "-ar", str(settings.SAMPLE_RATE),
                "-ac", "2",
                output_path
            ]

            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=60,
                creationflags=subprocess.CREATE_NO_WINDOW if os.name == "nt" else 0
            )

            if result.returncode != 0:
                raise RuntimeError(f"ffmpeg MP3->WAV failed: {result.stderr[-300:]}")

            # Clean up temp MP3
            try:
                os.remove(mp3_path)
            except OSError:
                pass

            wav_size_mb = os.path.getsize(output_path) / (1024 * 1024)
            logger.info(f"Suno WAV saved: {output_path} ({wav_size_mb:.1f}MB)")
            return output_path

        except requests.exceptions.RequestException as e:
            raise RuntimeError(f"Failed to download Suno audio: {e}")

    def _select_best_clip(self, clips):
        """
        Select the best clip from the generated results.

        Suno generates 2 clips per request. We pick the one with
        the highest quality/relevance score if available.

        Args:
            clips (list): List of completed clip dictionaries.

        Returns:
            dict: The best clip.
        """
        if not clips:
            raise RuntimeError("No clips to select from")

        if len(clips) == 1:
            return clips[0]

        # Try to pick by metadata_score or just take the first
        best = clips[0]
        for clip in clips[1:]:
            # Prefer clips with higher metadata_score
            current_score = best.get("metadata_score", 0) or 0
            new_score = clip.get("metadata_score", 0) or 0
            if new_score > current_score:
                best = clip

        logger.info(f"Selected clip {best.get('id', '?')} as best result")
        return best

    def remake(self, wav_path, prompt, duration=30, make_instrumental=True,
               tags="deep house, electronic, club", keep_mp3=False):
        """
        Generate a Deep House remake of a hymn using Suno AI.

        This is the main entry point for the pipeline. It:
        1. Converts the input WAV to MP3
        2. Base64-encodes the MP3 as audio influence
        3. Sends generation request to Suno
        4. Polls for completion
        5. Downloads and converts the result to WAV

        Args:
            wav_path (str): Path to the input WAV file (hymn base audio).
            prompt (str): Text prompt for the Deep House style.
            duration (int): Target duration in seconds (Suno generates ~30s-4min).
            make_instrumental (bool): Generate without vocals (default True).
            tags (str): Genre tags for the generation.
            keep_mp3 (bool): Keep the intermediate MP3 file (default False).

        Returns:
            str: Path to the generated remake WAV file.

        Raises:
            RuntimeError: If Suno API fails.
            FileNotFoundError: If input WAV doesn't exist.
        """
        if not self.is_available():
            raise RuntimeError("SunoRemaker not configured. Set SUNO_SESSION_TOKEN.")

        if not os.path.exists(wav_path):
            raise FileNotFoundError(f"Input WAV not found: {wav_path}")

        hymn_name = Path(wav_path).stem.replace("_base", "")

        # Step 1: Convert WAV to MP3
        logger.info(f"=== Suno Remake: {hymn_name} ===")

        mp3_path = wav_path.rsplit("_base.wav", 1)[0] + "_influence.mp3"
        if not os.path.exists(mp3_path):
            self._wav_to_mp3(wav_path, mp3_path)
        else:
            logger.info(f"Using existing MP3: {mp3_path}")

        # Step 2: Base64 encode for audio influence
        mp3_base64 = self._mp3_to_base64(mp3_path)
        audio_influence = self._build_audio_influence(mp3_base64, source_name=hymn_name)

        # Step 3: Generate songs via Suno API
        full_prompt = f"Create a {prompt} version inspired by this hymn melody. Transform it into a club-ready deep house track with four-on-the-floor kick, deep bass, atmospheric pads, and subtle references to the original hymn's melody."

        clips = self._generate_songs(
            prompt=full_prompt,
            audio_influence=audio_influence,
            make_instrumental=make_instrumental,
            tags=tags,
            title=f"{hymn_name} (Deep House Remix)"
        )

        # Step 4: Poll for completion
        clip_ids = [clip.get("id") for clip in clips if clip.get("id")]
        if not clip_ids:
            raise RuntimeError("Suno returned no clip IDs")

        completed_clips = self._poll_songs(clip_ids)

        # Check for errors
        for clip in completed_clips:
            if clip.get("status") == "error":
                error_msg = clip.get("error_message", "unknown")
                logger.error(f"Suno clip {clip.get('id')} failed: {error_msg}")

        # Filter out errored clips
        valid_clips = [c for c in completed_clips if c.get("status") != "error" and c.get("audio_url")]
        if not valid_clips:
            raise RuntimeError("All Suno clips failed or have no audio_url")

        # Step 5: Select best clip and download
        best_clip = self._select_best_clip(valid_clips)
        remake_wav = wav_path.rsplit("_base.wav", 1)[0] + "_remake.wav"

        self._download_audio(best_clip, remake_wav)

        # Clean up MP3 unless requested to keep
        if not keep_mp3:
            try:
                os.remove(mp3_path)
                logger.info(f"Cleaned up temp MP3: {mp3_path}")
            except OSError:
                pass

        logger.info(f"=== Suno Remake Complete: {remake_wav} ===")
        return remake_wav

    def batch_wav_to_mp3(self, output_dir, bitrate="192k"):
        """
        Convert all base WAV files in the output directory to MP3.

        This is a batch utility for pre-converting WAVs to MP3 format,
        useful for preparing audio influence files or reducing disk usage.

        Args:
            output_dir (str): Directory containing WAV files.
            bitrate (str): MP3 bitrate (default 192k).

        Returns:
            tuple: (converted_count, failed_count)
        """
        import glob

        wav_files = glob.glob(os.path.join(output_dir, "*_base.wav"))
        logger.info(f"Found {len(wav_files)} base WAV files to convert to MP3")

        converted = 0
        failed = 0

        for wav_path in sorted(wav_files):
            mp3_path = wav_path.rsplit("_base.wav", 1)[0] + "_base.mp3"

            if os.path.exists(mp3_path):
                logger.info(f"  Already exists: {os.path.basename(mp3_path)}")
                converted += 1
                continue

            try:
                self._wav_to_mp3(wav_path, mp3_path, bitrate=bitrate)
                converted += 1
            except Exception as e:
                logger.error(f"  FAILED: {os.path.basename(wav_path)}: {e}")
                failed += 1

        logger.info(f"Batch WAV->MP3 complete: {converted} converted, {failed} failed")
        return converted, failed

    def batch_remake(self, output_dir, style="Deep House", skip_existing=True):
        """
        Batch generate Deep House remakes for all hymn WAVs using Suno.

        Processes each base WAV file through the Suno API to create
        a Deep House version. Respects rate limits and credit constraints.

        Args:
            output_dir (str): Directory containing base WAV files.
            style (str): Style prompt for generation.
            skip_existing (bool): Skip if _remake.wav already exists.

        Returns:
            tuple: (success_count, failed_count)
        """
        import glob

        if not self.is_available():
            raise RuntimeError("SunoRemaker not configured")

        wav_files = glob.glob(os.path.join(output_dir, "*_base.wav"))
        logger.info(f"Found {len(wav_files)} hymns to remake via Suno")

        success = 0
        failed = 0

        for wav_path in sorted(wav_files):
            name = Path(wav_path).stem.replace("_base", "")
            remake_path = wav_path.replace("_base.wav", "_remake.wav")

            if skip_existing and os.path.exists(remake_path):
                # Check if it's a real Suno remake (not just a base copy fallback)
                remake_size = os.path.getsize(remake_path)
                base_size = os.path.getsize(wav_path)
                if remake_size != base_size:
                    logger.info(f"  Skipping {name} (remake exists and differs from base)")
                    success += 1
                    continue

            try:
                logger.info(f"\n--- Remaking: {name} ---")
                self.remake(wav_path, style)
                success += 1

                # Rate limiting: wait between requests to avoid 429
                time.sleep(2)

            except Exception as e:
                logger.error(f"  FAILED: {name}: {e}")
                failed += 1

                # If credits exhausted, stop the batch
                if "credits" in str(e).lower() or "402" in str(e):
                    logger.error("Suno credits exhausted. Stopping batch.")
                    break

        logger.info(f"\n=== Batch Suno Remake Complete ===")
        logger.info(f"Success: {success}")
        logger.info(f"Failed: {failed}")
        return success, failed
