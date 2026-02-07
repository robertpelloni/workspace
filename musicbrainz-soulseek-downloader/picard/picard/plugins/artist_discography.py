# -*- coding: utf-8 -*-

PLUGIN_NAME = 'Artist Discography & Bandcamp'
PLUGIN_AUTHOR = 'Jules'
PLUGIN_DESCRIPTION = 'Load all albums for an artist and open Bandcamp links. Includes Soulseek integration.'
PLUGIN_VERSION = '0.6'
PLUGIN_API_VERSIONS = ['2.9', '2.10', '2.11', '3.0']
PLUGIN_LICENSE = 'GPL-2.0-or-later'
PLUGIN_LICENSE_URL = 'https://www.gnu.org/licenses/gpl-2.0.html'

"""
Artist Discography & Bandcamp Plugin

This plugin provides tools to load an artist's full discography from MusicBrainz and open Bandcamp pages.

Features:
- **Load Artist Discography**: Context menu action (on Cluster/File/Album) to fetch all releases for the artist from MusicBrainz and load them into Picard.
- **Load Artist Discography (Tool)**: Main menu tool to search for an artist by name and load their discography.
- **Open on Bandcamp**: Context menu action (on Album) to open the Bandcamp page for the release. It uses Bandcamp URLs found in MusicBrainz relationships or falls back to a search.
- **Search on Soulseek**: Context menu action (on Album) to search for the album on Soulseek. Supports native search and download via `aioslsk`.

Requirements:
    This plugin requires the `aioslsk` library for Soulseek integration.
    To install:
        pip install aioslsk

    If the library is not found, the Soulseek features will default to a clipboard helper.
"""

import asyncio
import os
from functools import partial
from PyQt6 import QtWidgets, QtCore, QtGui
from picard import log, config
from picard.tagger import Tagger
from picard.album import Album
from picard.cluster import Cluster
from picard.file import File
from picard.config import TextOption
from picard.extension_points.item_actions import (
    register_album_action,
    register_cluster_action,
    register_file_action,
    BaseAction
)
from picard.extension_points.metadata import register_album_metadata_processor
from picard.extension_points.plugin_tools_menu import register_tools_menu_action
from picard.extension_points.options_pages import register_options_page
from picard.ui.options import OptionsPage
from picard.ui.util import FileDialog
from picard.i18n import gettext as _
from picard.util import webbrowser2

# Check for aioslsk availability
try:
    import aioslsk
    from aioslsk.client import SoulSeekClient
    from aioslsk.settings import Settings as SlskSettings, CredentialsSettings, SharesSettings
    from aioslsk.transfer.state import TransferState
    from aioslsk.transfer.model import TransferDirection
    from aioslsk.commands import PeerGetDirectoryContentCommand
    from aioslsk.protocol.primitives import AttributeKey
    HAS_AIOSLSK = True
except ImportError:
    HAS_AIOSLSK = False
    log.warning("Artist Discography Plugin: 'aioslsk' library not found. Soulseek integration will be limited to clipboard fallback.")

# --- Shared Loading Logic ---

def load_discography(tagger, artist_id):
    """
    Load all releases for a given artist ID into Picard.
    Initiates a recursive fetch of release pages from MusicBrainz.
    """
    log.info(f"Loading discography for artist ID: {artist_id}")
    _fetch_page(tagger, artist_id, offset=0)

def _fetch_page(tagger, artist_id, offset):
    tagger.webservice.mb_api.browse_releases(
        partial(_handle_response, tagger=tagger, artist_id=artist_id, offset=offset),
        artist=artist_id,
        limit=100,
        offset=offset,
        inc=('media',)
    )

def _handle_response(document, http, error, tagger, artist_id, offset):
    if error:
        log.error(f"Load Discography Error: {http.errorString()}")
        return

    releases = document.get('releases', [])
    release_count = document.get('release-count', 0)

    log.info(f"Loaded {len(releases)} releases (Offset: {offset}, Total: {release_count})")

    for release in releases:
        release_id = release['id']
        tagger.load_album(release_id)

    # Check for next page
    next_offset = offset + len(releases)
    if next_offset < release_count and len(releases) > 0:
        _fetch_page(tagger, artist_id, next_offset)
    else:
        log.info("Finished loading discography.")


