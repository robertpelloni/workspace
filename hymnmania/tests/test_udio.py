import os
import logging
from hymn_remaker.src.udio_api import UdioAPIClient
from dotenv import load_dotenv

# Load .env
load_dotenv()

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger("UdioTest")

def test_udio_connection():
    token = os.environ.get("UDIO_OAUTH_TOKEN")
    if not token:
        logger.error("UDIO_OAUTH_TOKEN not found in environment. Please set it in .env")
        return

    client = UdioAPIClient(oauth_token=token)
    logger.info("Testing Udio connection...")
    
    if client.is_available():
        logger.info("✅ Successfully connected to Udio!")
        # Try a dummy search or list songs to verify full API access
        try:
            headers = client._get_headers()
            import requests
            resp = requests.get("https://www.udio.com/api/songs?limit=1", headers=headers)
            if resp.status_code == 200:
                logger.info("✅ Full API access confirmed.")
                songs = resp.json()
                logger.info(f"Found {len(songs)} recent songs in your account.")
            else:
                logger.warning(f"⚠️ Connected but API returned {resp.status_code}: {resp.text[:100]}")
        except Exception as e:
            logger.error(f"❌ Error during API verification: {e}")
    else:
        logger.error("❌ Failed to connect. Your token might be invalid or expired.")

if __name__ == "__main__":
    test_udio_connection()
