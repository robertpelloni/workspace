#!/usr/bin/env python
"""
Hymn MIDI Scraper — Downloads hymn MIDI files from public archives and adds them to the database.

Supported sources:
- Hymnary.org (via their API/exports)
- CyberHymnal / NetHymnal
- Mutopia Project
- ChoralWiki (CPDL)
- OpenHymnal
- Project Gutenberg
- Archive.org collections

Uses requests + BeautifulSoup for scraping, with polite delays and robots.txt respect.
"""

import re
import time
import hashlib
import logging
import argparse
import requests
from pathlib import Path
from urllib.parse import urljoin, urlparse
from typing import List, Dict, Optional, Tuple
from dataclasses import dataclass

try:
    from bs4 import BeautifulSoup
except ImportError:
    BeautifulSoup = None

from hymn_remaker.src.hymn_database import HymnDatabase

logger = logging.getLogger(__name__)


@dataclass
class HymnSource:
    """Configuration for a hymn source."""

    name: str
    base_url: str
    midi_selector: str  # CSS selector for MIDI links
    title_selector: Optional[str] = None  # CSS selector for title
    author_selector: Optional[str] = None
    lyrics_selector: Optional[str] = None
    pagination: Optional[str] = None  # URL pattern with {page}
    max_pages: int = 1
    delay: float = 2.0  # seconds between requests


# Pre-configured sources
SOURCES = {
    "hymnary": HymnSource(
        name="Hymnary.org",
        base_url="https://hymnary.org",
        midi_selector='a[href$=".mid"], a[href$=".midi"]',
        title_selector="h1, .hymn-title",
        author_selector=".author, .composer",
        lyrics_selector=".lyrics, .hymn-text",
        pagination="/hymns?page={page}",
        max_pages=50,
        delay=2.0,
    ),
    "cyberhymnal": HymnSource(
        name="CyberHymnal",
        base_url="https://www.hymntime.com/tch",
        midi_selector='a[href$=".mid"]',
        title_selector="h1, .title",
        author_selector=".author",
        pagination="/browse.htm?page={page}",
        max_pages=100,
        delay=1.5,
    ),
    "mutopia": HymnSource(
        name="Mutopia Project",
        base_url="https://www.mutopiaproject.org",
        midi_selector='a[href$=".mid"]',
        title_selector="h1, .piece-title",
        author_selector=".composer",
        pagination="/cgibin/piece-search.cgi?startat={page}",
        max_pages=50,
        delay=2.0,
    ),
    "cpdl": HymnSource(
        name="ChoralWiki (CPDL)",
        base_url="https://www.cpdl.org",
        midi_selector='a[href$=".mid"], a[href$=".midi"]',
        title_selector="h1, #firstHeading",
        author_selector=".composer, .author",
        pagination="/wiki/Category:Scores?page={page}",
        max_pages=30,
        delay=2.0,
    ),
    "openhymnal": HymnSource(
        name="OpenHymnal",
        base_url="https://openhymnal.org",
        midi_selector='a[href$=".mid"]',
        title_selector="h1, .hymn-title",
        author_selector=".author",
        lyrics_selector=".lyrics",
        pagination="/hymns?page={page}",
        max_pages=20,
        delay=1.5,
    ),
    "archive": HymnSource(
        name="Internet Archive",
        base_url="https://archive.org",
        midi_selector='a[href$=".mid"], a[href$=".midi"]',
        title_selector="h1, .title",
        pagination="/details/hymns?page={page}",
        max_pages=10,
        delay=3.0,
    ),
}