# --- Metadata Processor for Bandcamp URLs ---

def bandcamp_url_handler(album, metadata, release_node):
    """Extract Bandcamp URLs from release relations and store in metadata."""
    if not release_node:
        return

    relations = release_node.get('relations', [])
    for relation in relations:
        if relation.get('target-type') == 'url':
            url_resource = relation.get('url', {}).get('resource', '')
            if 'bandcamp.com' in url_resource:
                # Store the first one found
                metadata['~bandcamp_url'] = url_resource
                return

register_album_metadata_processor(bandcamp_url_handler)


# --- Context Menu Action: Load Discography ---

class LoadDiscography(BaseAction):
    NAME = 'Load Artist Discography'

    def callback(self, objects):
        if not objects:
            return

        item = objects[0]
        artist_id = None

        if isinstance(item, Cluster):
            # Cluster metadata is a bit different, checking common fields
            if item.metadata['musicbrainz_albumartistid']:
                artist_id = item.metadata['musicbrainz_albumartistid']
        elif isinstance(item, File):
            artist_id = item.metadata['musicbrainz_albumartistid'] or item.metadata['musicbrainz_artistid']
        elif isinstance(item, Album): # Also allow running from an existing Album
             artist_id = item.metadata['musicbrainz_albumartistid']

        # Handle multi-value IDs (take the first one)
        if isinstance(artist_id, list):
            artist_id = artist_id[0]

        # Split if multiple IDs in string
        if artist_id and ';' in artist_id:
             artist_id = artist_id.split(';')[0].strip()

        if not artist_id:
            log.error("Load Discography: No Artist ID found in selected item.")
            return

        load_discography(Tagger.instance(), artist_id)


register_cluster_action(LoadDiscography())
register_file_action(LoadDiscography())
register_album_action(LoadDiscography())


# --- Main Menu Action: Load Discography ---

class LoadDiscographyTool(BaseAction):
    NAME = 'Load Artist Discography...'

    def callback(self, objects):
        # objects is ignored for main menu actions usually
        tagger = Tagger.instance()
        text, ok = QtWidgets.QInputDialog.getText(
            tagger.window,
            "Load Discography",
            "Enter Artist Name:"
        )
        if ok and text:
            self.search_artist(text)

    def search_artist(self, query):
        Tagger.instance().webservice.mb_api.find_artists(
            self._handle_search_response,
            query=query,
            limit=10
        )

    def _handle_search_response(self, document, http, error):
        tagger = Tagger.instance()
        if error:
            log.error(f"Artist Search Error: {http.errorString()}")
            QtWidgets.QMessageBox.critical(tagger.window, "Error", f"Search failed: {http.errorString()}")
            return

        artists = document.get('artists', [])
        if not artists:
            QtWidgets.QMessageBox.information(tagger.window, "Load Discography", "No artists found.")
            return

        # Prepare list for selection
        items = []
        for artist in artists:
            name = artist.get('name', 'Unknown')
            disambiguation = artist.get('disambiguation', '')
            area = artist.get('area', {}).get('name', '')
            desc = f"{name}"
            details = []
            if disambiguation: details.append(disambiguation)
            if area: details.append(area)
            if details:
                desc += f" ({', '.join(details)})"
            items.append(desc)

        item, ok = QtWidgets.QInputDialog.getItem(
            tagger.window,
            "Select Artist",
            "Choose an artist:",
            items,
            0,
            False
        )

        if ok and item:
            index = items.index(item)
            selected_artist = artists[index]
            artist_id = selected_artist['id']
            load_discography(tagger, artist_id)

register_tools_menu_action(LoadDiscographyTool())


# --- Context Menu Action: Open Bandcamp ---

