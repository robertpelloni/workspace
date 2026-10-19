"""
Suno AI client — HTTP API layer, authentication, session management, and polling.

This module handles all direct HTTP communication with the Suno API,
including authentication, captcha checks, session info, feed retrieval,
song generation via the v2-web endpoint, and polling for completion.

Authentication:
    Requires SUNO_SESSION_TOKEN + SUNO_CLIENT_TOKEN from suno.com cookies.
    1. Go to https://suno.com in your browser
    2. Open DevTools > Application > Cookies > suno.com
    3. Copy __session and __client cookie values
    4. Set SUNO_SESSION_TOKEN and SUNO_CLIENT_TOKEN in .env

API Endpoints (reverse-engineered from Suno web app):
    - Session:      GET  /api/session/
    - Captcha Check: POST /api/c/check {ctype: "generation"}
    - Generate:     POST /api/generate/v2-web/
    - Poll:         GET  /api/get/?ids=...
    - Feed:         GET  /api/feed/?page=1
"""

import os
import time
import json
import logging
import requests

from hymn_remaker import settings

logger = logging.getLogger(__name__)

# Suno API endpoints
SUNO_BASE_URL = "https://studio-api.prod.suno.com"
GEN_ENDPOINT = "/api/generate/v2-web/"
SESSION_ENDPOINT = "/api/session/"
CAPTCHA_CHECK_ENDPOINT = "/api/c/check"
FEED_ENDPOINT = "/api/feed/"

# Cloudflare Turnstile sitekeys (from Suno web app JS)
TURNSTILE_SITEKEY_GEN = "0x4AAAAAADI7xDNyj-3LcIbi"
TURNSTILE_SITEKEY_AUTH = "0x4AAAAAABtnpJo7aKMs9JLQ"
TURNSTILE_SITEKEY_GENERAL = "0x4AAAAAABd64Cd9aq5C--VE"

# Default model version
DEFAULT_MODEL_VERSION = "chirp-auk-turbo"

# Polling settings
POLL_INTERVAL = 5      # seconds between status checks
POLL_TIMEOUT = 300     # max seconds to wait for generation (5 min)


