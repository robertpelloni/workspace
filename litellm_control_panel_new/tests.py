import unittest
import os
import database
import engine
import asyncio

class TestFreeLLM(unittest.TestCase):
    def setUp(self):
        # Use a test database
        database.DB_NAME = "test_metrics.db"
        if os.path.exists(database.DB_NAME):
            os.remove(database.DB_NAME)
        database.init_db()

    def tearDown(self):
        if os.path.exists(database.DB_NAME):
            os.remove(database.DB_NAME)

    def test_database_init(self):
        self.assertTrue(os.path.exists(database.DB_NAME))
        candidates = database.get_candidate_models()
        self.assertEqual(len(candidates), 0)

    def test_model_latency_update(self):
        database.update_model_latency("test-model", "test-provider", 0.5)
        candidates = database.get_candidate_models()
        self.assertEqual(len(candidates), 1)
        self.assertEqual(candidates[0][0], "test-model")

    def test_circuit_breaker_temporal(self):
        database.update_model_latency("fail-model", "fail-provider", 0.5)
        # Fail 3 times
        database.handle_test_failure("fail-model", "fail-provider")
        database.handle_test_failure("fail-model", "fail-provider")
        database.handle_test_failure("fail-model", "fail-provider")

        conn = database.sqlite3.connect(database.DB_NAME)
        cursor = conn.cursor()
        cursor.execute("SELECT retry_after FROM model_history WHERE model_id = 'fail-model'")
        retry_after = cursor.fetchone()[0]
        conn.close()
        self.assertIsNotNone(retry_after)

    def test_manual_skip_temporal(self):
        database.update_model_latency("skip-model", "skip-provider", 0.5)
        database.set_model_skip_status("skip-model", True, duration_hours=24)

        conn = database.sqlite3.connect(database.DB_NAME)
        cursor = conn.cursor()
        cursor.execute("SELECT skip_expiry FROM model_history WHERE model_id = 'skip-model'")
        skip_expiry = cursor.fetchone()[0]
        conn.close()
        self.assertIsNotNone(skip_expiry)

    def test_provider_cycle_logic(self):
        # Initial
        database.update_provider_cycle("p1", found_models=False)
        database.update_provider_cycle("p1", found_models=False)
        database.update_provider_cycle("p1", found_models=False)

        conn = database.sqlite3.connect(database.DB_NAME)
        cursor = conn.cursor()
        cursor.execute("SELECT is_free_provider FROM providers WHERE provider_name = 'p1'")
        is_free = cursor.fetchone()[0]
        conn.close()
        self.assertEqual(is_free, 0)

    def test_scoring_logic(self):
        e = engine.ModelEngine(api_keys={})
        # Higher params, lower latency = better score
        score1 = e.calculate_score(405, 0.5)
        score2 = e.calculate_score(70, 0.5)
        score3 = e.calculate_score(405, 2.0)

        self.assertGreater(score1, score2)
        self.assertGreater(score1, score3)

    def test_parameter_extraction(self):
        e = engine.ModelEngine(api_keys={})
        self.assertEqual(e.extract_parameters({"id": "llama-3.1-405b-instruct"}), 405)
        self.assertEqual(e.extract_parameters({"name": "Gemma 2 132B"}), 132)
        self.assertEqual(e.extract_parameters({"description": "Massive 100b model"}), 100)

    def test_global_exclusions(self):
        e = engine.ModelEngine(api_keys={})
        # Mocking candidates
        candidates = [
            {"id": "llama-3.1-405b", "provider": "openrouter", "parameters": 405},
            {"id": "llama-3.1-405b-preview", "provider": "openrouter", "parameters": 405}
        ]
        # We need to mock get_ranked_models parts or just test the logic inside
        # Since GLOBAL_EXCLUSIONS is used in get_ranked_models loop

        # Testing logic directly
        filtered = [m for m in candidates if not any(exc in m['id'].lower() for exc in engine.GLOBAL_EXCLUSIONS)]
        self.assertEqual(len(filtered), 1)
        self.assertEqual(filtered[0]['id'], "llama-3.1-405b")

    def test_blacklist(self):
        database.update_model_latency("bad-model", "p1", 0.5)
        database.set_model_blacklist_status("bad-model", True)

        conn = database.sqlite3.connect(database.DB_NAME)
        cursor = conn.cursor()
        cursor.execute("SELECT is_blacklisted FROM model_history WHERE model_id = 'bad-model'")
        blacklisted = cursor.fetchone()[0]
        conn.close()
        self.assertEqual(blacklisted, 1)

    def test_savings_calculation(self):
        # 1. Update pricing
        database.update_model_pricing("expensive-model", "p1", 0.1, 0.2)

        # 2. Log usage
        database.log_usage("expensive-model", prompt_tokens=10, completion_tokens=5)

        # 3. Check summary: (10 * 0.1) + (5 * 0.2) = 1.0 + 1.0 = 2.0
        total, breakdown = database.get_savings_summary()
        self.assertEqual(total, 2.0)
        self.assertEqual(len(breakdown), 1)
        self.assertEqual(breakdown[0][0], "expensive-model")
        self.assertEqual(breakdown[0][1], 2.0)

    def test_activity_logging(self):
        # 1. Log some events
        database.log_activity("Test Event", "test-model", "test detail")
        database.log_activity("Another Event", None, "more detail")

        # 2. Retrieve
        logs = database.get_recent_activity(limit=10)
        self.assertEqual(len(logs), 2)
        self.assertEqual(logs[0][1], "Another Event")
        self.assertEqual(logs[1][1], "Test Event")
        self.assertEqual(logs[1][2], "test-model")

    def test_performance_summary(self):
        # 1. Add some probes
        database.record_probe("p1-model", "p1", 0.5, success=True)
        database.record_probe("p1-model", "p1", 1.5, success=False)
        database.record_probe("p2-model", "p2", 0.2, success=True)

        # 2. Get summary
        summary = database.get_performance_summary()
        self.assertEqual(summary['total_probes'], 3)
        # Avg of 0.5 and 0.2 = 0.35 (assuming failures don't count towards latency avg)
        self.assertAlmostEqual(summary['avg_ttft'], 0.35)
        # 2/3 success = 66.6%
        self.assertAlmostEqual(summary['success_rate'], 66.66, places=1)
        self.assertEqual(len(summary['providers']), 2)

    def test_stability_logging(self):
        # 1. Log metrics
        database.log_stability_metric(10, 500) # 10 QPM, 500 TPS
        database.log_stability_metric(5, 250)

        # 2. Retrieve
        history = database.get_load_history(limit=5)
        self.assertEqual(len(history), 2)
        self.assertEqual(history[0][1], 5) # LIFO order
        self.assertEqual(history[1][1], 10)

    def test_protocol_metrics_aggregation(self):
        # 1. Log some activities
        database.log_activity("Protocol Sync", "m1", "Cycle took 10.5s")
        database.log_activity("Protocol Sync", "m2", "Cycle took 5.0s")
        database.log_activity("Health Check Failure", "m1", "Failed")
        database.log_activity("Something Else", None, "Detail")

        # 2. Aggregate
        metrics = database.get_protocol_health_metrics()
        self.assertEqual(metrics['sync_count'], 2)
        self.assertEqual(metrics['avg_sync_duration'], 7.75) # (10.5 + 5.0) / 2
        # 4 events total, 1 failure = 25%
        self.assertEqual(metrics['error_rate'], 25.0)

    def test_engine_state_transitions(self):
        e = engine.ModelEngine(api_keys={})
        self.assertEqual(e.current_state, "Idle")

        # Manually trigger a state change (simulating what happens in get_ranked_models)
        e.current_state = "Fetching"
        self.assertEqual(e.current_state, "Fetching")

if __name__ == "__main__":
    unittest.main()
