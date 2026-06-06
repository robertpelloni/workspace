import os
import sys
import logging
from dotenv import load_dotenv

# Load .env
load_dotenv()

logging.basicConfig(level=logging.INFO, format="%(asctime)s - %(name)s - %(levelname)s - %(message)s")
logger = logging.getLogger("UdioAutomationTest")

# Extend path
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from hymn_remaker.src.udio_remaker import UdioRemaker

def test_automation():
    logger.info("Initializing UdioRemaker with browser automation support...")
    remaker = UdioRemaker()
    
    if not remaker.is_available():
        logger.error("❌ Udio service or Edge browser on port 9222 is NOT available. Please make sure Edge is open with --remote-debugging-port=9222 and logged into Udio.com.")
        return
        
    logger.info("✅ Udio browser automation detected as available!")
    
    # We will trigger a quick lofi test track
    prompt = "Lofi beat, chill ambient synth instrumental"
    style = "Chillwave"
    dummy_wav = "hymn_remaker/output/sample_hymn_test.wav"
    
    # Ensure a dummy WAV or output dir exists
    os.makedirs("hymn_remaker/output", exist_ok=True)
    if not os.path.exists(dummy_wav):
        with open(dummy_wav, "wb") as f:
            f.write(b"RIFF....WAVEfmt ....data....")
            
    logger.info(f"Triggering automated browser generation for prompt: '{prompt}'...")
    try:
        output_path = remaker.remake(dummy_wav, prompt=prompt, style=style)
        logger.info(f"🎉 SUCCESS! Automated Udio remake downloaded to: {output_path}")
    except Exception as e:
        logger.error(f"❌ Automation failed during execution: {e}")

if __name__ == "__main__":
    test_automation()
