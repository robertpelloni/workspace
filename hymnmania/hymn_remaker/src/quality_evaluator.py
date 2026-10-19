import librosa
import numpy as np
import logging

logger = logging.getLogger(__name__)

class QualityEvaluator:
    def __init__(self):
        pass

    def evaluate(self, audio_path):
        """
        Evaluate the quality of an audio file based on spectral and rhythmic features.
        Returns a score from 0 to 100.
        """
        try:
            y, sr = librosa.load(audio_path)

            # 1. Spectral Centroid (Brightness/Presence)
            centroid = librosa.feature.spectral_centroid(y=y, sr=sr)
            mean_centroid = np.mean(centroid)
            # Normalize: typical range for music is 1000-5000Hz
            brightness_score = np.clip((mean_centroid - 500) / 4500, 0, 1)

            # 2. Rhythmic Clarity (Onset Strength)
            onset_env = librosa.onset.onset_strength(y=y, sr=sr)
            rhythm_clarity = np.std(onset_env) / (np.mean(onset_env) + 1e-6)
            # Normalize: standard deviation of onset strength for clear beats is usually > 1.0
            rhythm_score = np.clip(rhythm_clarity / 2.0, 0, 1)

            # 3. Dynamic Range (RMS Energy variance)
            rms = librosa.feature.rms(y=y)
            rms_var = np.std(rms) / (np.mean(rms) + 1e-6)
            dynamic_score = np.clip(rms_var * 2.0, 0, 1)

            # Weighted sum
            final_score = (brightness_score * 0.3 + rhythm_score * 0.5 + dynamic_score * 0.2) * 100

            logger.info(f"Quality Evaluation for {audio_path}: Score={final_score:.2f} (B:{brightness_score:.2f}, R:{rhythm_score:.2f}, D:{dynamic_score:.2f})")
            return round(final_score, 2)

        except Exception as e:
            logger.error(f"Failed to evaluate audio {audio_path}: {e}")
            return 0.0

if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1:
        evaluator = QualityEvaluator()
        print(f"Score: {evaluator.evaluate(sys.argv[1])}")