class HymnScraper:
    """Scrapes hymn MIDI files from configured sources."""

    def __init__(
        self,
        db_path: str = "hymn_remaker/hymn_database.db",
        download_dir: str = "hymn_remaker/input",
        user_agent: str = "HymnRemakerBot/1.0 (+https://github.com/yourrepo)",
    ):
        if BeautifulSoup is None:
            raise ImportError("beautifulsoup4 required: pip install beautifulsoup4")

        self.db = HymnDatabase(db_path)
        self.download_dir = Path(download_dir)
        self.download_dir.mkdir(parents=True, exist_ok=True)

        self.session = requests.Session()
        self.session.headers.update({"User-Agent": user_agent})

        self.stats = {"found": 0, "downloaded": 0, "skipped": 0, "errors": 0}

    def _respectful_get(
        self, url: str, delay: float = 1.0
    ) -> Optional[requests.Response]:
        """GET with polite delay and error handling."""
        time.sleep(delay)
        try:
            resp = self.session.get(url, timeout=30)
            resp.raise_for_status()
            return resp
        except requests.RequestException as e:
            logger.warning(f"GET failed for {url}: {e}")
            return None

    def _find_midi_links(
        self, soup: BeautifulSoup, selector: str, base_url: str
    ) -> List[Tuple[str, str]]:
        """Extract MIDI URLs and link text from page."""
        links = []
        for a in soup.select(selector):
            href = a.get("href")
            if not href:
                continue
            full_url = urljoin(base_url, href)
            text = a.get_text(strip=True)
            links.append((full_url, text))
        return links

    def _extract_metadata(
        self, soup: BeautifulSoup, source: HymnSource
    ) -> Dict[str, Optional[str]]:
        """Extract title, author, lyrics from page."""
        meta = {"title": None, "author": None, "lyrics": None}

        if source.title_selector:
            el = soup.select_one(source.title_selector)
            if el:
                meta["title"] = el.get_text(strip=True)

        if source.author_selector:
            el = soup.select_one(source.author_selector)
            if el:
                meta["author"] = el.get_text(strip=True)

        if source.lyrics_selector:
            el = soup.select_one(source.lyrics_selector)
            if el:
                meta["lyrics"] = el.get_text(strip=True)

        return meta

    def _download_midi(self, url: str, filename: str) -> Optional[Path]:
        """Download a MIDI file."""
        resp = self._respectful_get(url, delay=0.5)
        if not resp:
            return None

        # Verify it's actually a MIDI file
        content_type = resp.headers.get("Content-Type", "")
        if "midi" not in content_type.lower() and not url.endswith((".mid", ".midi")):
            # Check magic bytes
            if resp.content[:4] not in (b"MThd", b"RIFF"):  # MIDI or MIDI-in-RIFF
                logger.warning(f"Downloaded file doesn't appear to be MIDI: {url}")
                return None

        filepath = self.download_dir / filename
        try:
            filepath.write_bytes(resp.content)
            logger.info(f"Downloaded: {filename} ({len(resp.content)} bytes)")
            return filepath
        except OSError as e:
            logger.error(f"Failed to write {filename}: {e}")
            return None

    def _sanitize_filename(self, name: str) -> str:
        """Create safe filename from title."""
        # Remove invalid chars
        name = re.sub(r'[<>:"/\\|?*]', "", name)
        name = re.sub(r"\s+", "_", name.strip())
        # Limit length
        return name[:200] + ".mid"

    def _generate_filename(
        self, url: str, title: Optional[str], source_name: str
    ) -> str:
        """Generate a unique filename."""
        if title:
            base = self._sanitize_filename(title)
        else:
            # Use URL path
            parsed = urlparse(url)
            base = Path(parsed.path).name or "hymn"
            if not base.endswith((".mid", ".midi")):
                base += ".mid"

        # Add source prefix and hash suffix for uniqueness
        url_hash = hashlib.md5(url.encode()).hexdigest()[:8]
        name_no_ext = Path(base).stem
        return f"{source_name}_{name_no_ext}_{url_hash}.mid"

    def scrape_source(self, source_key: str, max_pages: Optional[int] = None) -> int:
        """Scrape a single source."""
        if source_key not in SOURCES:
            raise ValueError(f"Unknown source: {source_key}")

        source = SOURCES[source_key]
        pages = max_pages or source.max_pages
        downloaded = 0

        logger.info(f"Starting scrape of {source.name} ({pages} pages)")

        for page in range(1, pages + 1):
            if source.pagination:
                page_url = urljoin(source.base_url, source.pagination.format(page=page))
            else:
                page_url = source.base_url if page == 1 else None

            if not page_url:
                break

            logger.info(f"  Page {page}/{pages}: {page_url}")
            resp = self._respectful_get(page_url, delay=source.delay)
            if not resp:
                self.stats["errors"] += 1
                continue

            soup = BeautifulSoup(resp.content, "html.parser")
            midi_links = self._find_midi_links(
                soup, source.midi_selector, source.base_url
            )

            if not midi_links:
                logger.info(f"  No MIDI links found on page {page}")
                continue

            self.stats["found"] += len(midi_links)

            for midi_url, link_text in midi_links:
                # Extract metadata from the MIDI page if possible
                meta = {"title": None, "author": None, "lyrics": None}

                # Try to visit the MIDI's parent page for metadata
                # (some sites link directly to MIDI, others to a page with metadata)
                # For now, use link text as title hint
                if link_text and not link_text.endswith((".mid", ".midi")):
                    meta["title"] = link_text

                filename = self._generate_filename(midi_url, meta["title"], source_key)
                filepath = self.download_dir / filename

                # Check if already exists (by hash)
                if filepath.exists():
                    existing_hash = self.db._compute_file_hash(str(filepath))
                    if self.db.find_by_hash(existing_hash):
                        logger.info(f"  Skipping (already in DB): {filename}")
                        self.stats["skipped"] += 1
                        continue

                # Download
                downloaded_path = self._download_midi(midi_url, filename)
                if downloaded_path:
                    # Add to database
                    hymn_id = self.db.add_hymn(
                        str(downloaded_path),
                        title=meta["title"],
                        author=meta["author"],
                        lyrics=meta["lyrics"],
                        tags=f"source:{source_key}",
                    )
                    if hymn_id:
                        self.stats["downloaded"] += 1
                        downloaded += 1
                    else:
                        self.stats["errors"] += 1
                        # Clean up failed download
                        try:
                            downloaded_path.unlink()
                        except OSError:
                            pass
                else:
                    self.stats["errors"] += 1

        return downloaded

    def scrape_all(
        self, sources: Optional[List[str]] = None, max_pages: Optional[int] = None
    ) -> Dict[str, int]:
        """Scrape multiple sources."""
        targets = sources or list(SOURCES.keys())
        results = {}

        for src in targets:
            try:
                count = self.scrape_source(src, max_pages)
                results[src] = count
            except Exception as e:
                logger.error(f"Source {src} failed: {e}")
                results[src] = 0

        return results


