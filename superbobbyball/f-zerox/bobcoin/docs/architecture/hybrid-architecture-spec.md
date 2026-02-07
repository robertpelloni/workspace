# Bobcoin Hybrid Architecture Specification v0.1

## 1. Executive Summary
Bobcoin is a high-throughput, privacy-focused blockchain designed to power a decentralized arcade economy. It integrates a physical "Proof of Play" mechanism (arcade game scores) with a high-performance ledger and a P2P content delivery network (Supertorrent).

**Core Philosophy**: "Sweat Equity." Value is created through physical effort (gameplay) and utility (serving content), not just burning electricity.

## 2. System Overview

The architecture is a hybrid model composing best-in-class components from existing ecosystems:

| Component | Technology Choice | Rationale |
|-----------|-------------------|-----------|
| **Core Ledger** | **Solana (Modified)** | Industry-leading throughput (65k+ TPS), parallel execution (Sealevel), and low latency for real-time arcade payments. |
| **Consensus (Sybil)** | **RandomX (Monero)** | CPU-optimized Proof of Work. Prevents ASIC centralization, allowing arcade machine CPUs to serve as validators/miners. |
| **Consensus (Reward)**| **ZK Proof of Play** | Rewards based on verified game scores. "Mining" happens by playing games. |
| **Privacy** | **Light Protocol (ZK Compression)** | UTXO-like privacy on top of Solana accounts. Fast, cheap, compliant privacy for user scores and balances. |
| **Storage/Bridge** | **Supertorrent P2P** | A BitTorrent-like supernode layer that stores game assets. Nodes earn Bobcoin for serving data. |

## 3. Detailed Architecture

### 3.1 The Ledger: Solana Fork (The "Bobchain")
We will fork the Solana codebase (`research/solana`) to leverage its Sealevel runtime and Pipeline architecture.

**Modifications Required:**
1.  **Replace Proof of History (PoH) / Tower BFT entry condition**:
    *   Instead of standard PoS leadership schedule, we introduce a **RandomX Difficulty Check**.
    *   Block producers must submit a valid RandomX hash to propose a block (or a hybrid PoS/PoW model where stake weight is boosted by Hashrate).
    *   *Goal*: Allow arcade machines (Consumer Hardware) to participate in block production without massive stake.

2.  **Native "Arcade" Transaction Type**:
    *   Optimized instruction path for submitting `ScoreProof` packets.
    *   High priority, low fee lane for verified arcade machines.

### 3.2 Proof of Play (PoP) & ZK Circuits
This is the novel mining mechanism.

*   **The Problem**: How to trust a high score from a machine?
*   **The Solution**: Zero-Knowledge Proofs + Hardware Attestation.
    *   **The Circuit**: A ZK circuit (written in o1js or SP1) that takes game inputs (frame data, button presses) and hash of the game ROM.
    *   **Output**: A proof $\pi$ asserting "Player X achieved Score Y on Game Z with valid inputs."
    *   **Verification**: The Bobchain verifies $\pi$. If valid, mints BOB tokens to Player X and Machine Owner.

### 3.3 Privacy Layer (Light Protocol Integration)
Arcade players may not want their entire location history and spending habits public.

*   **Implementation**: Integrate Light Protocol's ZK Compression.
*   **Mechanism**: State is compressed into a Merkle root stored on the main Solana ledger. Users update their private state (UTXOs) via ZK validity proofs.
*   **Experience**: Fast as Solana, private as Cash.

### 3.4 The Supertorrent Bridge
Connecting the file sharing layer to the value layer.

*   **Role**: Bobcoin acts as the incentive layer for Supertorrent.
*   **Mechanism**:
    *   **Storage Deals**: Users pay BOB to pin game ROMs/Assets.
    *   **Retrieval**: Supernodes (Supertorrent peers) serve files.
    *   **Settlement**: Payment channels (Lightning-style) open between leecher and seeder, settling on Bobcoin.

## 4. Hardware Requirements (Arcade Nodes)
*   **CPU**: Ryzen/Intel (Consumer grade okay due to RandomX).
*   **RAM**: 16GB+ (for Solana runtime + RandomX dataset).
*   **TPM**: Trusted Platform Module for machine identity attestation (preventing emulated spoofing).

## 5. Roadmap
1.  **Phase 1: The Core (Current)** - Fork Solana, strip PoS, implement RandomX testnet.
2.  **Phase 2: The Bridge** - Connect Supertorrent Node.js client to Bobchain.
3.  **Phase 3: The Game** - Build "StepMania" connector generating ZK Proofs of scores.
