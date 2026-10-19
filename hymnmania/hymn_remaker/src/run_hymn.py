#!/usr/bin/env python
"""
Run Suno generation for a hymn MIDI file.

Usage:
    python -m hymn_remaker.src.run_hymn <midi_path> [--lyrics-file <txt>]
"""

import argparse
import pathlib
import logging
import sys

from hymn_remaker.src.hymn_database import HymnDatabase
from hymn_remaker.src.suno_browser_automation import SunoBrowserAutomation

logging.basicConfig(
    level=logging.INFO,
    stream=sys.stdout,
    format="%(asctime)s %(name)s %(levelname)s %(message)s",
)
logger = logging.getLogger(__name__)


def load_lyrics(txt_path: str) -> str:
    """Load lyrics from a text file."""
    try:
        return pathlib.Path(txt_path).read_text(encoding="utf-8")
    except Exception as e:
        raise RuntimeError(f"Could not read lyrics file: {e}")


def main():
    parser = argparse.ArgumentParser(description="Run Suno generation for a hymn.")
    parser.add_argument("midi", help="Path to the MIDI file")
    parser.add_argument(
        "--lyrics-file", help="Optional path to a .txt file containing the hymn lyrics"
    )
    parser.add_argument(
        "--db", default="hymn_remaker/hymn_database.db", help="Path to hymn database"
    )
    args = parser.parse_args()

    midi_path = pathlib.Path(args.midi).resolve()
    if not midi_path.is_file():
        raise FileNotFoundError(f"MIDI file not found: {midi_path}")

    # Load or update hymn metadata in the DB
    db = HymnDatabase(args.db)
    hymn_id = db.add_hymn(str(midi_path))
    file_hash = db._compute_file_hash(str(midi_path))
    hymn = db.find_by_hash(file_hash)

    # Load lyrics (if any) and store them in the DB
    lyrics = None
    if args.lyrics_file and hymn_id is not None:
        lyrics = load_lyrics(args.lyrics_file)
        db.update_lyrics(hymn_id, lyrics, lyrics_source=args.lyrics_file)
        logger.info(f"Loaded lyrics ({len(lyrics)} chars) from {args.lyrics_file}")

    # Render the MIDI to an audio file (WAV expected at same path)
    rendered_wav = midi_path.with_suffix(".wav")
    if not rendered_wav.is_file():
        raise RuntimeError(f"Rendered audio not found: {rendered_wav}")

    # Run Suno automation
    sba = SunoBrowserAutomation()
    success = sba.trigger_generation(
        prompt=hymn.get("title") or "deep house remix of a hymn",
        audio_path=str(rendered_wav),
        make_instrumental=True,
        lyrics=lyrics,
    )
    if success:
        logger.info("✅ Generation started – you can now monitor Suno UI.")
    else:
        logger.error("❌ Generation failed – see logs for details.")


if __name__ == "__main__":
    main()
