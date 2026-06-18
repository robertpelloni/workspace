import unittest
import os
import time
import threading
import json
import httpx
from unittest.mock import MagicMock, patch

# Mock pystray before importing main to avoid X11 errors in headless environment
import sys
from unittest.mock import MagicMock
mock_pystray = MagicMock()
sys.modules['pystray'] = mock_pystray

import main
import database
import settings_ui
import api_server

class MockIcon:
    def __init__(self):
        self.menu = None
        self.title = ""
        self.icon = None
    def notify(self, message, title):
        pass
    def stop(self):
        pass

class TestIntegration(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        # Use test database
        database.DB_NAME = "integration_test.db"
        if os.path.exists(database.DB_NAME):
            os.remove(database.DB_NAME)
        database.init_db()

        # Mock settings
        cls.test_settings = {
            "OPENROUTER_API_KEY": "not_a_real_key",
            "CONFIG_PATH": "test_config.yaml",
            "ROUTING_ENABLED": True,
            "AUTO_PILOT": False,
            "ENABLE_API": True,
            "API_PORT": 8888,
            "PRIMARY_COUNT": 3
        }

        if os.path.exists("test_config.yaml"):
            os.remove("test_config.yaml")

    def setUp(self):
        # Patch load_settings and save_settings to use a local dict
        self.settings_patcher = patch('settings_ui.load_settings', return_value=self.test_settings.copy())
        self.save_patcher = patch('settings_ui.save_settings')
        self.mock_load = self.settings_patcher.start()
        self.mock_save = self.save_patcher.start()

        # Initialize app
        self.app = main.FreeLLM()
        self.app.icon = MockIcon()

        # Add some mock models
        self.app.ranked_models = [
            {"id": "model-1", "provider": "p1", "latency": 0.1, "score": 100, "parameters": 100},
            {"id": "model-2", "provider": "p2", "latency": 0.2, "score": 90, "parameters": 70}
        ]

    def tearDown(self):
        self.settings_patcher.stop()
        self.save_patcher.stop()

    def test_ui_to_settings_integration(self):
        """Verify that UI toggle methods update the internal settings correctly."""
        initial_routing = self.app.routing_enabled
        self.app.toggle_routing(None, None)
        self.assertNotEqual(self.app.routing_enabled, initial_routing)
        self.mock_save.assert_called()

    def test_api_status_integration(self):
        """Verify the API correctly reports the app's state."""
        # We don't need to actually start the server, we can test the FastAPI app directly
        # using httpx.AsyncClient or just call the endpoints via a TestClient if we had it,
        # but here we'll just check if the api_server logic correctly accesses app data.

        api = api_server.FreeLLMAPI(self.app, port=8888)

        # Test status route logic
        async def check_status():
            # Mocking the FastAPI app call
            for route in api.fastapi_app.routes:
                if route.path == "/status":
                    res = await route.endpoint()
                    self.assertEqual(res["primary_model"], "model-1")
                    self.assertTrue(res["is_online"])

        import asyncio
        asyncio.run(check_status())

    def test_manual_switch_activity_log(self):
        """Verify that a manual switch via UI logs the activity in DB."""
        self.app.select_model("model-2", "p2")(None, None)

        # Check database
        logs = database.get_recent_activity(limit=5)
        self.assertTrue(any("Manual Switch" in str(l) for l in logs))
        self.assertTrue(any("model-2" in str(l) for l in logs))

    def test_model_ordering_persistence(self):
        """Verify that reordering models via UI correctly updates ranked_models."""
        # model-2 is at index 1
        self.app.move_up("model-2", "p2")(None, None)
        self.assertEqual(self.app.ranked_models[0]["id"], "model-2")

    @classmethod
    def tearDownClass(cls):
        if os.path.exists(database.DB_NAME):
            os.remove(database.DB_NAME)
        if os.path.exists("test_config.yaml"):
            os.remove("test_config.yaml")

if __name__ == "__main__":
    unittest.main()
