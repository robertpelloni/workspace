import asyncio
import threading
import time
import datetime
import os
import sys
import tempfile
from typing import List, Dict, Any

from PIL import Image, ImageDraw
import pystray
from pystray import MenuItem as item

import database
import engine
import config_manager
import settings_ui
import process_manager
import log_viewer
import dashboard_ui
import query_ui
import status_window
import comparison_ui
import api_server
import savings_ui
import monitoring_ui
import protocol_ui
import execution_dashboard

# Debug: catch unhandled exceptions that might silently kill the process
import traceback as _tb
_orig_excepthook = sys.excepthook
def _debug_excepthook(exc_type, exc_value, exc_tb):
    print(f"UNHANDLED EXCEPTION: {exc_type.__name__}: {exc_value}", file=sys.stderr, flush=True)
    _tb.print_exception(exc_type, exc_value, exc_tb, file=sys.stderr)
    _orig_excepthook(exc_type, exc_value, exc_tb)
sys.excepthook = _debug_excepthook

def _debug_exit():
    print("PROCESS EXITING - atexit handler called", flush=True)
import atexit as _atexit2
_atexit2.register(_debug_exit)


# ── Single-instance enforcement ──────────────────────────────────────────────
LOCK_FILE = os.path.join(tempfile.gettempdir(), "freellm.lock")


def _is_pid_our_app(pid):
    """Check if a PID belongs to our main.py app (not a reused PID)."""
    try:
        if sys.platform == "win32":
            import subprocess as sp
            r = sp.run(
                ["wmic", "process", "where", f"processid={pid}", "get", "commandline"],
                capture_output=True, text=True, timeout=3,
            )
            return "main.py" in r.stdout
        else:
            try:
                os.kill(pid, 0)
                return True
            except ProcessLookupError:
                return False
    except Exception:
        return False