class OpenBandcamp(BaseAction):
    NAME = 'Open on Bandcamp'

    def callback(self, objects):
        for item in objects:
            if isinstance(item, Album):
                self._open_album(item)

    def _open_album(self, album):
        url = album.metadata['~bandcamp_url']
        if url:
            log.info(f"Opening Bandcamp URL: {url}")
            webbrowser2.open(url)
        else:
            # Fallback search
            artist = album.metadata['albumartist']
            title = album.metadata['album']
            if artist and title:
                search_query = f"{artist} {title} bandcamp"
                # Simple google search or bandcamp search
                encoded_query = QtCore.QUrl.toPercentEncoding(search_query).data().decode('utf-8')
                url = f"https://bandcamp.com/search?q={encoded_query}"
                log.info(f"Bandcamp URL not found, searching: {url}")
                webbrowser2.open(url)
            else:
                log.warning("Cannot search Bandcamp: Missing artist or album title.")

register_album_action(OpenBandcamp())

# --- Soulseek Integration ---

# Register Options
TextOption('setting', 'soulseek_username', '')
TextOption('setting', 'soulseek_password', '')
TextOption('setting', 'soulseek_download_dir', '')

# Options Page
class SoulseekOptionsPage(OptionsPage):
    NAME = 'soulseek_options'
    TITLE = 'Soulseek'
    PARENT = 'plugins'

    OPTIONS = (
        ('soulseek_username', ''),
        ('soulseek_password', ''),
        ('soulseek_download_dir', ''),
    )

    def __init__(self, parent=None):
        super().__init__(parent=parent)
        self.box = QtWidgets.QVBoxLayout(self)

        self.username_label = QtWidgets.QLabel(_("Soulseek Username:"))
        self.box.addWidget(self.username_label)
        self.username_edit = QtWidgets.QLineEdit()
        self.box.addWidget(self.username_edit)

        self.password_label = QtWidgets.QLabel(_("Soulseek Password:"))
        self.box.addWidget(self.password_label)
        self.password_edit = QtWidgets.QLineEdit()
        self.password_edit.setEchoMode(QtWidgets.QLineEdit.EchoMode.Password)
        self.box.addWidget(self.password_edit)

        self.dir_label = QtWidgets.QLabel(_("Download Directory:"))
        self.box.addWidget(self.dir_label)

        self.dir_layout = QtWidgets.QHBoxLayout()
        self.dir_edit = QtWidgets.QLineEdit()
        self.dir_button = QtWidgets.QPushButton("...")
        self.dir_button.clicked.connect(self.select_directory)
        self.dir_layout.addWidget(self.dir_edit)
        self.dir_layout.addWidget(self.dir_button)
        self.box.addLayout(self.dir_layout)

        if not HAS_AIOSLSK:
            self.warning_label = QtWidgets.QLabel(_("<b>Note:</b> 'aioslsk' library is missing. Native search is disabled."))
            self.box.addWidget(self.warning_label)

        self.box.addStretch(1)

    def select_directory(self):
        path = FileDialog.getExistingDirectory(
            parent=self,
            directory=self.dir_edit.text(),
        )
        if path:
             self.dir_edit.setText(path)

    def load(self):
        self.username_edit.setText(config.setting['soulseek_username'])
        self.password_edit.setText(config.setting['soulseek_password'])
        self.dir_edit.setText(config.setting['soulseek_download_dir'])

    def save(self):
        config.setting['soulseek_username'] = self.username_edit.text()
        config.setting['soulseek_password'] = self.password_edit.text()
        config.setting['soulseek_download_dir'] = self.dir_edit.text()

register_options_page(SoulseekOptionsPage)


