import subprocess
import sys
import os

def build():
    print("Building FreeLLM...")

    # Ensure dependencies are installed
    # subprocess.check_call([sys.executable, "-m", "pip", "install", "pystray", "httpx", "ruamel.yaml", "pyinstaller", "Pillow"])

    cmd = [
        "pyinstaller",
        "--noconsole",
        "--onefile",
        "--name", "FreeLLM",
        "--clean",
        "main.py"
    ]

    try:
        subprocess.check_call(cmd)
        print("Build successful! Check the dist/ folder.")
    except Exception as e:
        print(f"Build failed: {e}")

if __name__ == "__main__":
    build()
