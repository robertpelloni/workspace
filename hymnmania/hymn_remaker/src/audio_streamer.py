import threading
import subprocess
import time
import os
import numpy as np
from flask import Flask, Response

class AudioStreamer:
    """
    Renders audio from HymnPlayer in a background thread and streams it over HTTP as MP3.
    """
    def __init__(self, player, port=8000):
        self.player = player
        self.port = port
        self.app = Flask(__name__)
        self.is_streaming = False
        self.stop_event = threading.Event()
        self.current_peaks = [0.0, 0.0]

        @self.app.route('/stream.mp3')
        def stream():
            return Response(self._generate_mp3(), mimetype='audio/mpeg')

    def _generate_mp3(self):
        """
        Background worker that pulls raw PCM from C++ and pipes to FFmpeg for MP3 encoding.
        """
        # ffmpeg command to read raw f32le 44.1k stereo from stdin and output mp3 to stdout
        cmd = [
            'ffmpeg', '-f', 'f32le', '-ar', '44100', '-ac', '2', '-i', 'pipe:0',
            '-f', 'mp3', '-acodec', 'libmp3lame', '-ab', '128k', 'pipe:1'
        ]
        process = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)

        def pull_pcm():
            chunk_size = 1024
            while not self.stop_event.is_set():
                pcm = self.player.render_audio(chunk_size)
                if pcm is not None:
                    # Update peaks for visualizer
                    self.current_peaks = [float(np.max(np.abs(pcm[::2]))), float(np.max(np.abs(pcm[1::2])))]
                    try:
                        process.stdin.write(pcm.tobytes())
                    except BrokenPipeError:
                        break
                else:
                    time.sleep(0.01)
            process.stdin.close()

        threading.Thread(target=pull_pcm, daemon=True).start()

        while not self.stop_event.is_set():
            data = process.stdout.read(4096)
            if not data:
                break
            yield data

        process.terminate()

    def start(self):
        if not self.is_streaming:
            self.is_streaming = True
            self.stop_event.clear()
            threading.Thread(target=lambda: self.app.run(host='0.0.0.0', port=self.port, threaded=True, debug=False, use_reloader=False), daemon=True).start()

    def stop(self):
        self.stop_event.set()
        self.is_streaming = False

    def get_peaks(self):
        return self.current_peaks
