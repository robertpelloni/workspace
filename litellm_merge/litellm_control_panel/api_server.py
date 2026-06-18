from fastapi import FastAPI, HTTPException
import uvicorn
import threading
import database

class LiteLLMAPI:
    def __init__(self, app_instance, port=8000):
        self.app = app_instance
        self.port = port
        self.fastapi_app = FastAPI(title="LiteLLM Control Panel API")
        self._setup_routes()

    def _setup_routes(self):
        @self.fastapi_app.get("/status")
        async def get_status():
            return {
                "proxy_running": self.app.process_mgr.is_running(),
                "primary_model": self.app.ranked_models[0]['id'] if self.app.ranked_models else None,
                "is_working": self.app.is_working,
                "is_online": self.app.is_online
            }

        @self.fastapi_app.get("/rankings")
        async def get_rankings():
            return self.app.ranked_models

        @self.fastapi_app.get("/providers")
        async def get_providers():
            stats = database.get_provider_status()
            return [
                {"name": name, "online": bool(is_free), "empty_cycles": empty_cycles, "last_check": str(last_check)}
                for name, is_free, empty_cycles, last_check in stats
            ]

        @self.fastapi_app.get("/logs/engine")
        async def get_engine_logs(limit: int = 100):
            logs = list(self.app.engine.log_queue)
            return [line for _, line in logs[-limit:]]

        @self.fastapi_app.post("/refresh")
        async def trigger_refresh():
            self.app.refresh_now(None, None)
            return {"status": "Refresh triggered"}

        @self.fastapi_app.post("/proxy/start")
        async def start_proxy():
            if self.app.launch_litellm(None, None):
                return {"status": "Proxy start requested"}
            raise HTTPException(status_code=500, detail="Failed to start proxy")

        @self.fastapi_app.post("/proxy/stop")
        async def stop_proxy():
            self.app.stop_litellm(None, None)
            return {"status": "Proxy stop requested"}

        @self.fastapi_app.post("/proxy/restart")
        async def restart_proxy():
            self.app.restart_litellm(None, None)
            return {"status": "Proxy restart requested"}

    def run(self):
        config = uvicorn.Config(self.fastapi_app, host="127.0.0.1", port=self.port, log_level="info")
        server = uvicorn.Server(config)
        server.run()

def start_api_server(app_instance, port=8000):
    api = LiteLLMAPI(app_instance, port)
    threading.Thread(target=api.run, daemon=True).start()
