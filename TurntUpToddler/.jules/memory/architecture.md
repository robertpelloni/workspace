### Project Architecture: Hymn Remaker

The **Hymn Remaker** project is a distributed, AI-driven production platform designed to modernize traditional hymns and classical music. It has evolved from a monolithic application into a scalable, cloud-native microservices suite.

#### 1. High-Level Architecture
*   **Microservices Decomposition**:
    *   **Backend API (FastAPI)**: Serves as the central orchestrator, managing job ingestion, state persistence, and providing a RESTful interface for the dashboard and external clients.
    *   **Frontend Dashboard (Next.js)**: A modern, reactive UI for creating jobs, monitoring progress in real-time, and interacting with the manual review system.
    *   **Render Worker Cluster (Python)**: Handles heavy-duty rendering and AI generation tasks (MusicGen, Suno, Video Generation). It scales horizontally to process multiple jobs in parallel.
    *   **Radio Service (Python/FFmpeg)**: A standalone microservice dedicated to persistent RTMP streaming (e.g., to YouTube Live), managed via distributed Redis Pub/Sub signals.
*   **Infrastructure & Orchestration**:
    *   **Kubernetes (K8s)**: Managed via Kustomize manifests (`kubernetes/base/`), orchestrating deployments, services, ingress, and persistent volumes.
    *   **Shared Storage**: Utilizes Persistent Volume Claims (PVCs) for `input` and `output` directories, ensuring that both API and Worker nodes share the same file system for media assets.
    *   **Docker Multi-Stage Builds**: A critical pattern for managing the 10GB+ machine learning footprint (PyTorch, ONNX). The `Builder -> ML-Deps -> Runtime` sequence optimizes final image size while preserving heavy dependencies.

#### 2. Data & Task Management
*   **Task Ingestion**: Jobs are submitted via the API and queued in **RabbitMQ** for asynchronous processing.
*   **State Persistence & Telemetry**: **Redis** acts as the primary state store. As of v1.50.0, it uses **Atomic Redis Hashes** (`job:{id}`) to track status, progress, and messages, eliminating race conditions during polling.
*   **Job Resiliency**: A global **Job Retry Mechanism** stores the full configuration of every job in Redis, allowing users to re-trigger failed renders from the dashboard without re-uploading files.
*   **Interactive Review Loop**: A "human-in-the-loop" mechanism where workers pause tasks and wait for user approval or edits via Redis before final video assembly.

#### 3. Core Processing Patterns
*   **Hybrid Engine**: Core MIDI rendering is performed by a high-performance C++ engine bridged to Python via **pybind11**, combining low-level audio precision with high-level AI flexibility.
*   **FFmpeg Assembly Pipeline**:
    *   **Polymorphic Backgrounds**: Automatically detects asset types (image vs. video) and applies correct filters (`-loop 1` or `-stream_loop -1`) to match audio duration.
    *   **Subtitle Burning**: Uses **Unicode NFKD normalization** to strip/normalize non-standard characters, preventing FFmpeg failures while preserving international accents.
    *   **4K UHD Output**: Parameterized scaling filters allow for high-resolution (3840x2160) video generation.
*   **Style Intelligence**:
    *   **MidiAnalyzer**: Calculates note density and BPM to provide "Auto-Detect" style suggestions.
    *   **Music21 Integration**: Enables algorithmic score modifications (e.g., "Swing" or "Lullaby" arrangements) before synthesis.

#### 4. Key Design Decisions
*   **Decoupled Frontend**: Transitioning from Streamlit to Next.js provided a more responsive UI and better separation of concerns for scaling.
*   **Robust Fallbacks**: The pipeline implements multi-tier fallbacks (e.g., Suno -> Replicate -> Base Audio) to ensure job completion even if specific AI services fail.
*   **Atomic Redis Connection Pooling**: The FastAPI backend implements a global Redis connection pool to improve concurrent performance and resource efficiency under high load.
*   **Dynamic Video Fallback**: Robust handling for AI video generation ensures the system gracefully falls back to static album art if a video asset fails to generate.

#### 5. Documentation & Governance
The project adheres to a strict set of documentation standards to maintain context across sessions:
*   `VISION.md`: Ultimate goals and core foundational concepts.
*   `ROADMAP.md` & `TODO.md`: Structural milestones and granular short-term tasks.
*   `CHANGELOG.md`: Detailed version history (currently v1.50.0).
*   `MEMORY.md`: Architectural observations and design preferences.
*   `AGENTS.md`: Mandatory instructions for autonomous agents to ensure consistency and safety.

---

I have summarized the current state of the project based on the latest refactors and bug fixes. I am now ready for the next step.