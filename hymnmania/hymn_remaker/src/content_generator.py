import os
import openai
import logging
import json
import hashlib
import requests
from .utils import retry_request

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class ContentGenerator:
    def __init__(self, api_key=None):
        """Initialize the ContentGenerator with an OpenAI API key."""
        self.api_key = api_key or os.environ.get("OPENAI_API_KEY")
        if not self.api_key:
            logger.warning("OPENAI_API_KEY not set. Will use offline fallbacks.")
        if self.api_key:
            self.client = openai.OpenAI(api_key=self.api_key)
        else:
            self.client = None

    def generate_metadata(self, hymn_name, style="Deep House"):
        """Generate title, description, and tags using GPT-4, with offline fallback."""
        if self.client:
            try:
                prompt = (
                    f"Generate metadata for a YouTube video featuring a {style} remake "
                    f"of the hymn '{hymn_name}'.\n"
                    f"Provide the following fields in JSON format:\n"
                    f"1. title: A catchy, modern title for the video.\n"
                    f"2. description: A compelling description (max 1000 chars).\n"
                    f"3. tags: A list of 10 relevant tags."
                )
                logger.info(f"Generating metadata for '{hymn_name}' via OpenAI...")
                response = self.client.chat.completions.create(
                    model="gpt-4-turbo",
                    messages=[
                        {"role": "system", "content": "You are a creative content strategist for a music channel. You must respond in valid JSON."},
                        {"role": "user", "content": prompt}
                    ],
                    response_format={"type": "json_object"}
                )
                content = response.choices[0].message.content
                metadata = json.loads(content)
                logger.info("Metadata generated successfully via OpenAI.")
                return metadata
            except Exception as e:
                err_msg = str(e)
                if "insufficient_quota" in err_msg or "429" in err_msg:
                    logger.warning("OpenAI quota exceeded. Using offline fallback for metadata.")
                else:
                    logger.warning(f"OpenAI metadata generation failed: {err_msg[:100]}. Using offline fallback.")

        # Offline fallback
        return self._offline_metadata(hymn_name, style)

    def generate_lyrics(self, hymn_name):
        """Generate synced lyrics using GPT-4, with offline fallback."""
        if self.client:
            try:
                prompt = (
                    f"Provide the original public domain lyrics for the hymn '{hymn_name}'.\n"
                    f"Output them in a JSON array where each element has:\n"
                    f"- 'text': The line of lyrics.\n"
                    f"- 'start': Estimated start time in seconds (float).\n"
                    f"- 'end': Estimated end time in seconds (float).\n"
                    f"First line starts around 5 seconds in. Estimate pacing for 3-4 min song."
                )
                logger.info(f"Generating synced lyrics for '{hymn_name}' via OpenAI...")
                response = self.client.chat.completions.create(
                    model="gpt-4-turbo",
                    messages=[
                        {"role": "system", "content": "You are a lyric synchronization expert. Respond in valid JSON with a 'lyrics' key containing a list of objects."},
                        {"role": "user", "content": prompt}
                    ],
                    response_format={"type": "json_object"}
                )
                content = response.choices[0].message.content
                lyrics_data = json.loads(content)
                lyrics = lyrics_data.get("lyrics", [])
                logger.info(f"Generated {len(lyrics)} lines of synced lyrics via OpenAI.")
                return lyrics
            except Exception as e:
                err_msg = str(e)
                if "insufficient_quota" in err_msg or "429" in err_msg:
                    logger.warning("OpenAI quota exceeded. Using offline fallback for lyrics.")
                else:
                    logger.warning(f"OpenAI lyrics generation failed: {err_msg[:100]}. Using offline fallback.")

        return self._offline_lyrics(hymn_name)

    def generate_art(self, prompt):
        """Generate album art using DALL-E 3, with local caching and offline fallback."""
        cache_dir = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
                                 ".cache", "art")
        os.makedirs(cache_dir, exist_ok=True)
        prompt_hash = hashlib.md5(prompt.encode('utf-8')).hexdigest()
        cached_image_path = os.path.join(cache_dir, f"{prompt_hash}.png")

        if os.path.exists(cached_image_path):
            logger.info(f"Found cached album art for prompt hash {prompt_hash}")
            return cached_image_path

        # Try DALL-E 3
        if self.client:
            try:
                logger.info(f"Generating album art via DALL-E 3 for: '{prompt[:60]}...'")
                response = self.client.images.generate(
                    model="dall-e-3",
                    prompt=prompt,
                    size="1024x1024",
                    quality="standard",
                    n=1,
                )
                image_url = response.data[0].url
                logger.info(f"Album art generated: {image_url}")
                try:
                    img_response = requests.get(image_url)
                    img_response.raise_for_status()
                    with open(cached_image_path, "wb") as f:
                        f.write(img_response.content)
                    return cached_image_path
                except Exception as e:
                    logger.error(f"Failed to cache album art: {e}")
                    return image_url
            except Exception as e:
                err_msg = str(e)
                if "insufficient_quota" in err_msg or "429" in err_msg:
                    logger.warning("OpenAI quota exceeded. Using offline fallback for album art.")
                else:
                    logger.warning(f"DALL-E 3 art generation failed: {err_msg[:100]}. Using offline fallback.")

        return self._offline_art(prompt, cached_image_path)

    # --- Offline Fallback Methods ---

    def _offline_metadata(self, hymn_name, style="Deep House"):
        """Generate sensible default metadata without API calls."""
        clean_name = hymn_name.replace("_", " ").replace("-", " ").title()
        metadata = {
            "title": f"{clean_name} ({style} Remix)",
            "description": (
                f"A {style} remix of the classic hymn '{clean_name}'. "
                f"Reimagined with modern production while preserving the beautiful "
                f"original melody. Generated by Hymn Remaker AI pipeline."
            ),
            "tags": [
                "hymn", "remix", style.lower().split(",")[0].strip(),
                "worship", "christian music", "cover", clean_name.lower(),
                "ai generated", "music", "sacred"
            ]
        }
        logger.info(f"Generated offline metadata for '{hymn_name}'")
        return metadata

    def _offline_lyrics(self, hymn_name):
        """Generate basic lyrics without API calls."""
        clean_name = hymn_name.replace("_", " ").replace("-", " ").title()
        lyrics = []
        start = 3.0
        for line_text in [f"{clean_name}", "Verse 1", f"{clean_name}",
                          "Verse 2", f"{clean_name}", "Amen"]:
            lyrics.append({"text": line_text, "start": start, "end": start + 4.0})
            start += 5.0
        logger.info(f"Generated {len(lyrics)} lines of offline lyrics for '{hymn_name}'")
        return lyrics

    def _offline_art(self, prompt, cached_path):
        """Generate a simple album art image without API calls."""
        try:
            from PIL import Image, ImageDraw, ImageFont
            img = Image.new('RGB', (1024, 1024), color=(20, 30, 60))
            draw = ImageDraw.Draw(img)
            # Draw gradient background
            for y in range(1024):
                r = int(20 + (y / 1024) * 40)
                g = int(30 + (y / 1024) * 20)
                b = int(60 + (y / 1024) * 80)
                draw.line([(0, y), (1024, y)], fill=(r, g, b))
            # Extract title from prompt
            title = prompt.split("for ")[-1].split(",")[0].strip() if "for " in prompt else "Hymn Remaker"
            try:
                font = ImageFont.truetype("arial.ttf", 48)
            except Exception:
                font = ImageFont.load_default()
            draw.text((512, 500), title, fill=(255, 255, 255), anchor="mm", font=font)
            draw.text((512, 570), "Hymn Remaker", fill=(180, 180, 220), anchor="mm", font=font)
            img.save(cached_path)
            logger.info(f"Offline album art saved to {cached_path}")
            return cached_path
        except Exception as e:
            logger.error(f"Failed to generate offline art: {e}")
            return None


if __name__ == "__main__":
    if os.environ.get("OPENAI_API_KEY"):
        generator = ContentGenerator()
        import sys
        if len(sys.argv) > 1:
            hymn = sys.argv[1]
            print(generator.generate_metadata(hymn))
        else:
            print("Usage: python content_generator.py <hymn_name>")
    else:
        print("OPENAI_API_KEY not set. Skipping real test.")
