"""
Udio AI Music Remaker - Deep House generation via Udio.
"""
import os
import time
import logging
import subprocess
import glob
import json
import requests
from pathlib import Path
from hymn_remaker import settings

logger = logging.getLogger(__name__)

class UdioRemaker:
    def __init__(self, auth_token=None, cookie_string=None):
        self.auth_token = auth_token or os.environ.get("UDIO_OAUTH_TOKEN") or settings.UDIO_AUTH_TOKEN
        self.cookie_string = cookie_string or os.environ.get("UDIO_COOKIE_STRING")
        self.client = None

        if self.auth_token:
            try:
                from udio_wrapper import UdioWrapper
                self.client = UdioWrapper(self.auth_token)
                self._apply_2026_patches()
                logger.info("UdioRemaker initialized with Auth Token and 2026 patches.")
            except Exception as e:
                try: logger.warning(f"Failed to initialize UdioWrapper: {e}")
                except: print(f"Failed to initialize UdioWrapper: {e}")

        # Initialize CDP automation for Edge
        try:
            from hymn_remaker.src.udio_browser_automation import UdioBrowserAutomation
            self.edge_auto = UdioBrowserAutomation()
        except Exception as e:
            try: logger.error(f"Failed to load UdioBrowserAutomation: {e}")
            except: print(f"Failed to load UdioBrowserAutomation: {e}")

    def _apply_2026_patches(self):
        """Monkey-patch the udio-wrapper to use correct 2026 cookie naming and headers."""
        if not self.client: return
        auth_token = self.auth_token
        cookie_str = self.cookie_string or os.environ.get("UDIO_COOKIE_STRING", "")
        if not cookie_str:
            c0 = os.environ.get("UDIO_COOKIE_0", "")
            c1 = os.environ.get("UDIO_COOKIE_1", "")
            if c0:
                cookie_str = f"sb-ssr-production-auth-token.0={c0}"
                if c1: cookie_str += f"; sb-ssr-production-auth-token.1={c1}"

        def patched_get_headers(self_inner, get_request=False):
            return {
                "Accept": "application/json, text/plain, */*",
                "Content-Type": "application/json",
                "Authorization": f"Bearer {auth_token}",
                "Cookie": cookie_str,
                "Origin": "https://www.udio.com",
                "Referer": "https://www.udio.com/studio",
                "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/148.0.0.0 Safari/537.36 Edg/148.0.0.0",
                "X-Udio-Request-Source": "web"
            }

        import types
        self.client.get_headers = types.MethodType(patched_get_headers, self.client)
        logger.info("Successfully patched UdioWrapper with 2026 security headers.")

    def is_available(self):
        if self.client is not None or self.cookie_string: return True
        try:
            requests.get("http://localhost:9222/json", timeout=1)
            return True
        except: return False

    def _upload_to_bridge(self, file_path):
        try:
            logger.info(f"Uploading {os.path.basename(file_path)} to tmpfiles.org bridge...")
            with open(file_path, 'rb') as f:
                files = {'file': f}
                response = requests.post('https://tmpfiles.org/api/v1/upload', files=files, timeout=60)
                response.raise_for_status()
                data = response.json()
                file_url = data['data']['url']
                direct_url = file_url.replace('https://tmpfiles.org/', 'https://tmpfiles.org/dl/')
                logger.info(f"Bridge upload successful: direct URL = {direct_url}")
                return direct_url
        except Exception as e:
            logger.error(f"Bridge upload failed: {e}")
            return None

    def remake(self, wav_path, prompt, variance=0.35, mode="auto", prompt_strength=0.65, manual_mode=True, extension_hack=False, negative_prompt="organ, classical, baroque, church organ, cathedral"):
        unique_prompt = f"HYMNMANIA: {prompt}"
        if mode == "browser":
            return self.remake_edge(wav_path, unique_prompt, variance=variance, prompt_strength=prompt_strength, manual_mode=manual_mode, extension_hack=extension_hack, negative_prompt=negative_prompt)
        try:
            if self.client:
                return self.remake_api(wav_path, unique_prompt, variance=variance, prompt_strength=prompt_strength, manual_mode=manual_mode, extension_hack=extension_hack)
            else:
                return self.remake_edge(wav_path, unique_prompt, variance=variance, prompt_strength=prompt_strength, manual_mode=manual_mode, extension_hack=extension_hack, negative_prompt=negative_prompt)
        except Exception as e:
            if mode == "auto":
                logger.warning(f"Standard remake failed: {e}. Falling back to Edge Automation mode...")
                return self.remake_edge(wav_path, unique_prompt, variance=variance, prompt_strength=prompt_strength, manual_mode=manual_mode, extension_hack=extension_hack, negative_prompt=negative_prompt)
            raise

    def remake_api(self, wav_path, prompt, variance=0.35, prompt_strength=0.65, manual_mode=True, extension_hack=False):
        if not self.client:
            raise RuntimeError("Udio client not initialized for API mode.")

        mp3_upload_path = wav_path.replace(".wav", "_upload.mp3")
        subprocess.run([settings.FFMPEG_BIN, "-y", "-i", wav_path, "-codec:a", "libmp3lame", "-q:a", "2", mp3_upload_path], check=True, capture_output=True)
        try:
            public_url = self._upload_to_bridge(mp3_upload_path)
            if not public_url: raise RuntimeError("Failed to obtain public URL.")

            full_prompt = f"{prompt}. [Audio Influence: {variance}]"
            self.client.extend(prompt=full_prompt, audio_conditioning_path=public_url, seed=-1)

            download_dir = "extend_songs"
            time.sleep(10)
            files = glob.glob(os.path.join(download_dir, "*.mp3"))
            if not files: raise RuntimeError("No downloaded MP3 found.")
            latest_mp3 = max(files, key=os.path.getmtime)

            output_dir = os.path.dirname(wav_path)
            hymn_name = os.path.basename(wav_path).replace("_base.wav", "")
            final_path = os.path.join(output_dir, f"{hymn_name}_remake.wav")
            subprocess.run([settings.FFMPEG_BIN, "-y", "-i", latest_mp3, final_path], check=True, capture_output=True)
            return final_path
        finally:
            if os.path.exists(mp3_upload_path): os.remove(mp3_upload_path)

    def remake_edge(self, wav_path, prompt, variance=0.35, prompt_strength=0.65, manual_mode=True, extension_hack=False, negative_prompt="organ, classical, baroque, church organ, cathedral"):
        if not os.path.exists(wav_path): raise FileNotFoundError(f"Audio file not found: {wav_path}")
        source_audio = wav_path
        if extension_hack:
            logger.info("Applying Udio Extension Hack: Cropping to 15s...")
            cropped_path = wav_path.replace(".wav", "_crop15.wav")
            subprocess.run([settings.FFMPEG_BIN, "-y", "-i", wav_path, "-t", "15", cropped_path], check=True, capture_output=True)
            source_audio = cropped_path

        timestamp = int(time.time())
        mp3_upload_path = source_audio.replace(".wav", f"_upload_{timestamp}.mp3")
        if not mp3_upload_path.endswith(".mp3"): mp3_upload_path += ".mp3"
        subprocess.run([settings.FFMPEG_BIN, "-y", "-i", source_audio, "-codec:a", "libmp3lame", "-q:a", "2", mp3_upload_path], check=True, capture_output=True)

        try:
            logger.info("Triggering Edge Automation (CDP)...")
            # tag_prompt used if prompt is generic, otherwise use provided prompt
            success = self.edge_auto.trigger_generation(prompt=prompt, audio_path=mp3_upload_path, variance=variance, negative_prompt=negative_prompt)
            if not success: raise RuntimeError("Edge automation failed.")

            logger.info("Generation triggered! Waiting for completion...")
            download_triggered = self.edge_auto.wait_for_completion_and_download(timeout=300)
            if not download_triggered: raise RuntimeError("Edge automation failed to trigger download.")

            download_dir = os.path.join(os.path.expanduser("~"), "Downloads")
            start_time = time.time()
            final_path = None
            while time.time() - start_time < 60:
                files = glob.glob(os.path.join(download_dir, "*.mp3"))
                if files:
                    latest_mp3 = max(files, key=os.path.getmtime)
                    if time.time() - os.path.getmtime(latest_mp3) < 45:
                        final_path = latest_mp3
                        break
                time.sleep(5)

            if not final_path: raise RuntimeError("Timed out waiting for file in Downloads.")

            output_dir = os.path.dirname(wav_path)
            hymn_name = os.path.basename(wav_path).replace("_base.wav", "")
            remake_path = os.path.join(output_dir, f"{hymn_name}_remake.wav")
            subprocess.run([settings.FFMPEG_BIN, "-y", "-i", final_path, remake_path], check=True, capture_output=True)
            return remake_path
        finally:
            if os.path.exists(mp3_upload_path): os.remove(mp3_upload_path)
            if extension_hack and os.path.exists(source_audio): os.remove(source_audio)

if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO)
    remaker = UdioRemaker()