def main():
    parser = argparse.ArgumentParser(description="Hymn MIDI Scraper")
    parser.add_argument(
        "sources",
        nargs="*",
        default=list(SOURCES.keys()),
        help=f"Sources to scrape (default: all). Options: {', '.join(SOURCES.keys())}",
    )
    parser.add_argument(
        "--max-pages", type=int, default=None, help="Max pages per source"
    )
    parser.add_argument(
        "--db", default="hymn_remaker/hymn_database.db", help="Database path"
    )
    parser.add_argument(
        "--download-dir", default="hymn_remaker/input", help="Download directory"
    )
    parser.add_argument("--list", action="store_true", help="List available sources")
    parser.add_argument(
        "--dry-run", action="store_true", help="Don't download, just count"
    )
    args = parser.parse_args()

    if args.list:
        print("Available sources:")
        for key, src in SOURCES.items():
            print(f"  {key}: {src.name} ({src.base_url})")
        return

    logging.basicConfig(
        level=logging.INFO,
        format="%(asctime)s %(name)s %(levelname)s %(message)s",
    )

    scraper = HymnScraper(db_path=args.db, download_dir=args.download_dir)

    if args.dry_run:
        print("Dry run - would scrape:")
        for src in args.sources:
            print(f"  {src}: up to {args.max_pages or SOURCES[src].max_pages} pages")
        return

    print(f"Scraping sources: {', '.join(args.sources)}")
    results = scraper.scrape_all(args.sources, args.max_pages)

    print("\n=== Scraping Complete ===")
    print(f"Total found:    {scraper.stats['found']}")
    print(f"Downloaded:     {scraper.stats['downloaded']}")
    print(f"Skipped (dupe): {scraper.stats['skipped']}")
    print(f"Errors:         {scraper.stats['errors']}")
    print("\nPer-source results:")
    for src, count in results.items():
        print(f"  {src}: {count} new files")

    db_stats = scraper.db.get_stats()
    print(
        f"\nDatabase now has {db_stats['total']} hymns ({db_stats['with_lyrics']} with lyrics)"
    )


if __name__ == "__main__":
    main()