def _kill_process_tree(pid):
    """Kill a process and all its children on any platform."""
    try:
        if sys.platform == "win32":
            import subprocess as sp, ctypes
            # Use taskkill /F /T to kill the entire tree
            sp.run(
                ["taskkill", "/F", "/T", "/PID", str(pid)],
                capture_output=True, timeout=5,
            )
            # Wait for process to fully exit
            kernel32 = ctypes.windll.kernel32
            handle = kernel32.OpenProcess(0x100000, False, pid)
            if handle:
                kernel32.WaitForSingleObject(handle, 3000)
                kernel32.CloseHandle(handle)
        else:
            import signal
            try:
                os.kill(pid, signal.SIGTERM)
            except ProcessLookupError:
                return
            time.sleep(1)
            try:
                os.kill(pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
    except Exception:
        pass


def _kill_port_4000():
    """Kill any process listening on port 4000 (orphaned FreeLLM)."""
    try:
        if sys.platform == "win32":
            import subprocess as sp, ctypes
            r = sp.run(["netstat", "-ano"], capture_output=True, text=True, timeout=5)
            kernel32 = ctypes.windll.kernel32
            for line in r.stdout.split(chr(10)):
                if ":4000" in line and "LISTEN" in line:
                    parts = line.strip().split()
                    if parts:
                        try:
                            port_pid = int(parts[-1])
                            handle = kernel32.OpenProcess(1, False, port_pid)
                            if handle:
                                kernel32.TerminateProcess(handle, 1)
                                kernel32.CloseHandle()
                        except (ValueError, OSError):
                            pass
        else:
            import subprocess as sp
            sp.run(["fuser", "-k", "4000/tcp"], capture_output=True, timeout=5)
    except Exception:
        pass


def enforce_single_instance():
    """Kill any existing instance (and orphaned FreeLLM) and take over the lock.

    On startup, this function:
    1. Reads the PID from the lock file
    2. Verifies the PID is actually our app (not a reused PID)
    3. Kills the old instance with its entire process tree
    4. Kills any orphaned FreeLLM process on port 4000
    5. Writes our own PID to the lock file
    6. Registers cleanup handlers
    """
    # Read existing PID from lock file
    old_pid = None
    if os.path.exists(LOCK_FILE):
        try:
            with open(LOCK_FILE, "r") as f:
                old_pid = int(f.read().strip())
        except (ValueError, OSError):
            pass

    # Kill the old process if it's still running AND is actually our app
    if old_pid and _is_pid_our_app(old_pid):
        print(f"Found previous instance (PID {old_pid}). Terminating...")
        _kill_process_tree(old_pid)
        print(f"Terminated previous instance (PID {old_pid})")
        time.sleep(2)
    elif old_pid:
        # PID exists but isn't our app - it was reused. Just take the lock.
        print(f"Lock file PID {old_pid} is no longer our app. Taking over.")

    # Also kill any orphaned FreeLLM on port 4000
    _kill_port_4000()

    # Write our PID to the lock file
    with open(LOCK_FILE, "w") as f:
        f.write(str(os.getpid()))

    # Register cleanup on exit (best-effort; won't run on hard kill)
    import atexit
    atexit.register(lambda: os.remove(LOCK_FILE) if os.path.exists(LOCK_FILE) else None)


# The actual FreeLLM config used by the system
HERMES_CONFIG_PATH = os.path.join(
    os.path.expanduser("~"), ".hermes", "freellm-config.yaml"
)


class FreeLLM:
    def __init__(self):
        self.settings = settings_ui.load_settings()
        self.last_benchmark_time = None
        self.is_online = True
        self.is_working = False

        # Use the hermes config path by default, allow override in settings
        self.config_path = self.settings.get("CONFIG_PATH", HERMES_CONFIG_PATH)
        self.process_mgr = process_manager.FreeLLMProcess(config_path=self.config_path)

        # Load API keys: settings first, then fall back to environment variables
        # Filter out empty API keys to avoid "Illegal header value" errors
        import os

        _env_map = {
            "openrouter": "OPENROUTER_API_KEY",
            "groq": "GROQ_API_KEY",
            "together": "TOGETHER_API_KEY",
            "deepinfra": "DEEPINFRA_API_KEY",
            "cerebras": "CEREBRAS_API_KEY",
            "github": "GITHUB_TOKEN",
            "gemini": "GEMINI_API_KEY",
            "huggingface": "HUGGINGFACE_API_KEY",
            "nvidia": "NVIDIA_NIM_API_KEY",
            "mistral": "MISTRAL_API_KEY",
            "codestral": "CODESTRAL_API_KEY",
            "cohere": "COHERE_API_KEY",
            "sambanova": "SAMBANOVA_API_KEY",
            "fireworks": "FIREWORKS_API_KEY",
            "hyperbolic": "HYPERBOLIC_API_KEY",
            "nebius": "NEBIUS_API_KEY",
            "cloudflare": "CLOUDFLARE_API_KEY",
        }
        api_keys = {}
        for provider, env_name in _env_map.items():
            key = (
                self.settings.get(f"{provider.upper()}_API_KEY", "")
                if provider != "github"
                else self.settings.get("GITHUB_API_KEY", "")
            )
            if not key:
                key = os.environ.get(env_name, "")
            if key:
                api_keys[provider] = key

        weights = {
            "size": float(self.settings.get("SIZE_WEIGHT", 0.6)),
            "context": float(self.settings.get("CONTEXT_WEIGHT", 0.2)),
            "latency": float(self.settings.get("LATENCY_WEIGHT", 0.2)),
        }

        base_urls = {
            "openrouter": self.settings.get("OPENROUTER_BASE_URL", ""),
            "groq": self.settings.get("GROQ_BASE_URL", ""),
            "together": self.settings.get("TOGETHER_BASE_URL", ""),
            "deepinfra": self.settings.get("DEEPINFRA_BASE_URL", ""),
            "cerebras": self.settings.get("CEREBRAS_BASE_URL", ""),
            "gemini": self.settings.get("GEMINI_BASE_URL", ""),
            "ollama": self.settings.get("OLLAMA_BASE_URL", ""),
            "lm_studio": self.settings.get("LM_STUDIO_BASE_URL", ""),
        }

        # Pass cloudflare account ID through api_keys (special case)
        api_keys["cloudflare_account_id"] = self.settings.get(
            "CLOUDFLARE_ACCOUNT_ID", ""
        )

        self.engine = engine.ModelEngine(
            api_keys=api_keys,
            weights=weights,
            base_urls=base_urls,
            min_params=int(self.settings.get("MIN_PARAMETERS", 100)),
        )
        # Ensure providers with API keys are not blacklisted in the DB
        # (prevents death-spiral: no key -> 0 models -> 3 empty cycles -> blacklisted)
        _fix_conn = database.sqlite3.connect(database.DB_NAME)
        _fix_cur = _fix_conn.cursor()
        for prov in api_keys:
            if prov != "cloudflare_account_id":
                _fix_cur.execute(
                    "UPDATE providers SET is_free_provider = 1 WHERE provider_name = ? AND is_free_provider = 0",
                    (prov,),
                )
        _fix_conn.commit()
        _fix_conn.close()

        # Apply exclusions from settings
        engine.GLOBAL_EXCLUSIONS = [
            x.strip()
            for x in self.settings.get("GLOBAL_EXCLUSIONS", "").split(",")
            if x.strip()
        ]

        self.ranked_models: List[Dict[str, Any]] = []
        self.routing_enabled = self.settings.get("ROUTING_ENABLED", True)
        self.auto_pilot = self.settings.get("AUTO_PILOT", False)
        self.running = True
        self.icon = None
        self.loop = asyncio.new_event_loop()

        # Primary group size (how many top models go in free-llm vs free-llm-fallback)
        self.primary_count = int(self.settings.get("PRIMARY_COUNT", 5))

        # Start API server if enabled
        if self.settings.get("ENABLE_API", False):
            api_port = int(self.settings.get("API_PORT", 8000))
            api_server.start_api_server(self, port=api_port)

        # Initialize DB
        database.init_db()

        # Load models from existing config first (instant startup)
        self._load_models_from_config()

        # Then load last rankings from DB as supplementary data
        db_rankings = database.get_last_rankings()
        if db_rankings and not self.ranked_models:
            self.ranked_models = db_rankings

    def _load_models_from_config(self):
        """Read the existing FreeLLM config and populate ranked_models from it.
        This gives instant startup without needing to benchmark first."""
        try:
            entries = config_manager.get_model_entries(self.config_path)
            if not entries:
                return

            models = []
            for e in entries:
                # Skip if we can't identify the model
                if e["provider"] == "unknown":
                    continue
                m = {
                    "id": e["id"],
                    "provider": e["provider"],
                    "parameters": 0,  # Will be filled by benchmark
                    "latency": 0.0,
                    "score": 0.0,
                    "context_length": 0,
                    "group": e["group"],
                }
                models.append(m)

            if models:
                # Put primary group models first, then fallback
                primary = [m for m in models if m["group"] == "free-llm"]
                fallback = [m for m in models if m["group"] != "free-llm"]
                self.ranked_models = primary + fallback
                print(
                    f"Loaded {len(primary)} primary + {len(fallback)} fallback models from existing config."
                )
        except Exception as e:
            print(f"Could not load models from config: {e}")

    def create_image(self, width, height, color, traffic=False):
        image = Image.new("RGBA", (width, height), (0, 0, 0, 0))
        dc = ImageDraw.Draw(image)
        margin = 12

        # Draw main circle
        dc.ellipse([margin, margin, width - margin, height - margin], fill=color)

        if traffic:
            # Draw up/down arrow indicators for traffic
            # Up arrow (cyan)
            dc.polygon(
                [(width // 2, 2), (width // 2 - 8, 10), (width // 2 + 8, 10)],
                fill="cyan",
            )
            # Down arrow (magenta)
            dc.polygon(
                [
                    (width // 2, height - 2),
                    (width // 2 - 8, height - 10),
                    (width // 2 + 8, height - 10),
                ],
                fill="magenta",
            )

        return image

    def notify(self, message, title="FreeLLM"):
        if not self.icon or not self.settings.get("ENABLE_NOTIFICATIONS", True):
            return
        self.icon.notify(message, title)

    def update_tray_status(self):
        if not self.icon:
            return
        color = "gray"
        tooltip = "FreeLLM"
        traffic = self.process_mgr.is_traffic_active()

        if self.is_working:
            color = "blue"
            tooltip = "FreeLLM (Working...)"
        elif not self.is_online:
            color = "gray"
            tooltip = "FreeLLM (Offline)"
        elif self.ranked_models:
            best = self.ranked_models[0]
            best_latency = best.get("latency", 0)
            if best_latency == 0:
                color = "gray"
            elif best_latency < 0.5:
                color = "green"
            elif best_latency < 1.5:
                color = "yellow"
            else:
                color = "red"
            lat_str = f"{best['latency']:.2f}s" if best_latency > 0 else "?"
            tooltip = f"Primary: {best['id']} ({lat_str})"
        else:
            color = "red"
            tooltip = "No models available"

        status = " (Running)" if self.process_mgr.is_running() else " (Stopped)"
        tooltip += status
        self.icon.icon = self.create_image(64, 64, color, traffic=traffic)
        self.icon.title = tooltip

    def on_quit(self, icon, item):
        self.running = False
        if self.settings.get("AUTO_MANAGE_FREELLM", True):
            self.process_mgr.stop()
        icon.stop()

    def toggle_routing(self, icon, item):
        self.routing_enabled = not self.routing_enabled
        self.settings["ROUTING_ENABLED"] = self.routing_enabled
        settings_ui.save_settings(self.settings)
        print(f"Master Routing: {self.routing_enabled}")

    def toggle_auto_pilot(self, icon, item):
        self.auto_pilot = not self.auto_pilot
        self.settings["AUTO_PILOT"] = self.auto_pilot
        settings_ui.save_settings(self.settings)
        print(f"Auto-Pilot: {self.auto_pilot}")

    def enable_startup(self, icon, item):
        import startup

        startup.add_to_startup()

    def disable_startup(self, icon, item):
        import startup

        startup.remove_from_startup()

    def maintenance_clear_skips(self, icon, item):
        database.clear_skip_list()
        self.notify("Skip list cleared.")

    def maintenance_clear_blacklist(self, icon, item):
        database.clear_blacklist()
        self.notify("Blacklist cleared.")

    def maintenance_reset_stats(self, icon, item):
        database.reset_all_stats()
        self.notify("All provider and model stats reset.")

    def maintenance_cleanup_probes(self, icon, item):
        deleted = database.cleanup_old_probes(days=90)
        self.notify(f"Cleaned up {deleted} old probe records.")

    def maintenance_backup_config(self, icon, item):
        config_manager.apply_ranked_models(self.ranked_models, self.config_path)
        self.notify(f"Config backed up to {self.config_path}.bak")

    def maintenance_restore_config(self, icon, item):
        import shutil

        if os.path.exists(self.config_path + ".bak"):
            shutil.copy(self.config_path + ".bak", self.config_path)
            self.notify("Config restored from backup.")
            self._load_models_from_config()
            if self.icon:
                self.icon.menu = self.build_menu()
            self.process_mgr.restart()
        else:
            self.notify("Backup file not found.")

    def toggle_provider(self, provider_name):
        def inner(icon, item):
            conn = database.sqlite3.connect(database.DB_NAME)
            cursor = conn.cursor()
            cursor.execute(
                "SELECT is_free_provider FROM providers WHERE provider_name = ?",
                (provider_name,),
            )
            row = cursor.fetchone()
            new_status = 0 if row and row[0] else 1
            cursor.execute(
                "UPDATE providers SET is_free_provider = ? WHERE provider_name = ?",
                (new_status, provider_name),
            )
            conn.commit()
            conn.close()
            self.refresh_now(None, None)

        return inner

    def launch_interface(self, icon=None, item=None):
        import webbrowser

        url = self.settings.get("INTERFACE_URL", "http://localhost:4000")
        webbrowser.open(url)

    def open_docs(self, icon=None, item=None):
        import webbrowser

        webbrowser.open("https://docs.freellm.ai/")

    def copy_active_model(self, icon=None, item=None):
        if self.ranked_models:
            import tkinter

            r = tkinter.Tk()
            r.withdraw()
            r.clipboard_clear()
            r.clipboard_append(self.ranked_models[0]["id"])
            r.update()
            r.destroy()
            self.notify(f"Copied {self.ranked_models[0]['id']} to clipboard.")

    def get_freellm_env(self):
        """Prepare environment variables for the FreeLLM child process.
        Ensures API keys from settings (or env) are propagated so
        freellm can actually authenticate with providers.
        """
        import os as _os

        env = {}
        key_map = {
            "OPENROUTER_API_KEY": "OPENROUTER_API_KEY",
            "GROQ_API_KEY": "GROQ_API_KEY",
            "TOGETHER_API_KEY": "TOGETHER_API_KEY",
            "DEEPINFRA_API_KEY": "DEEPINFRA_API_KEY",
            "CEREBRAS_API_KEY": "CEREBRAS_API_KEY",
            "GITHUB_API_KEY": "GITHUB_TOKEN",
            "HUGGINGFACE_API_KEY": "HUGGINGFACE_API_KEY",
            "NVIDIA_API_KEY": "NVIDIA_NIM_API_KEY",
            "MISTRAL_API_KEY": "MISTRAL_API_KEY",
            "CODESTRAL_API_KEY": "CODESTRAL_API_KEY",
            "COHERE_API_KEY": "COHERE_API_KEY",
            "SAMBANOVA_API_KEY": "SAMBANOVA_API_KEY",
            "FIREWORKS_API_KEY": "FIREWORKS_API_KEY",
            "HYPERBOLIC_API_KEY": "HYPERBOLIC_API_KEY",
            "NEBIUS_API_KEY": "NEBIUS_API_KEY",
            "CLOUDFLARE_API_KEY": "CLOUDFLARE_API_KEY",
            "CLOUDFLARE_ACCOUNT_ID": "CLOUDFLARE_ACCOUNT_ID",
        }
        for settings_key, env_var in key_map.items():
            val = self.settings.get(settings_key, "")
            if not val:
                val = _os.environ.get(env_var, "")
            if val:
                env[env_var] = val
        return env

    def launch_freellm(self, icon, item):
        success = self.process_mgr.start(env=self.get_freellm_env())
        if success:
            self.notify("FreeLLM Proxy started successfully.", "Process Update")
        else:
            self.notify("Failed to start FreeLLM Proxy.", "Process Error")
        self.update_tray_status()
        return success

    def stop_freellm(self, icon, item):
        success = self.process_mgr.stop()
        if success:
            self.notify("FreeLLM Proxy stopped.", "Process Update")
        self.update_tray_status()
        return success

    def restart_freellm(self, icon, item):
        success = self.process_mgr.restart(env=self.get_freellm_env())
        if success:
            self.notify("FreeLLM Proxy restarted.", "Process Update")
        else:
            self.notify("Failed to restart FreeLLM Proxy.", "Process Error")
        self.update_tray_status()
        return success

    def show_logs(self, icon, item):
        def run_logs():
            viewer = log_viewer.LogViewer(process_mgr=self.process_mgr)
            viewer.run()

        threading.Thread(target=run_logs, daemon=True).start()

    def show_engine_logs(self, icon, item):
        def run_logs():
            viewer = log_viewer.LogViewer(engine=self.engine)
            viewer.run()

        threading.Thread(target=run_logs, daemon=True).start()

    def show_dashboard(self, icon=None, item=None):
        def run_dashboard():
            ui = dashboard_ui.DashboardUI(self)
            ui.run()

        threading.Thread(target=run_dashboard, daemon=True).start()

    def show_query(self, icon=None, item=None):
        def run_query():
            ui = query_ui.QueryUI(self.settings)
            ui.run()

        threading.Thread(target=run_query, daemon=True).start()

    def show_comparison(self, icon=None, item=None):
        def run_comparison():
            ui = comparison_ui.ComparisonUI(self.settings, self.ranked_models)
            ui.run()

        threading.Thread(target=run_comparison, daemon=True).start()

    def show_status(self, icon=None, item=None):
        def run_status():
            ui = status_window.StatusWindow(self)
            ui.run()

        threading.Thread(target=run_status, daemon=True).start()

    def show_leaderboard(self, icon=None, item=None):
        def run_leaderboard():
            ui = dashboard_ui.LeaderboardUI(self)
            ui.run()

        threading.Thread(target=run_leaderboard, daemon=True).start()

    def show_savings(self, icon=None, item=None):
        def run_savings():
            ui = savings_ui.SavingsDashboardUI(self)
            ui.run()

        threading.Thread(target=run_savings, daemon=True).start()

    def show_monitoring(self, icon=None, item=None):
        def run_monitoring():
            ui = monitoring_ui.MonitoringUI(self)
            ui.run()

        threading.Thread(target=run_monitoring, daemon=True).start()

    def show_protocol(self, icon=None, item=None):
        def run_protocol():
            ui = protocol_ui.ProtocolOversightUI(self)
            ui.run()
        threading.Thread(target=run_protocol, daemon=True).start()

    def show_execution(self, icon=None, item=None):
        def run_execution():
            ui = execution_dashboard.ExecutionDashboardUI(self)
            ui.run()
        threading.Thread(target=run_execution, daemon=True).start()

    def view_config(self, icon, item):
        if os.path.exists(self.config_path):
            if os.name == "nt":
                os.startfile(self.config_path)
            else:
                import subprocess

                subprocess.call(["open", self.config_path])

    def show_settings(self, icon, item):
        def run_ui():
            ui = settings_ui.SettingsUI(
                on_save_callback=self.on_settings_saved, engine=self.engine
            )
            ui.run()

        threading.Thread(target=run_ui, daemon=True).start()

    def on_settings_saved(self, new_settings):
        self.settings = new_settings
        self.config_path = self.settings.get("CONFIG_PATH", HERMES_CONFIG_PATH)
        self.process_mgr.config_path = self.config_path

        import startup

        if self.settings.get("START_WITH_WINDOWS", False):
            startup.add_to_startup()
        else:
            startup.remove_from_startup()

        # Reload API keys with env var fallback
        import os as _os

        _env_map = {
            "openrouter": "OPENROUTER_API_KEY",
            "groq": "GROQ_API_KEY",
            "together": "TOGETHER_API_KEY",
            "deepinfra": "DEEPINFRA_API_KEY",
            "cerebras": "CEREBRAS_API_KEY",
            "github": "GITHUB_TOKEN",
            "gemini": "GEMINI_API_KEY",
            "huggingface": "HUGGINGFACE_API_KEY",
            "nvidia": "NVIDIA_NIM_API_KEY",
            "mistral": "MISTRAL_API_KEY",
            "codestral": "CODESTRAL_API_KEY",
            "cohere": "COHERE_API_KEY",
            "sambanova": "SAMBANOVA_API_KEY",
            "fireworks": "FIREWORKS_API_KEY",
            "hyperbolic": "HYPERBOLIC_API_KEY",
            "nebius": "NEBIUS_API_KEY",
            "cloudflare": "CLOUDFLARE_API_KEY",
            "opencode_zen": "",  # No key needed
        }
        new_api_keys = {}
        for provider, env_name in _env_map.items():
            key = (
                self.settings.get(f"{provider.upper()}_API_KEY", "")
                if provider != "github"
                else self.settings.get("GITHUB_API_KEY", "")
            )
            if not key:
                key = _os.environ.get(env_name, "")
            if key:
                new_api_keys[provider] = key
        self.engine.api_keys = new_api_keys
        self.engine.base_urls = {
            "openrouter": self.settings.get("OPENROUTER_BASE_URL", ""),
            "groq": self.settings.get("GROQ_BASE_URL", ""),
            "together": self.settings.get("TOGETHER_BASE_URL", ""),
            "deepinfra": self.settings.get("DEEPINFRA_BASE_URL", ""),
            "cerebras": self.settings.get("CEREBRAS_BASE_URL", ""),
            "github": self.settings.get("GITHUB_BASE_URL", ""),
            "gemini": self.settings.get("GEMINI_BASE_URL", ""),
            "huggingface": self.settings.get("HUGGINGFACE_BASE_URL", ""),
            "nvidia": self.settings.get("NVIDIA_BASE_URL", ""),
            "ollama": self.settings.get("OLLAMA_BASE_URL", ""),
            "lm_studio": self.settings.get("LM_STUDIO_BASE_URL", ""),
        }
        self.engine.weights = {
            "size": float(self.settings.get("SIZE_WEIGHT", 0.6)),
            "context": float(self.settings.get("CONTEXT_WEIGHT", 0.2)),
            "latency": float(self.settings.get("LATENCY_WEIGHT", 0.2)),
        }
        self.engine.min_params = int(self.settings.get("MIN_PARAMETERS", 100))
        engine.GLOBAL_EXCLUSIONS = [
            x.strip()
            for x in self.settings.get("GLOBAL_EXCLUSIONS", "").split(",")
            if x.strip()
        ]
        self.primary_count = int(self.settings.get("PRIMARY_COUNT", 5))

        self.notify("Settings saved and applied.", "Configuration Update")
        asyncio.run_coroutine_threadsafe(self.refresh_logic(), self.loop)

    # ── Model Selection & Reordering ──────────────────────────────────────

    def select_model(self, model_id, provider):
        """Switch a model to be the primary choice (move to top of free-llm)."""

        def inner(icon, item):
            # Move this model to the top of ranked_models (position 0 in primary)
            model = None
            for m in self.ranked_models:
                if m["id"] == model_id and m.get("provider") == provider:
                    model = m
                    break
            if model and model in self.ranked_models:
                self.ranked_models.remove(model)
                self.ranked_models.insert(0, model)
                config_manager.apply_ranked_models(
                    self.ranked_models,
                    self.config_path,
                    primary_count=self.primary_count,
                )
                database.log_activity(
                    "Manual Switch", model_id, f"Switched primary via menu ({provider})"
                )
                self.notify(f"Switched primary to {model_id}", "Model Selected")
                if self.icon:
                    self.icon.menu = self.build_menu()

        return inner

    def promote_to_primary(self, model_id, provider):
        """Move a fallback model up to the primary group."""

        def inner(icon, item):
            model = None
            for m in self.ranked_models:
                if m["id"] == model_id and m.get("provider") == provider:
                    model = m
                    break
            if not model:
                return

            # Find the current boundary between primary and fallback
            current_primary = [
                m
                for m in self.ranked_models
                if m.get("group") == "free-llm"
                or self.ranked_models.index(m) < self.primary_count
            ]
            if model in current_primary:
                self.notify(f"{model_id} is already in primary group.")
                return

            # Move model to the end of the primary group
            self.ranked_models.remove(model)
            insert_pos = min(self.primary_count - 1, len(self.ranked_models))
            self.ranked_models.insert(insert_pos, model)

            # Update the config
            primary_ids = [m["id"] for m in self.ranked_models[: self.primary_count]]
            config_manager.reorder_primary(primary_ids, self.config_path)
            self.notify(f"Promoted {model_id} to primary group.", "Model Promoted")
            if self.icon:
                self.icon.menu = self.build_menu()

        return inner

    def demote_to_fallback(self, model_id, provider):
        """Move a primary model down to the fallback group."""

        def inner(icon, item):
            model = None
            for m in self.ranked_models:
                if m["id"] == model_id and m.get("provider") == provider:
                    model = m
                    break
            if not model:
                return

            idx = self.ranked_models.index(model)
            if idx >= self.primary_count:
                self.notify(f"{model_id} is already in fallback group.")
                return

            # Move model to the top of the fallback group
            self.ranked_models.remove(model)
            insert_pos = self.primary_count  # First position in fallback
            self.ranked_models.insert(insert_pos, model)

            # Update the config
            primary_ids = [m["id"] for m in self.ranked_models[: self.primary_count]]
            config_manager.reorder_primary(primary_ids, self.config_path)
            self.notify(f"Demoted {model_id} to fallback group.", "Model Demoted")
            if self.icon:
                self.icon.menu = self.build_menu()

        return inner

    def move_up(self, model_id, provider):
        """Move a model up one position in its group."""

        def inner(icon, item):
            idx = None
            for i, m in enumerate(self.ranked_models):
                if m["id"] == model_id and m.get("provider") == provider:
                    idx = i
                    break
            if idx is not None and idx > 0:
                self.ranked_models[idx], self.ranked_models[idx - 1] = (
                    self.ranked_models[idx - 1],
                    self.ranked_models[idx],
                )
                primary_ids = [
                    m["id"] for m in self.ranked_models[: self.primary_count]
                ]
                config_manager.reorder_primary(primary_ids, self.config_path)
                if self.icon:
                    self.icon.menu = self.build_menu()

        return inner

    def move_down(self, model_id, provider):
        """Move a model down one position in its group."""

        def inner(icon, item):
            idx = None
            for i, m in enumerate(self.ranked_models):
                if m["id"] == model_id and m.get("provider") == provider:
                    idx = i
                    break
            if idx is not None and idx < len(self.ranked_models) - 1:
                self.ranked_models[idx], self.ranked_models[idx + 1] = (
                    self.ranked_models[idx + 1],
                    self.ranked_models[idx],
                )
                primary_ids = [
                    m["id"] for m in self.ranked_models[: self.primary_count]
                ]
                config_manager.reorder_primary(primary_ids, self.config_path)
                if self.icon:
                    self.icon.menu = self.build_menu()

        return inner

    def skip_model(self, model_id):
        def inner(icon, item):
            database.set_model_skip_status(model_id, True, duration_hours=24)
            asyncio.run_coroutine_threadsafe(self.refresh_logic(), self.loop)

        return inner

    def blacklist_model(self, model_id):
        def inner(icon, item):
            database.set_model_blacklist_status(model_id, True)
            asyncio.run_coroutine_threadsafe(self.refresh_logic(), self.loop)

        return inner

    def refresh_now(self, icon, item):
        asyncio.run_coroutine_threadsafe(self.refresh_logic(), self.loop)

    async def refresh_logic(self, auto_pilot=False):
        self.is_working = True
        self.update_tray_status()
        start_time = time.perf_counter()

        # 1. Check connectivity
        self.is_online = await self.engine.check_connectivity()
        if not self.is_online:
            print("No internet connectivity. Skipping refresh.")
            self.notify(
                "No internet connectivity detected. Retrying soon...",
                "Connectivity Alert",
            )
            self.is_working = False
            self.update_tray_status()
            return False

        print("Refreshing model rankings...")
        database.log_activity("Sync Started", None, "Starting model benchmarking cycle")
        self.ranked_models = await self.engine.get_ranked_models()
        self.last_benchmark_time = datetime.datetime.now()

        if self.routing_enabled and self.ranked_models:
            # Write the full two-group config (primary + fallback)
            config_manager.apply_ranked_models(
                self.ranked_models, self.config_path, primary_count=self.primary_count
            )
            best = self.ranked_models[0]
            duration = time.perf_counter() - start_time
            if auto_pilot:
                database.log_activity(
                    "Auto Switch",
                    best["id"],
                    f"Auto-pilot selected best model ({best['provider']})",
                )
                self.notify(
                    f"Auto-pilot: {best['id']} ({best['provider']})", "Model Switch"
                )
            else:
                database.log_activity(
                    "Sync Complete", best["id"], f"Top model identified: {best['id']}"
                )

        self.is_working = False
        if self.icon:
            self.icon.menu = self.build_menu()
        self.update_tray_status()

        if self.ranked_models:
            best = self.ranked_models[0]
            lat = best.get("latency", 0)
            self.notify(
                f"Refresh complete. Top model: {best['id']} ({lat:.2f}s)",
                "Sync Complete",
            )

        print("Refresh complete.")
        return True

    def build_menu(self):
        menu_items = []

        menu_items.append(
            item(
                "Master Routing",
                self.toggle_routing,
                checked=lambda item: self.routing_enabled,
            )
        )
        menu_items.append(
            item(
                "Copy Active Model",
                self.copy_active_model,
                enabled=len(self.ranked_models) > 0,
            )
        )
        menu_items.append(pystray.Menu.SEPARATOR)

        # 1. Primary Actions & Status
        is_running = self.process_mgr.is_running()
        status_text = "Running" if is_running else "Stopped"
        active_model_name = (
            self.ranked_models[0]["id"] if self.ranked_models else "None"
        )
        menu_items.append(
            item(
                f"FreeLLM: {status_text} | Primary: {active_model_name}",
                lambda: None,
                enabled=False,
            )
        )
        menu_items.append(pystray.Menu.SEPARATOR)

        menu_items.append(
            item("Open LLM Interface", self.launch_interface, default=True)
        )
        menu_items.append(item("Settings", self.show_settings))
        menu_items.append(pystray.Menu.SEPARATOR)
        menu_items.append(item("Quick Query", self.show_query))
        menu_items.append(
            item(
                "Model Comparison",
                self.show_comparison,
                enabled=len(self.ranked_models) > 0,
            )
        )
        menu_items.append(item("Show Dashboard", self.show_dashboard))
        menu_items.append(item("Model Leaderboard", self.show_leaderboard))
        menu_items.append(item("Cost Savings", self.show_savings))
        menu_items.append(item("Monitoring Dashboard", self.show_monitoring))
        menu_items.append(item("Protocol Oversight", self.show_protocol))
        menu_items.append(item("Execution Dashboard", self.show_execution))
        menu_items.append(item("System Status", self.show_status))
        menu_items.append(pystray.Menu.SEPARATOR)

        # 2. FreeLLM Session Control
        control_items = [
            item("Start Proxy", self.launch_freellm, enabled=not is_running),
            item("Stop Proxy", self.stop_freellm, enabled=is_running),
            item("Restart Proxy", self.restart_freellm, enabled=is_running),
            item("View Proxy Logs", self.show_logs),
            item("View Engine Logs", self.show_engine_logs),
            item("View Config", self.view_config),
        ]
        menu_items.append(item("FreeLLM Control", pystray.Menu(*control_items)))

        # 3. Model Rankings — Primary group
        primary_items = []
        fallback_items = []

        for i, m in enumerate(self.ranked_models):
            lat_str = f"{m['latency']:.2f}s" if m.get("latency", 0) > 0 else "?"
            score_str = f"score={m['score']:.0f}" if m.get("score", 0) != 0 else ""
            params_str = f"{m['parameters']}B" if m.get("parameters", 0) > 0 else ""
            group_tag = "★" if i < self.primary_count else "  "
            model_label = f"{group_tag} {m['id']} ({m['provider']}) {params_str} {lat_str} {score_str}".strip()

            submenu_items = [
                item("Set as Primary ★", self.select_model(m["id"], m["provider"])),
            ]

            # Promote/Demote between groups
            if i < self.primary_count:
                submenu_items.append(
                    item(
                        "↓ Demote to Fallback",
                        self.demote_to_fallback(m["id"], m["provider"]),
                    )
                )
                if i > 0:
                    submenu_items.append(
                        item("↑ Move Up", self.move_up(m["id"], m["provider"]))
                    )
                if i < self.primary_count - 1:
                    submenu_items.append(
                        item("↓ Move Down", self.move_down(m["id"], m["provider"]))
                    )
            else:
                submenu_items.append(
                    item(
                        "↑ Promote to Primary",
                        self.promote_to_primary(m["id"], m["provider"]),
                    )
                )
                if i > self.primary_count:
                    submenu_items.append(
                        item("↑ Move Up", self.move_up(m["id"], m["provider"]))
                    )
                if i < len(self.ranked_models) - 1:
                    submenu_items.append(
                        item("↓ Move Down", self.move_down(m["id"], m["provider"]))
                    )

            submenu_items.append(pystray.Menu.SEPARATOR)
            submenu_items.append(item("Skip (24h)", self.skip_model(m["id"])))
            submenu_items.append(item("Blacklist", self.blacklist_model(m["id"])))

            submenu = pystray.Menu(*submenu_items)

            if i < self.primary_count:
                primary_items.append(item(model_label, submenu))
            else:
                fallback_items.append(item(model_label, submenu))

        if primary_items:
            menu_items.append(
                item(f"★ Primary ({self.primary_count})", pystray.Menu(*primary_items))
            )
        if fallback_items:
            menu_items.append(
                item(
                    f"  Fallback ({len(fallback_items)})", pystray.Menu(*fallback_items)
                )
            )
        if not primary_items and not fallback_items:
            menu_items.append(
                item("No models loaded yet...", lambda: None, enabled=False)
            )

        menu_items.append(
            item(
                "Auto-Pilot Mode",
                self.toggle_auto_pilot,
                checked=lambda item: self.auto_pilot,
            )
        )
        menu_items.append(item("Refresh Now", self.refresh_now))
        menu_items.append(pystray.Menu.SEPARATOR)

        # 4. Providers & Maintenance
        provider_stats = database.get_provider_status()
        if provider_stats:
            toggle_items = []
            for name, is_free, empty_cycles, last_check in provider_stats:
                toggle_items.append(
                    item(
                        name,
                        self.toggle_provider(name),
                        checked=lambda item, ns=is_free: ns,
                    )
                )
            menu_items.append(item("Enable Providers", pystray.Menu(*toggle_items)))

        menu_items.append(item("Documentation", self.open_docs))

        startup_menu = pystray.Menu(
            item("Enable", self.enable_startup),
            item("Disable", self.disable_startup),
        )
        menu_items.append(item("Start with Windows", startup_menu))

        maintenance_menu = pystray.Menu(
            item("Clear Skip List", self.maintenance_clear_skips),
            item("Clear Blacklist", self.maintenance_clear_blacklist),
            item("Reset Provider Stats", self.maintenance_reset_stats),
            item("Cleanup Old Probes (>90d)", self.maintenance_cleanup_probes),
            item("Backup FreeLLM Config", self.maintenance_backup_config),
            item("Restore FreeLLM Config", self.maintenance_restore_config),
        )
        menu_items.append(item("Maintenance", maintenance_menu))

        menu_items.append(pystray.Menu.SEPARATOR)
        menu_items.append(item("Quit", self.on_quit))

        return pystray.Menu(*menu_items)

    async def monitor_active_model(self):
        """Monitors the active FreeLLM model health and tracks load stability."""
        consecutive_failures = 0
        last_metrics_time = time.time()
        _startup_grace = time.time() + 30  # Skip health checks for 30s after app start
        while self.running:
            now = time.time()
            # 1. Stability Tracking: Calculate QPM and TPS every minute
            if now - last_metrics_time >= 60:
                conn = database.sqlite3.connect(database.DB_NAME)
                cursor = conn.cursor()
                one_min_ago = datetime.datetime.now() - datetime.timedelta(minutes=1)
                cursor.execute("""
                    SELECT COUNT(*), SUM(prompt_tokens + completion_tokens)
                    FROM usage WHERE timestamp > ?
                """, (one_min_ago.isoformat(),))
                counts = cursor.fetchone()
                qpm = counts[0] or 0
                tps = (counts[1] or 0) / 60.0
                database.log_stability_metric(qpm, tps)
                last_metrics_time = now
                conn.close()

            is_running = self.process_mgr.is_running()
            auto_manage = self.settings.get("AUTO_MANAGE_FREELLM", True)
            if is_running:
                # Give FreeLLM a grace period on first health check
                if consecutive_failures == 0:
                    await asyncio.sleep(15)
                if not self.process_mgr.check_health():
                    consecutive_failures += 1
                    print(f"FreeLLM health check failed ({consecutive_failures}/3)")
                    active_id = (
                        self.ranked_models[0]["id"] if self.ranked_models else "Unknown"
                    )
                    database.log_activity(
                        "Health Check Failure",
                        active_id,
                        f"Attempt {consecutive_failures}/3 failed",
                    )
                else:
                    consecutive_failures = 0
                if consecutive_failures >= 3:
                    print(
                        "Active model seems unhealthy, triggering refresh/fallback..."
                    )
                    database.log_activity(
                        "Fallback Triggered",
                        None,
                        "Triggering refresh due to consecutive health failures",
                    )
                    self.notify(
                        "FreeLLM health check failed multiple times. Triggering fallback...",
                        "Health Alert",
                    )
                    await self.refresh_logic(auto_pilot=self.auto_pilot)
                    consecutive_failures = 0
            elif auto_manage:
                if time.time() < _startup_grace:
                    # During startup grace period, FreeLLM may still be binding
                    await asyncio.sleep(5)
                else:
                    print("FreeLLM process stopped unexpectedly. Attempting restart...")
                    self.notify(
                        "FreeLLM process stopped. Attempting restart...",
                        "Process Alert",
                    )
                    self.process_mgr.start(env=self.get_freellm_env())
                    await asyncio.sleep(60)

    async def background_worker(self):
        """Background loop for periodic model benchmarking.

        Two-tier cadence:
          - Quick pulse every 10 min: re-checks top 5 models for latency drift
          - Full refresh every 60 min: complete re-rank of all models
        """
        asyncio.create_task(self.monitor_active_model())
        full_refresh_interval = 3600  # 1 hour between full refreshes
        pulse_interval = 600  # 10 minutes between quick pulses
        last_full_refresh = 0  # Force first cycle to be a full refresh

        while self.running:
            now = time.time()
            time_since_full = now - last_full_refresh

            try:
                if time_since_full >= full_refresh_interval or not self.ranked_models:
                    # Full refresh: benchmark all candidates and re-rank
                    success = await self.refresh_logic(auto_pilot=self.auto_pilot)
                    if success:
                        print("Rankings updated successfully (full refresh).")
                        last_full_refresh = now
                    else:
                        print("Refresh failed (likely connectivity). Retrying soon.")
                else:
                    # Quick pulse: re-check only top models
                    if self.ranked_models and self.routing_enabled:
                        self.ranked_models, changed = await self.engine.quick_pulse(
                            self.ranked_models, top_n=5
                        )
                        # Only rewrite config if rankings actually changed
                        if changed and self.ranked_models:
                            config_manager.apply_ranked_models(
                                self.ranked_models, self.config_path,
                                primary_count=self.primary_count,
                            )
                            if self.icon:
                                self.icon.menu = self.build_menu()
                            self.update_tray_status()
                            print(f"Quick pulse: rankings changed, config updated. Next check in {pulse_interval // 60} min.")
                        else:
                            print(f"Quick pulse: no changes. Next check in {pulse_interval // 60} min.")
                    else:
                        print("No models to pulse. Skipping.")
            except Exception as e:
                print(f"Error in background worker: {e}")

            # Sleep until next pulse interval
            for _ in range(pulse_interval):
                if not self.running:
                    break
                await asyncio.sleep(1)

    def run_async_loop(self):
        asyncio.set_event_loop(self.loop)
        try:
            self.loop.run_until_complete(self.background_worker())
        except Exception as e:
            print(f"Critical error in async loop: {e}")

    def run(self):
        # Start FreeLLM if configured
        if self.settings.get("AUTO_MANAGE_FREELLM", True):
            self.process_mgr.start(env=self.get_freellm_env())

        # Start background thread
        threading.Thread(target=self.run_async_loop, daemon=True).start()

        # Set tray icon
        self.icon = pystray.Icon(
            "FreeLLM",
            self.create_image(64, 64, "gray"),
            "FreeLLM",
            menu=self.build_menu(),
        )

        # Update tray tooltip after icon starts (use a short delayed call)
        def _delayed_update():
            print("Tray update thread started.")
            while self.running:
                try:
                    self.update_tray_status()
                except Exception as e:
                    print(f"Error updating tray: {e}")
                time.sleep(1.0)  # Slower updates for stability

        threading.Thread(target=_delayed_update, daemon=True).start()
        print("Starting tray icon...")
        try:
            self.icon.run()
        except Exception as e:
            print(f"Tray icon error: {e}")
        # Keep app alive even if tray icon fails
        print("Tray icon stopped. Keeping process alive for FreeLLM...")
        while self.running:
            time.sleep(5)


if __name__ == "__main__":
    enforce_single_instance()
    app = FreeLLM()
    app.run()
