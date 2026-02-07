const BobcoinBridge = require('./bobcoin');

async function testIntegration() {
    console.log('=== Starting Bobcoin Integration Test ===');
    console.log('Testing Hybrid Consensus: Proof of Useful Stake (PoUS)');
    
    const bridge = new BobcoinBridge();
    const myAddress = bridge.keypair.publicKey.toBase58();
    console.log(`Validator/Player Address: ${myAddress}\n`);

    console.log('--- Step 1: Proof of Storage (Validator Gating) ---');
    const storedFiles = ['file_hash_1', 'file_hash_2', 'file_hash_3'];
    const merkleRoot = bridge.generateStorageProof(storedFiles);
    
    if (merkleRoot) {
        const signature = await bridge.submitProofOfStorage(merkleRoot, 1024 * 1024 * 100); 
        console.log(`Storage Proof Submitted. Tx: ${signature}`);
        
        const isEligible = await bridge.isValidatorEligible(myAddress);
        console.log(`Is Validator Eligible? ${isEligible ? 'YES' : 'NO'}`);
    } else {
        console.error('Failed to generate storage proof');
    }
    console.log('\n');

    console.log('--- Step 2: Proof of Play (The Mint) ---');
    
    const mockProof = {
        playerId: myAddress,
        publicValues: {
            perfects: 50,
            greats: 10,
            score: 5500 
        },
        proofBytes: 'mock_zk_bytes_xyz'
    };

    try {
        const result = await bridge.mintTokensForGameScore(myAddress, mockProof);
        if (result.signature) {
            console.log(`Success! Minted ${result.amount} BOB tokens.`);
            console.log(`Mint Tx: ${result.signature}`);
        } else {
            console.log('No tokens minted (score too low?)');
        }
    } catch (error) {
        console.error('Minting failed:', error.message);
    }
    
    console.log('\n=== Integration Test Complete ===');
}

testIntegration().catch(console.error);