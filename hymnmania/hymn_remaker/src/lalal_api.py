import os
import time
import requests
import logging

logger = logging.getLogger(__name__)

class LalalAPI:
    def __init__(self, license_key=None):
        self.license_key = license_key or os.environ.get("LALAL_LICENSE_KEY")
        self.base_url = "https://www.lalal.ai/api/v1"

    def is_available(self):
        return self.license_key is not None

    def separate_vocals(self, audio_path, output_dir):
        """
        Full pipeline to separate vocals using LALAL.AI API.
        """
        if not self.is_available():
            raise RuntimeError("LALAL_LICENSE_KEY not set.")

        # 1. Upload
        source_id = self.upload(audio_path)

        # 2. Split
        task_id = self.split(source_id)

        # 3. Poll
        result = self.poll_task(task_id)

        # 4. Download
        vocal_url = None
        for track in result.get("tracks", []):
            if track.get("label") == "vocals" and track.get("type") == "stem":
                vocal_url = track.get("url")
                break

        if not vocal_url:
            raise RuntimeError("Vocal stem URL not found in LALAL.AI result.")

        filename = os.path.basename(audio_path)
        name_no_ext = os.path.splitext(filename)[0]
        vocal_path = os.path.join(output_dir, f"{name_no_ext}_vocals_lalal.wav")

        logger.info(f"Downloading LALAL.AI vocals: {vocal_url}")
        resp = requests.get(vocal_url)
        resp.raise_for_status()
        with open(vocal_path, "wb") as f:
            f.write(resp.content)

        return vocal_path

    def upload(self, audio_path):
        url = f"{self.base_url}/upload/"
        filename = os.path.basename(audio_path)
        headers = {
            "X-License-Key": self.license_key,
            "Content-Disposition": f"attachment; filename={filename}"
        }
        logger.info(f"Uploading to LALAL.AI: {audio_path}")
        with open(audio_path, "rb") as f:
            resp = requests.post(url, headers=headers, data=f)
        resp.raise_for_status()
        return resp.json()["id"]

    def split(self, source_id, stem="vocals"):
        url = f"{self.base_url}/split/stem_separator/"
        headers = {
            "X-License-Key": self.license_key
        }
        data = {
            "source_id": source_id,
            "presets": {
                "stem": stem
            }
        }
        logger.info(f"Starting LALAL.AI split task for source: {source_id}")
        resp = requests.post(url, headers=headers, json=data)
        resp.raise_for_status()
        return resp.json()["task_id"]

    def poll_task(self, task_id, interval=5, timeout=300):
        url = f"{self.base_url}/check/"
        headers = {
            "X-License-Key": self.license_key
        }
        data = {
            "task_ids": [task_id]
        }

        start_time = time.time()
        while time.time() - start_time < timeout:
            resp = requests.post(url, headers=headers, json=data)
            resp.raise_for_status()
            status_data = resp.json()["result"][task_id]
            status = status_data["status"]

            if status == "success":
                return status_data["result"]
            elif status == "error":
                raise RuntimeError(f"LALAL.AI task failed: {status_data.get('error')}")

            logger.info(f"LALAL.AI task {task_id} status: {status}")
            time.sleep(interval)

        raise TimeoutError("LALAL.AI task timed out.")
