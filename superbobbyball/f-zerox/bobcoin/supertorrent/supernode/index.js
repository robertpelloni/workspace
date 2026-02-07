const BobcoinBridge = require('./blockchain/bobcoin');
const MockTorrentManager = require('./torrent-manager');

const torrentManager = new MockTorrentManager();
const bobcoinBridge = new BobcoinBridge();
const myAddress = bobcoinBridge.keypair.publicKey.toBase58();

console.log('=== Supertorrent Node Startup ===');
console.log(`Validator Address: ${myAddress}`);

torrentManager.addFile('hash_ubuntu_iso', 4 * 1024 * 1024 * 1024); 
torrentManager.addFile('hash_wiki_dump', 20 * 1024 * 1024 * 1024); 
torrentManager.addFile('hash_big_buck_bunny', 500 * 1024 * 1024); 

async function runProofOfStorageLoop() {
    console.log('\n[Supernode] Starting Proof of Storage Loop...');

    const storedFiles = torrentManager.getStoredFiles();
    const totalSize = torrentManager.getTotalStorageSize();

    if (storedFiles.length === 0) {
        console.log('[Supernode] No files stored. Skipping proof.');
        return;
    }

    console.log(`[Supernode] Generating proof for ${storedFiles.length} files (${(totalSize / 1024 / 1024).toFixed(2)} MB total)...`);
    
    const merkleRoot = bobcoinBridge.generateStorageProof(storedFiles);
    
    if (merkleRoot) {
        try {
            const signature = await bobcoinBridge.submitProofOfStorage(merkleRoot, totalSize);
            console.log(`[Supernode] Proof submitted successfully! Tx: ${signature}`);
            
            const isEligible = await bobcoinBridge.isValidatorEligible(myAddress);
            console.log(`[Supernode] Validator Status: ${isEligible ? 'ACTIVE' : 'INACTIVE'}`);
        } catch (error) {
            console.error('[Supernode] Failed to submit proof:', error);
        }
    }
}

runProofOfStorageLoop();