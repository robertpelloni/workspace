"""
Hymn Database — SQLite database for hymn MIDI files with metadata, dedupe, and lyrics support.
"""

import sqlite3
import hashlib
import os
from pathlib import Path
from typing import Optional, List, Dict, Any


class HymnDatabase:
    """SQLite database to track hymn MIDI files with full metadata."""

    def __init__(self, db_path: str = "hymn_database.db"):
        self.db_path = db_path
        self.init_db()

    def init_db(self):
        """Create tables if they don't exist."""
        with sqlite3.connect(self.db_path) as conn:
            conn.execute("""
                CREATE TABLE IF NOT EXISTS hymns (
                    id INTEGER PRIMARY KEY AUTOINCREMENT,
                    filename TEXT NOT NULL,
                    original_filename TEXT,
                    file_hash TEXT UNIQUE NOT NULL,
                    file_size INTEGER NOT NULL,
                    mod_date REAL NOT NULL,
                    source_path TEXT,
                    title TEXT,
                    author TEXT,
                    lyrics TEXT,
                    lyrics_source TEXT,
                    tags TEXT,
                    created_at REAL DEFAULT (strftime('%s', 'now')),
                    updated_at REAL DEFAULT (strftime('%s', 'now'))
                )
            """)
            conn.execute("""
                CREATE INDEX IF NOT EXISTS idx_file_hash ON hymns(file_hash)
            """)
            conn.execute("""
                CREATE INDEX IF NOT EXISTS idx_title ON hymns(title)
            """)

    def _compute_file_hash(self, filepath: str) -> str:
        """Compute SHA256 hash of file for deduping."""
        sha256 = hashlib.sha256()
        with open(filepath, "rb") as f:
            for chunk in iter(lambda: f.read(8192), b""):
                sha256.update(chunk)
        return sha256.hexdigest()

    def add_hymn(
        self,
        filepath: str,
        title: Optional[str] = None,
        author: Optional[str] = None,
        lyrics: Optional[str] = None,
        lyrics_source: Optional[str] = None,
        tags: Optional[str] = None,
    ) -> Optional[int]:
        """Add a hymn file to the database. Returns the row id or None if failed."""
        stat = os.stat(filepath)
        file_hash = self._compute_file_hash(filepath)
        filename = os.path.basename(filepath)
        source_path = str(Path(filepath).parent)

        with sqlite3.connect(self.db_path) as conn:
            cursor = conn.cursor()
            cursor.execute(
                """
                INSERT OR REPLACE INTO hymns 
                (filename, original_filename, file_hash, file_size, mod_date, source_path, 
                 title, author, lyrics, lyrics_source, tags)
                VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
                """,
                (
                    filename,
                    filename,
                    file_hash,
                    stat.st_size,
                    stat.st_mtime,
                    source_path,
                    title,
                    author,
                    lyrics,
                    lyrics_source,
                    tags,
                ),
            )
            return cursor.lastrowid

    def find_by_hash(self, file_hash: str) -> Optional[Dict[str, Any]]:
        """Find a hymn by its file hash."""
        with sqlite3.connect(self.db_path) as conn:
            conn.row_factory = sqlite3.Row
            cursor = conn.execute(
                "SELECT * FROM hymns WHERE file_hash = ?", (file_hash,)
            )
            row = cursor.fetchone()
            return dict(row) if row else None

    def find_by_title(self, title: str) -> List[Dict[str, Any]]:
        """Find hymns by title (partial match)."""
        with sqlite3.connect(self.db_path) as conn:
            conn.row_factory = sqlite3.Row
            cursor = conn.execute(
                "SELECT * FROM hymns WHERE title LIKE ?", (f"%{title}%",)
            )
            return [dict(row) for row in cursor.fetchall()]

    def get_all(self) -> List[Dict[str, Any]]:
        """Get all hymns."""
        with sqlite3.connect(self.db_path) as conn:
            conn.row_factory = sqlite3.Row
            cursor = conn.execute("SELECT * FROM hymns ORDER BY title")
            return [dict(row) for row in cursor.fetchall()]

    def update_lyrics(
        self, hymn_id: int, lyrics: str, lyrics_source: Optional[str] = None
    ):
        """Update lyrics for a hymn."""
        with sqlite3.connect(self.db_path) as conn:
            conn.execute(
                """
                UPDATE hymns 
                SET lyrics = ?, lyrics_source = ?, updated_at = (strftime('%s', 'now'))
                WHERE id = ?
                """,
                (lyrics, lyrics_source, hymn_id),
            )

    def scan_and_add_directory(self, directory: str, recursive: bool = True):
        """Scan a directory for MIDI files and add them to the database."""
        dir_path = Path(directory)
        pattern = "**/*.mid*" if recursive else "*.mid*"
        count = 0
        for filepath in dir_path.glob(pattern):
            if filepath.suffix.lower() in [".mid", ".midi"]:
                self.add_hymn(str(filepath))
                count += 1
        return count

    def get_stats(self) -> Dict[str, Any]:
        """Get database statistics."""
        with sqlite3.connect(self.db_path) as conn:
            cursor = conn.execute("SELECT COUNT(*) FROM hymns")
            total = cursor.fetchone()[0]
            cursor = conn.execute(
                "SELECT COUNT(*) FROM hymns WHERE lyrics IS NOT NULL AND lyrics != ''"
            )
            with_lyrics = cursor.fetchone()[0]
            return {"total": total, "with_lyrics": with_lyrics}


if __name__ == "__main__":
    # Quick test
    db = HymnDatabase()
    print(f"Stats: {db.get_stats()}")
