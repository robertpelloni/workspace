# Bobcoin: Hybrid Proof of Useful Stake Ecosystem

Bobcoin is a next-generation blockchain project implementing **Proof of Useful Stake (PoUS)**. It combines decentralized file storage with Zero-Knowledge verification of gameplay/computation to create a useful, fun, and secure network.

## Repository Structure

*   **`supertorrent/`**: The Node.js implementation of the Supernode (Validator).
    *   Handles **Proof of Storage**: Gating validator access based on stored file proofs.
    *   Handles **Token Minting**: verifying ZK proofs from the game layer.
*   **`proof-of-play/`**: The Rust SP1 Zero-Knowledge Circuit (The Mint).
    *   Generates ZK-SNARKs proving that a player achieved a specific score without cheating.

## Architecture

1.  **The Filter (Storage)**: Nodes store data (torrents) to earn the right to validate.
2.  **The Mint (Play)**: Users play games, generating ZK proofs of their scores. The blockchain validates these proofs and mints tokens accordingly.

## Status (Prototype)
*   **Consensus Logic**: Implemented in `supertorrent/supernode/blockchain/bobcoin.js`.
*   **ZK Circuits**: Defined in `proof-of-play/src/main.rs`.
*   **Integration**: Functional prototype running with mocked on-chain state for rapid testing.

## Quick Start
Run the full integration test:
```bash
node supertorrent/supernode/blockchain/test-integration.js
```
