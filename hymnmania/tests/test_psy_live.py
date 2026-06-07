import unittest
import time
from hymn_remaker.src.psy_sequencer import PsyGenerator

class MockPort:
    def __init__(self):
        self.messages = []
    def send(self, msg):
        self.messages.append(msg)

class TestLiveStreaming(unittest.TestCase):
    def test_live_config_updates(self):
        gen = PsyGenerator()
        port = MockPort()

        # Start with low density
        config = {"targetBpm": 300, "euclideanDensity": 1, "mode": "loop"}

        def get_config():
            return config

        import threading
        stop_event = threading.Event()

        # Run streaming in a thread for 1 bar
        t = threading.Thread(target=gen.stream_to_port, args=(port, None, get_config, stop_event))
        t.start()

        time.sleep(1) # Let it play a bit
        low_density_msg_count = len(port.messages)

        # Update density mid-stream
        config["euclideanDensity"] = 16
        time.sleep(1)
        high_density_msg_count = len(port.messages) - low_density_msg_count

        stop_event.set()
        t.join()

        self.assertGreater(high_density_msg_count, low_density_msg_count)

if __name__ == "__main__":
    unittest.main()
