import logging
import os
import subprocess
import glob
import time
import random
from queue import Queue
from threading import Thread, Event

logger = logging.getLogger(__name__)

class RadioStreamer:
    def __init__(self, rtmp_url, stream_key=None, input_dir="hymn_remaker/output"):
        """
        Proof of concept wrapper to continuously stream generated videos via RTMP.

        Args:
            rtmp_url (str): The RTMP endpoint URL (e.g., rtmp://a.rtmp.youtube.com/live2)
            stream_key (str): The stream key (appended to the URL if provided)
            input_dir (str): Directory containing the source .mp4 files.
        """
        self.full_url = f"{rtmp_url}/{stream_key}" if stream_key else rtmp_url
        self.input_dir = input_dir
        self.is_streaming = False
        self.stream_thread = None
        self.current_track = None
        self.skip_event = Event()

    def _get_videos(self):
        """Retrieve a list of generated .mp4 files."""
        return glob.glob(os.path.join(self.input_dir, "*.mp4"))

    def _stream_loop(self):
        """Infinite loop that continuously concatenates and streams videos to the RTMP endpoint."""
        logger.info(f"Starting 24/7 Live Radio stream to {self.full_url}...")
        self.is_streaming = True

        while self.is_streaming:
            videos = self._get_videos()

            if not videos:
                logger.warning(f"No videos found in {self.input_dir}. Waiting...")
                time.sleep(10)
                continue

            # Randomize playlist
            random.shuffle(videos)

            for video in videos:
                if not self.is_streaming:
                    break

                logger.info(f"Streaming track: {video}")

                # Use FFmpeg to push the stream.
                # -re reads input at native frame rate (vital for streaming)
                # -c copy copies the streams directly without re-encoding (saves CPU)
                cmd = [
                    "ffmpeg",
                    "-re",
                    "-i", video,
                    "-c:v", "copy",
                    "-c:a", "copy",
                    "-f", "flv",
                    self.full_url
                ]

                try:
                    # Run the subprocess. If it finishes, it moves to the next video in the loop.
                    process = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

                    # We wait for the stream to finish or be interrupted
                    self.current_track = os.path.basename(video)
                    while process.poll() is None:
                        if not self.is_streaming:
                            logger.info("Interrupting stream...")
                            process.terminate()
                            break
                        if self.skip_event.is_set():
                            logger.info("Skipping track...")
                            process.terminate()
                            self.skip_event.clear()
                            break
                        time.sleep(1)
                    self.current_track = None

                except Exception as e:
                    logger.error(f"Stream failed for {video}: {e}")
                    time.sleep(5)

        logger.info("Live Radio stream stopped.")

    def start(self):
        """Start the streaming thread."""
        if not self.is_streaming:
            self.stream_thread = Thread(target=self._stream_loop, daemon=True)
            self.stream_thread.start()

    def skip_track(self):
        """Skip the currently playing track."""
        self.skip_event.set()

    def stop(self):
        """Stop the streaming thread."""
        self.is_streaming = False
        if self.stream_thread:
            self.stream_thread.join()

if __name__ == "__main__":
    # Test execution
    import sys
    logging.basicConfig(level=logging.INFO)

    if len(sys.argv) > 1:
        rtmp = sys.argv[1]
        streamer = RadioStreamer(rtmp)
        try:
            streamer.start()
            while True:
                time.sleep(1)
        except KeyboardInterrupt:
            streamer.stop()
    else:
        print("Usage: python radio_streamer.py <rtmp_url>")