# Soulseek Service (Threaded Worker)
class SoulseekService(QtCore.QThread):
    results_found = QtCore.pyqtSignal(list, object)
    download_complete = QtCore.pyqtSignal(str, object)
    folder_download_started = QtCore.pyqtSignal(str, object)
    service_error = QtCore.pyqtSignal(str, object)

    _instance = None

    @classmethod
    def instance(cls):
        if cls._instance is None:
            cls._instance = SoulseekService()
        return cls._instance

    def __init__(self):
        super().__init__()
        self.loop = None
        self.client = None
        self.username = ""
        self.password = ""
        self.download_dir = ""
        self.running = False

    def configure(self, username, password, download_dir):
        self.username = username
        self.password = password
        self.download_dir = download_dir

    def run(self):
        if not HAS_AIOSLSK:
             return

        self.loop = asyncio.new_event_loop()
        asyncio.set_event_loop(self.loop)
        self.loop.run_forever()

    def start_service(self):
        if not self.isRunning():
            self.start()

    def perform_search(self, query, context):
        if self.loop:
            asyncio.run_coroutine_threadsafe(self._do_search(query, context), self.loop)

    def perform_download(self, user, filename, context):
        if self.loop:
            asyncio.run_coroutine_threadsafe(self._do_download(user, filename, context), self.loop)

    def perform_download_folder(self, user, folder_path, context):
        if self.loop:
            asyncio.run_coroutine_threadsafe(self._do_download_folder(user, folder_path, context), self.loop)

    async def _ensure_client(self):
        if self.client:
            return self.client

        settings = SlskSettings(
            credentials=CredentialsSettings(
                username=self.username,
                password=self.password
            ),
            shares=SharesSettings(
                download=self.download_dir
            )
        )
        self.client = SoulSeekClient(settings)
        await self.client.start()
        await self.client.login()
        return self.client

    async def _do_search(self, query, context):
        try:
            client = await self._ensure_client()
            results = []
            async for result in client.search(query):
                results.append(result)
                if len(results) >= 50:
                    break
            self.results_found.emit(results, context)
        except Exception as e:
            self.service_error.emit(str(e), context)

    async def _do_download(self, user, filename, context):
        try:
            client = await self._ensure_client()
            await self._download_file_internal(client, user, filename, context)
        except Exception as e:
            self.service_error.emit(str(e), context)

    async def _download_file_internal(self, client, user, filename, context):
        transfer = await client.transfer_manager.download(user, filename)
        # Monitor progress
        while not transfer.state.is_complete:
                # Check for failures
                if transfer.state.is_aborted or transfer.state.is_failed:
                    self.service_error.emit(f"Download failed: {filename}", context)
                    return
                await asyncio.sleep(1)

        if transfer.local_path:
                self.download_complete.emit(transfer.local_path, context)

    async def _do_download_folder(self, user, folder_path, context):
        try:
            client = await self._ensure_client()
            self.folder_download_started.emit(folder_path, context)

            # Fetch directory listing
            cmd = PeerGetDirectoryContentCommand(user, folder_path)
            response = await client.execute(cmd)

            # Response is list[DirectoryData], we assume the structure matches the folder we asked for
            # The structure is usually flat or hierarchical depending on server response
            # But the 'files' field in DirectoryData is what we need

            # Flatten or find relevant files
            downloads_queued = 0
            for dir_data in response:
                # Construct full path. DirectoryData.name is typically the folder name.
                # If we requested "A\B", we expect files in that folder.
                # Just downloading files in the immediate folder response for now.

                for file_info in dir_data.files:
                    # Simple filter for audio/image extensions
                    ext = file_info.extension.lower()
                    if ext in ('mp3', 'flac', 'm4a', 'ogg', 'wav', 'jpg', 'jpeg', 'png'):
                        full_remote_path = f"{folder_path}\\{file_info.filename}"
                        # Check separator (Soulseek usually sends backslash)
                        if '\\' not in folder_path and '/' in folder_path:
                             full_remote_path = f"{folder_path}/{file_info.filename}"

                        # Queue download (async, don't wait for each one sequentially here)
                        asyncio.create_task(self._download_file_internal(client, user, full_remote_path, context))
                        downloads_queued += 1

            if downloads_queued == 0:
                self.service_error.emit(f"No audio files found in folder: {folder_path}", context)

        except Exception as e:
            self.service_error.emit(f"Folder download error: {e}", context)


