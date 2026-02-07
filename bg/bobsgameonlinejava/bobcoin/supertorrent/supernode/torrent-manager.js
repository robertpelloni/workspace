/**
 * MockTorrentManager
 * Simulates a BitTorrent client managing stored files.
 */
class MockTorrentManager {
    constructor() {
        this.storedFiles = new Map();
    }

    /**
     * Simulates downloading/seeding a new file.
     * @param {string} fileHash
     * @param {number} sizeBytes
     */
    addFile(fileHash, sizeBytes) {
        this.storedFiles.set(fileHash, sizeBytes);
        console.log(`[TorrentManager] Added file: ${fileHash} (${(sizeBytes / 1024 / 1024).toFixed(2)} MB)`);
    }

    /**
     * Returns the list of all stored file hashes.
     * @returns {string[]}
     */
    getStoredFiles() {
        return Array.from(this.storedFiles.keys());
    }

    /**
     * Returns the total size of storage being provided.
     * @returns {number}
     */
    getTotalStorageSize() {
        let total = 0;
        for (const size of this.storedFiles.values()) {
            total += size;
        }
        return total;
    }
}

module.exports = MockTorrentManager;
