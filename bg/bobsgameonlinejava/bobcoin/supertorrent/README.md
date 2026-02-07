# Supertorrent Node - Bobcoin Validator

This repository contains the Node.js implementation of a **Bobcoin Supernode**, which serves as a Validator in the Proof of Useful Stake (PoUS) consensus.

## Hybrid Consensus Architecture

Bobcoin uses a hybrid consensus mechanism:

1.  **Proof of Useful Stake (The Filter)**:
    *   Nodes must store files for the network to qualify as validators.
    *   **Mechanism**: Nodes generate a Merkle Root of their stored files and submit it on-chain (mocked in prototype).
    *   **Goal**: Replaces wasteful hashing (PoW) with useful storage.

2.  **Proof of Play (The Mint)**:
    *   Tokens are minted by "playing" (verifying computations or actual gameplay).
    *   **Mechanism**: Uses ZK proofs (via SP1) to verify game scores without revealing inputs.
    *   **Goal**: Distributes tokens based on skill/effort, verified by the blockchain.

## Getting Started

### Prerequisites
*   Node.js (v18+)

### Installation
```bash
npm install
```
*(Note: For the prototype, dependencies are mocked if not found, so you can run it immediately)*

### Running the Node & Tests
Run the integration test to simulate the full lifecycle (Storage Proof -> Validator Check -> Game Proof -> Token Mint):

```bash
node supertorrent/supernode/blockchain/test-integration.js
```

## Structure
*   `blockchain/bobcoin.js`: Core bridge logic connecting the node to the Solana/Light Protocol network (mocked).
*   `blockchain/test-integration.js`: Simulation script demonstrating the consensus flow.
