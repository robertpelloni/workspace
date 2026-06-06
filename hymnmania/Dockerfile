# --- Stage 1: Build the C++ Pybind11 Engine ---
FROM python:3.12-slim AS builder

WORKDIR /build

# Install compilation dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    libfluidsynth-dev \
    && rm -rf /var/lib/apt/lists/*

# Install Pybind11
COPY hymn_remaker/requirements.txt .
RUN pip install --no-cache-dir pybind11

# Copy source and build
COPY Makefile .
COPY src/engine/ src/engine/
RUN make extension

# --- Stage 2: ML Inference Dependencies (heavy) ---
FROM python:3.12-slim AS ml-deps

WORKDIR /ml-deps

# Install system deps for oemer (OpenCV/ONNX) and demucs (PyTorch)
RUN apt-get update && apt-get install -y \
    ffmpeg \
    libgl1 \
    libglib2.0-0 \
    && rm -rf /var/lib/apt/lists/*

COPY hymn_remaker/requirements.txt .
RUN pip install --no-cache-dir \
    torch==2.7.1 \
    torchaudio==2.7.1 \
    oemer==0.1.8 \
    demucs==4.0.1 \
    opencv-python-headless==4.11.0.86 \
    onnxruntime==1.22.0

# --- Stage 3: Runtime Environment (slim) ---
FROM python:3.12-slim

WORKDIR /app

# Install only lightweight runtime system dependencies
RUN apt-get update && apt-get install -y \
    ffmpeg \
    fluidsynth \
    fluid-soundfont-gm \
    rubberband-cli \
    && rm -rf /var/lib/apt/lists/*

# Install lightweight Python dependencies only
COPY hymn_remaker/requirements.txt .
RUN pip install --no-cache-dir --no-deps \
    midi2audio==0.1.1 \
    replicate==1.0.7 \
    openai==2.30.0 \
    google-api-python-client==2.186.0 \
    google-auth-oauthlib==1.2.3 \
    google-auth-httplib2==0.2.1 \
    python-dotenv==1.1.1 \
    Pillow==11.3.0 \
    pydub==0.25.1 \
    streamlit==1.57.0 \
    elevenlabs==2.46.0 \
    watchdog==6.0.0 \
    soundfile==0.12.1 \
    mido==1.3.3 \
    music21==9.9.1 \
    pybind11==3.0.4 \
    redis==5.0.3 \
    streamlit-autorefresh==1.0.1 \
    playwright-stealth==2.0.3 \
    pyrubberband==0.4.0 \
    && pip install --no-cache-dir \
    google-auth>=2.41 \
    google-api-core>=2.30 \
    elevenlabs>=2.46 \
    streamlit>=1.57 \
    requests>=2.32 \
    numpy>=1.26 \
    scipy>=1.14

# Copy compiled C++ extension from builder
COPY --from=builder /build/hymn_player_ext*.so ./

# Copy ML packages from ml-deps stage (PyTorch, oemer, demucs, OpenCV, ONNX)
COPY --from=ml-deps /usr/local/lib/python3.12/site-packages/ /usr/local/lib/python3.12/site-packages/

# Copy the rest of the application
COPY . .

# Expose Streamlit port
EXPOSE 8501

# Default to running the Streamlit UI, but can be overridden in docker-compose for daemon mode
CMD ["python", "-m", "streamlit", "run", "hymn_remaker/app.py", "--server.port=8501", "--server.address=0.0.0.0"]
