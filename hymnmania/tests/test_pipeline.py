import os
import unittest
import sys
import wave
import mido

# Add pipeline directory to path
sys.path.append(os.path.join(os.path.dirname(__file__), "..", "pipeline"))

from processing.sonic_vacuum import SonicVacuumProcessor
from processing.symbolic_norm import SymbolicNormalizer
from processing.house_quantizer import HouseStructuralQuantizer

class TestPipeline(unittest.TestCase):
    def setUp(self):
        self.test_midi = "test_input/God Is So Good.mid"
        if not os.path.exists(self.test_midi):
            # Create a dummy midi if missing
            mid = mido.MidiFile()
            track = mido.MidiTrack()
            mid.tracks.append(track)
            track.append(mido.Message('note_on', note=60, velocity=64, time=0))
            track.append(mido.Message('note_off', note=60, velocity=64, time=480))
            os.makedirs("test_input", exist_ok=True)
            mid.save(self.test_midi)

    def test_sonic_vacuum(self):
        output = "hymn_remaker/output/test_vacuum.wav"
        processor = SonicVacuumProcessor(self.test_midi)
        processor.render_sine_wave(output)
        self.assertTrue(os.path.exists(output))
        with wave.open(output, 'rb') as f:
            self.assertEqual(f.getframerate(), 44100)
            self.assertGreater(f.getnframes(), 0)

    def test_symbolic_norm(self):
        output = "hymn_remaker/output/test_norm.mid"
        norm = SymbolicNormalizer(self.test_midi)
        norm.normalize(output)
        self.assertTrue(os.path.exists(output))
        mid = mido.MidiFile(output)
        for track in mid.tracks:
            for msg in track:
                if msg.type == 'note_on':
                    self.assertEqual(msg.velocity, 100)

    def test_house_quantizer(self):
        output = "hymn_remaker/output/test_house.mid"
        quantizer = HouseStructuralQuantizer(self.test_midi)
        quantizer.quantize(output)
        self.assertTrue(os.path.exists(output))
        mid = mido.MidiFile(output)
        # Check for kick drum track
        kick_found = False
        for track in mid.tracks:
            if any(msg.type == 'note_on' and msg.note == 36 for msg in track):
                kick_found = True
        self.assertTrue(kick_found)

if __name__ == '__main__':
    unittest.main()