class SunoAPIClient:
    """Low-level HTTP client for the Suno AI API.

    Handles authentication headers, session validation, captcha checks,
    song generation requests, completion polling, and audio downloads.
    """

    def __init__(self, session_token=None, client_token=None, model_version=None):
        self.session_token = session_token or os.environ.get("SUNO_SESSION_TOKEN", "")
        self.client_token = client_token or os.environ.get("SUNO_CLIENT_TOKEN", "")
        self.model_version = model_version or os.environ.get("SUNO_MODEL_VERSION", DEFAULT_MODEL_VERSION)
        self.base_url = os.environ.get("SUNO_BASE_URL", SUNO_BASE_URL)

        if not self.session_token:
            logger.warning("SUNO_SESSION_TOKEN not set. SunoAPIClient will not function.")
            logger.warning("Get your token from suno.com browser cookies (DevTools > Application > Cookies)")
        else:
            logger.info(f"SunoAPIClient initialized with model {self.model_version}")

        self.ffmpeg_bin = settings.FFMPEG_BIN

    # ------------------------------------------------------------------
    # Authentication & Headers
    # ------------------------------------------------------------------

    def _get_headers(self):
        """Build request headers with auth tokens."""
        headers = {
            "Accept": "*/*",
            "Accept-Language": "en-US,en;q=0.9",
            "Authorization": f"Bearer {self.session_token}",
            "Content-Type": "application/json",
            "Origin": "https://suno.com",
            "Referer": "https://suno.com/",
            "User-Agent": (
                "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
                "AppleWebKit/537.36 (KHTML, like Gecko) "
                "Chrome/131.0.0.0 Safari/537.36"
            ),
            "sec-ch-ua": '"Google Chrome";v="131", "Chromium";v="131", "Not_A Brand";v="24"',
            "sec-ch-ua-mobile": "?0",
            "sec-ch-ua-platform": '"Windows"',
            "sec-fetch-dest": "empty",
            "sec-fetch-mode": "cors",
            "sec-fetch-site": "cross-site",
        }
        cookie_parts = []
        if self.session_token:
            cookie_parts.append(f"__session={self.session_token}")
        if self.client_token:
            cookie_parts.append(f"__client={self.client_token}")
        if cookie_parts:
            headers["Cookie"] = "; ".join(cookie_parts)
        return headers

    # ------------------------------------------------------------------
    # Session & Status
    # ------------------------------------------------------------------

    def is_available(self):
        """Check if Suno API is configured and session is valid."""
        if not self.session_token:
            return False
        try:
            headers = self._get_headers()
            resp = requests.get(
                f"{self.base_url}{SESSION_ENDPOINT}",
                headers=headers,
                timeout=10,
            )
            if resp.status_code == 200:
                data = resp.json()
                user = data.get("user", {})
                handle = user.get("handle", "")
                return bool(handle)
            return False
        except Exception:
            return False

    def check_captcha(self):
        """Check if CAPTCHA is required for generation.

        Returns:
            dict: {"required": bool, "captcha_version": int}
        """
        headers = self._get_headers()
        try:
            resp = requests.post(
                f"{self.base_url}{CAPTCHA_CHECK_ENDPOINT}",
                json={"ctype": "generation"},
                headers=headers,
                timeout=10,
            )
            if resp.status_code == 200:
                return resp.json()
            return {"required": True, "captcha_version": 1}
        except Exception as e:
            logger.warning(f"Captcha check failed: {e}")
            return {"required": True, "captcha_version": 1}

    def get_session_info(self):
        """Get current session info from Suno API.

        Returns:
            dict: Session data including user info, credits, and available models.
        """
        headers = self._get_headers()
        resp = requests.get(
            f"{self.base_url}{SESSION_ENDPOINT}",
            headers=headers,
            timeout=15,
        )
        if resp.status_code == 200:
            return resp.json()
        elif resp.status_code == 401:
            raise RuntimeError("SUNO_SESSION_TOKEN expired. Get a new one from suno.com")
        else:
            raise RuntimeError(f"Session check failed: {resp.status_code} {resp.text[:200]}")

    def get_feed(self, page=1):
        """Get user's song feed.

        Returns:
            list: List of clip dictionaries from the user's feed.
        """
        headers = self._get_headers()
        resp = requests.get(
            f"{self.base_url}{FEED_ENDPOINT}?page={page}",
            headers=headers,
            timeout=15,
        )
        if resp.status_code == 200:
            return resp.json()
        else:
            raise RuntimeError(f"Feed request failed: {resp.status_code}")

    # ------------------------------------------------------------------
    # Audio Upload (for influence/input clips)
    # ------------------------------------------------------------------

    def upload_audio(self, audio_path):
        """Upload an audio file to Suno for use as influence content.

        Follows Suno's upload flow:
            1. POST /api/uploads/audio/ to get presigned S3 URL
            2. Upload file to S3
            3. POST /api/uploads/audio/{id} to confirm
            4. Poll GET /api/uploads/audio/{id} until complete

        Args:
            audio_path (str): Path to the audio file (MP3 or WAV).

        Returns:
            dict: Upload info with 'id', 's3_id', 'title', or None on failure.
        """
        if not self.session_token:
            logger.error("No session token for audio upload")
            return None
        if not os.path.exists(audio_path):
            logger.error(f"Audio file not found: {audio_path}")
            return None

        import os as _os  # already imported at top; explicit for clarity
        ext = _os.path.splitext(audio_path)[1].lstrip('.').lower()
        if ext not in ('mp3', 'wav', 'm4a', 'ogg', 'flac'):
            logger.warning(f"Unsupported audio format: {ext}")
            ext = 'mp3'

        headers = self._get_headers()
        base = self.base_url

        # Step 1: Request presigned upload URL
        logger.info(f"Requesting audio upload URL for {os.path.basename(audio_path)}...")
        try:
            resp = requests.post(
                f"{base}/api/uploads/audio/",
                json={"extension": ext, "upload_type": "file_upload"},
                headers=headers,
                timeout=15,
            )
            if resp.status_code != 200:
                logger.error(f"Upload URL request failed: {resp.status_code} {resp.text[:200]}")
                return None
            upload_info = resp.json()
            upload_id = upload_info.get("id")
            upload_url = upload_info.get("url", "")
            fields = upload_info.get("fields", {})
            if not upload_id:
                logger.error("No upload ID returned")
                return None
            logger.info(f"Upload ID: {upload_id}")
        except Exception as e:
            logger.error(f"Upload URL request error: {e}")
            return None

        # Step 2: Upload file to S3
        logger.info(f"Uploading to S3...")
        try:
            with open(audio_path, 'rb') as f:
                file_data = f.read()
            s3_files = {"file": (os.path.basename(audio_path), file_data, f"audio/{ext}")}
            s3_data = dict(fields) if fields else {}
            s3_data.pop("Content-Type", None)
            s3_resp = requests.post(upload_url, data=s3_data, files=s3_files, timeout=60)
            if s3_resp.status_code not in (200, 201, 204):
                logger.warning(f"S3 upload returned {s3_resp.status_code}")
        except Exception as e:
            logger.error(f"S3 upload error: {e}")
            return None

        # Step 3: Confirm upload
        logger.info("Confirming upload...")
        try:
            resp = requests.post(
                f"{base}/api/uploads/audio/{upload_id}",
                json={
                    "upload_type": "file_upload",
                    "upload_filename": os.path.basename(audio_path),
                },
                headers=headers,
                timeout=15,
            )
            if resp.status_code != 200:
                logger.warning(f"Upload confirm: {resp.status_code}")
        except Exception as e:
            logger.warning(f"Upload confirm error: {e}")

        # Step 4: Poll until complete
        logger.info("Waiting for audio processing...")
        for i in range(30):
            time.sleep(2)
            try:
                resp = requests.get(
                    f"{base}/api/uploads/audio/{upload_id}",
                    headers=headers,
                    timeout=10,
                )
                if resp.status_code == 200:
                    info = resp.json()
                    status = info.get("status", "")
                    if status == "complete":
                        logger.info(f"Audio upload complete! s3_id={info.get('s3_id', '?')}")
                        return info
                    elif status in ("failed", "error", "rejected"):
                        logger.error(f"Audio upload failed: {status}")
                        return None
                    elif i % 5 == 4:
                        logger.info(f"  Status: {status} ({(i+1)*2}s)")
            except Exception as e:
                if i % 5 == 4:
                    logger.warning(f"  Poll error: {e}")

        logger.error("Audio upload timed out")
        return None

    # ------------------------------------------------------------------
    # Song Generation via API
    # ------------------------------------------------------------------

    def generate_songs(self, prompt, turnstile_token=None, make_instrumental=True,
                       tags=None, title=None, generation_type="TEXT",
                       audio_influence_id=None, audio_influence_weight=0.5):
        """Submit a song generation request to Suno via the v2-web API.

        Args:
            prompt (str): Text description of the song to generate.
            turnstile_token (str): Cloudflare Turnstile token (required for v2-web).
            make_instrumental (bool): Whether to generate instrumental only.
            tags (str): Genre tags (e.g., "deep house, electronic").
            title (str): Song title.
            generation_type (str): One of TEXT, AUDIO, IMAGE, VIDEO, TWITTER, SIMPLE_REMIX.
            audio_influence_id (str): ID of an uploaded audio file.
            audio_influence_weight (float): Influence strength (0.0 to 1.0).

        Returns:
            list: List of clip dictionaries from the API response.

        Raises:
            RuntimeError: If the API request fails.
        """
        if not self.session_token:
            raise RuntimeError("SUNO_SESSION_TOKEN not configured")

        payload = {
            "token": turnstile_token if turnstile_token else None,
            "gpt_description_prompt": prompt,
            "mv": self.model_version,
            "prompt": "",
            "make_instrumental": make_instrumental,
            "generation_type": "AUDIO" if audio_influence_id else generation_type,
            "metadata": {
                "create_mode": "simple",
                "user_tier": "free",
                "lyrics_model": "default",
            },
        }

        if audio_influence_id:
            payload["audio_influence_id"] = audio_influence_id
            payload["audio_influence_weight"] = audio_influence_weight
            if not tags:
                tags = "deep house, electronic"
            if not title:
                title = "Hymn Remix"

        if tags:
            payload["tags"] = tags
        if title:
            payload["title"] = title

        logger.info(f"Submitting Suno generation request via API...")
        if audio_influence_id:
            logger.info(f"  Audio Influence ID: {audio_influence_id}")
        logger.info(f"  Prompt: {prompt[:100]}...")
        logger.info(f"  Model: {self.model_version}")
        logger.info(f"  Instrumental: {make_instrumental}")
        logger.info(f"  Has Turnstile token: {bool(turnstile_token)}")

        headers = self._get_headers()
        url = f"{self.base_url}{GEN_ENDPOINT}"

        try:
            response = requests.post(url, json=payload, headers=headers, timeout=30)

            if response.status_code == 401:
                raise RuntimeError("SUNO_SESSION_TOKEN is invalid or expired. Get a new one from suno.com")
            if response.status_code == 402:
                raise RuntimeError("Suno credits exhausted. Wait for daily reset or upgrade plan.")
            if response.status_code == 429:
                raise RuntimeError("Suno rate limit hit. Waiting before retry.")

            if response.status_code == 422:
                try:
                    error_data = response.json()
                    error_type = error_data.get("error_type", "")
                    if error_type == "token_validation_failed":
                        raise RuntimeError(
                            "Turnstile token validation failed. Need a fresh token. "
                            "Use get_turnstile_token() or browser automation mode."
                        )
                    detail = error_data.get("detail", "")
                    if "params" in str(detail) and "prompt" in str(detail):
                        raise RuntimeError(
                            f"API payload format error. The Suno API may have changed. "
                            f"Detail: {str(detail)[:300]}"
                        )
                except (json.JSONDecodeError, AttributeError):
                    pass
                raise RuntimeError(f"Suno API validation error 422: {response.text[:300]}")

            if response.status_code == 503:
                raise RuntimeError("Suno API is temporarily unavailable (503). Try again later.")
            if response.status_code != 200:
                raise RuntimeError(f"Suno API error {response.status_code}: {response.text[:300]}")

            clips = response.json()
            if isinstance(clips, dict) and "clips" in clips:
                clips = clips["clips"]

            logger.info(f"Suno generation submitted: {len(clips) if isinstance(clips, list) else 1} clip(s)")
            if isinstance(clips, list):
                for clip in clips:
                    clip_id = clip.get("id", "unknown")
                    logger.info(f"  Clip ID: {clip_id}")

            return clips

        except requests.exceptions.ConnectionError as e:
            raise RuntimeError(f"Cannot connect to Suno API: {e}")
        except requests.exceptions.Timeout:
            raise RuntimeError("Suno API request timed out")

    # ------------------------------------------------------------------
    # Polling & Download
    # ------------------------------------------------------------------

    def poll_songs(self, clip_ids):
        """Poll Suno API until songs are complete.

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
                    timeout=15,
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

    def download_audio(self, clip, output_path):
        """Download the generated audio from a completed Suno clip.

        Suno provides audio_url (MP3). We download the MP3 and convert
        to WAV for pipeline compatibility.

        Args:
            clip (dict): Completed clip dictionary from Suno.
            output_path (str): Path to save the output WAV file.

        Returns:
            str: Path to the downloaded WAV file.

        Raises:
            RuntimeError: If download fails.
        """
        import subprocess
        import os

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
                "-y", "-i", mp3_path,
                "-codec:a", "pcm_s16le",
                "-ar", str(settings.SAMPLE_RATE),
                "-ac", "2",
                output_path,
            ]
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=60,
                creationflags=subprocess.CREATE_NO_WINDOW if os.name == "nt" else 0,
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

    @staticmethod
    def select_best_clip(clips):
        """Select the best clip from the generated results.

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

        best = clips[0]
        for clip in clips[1:]:
            current_score = best.get("metadata_score", 0) or 0
            new_score = clip.get("metadata_score", 0) or 0
            if new_score > current_score:
                best = clip

        logger.info(f"Selected clip {best.get('id', '?')} as best result")
        return best
