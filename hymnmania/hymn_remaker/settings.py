import os
from dotenv import load_dotenv

# Load environment variables
load_dotenv()
load_dotenv(os.path.join(os.path.dirname(__file__), ".env"))


# --- Paths ---
BASE_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), ".."))
INPUT_DIR = os.path.join(BASE_DIR, "hymn_remaker", "input")
OUTPUT_DIR = os.path.join(BASE_DIR, "hymn_remaker", "output")
CACHE_DIR = os.path.join(BASE_DIR, ".cache")
ART_CACHE_DIR = os.path.join(CACHE_DIR, "art")

# --- Default Fallback Paths ---
# Local soundfonts directory (bundled with the project)
_SOUNDFONTS_DIR = os.path.join(os.path.dirname(__file__), "soundfonts")

DEFAULT_SOUNDFONT_PATHS = [
    # Local project soundfonts (Windows/macOS/Linux portable)
    os.path.join(_SOUNDFONTS_DIR, "MV30_SC-55.sf2"),
    os.path.join(_SOUNDFONTS_DIR, "FluidR3_GM.sf2"),
    os.path.join(_SOUNDFONTS_DIR, "GeneralUser_GS.sf2"),
    # Linux system paths
    '/usr/share/sounds/sf2/FluidR3_GM.sf2',
    '/usr/share/sounds/sf2/default-GM.sf2',
    '/usr/share/soundfonts/default.sf2',
    '/usr/local/share/fluidsynth/sounds/FluidR3_GM.sf2',
    # macOS Homebrew paths
    '/opt/homebrew/share/soundfonts/FluidR3_GM.sf2',
    '/usr/local/share/soundfonts/FluidR3_GM.sf2',
]

# --- Pipeline Settings ---
DEFAULT_STYLE = "Deep House, high quality, electronic"
DEFAULT_VIDEO_FORMAT = "Standard 16:9"
DEFAULT_ELEVENLABS_VOICE_ID = "21m00Tcm4TlvDq8ikWAM"
DEFAULT_ELEVENLABS_MODEL = "eleven_multilingual_v2"

# --- Audio Engine Settings ---
SAMPLE_RATE = 44100
REVERB_TAIL_SECONDS = 2.0

# --- FluidSynth Binary ---
# Local bundled binary (Windows) or system PATH
_BIN_DIR = os.path.join(os.path.dirname(__file__), "bin")
FLUIDSYNTH_BIN = os.path.join(_BIN_DIR, "fluidsynth.exe") if os.name == "nt" else "fluidsynth"
# --- FFmpeg Binary ---
# Local bundled binary (Windows) or system PATH
FFMPEG_BIN = os.path.join(_BIN_DIR, "ffmpeg.exe") if os.name == "nt" else "ffmpeg"
FFPROBE_BIN = os.path.join(_BIN_DIR, "ffprobe.exe") if os.name == "nt" else "ffprobe"


# --- Suno AI Music API ---
SUNO_SESSION_TOKEN = os.environ.get("SUNO_SESSION_TOKEN", "")
SUNO_MODEL_VERSION = os.environ.get("SUNO_MODEL_VERSION", "chirp-v4")
SUNO_BASE_URL = os.environ.get("SUNO_BASE_URL", "https://studio-api.suno.ai")
SUNO_POLL_INTERVAL = int(os.environ.get("SUNO_POLL_INTERVAL", "5"))
SUNO_POLL_TIMEOUT = int(os.environ.get("SUNO_POLL_TIMEOUT", "300"))

# --- Udio AI Music API ---
UDIO_AUTH_TOKEN = os.environ.get("UDIO_AUTH_TOKEN", "") or os.environ.get("UDIO_OAUTH_TOKEN", "")
UDIO_CLIENT_ID = os.environ.get("UDIO_CLIENT_ID", "")
UDIO_CLIENT_SECRET = os.environ.get("UDIO_CLIENT_SECRET", "")
UDIO_POLL_INTERVAL = int(os.environ.get("UDIO_POLL_INTERVAL", "10"))
UDIO_POLL_TIMEOUT = int(os.environ.get("UDIO_POLL_TIMEOUT", "600"))

# --- MP3 Conversion ---
DEFAULT_MP3_BITRATE = "192k"

# --- Remake Priority ---
# Which AI service to use first for Step 2 (remake)
# Options: "udio-oauth", "udio", "suno", "replicate"
REMAKE_PRIORITY = os.environ.get("REMAKE_PRIORITY", "suno")
