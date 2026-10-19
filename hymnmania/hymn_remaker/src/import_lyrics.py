#!/usr/bin/env python
"""
Import lyrics into hymn database from:
  - Existing MIDI files (mido lyrics extraction)
  - Adjacent .txt files (same filename with .txt extension)
  - Interactive input when neither available
"""

import os
import sys
import json
import logging
from pathlib import Path
from typing import Optional

logging.basicConfig(level=logging.INFO, format="%(asctime)s %(name)s %(levelname)s %(message)s")
logger = logging.getLogger(__name__)

# Add parent to path for imports
sys.path.insert(0, str(Path(__file__).parent.parent))

from hymn_remaker.src.hymn_database import HymnDatabase
from hymn_remaker.src.midi_analyzer import MidiAnalyzer

def import_lyrics_to_db(db_path: str = "hymn_remaker/hymn_database.db", input_dir: str = "hymn_remaker/input"):
    """Scan directory and import lyrics into database."""
    db = HymnDatabase(db_path)
    
    midi_files = list(Path(input_dir).glob("*.mid*"))
    updated = 0
    
    for midi_path in midi_files:
        if midi_path.suffix.lower() not in [".mid", ".midi"]:
            continue
            
        # Compute hash to find record
        file_hash = db._compute_file_hash(str(midi_path))
        hymn = db.find_by_hash(file_hash)
        
        if not hymn:
            logger.warning(f"No DB record for {midi_path.name}")
            continue
            
        if hymn.get("lyrics"):
            logger.info(f"{midi_path.name}: lyrics already in DB, skipping")
            continue
        
        lyrics = None
        
        # Try MIDI extraction first
        metadata = MidiAnalyzer.extract_all_metadata(str(midi_path))
        if metadata.get("raw_lyrics_text"):