# Custom Tree Item for Numeric Sorting
class SoulseekResultItem(QtWidgets.QTreeWidgetItem):
    def __lt__(self, other):
        column = self.treeWidget().sortColumn()
        text1 = self.text(column)
        text2 = other.text(column)

        # Sort by numeric value for Bitrate(2), Size (3), Speed (4), and Queue (5)
        if column in (2, 3, 4, 5):
            try:
                return float(text1) < float(text2)
            except ValueError:
                return text1 < text2
        return text1 < text2

# Soulseek Search Dialog
class SoulseekSearchDialog(QtWidgets.QDialog):
    def __init__(self, parent, initial_query, target_album=None):
        super().__init__(parent)
        self.target_album = target_album
        self.context_id = object()
        self.setWindowTitle(_("Soulseek Search"))
        self.resize(900, 400)
        self.layout = QtWidgets.QVBoxLayout(self)

        # Search Input
        self.search_layout = QtWidgets.QHBoxLayout()
        self.query_edit = QtWidgets.QLineEdit(initial_query)
        self.search_button = QtWidgets.QPushButton(_("Search"))
        self.search_button.clicked.connect(self.start_search)
        self.search_layout.addWidget(self.query_edit)
        self.search_layout.addWidget(self.search_button)
        self.layout.addLayout(self.search_layout)

        # Results List
        self.results_list = QtWidgets.QTreeWidget()
        self.results_list.setHeaderLabels([_("Filename"), _("User"), _("Bitrate"), _("Size (MB)"), _("Speed (kB/s)"), _("In Queue")])
        self.results_list.setSortingEnabled(True)
        self.results_list.itemDoubleClicked.connect(self.start_download)
        self.results_list.setContextMenuPolicy(QtCore.Qt.ContextMenuPolicy.CustomContextMenu)
        self.results_list.customContextMenuRequested.connect(self.show_context_menu)
        self.layout.addWidget(self.results_list)

        # Status
        self.status_label = QtWidgets.QLabel(_("Ready. Double-click a result to download."))
        self.layout.addWidget(self.status_label)

        # Service Setup
        self.service = SoulseekService.instance()
        self.service.results_found.connect(self.display_results)
        self.service.download_complete.connect(self.on_download_complete)
        self.service.folder_download_started.connect(self.on_folder_download_started)
        self.service.service_error.connect(self.on_error)

        # Configure service
        username = config.setting['soulseek_username']
        password = config.setting['soulseek_password']
        download_dir = config.setting['soulseek_download_dir']
        self.service.configure(username, password, download_dir)
        self.service.start_service()

    def start_search(self):
        query = self.query_edit.text()
        self.results_list.clear()
        self.status_label.setText(_("Searching..."))
        self.search_button.setEnabled(False)
        self.service.perform_search(query, self.context_id)

    def display_results(self, results, context):
        if context is not self.context_id:
            return

        self.search_button.setEnabled(True)
        if not results:
             self.status_label.setText(_("No results found."))
             return

        for res in results:
            try:
                filename = getattr(res, 'filename', str(res))
                user = getattr(res, 'user', 'Unknown')

                # Get Attributes
                attrs = res.get_attribute_map()
                bitrate = attrs.get(AttributeKey.BITRATE, 0)

                size_bytes = getattr(res, 'size', 0)
                size_mb = f"{size_bytes / (1024 * 1024):.2f}"

                speed_bytes = getattr(res, 'speed', 0)
                speed_kb = f"{speed_bytes / 1024:.0f}"

                slots = str(getattr(res, 'slots', '?'))
                if getattr(res, 'is_free', False):
                    slots += " (Free)"

                item = SoulseekResultItem([filename, user, str(bitrate), size_mb, speed_kb, slots])

                # Quality Highlighting
                ext = getattr(res, 'extension', '').lower()
                font = item.font(0)

                if ext in ('flac', 'wav') or bitrate >= 320:
                    # High Quality: Bold + Greenish tint
                    font.setBold(True)
                    for i in range(6):
                        item.setFont(i, font)
                        item.setForeground(i, QtGui.QBrush(QtGui.QColor(0, 100, 0))) # Dark Green
                elif bitrate > 0 and bitrate < 192 and ext == 'mp3':
                    # Low Quality: Red tint
                    for i in range(6):
                        item.setForeground(i, QtGui.QBrush(QtGui.QColor(150, 0, 0))) # Dark Red

                item.setData(0, QtCore.Qt.ItemDataRole.UserRole, filename)
                item.setData(1, QtCore.Qt.ItemDataRole.UserRole, user)
                self.results_list.addTopLevelItem(item)
            except Exception as e:
                # log.debug(f"Row error: {e}")
                continue
        self.status_label.setText(_("Found {} results").format(len(results)))

    def start_download(self, item, column):
        self._initiate_download(item, folder=False)

    def show_context_menu(self, position):
        item = self.results_list.itemAt(position)
        if not item:
            return

        menu = QtWidgets.QMenu()
        dl_action = menu.addAction(_("Download File"))
        dl_folder_action = menu.addAction(_("Download Album Folder"))

        action = menu.exec(self.results_list.viewport().mapToGlobal(position))

        if action == dl_action:
            self._initiate_download(item, folder=False)
        elif action == dl_folder_action:
            self._initiate_download(item, folder=True)

    def _initiate_download(self, item, folder=False):
        filename = item.data(0, QtCore.Qt.ItemDataRole.UserRole)
        user = item.data(1, QtCore.Qt.ItemDataRole.UserRole)

        if not config.setting['soulseek_download_dir']:
             QtWidgets.QMessageBox.warning(self, _("Config Error"), _("Please set a download directory in Options."))
             return

        if folder:
            # Extract folder path
            # Soulseek usually sends Windows-style paths
            folder_path = os.path.dirname(filename)
            # Handle potential mix if platform differs from remote, but usually slsk preserves structure string
            if not folder_path and '\\' in filename:
                 folder_path = filename.rsplit('\\', 1)[0]

            self.status_label.setText(_("Requesting folder download: {}").format(folder_path))
            self.service.perform_download_folder(user, folder_path, self.context_id)
        else:
            self.status_label.setText(_("Downloading: {}").format(filename))
            self.service.perform_download(user, filename, self.context_id)

    def on_download_complete(self, path, context):
        if context is not self.context_id:
            return

        # Add to Picard and try to match to target album
        tagger = Tagger.instance()
        tagger.add_files([path], target=self.target_album)
        # Update status quietly as multiple files might be coming in
        self.status_label.setText(_("Downloaded: {}").format(os.path.basename(path)))

    def on_folder_download_started(self, folder, context):
        if context is not self.context_id:
            return

        QtWidgets.QMessageBox.information(self, _("Download Started"),
            _("Folder download started:\n{}\n\nFiles will automatically appear in Picard as they finish.").format(folder))

    def on_error(self, msg, context):
        if context is not self.context_id:
            return

        self.status_label.setText(_("Error: {}").format(msg))
        self.search_button.setEnabled(True)


# Context Menu Action
class SearchSoulseek(BaseAction):
    NAME = 'Search on Soulseek'

    def callback(self, objects):
        for item in objects:
            if isinstance(item, Album):
                self._search_soulseek(item)

    def _search_soulseek(self, album):
        tagger = Tagger.instance()
        artist = album.metadata['albumartist']
        title = album.metadata['album']

        if not artist or not title:
             log.warning("Soulseek search: Missing artist or album title.")
             return

        query = f"{artist} {title}"
        username = config.setting['soulseek_username']
        password = config.setting['soulseek_password']

        if HAS_AIOSLSK and username and password:
            dialog = SoulseekSearchDialog(tagger.window, query, target_album=album)
            dialog.exec()
        else:
            # Fallback
            QtWidgets.QApplication.clipboard().setText(query)
            msg = f"Copied to clipboard: {query}"
            if HAS_AIOSLSK and (not username or not password):
                msg += " (Configure credentials in Options for native search)"
            tagger.window.statusBar().showMessage(msg, 5000)

register_album_action(SearchSoulseek())
