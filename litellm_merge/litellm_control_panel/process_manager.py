import subprocess
import os
import sys
import threading
import time


def _kill_port(port=4000):
    """Kill any process listening on the given port to prevent bind failures."""
    try:
        if sys.platform == "win32":
            result = subprocess.run(
                ["netstat", "-ano"], capture_output=True, text=True, timeout=5
            )
            pids = set()
            for line in result.stdout.split("\n"):
                if f":{port}" in line and "LISTEN" in line:
                    parts = line.strip().split()
                    if parts:
                        try:
                            pids.add(int(parts[-1]))
                        except ValueError:
                            pass
            import ctypes

            kernel32 = ctypes.windll.kernel32
            for pid in pids:
                handle = kernel32.OpenProcess(1, False, pid)
                if handle:
                    kernel32.TerminateProcess(handle, 1)
                    kernel32.CloseHandle()
                    print(f"Killed zombie on port {port} (PID {pid})")
            if pids:
                time.sleep(2)
        else:
            subprocess.run(
                ["fuser", "-k", f"{port}/tcp"], capture_output=True, timeout=5
            )
            time.sleep(1)
    except Exception as e:
        print(f"Warning: could not clear port {port}: {e}")


def _port_is_open(port=4000, timeout=2):
    """Check if a TCP port is open (something is listening)."""
    import socket

    try:
        sock = socket.create_connection(("127.0.0.1", port), timeout=timeout)
        sock.close()
        return True
    except (socket.timeout, ConnectionRefusedError, OSError):
        return False


class LiteLLMProcess:
    def __init__(self, config_path="config.yaml"):
        self.config_path = config_path
        self.process = None
        self.log_buffer = []
        self.last_traffic_time = 0
        self.traffic_active = False
        self._starting = False  # Guard against concurrent starts

    def _read_stdout(self):
        """Continuously read stdout to prevent pipe deadlocks and track traffic."""
        if not self.process or not self.process.stdout:
            return
        for line in iter(self.process.stdout.readline, ""):
            if line:
                line_lower = line.lower()
                if (
                    "post /" in line_lower
                    or "gave_response" in line_lower
                    or "success" in line_lower
                ):
                    self.last_traffic_time = time.time()
                    self.traffic_active = True
                self.log_buffer.append(line)
                if len(self.log_buffer) > 1000:
                    self.log_buffer.pop(0)

    def is_traffic_active(self):
        """Check if there has been recent traffic (last 2 seconds)."""
        if time.time() - self.last_traffic_time < 2.0:
            return True
        self.traffic_active = False
        return False

    def start(self, env=None):
        """Start the LiteLLM proxy process (non-blocking).

        Starts the subprocess and returns immediately. The monitor loop
        will detect when the port becomes available via is_running()/check_health().

        Args:
            env: Optional dict of environment variables to pass to the child
                 process (e.g. API keys). Merged on top of os.environ.
        """
        # Guard against concurrent starts
        if self._starting:
            return True
        self._starting = True

        try:
            # Check if LiteLLM is already running on port 4000
            if _port_is_open():
                print("LiteLLM is already running on port 4000.")
                return True

            # Kill any zombie on port 4000 before starting
            _kill_port(4000)

            # Check if config file exists
            if not os.path.exists(self.config_path):
                print(f"Config file not found: {self.config_path} - skipping start")
                return False

            print(f"Starting LiteLLM with config: {self.config_path}")

            cmd = ["litellm", "--config", self.config_path, "--port", "4000"]
            creationflags = 0
            if sys.platform == "win32":
                creationflags = subprocess.CREATE_NO_WINDOW

            # Prepare full environment: inherit current + overlay extras
            full_env = os.environ.copy()
            if env:
                full_env.update(env)

            self.process = subprocess.Popen(
                cmd,
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT,
                text=True,
                creationflags=creationflags,
                env=full_env,
                bufsize=1,  # Line buffered
            )

            # Start background thread to consume stdout
            threading.Thread(target=self._read_stdout, daemon=True).start()
            print(f"LiteLLM subprocess started (PID {self.process.pid})")
            return True

        except Exception as e:
            print(f"Failed to start LiteLLM: {e}")
            return False
        finally:
            self._starting = False

    def stop(self):
        """Stop LiteLLM by killing all processes on port 4000."""
        _kill_port(4000)
        self.process = None
        return True

    def restart(self, env=None):
        """Restart the LiteLLM proxy process."""
        self.stop()
        time.sleep(2)
        return self.start(env=env)

    def is_running(self):
        """Check if LiteLLM is running by checking if port 4000 is open.

        We check the PORT instead of the subprocess because on Windows,
        litellm spawns a uvicorn child process. The parent wrapper may
        exit while the actual server continues running on the port.
        """
        return _port_is_open()

    def check_health(self):
        """Checks if the LiteLLM proxy is responding.

        First does a quick TCP port check, then tries HTTP endpoints.
        A timeout on the HTTP check means the server is alive but busy = healthy.
        """
        import httpx

        # Quick TCP check - if port 4000 isn't open, server is down
        if not _port_is_open():
            return False

        # Port is open - try HTTP health endpoint
        for endpoint in ["/health", "/health/readiness", "/health/liveness"]:
            try:
                response = httpx.get(f"http://localhost:4000{endpoint}", timeout=5.0)
                if response.status_code == 200:
                    return True
            except httpx.TimeoutException:
                # Timeout = server is alive but slow to respond = HEALTHY
                return True
            except:
                continue

        # Port is open but no HTTP response yet (still initializing)
        return True  # Port is open = server is alive
