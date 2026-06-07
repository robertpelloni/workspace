import os
import unittest
from hymn_remaker.src.psy_sequencer import PsyGenerator

class TestPsySequencerRealtime(unittest.TestCase):
    def setUp(self):
        self.gen = PsyGenerator()

    def test_generate_bar_messages(self):
        config = {"targetBpm": 145, "euclideanDensity": 5}
        dna = ([], []) # Empty DNA
        messages = self.gen.generate_bar_messages(0, config, dna)
        self.assertTrue(len(messages) > 0)
        # Should have kick notes (36) and silence notes (0)
        notes = [m[1].note for m in messages if m[1].type == 'note_on']
        self.assertIn(36, notes)

    def test_dna_extraction_fallback(self):
        # Test with None input_mid
        dna = self.gen._extract_dna(None)
        self.assertEqual(dna, ([], []))

if __name__ == "__main__":
    unittest.main()
