# Bobcoin Architecture: Detailed Technical Specification v1.0

## 1. System Components & Technology Stack

Bobcoin is a hybrid blockchain ecosystem designed for high-throughput gaming payments, decentralized storage, and physical proof-of-work.

### 1.1 The Core Chain (The "Bobchain")
*   **Base Codebase**: Solana v2.0 (Rust)
*   **Consensus Mechanism**: **Proof of Useful Stake (PoUS)**
    *   **The Spine (Consensus)**: Standard Solana DPoS (Tower BFT) for sub-second finality.
    *   **The Filter (Validator Eligibility)**: **Proof of Storage**.
        *   *Requirement*: To earn validator fees, nodes must prove they are seeding active Supertorrent files (storage capacity > stake weight).
    *   **The Mint (Distribution)**: **Proof of Play**.
        *   *Role*: Token generation event. Validated gameplay mints new tokens; it does not secure block ordering.
*   **Runtime**: Sealevel (Parallel Smart Contracts).
*   **Privacy Layer**: Light Protocol (ZK Compression).
    *   *Role*: Private UTXO-like state for user balances and game scores.
*   **Token Standard**: SPL Token + Compressed Token Extensions.

### 1.2 The "Proof of Play" (PoP) Layer
*   **Proving System**: **Succinct SP1 (RISC-V zkVM)**.
    *   *Input*: Game log (input events, timestamps, RNG seed).
    *   *Logic*: Re-execution of StepMania game engine logic in Rust.
    *   *Output*: ZK Proof $\pi$ asserting "Score $S$ was achieved with valid inputs $I$ on Song $M$."
*   **Verification**: On-chain via `sp1-solana` verifier program.
*   **Hardware Target**: Consumer Arcade PCs (Intel/AMD, 16GB RAM).
    *   *Fallback*: Succinct Prover Network (if local proving > 60s).

### 1.3 The Storage Bridge (Supertorrent)
*   **Framework**: Node.js (Supertorrent peer).
*   **Bridge Logic**: `BobcoinBridge` class.
*   **Role**:
    *   Manages Storage Deals (file pinning).
    *   Submits Proof-of-Storage (Merkle proofs).
    *   Handles P2P Payments (Payment Channels).

---

## 2. "Proof of Play" Implementation Details

### 2.1 The Circuit (SP1 Rust Program)
Unlike traditional circuits, we write standard Rust code that simulates the game engine:

```rust
// pseudo-code for SP1 program
struct GameInput {
    arrows: Vec<ArrowEvent>,
    song_hash: [u8; 32],
    rng_seed: u64,
}

fn main() {
    let inputs = sp1_zkvm::io::read::<GameInput>();
    
    // 1. Validate Timing
    // Ensure arrows match song beatmap within timing windows (Perfect/Great/Good)
    let score = engine::calculate_score(&inputs.arrows, &inputs.song_hash);
    
    // 2. Validate Anti-Cheat
    // Check for impossible inputs (e.g., 20 presses per second)
    assert!(engine::validate_human_limits(&inputs.arrows));
    
    // 3. Commit Output
    sp1_zkvm::io::commit(&score);
}
```

### 2.2 The Verification Flow
1.  **Game End**: Arcade machine compiles inputs into `GameInput` struct.
2.  **Prove**: Machine runs `sp1_prover` (local) to generate proof $\pi$.
3.  **Submit**: Machine sends transaction to Bobchain with $\pi$.
4.  **Verify & Mint**:
    *   Chain validates $\pi$ using `sp1-solana` verifier.
    *   If valid, smart contract mints $BOB tokens to player's wallet.

---

## 3. Storage & Bandwidth Economy (Supertorrent Integration)

### 3.1 Storage Deals
*   **Deal**: A contract between a *Seeder* (Arcade Machine) and *Publisher* (Game Dev).
*   **Terms**: "Store `game_assets.zip` (10GB) for 30 days."
*   **Proof**: Seeder must periodically submit Merkle proofs of file possession.

### 3.2 Bandwidth Micro-payments
*   **Technology**: State Channels (Lightning-style) on Solana.
*   **Flow**:
    1.  *Leecher* opens channel with *Seeder*.
    2.  *Leecher* requests 1MB chunk.
    3.  *Leecher* signs off-chain state update "I owe you 0.0001 BOB".
    4.  *Seeder* sends chunk.
    5.  Channel settles on-chain periodically.

---

## 4. Privacy Architecture (Light Protocol)

### 4.1 Private High Scores
*   Users may want to hide their total playtime or earnings.
*   **Implementation**: Scores are stored as **Compressed Accounts** (Merkle leaves) on Solana.
*   **View**: Users can view their own history via their private key.
*   **Public Reveal**: Users can choose to "reveal" a specific high score for a leaderboard by providing a validity proof.

### 4.2 Private Balances
*   Standard ZK-UTXO model for $BOB transfers.
*   Arcade machines (public entities) may have public balances.
*   Players (private individuals) keep private balances.

---

## 5. Development Roadmap

### Phase 1: The Core (Now)
*   [x] Research Architecture.
*   [x] Prototype `BobcoinBridge` in Node.js (Mock -> Real).
*   [x] Create SP1 "Hello World" circuit for Game Score.

### Phase 2: The Integration
*   [ ] Connect Node.js Bridge to Solana Devnet.
*   [ ] Implement basic ZK Compression minting/transfer in Bridge.

### Phase 3: The Arcade
*   [ ] Port StepMania scoring logic to Rust (for SP1).
*   [ ] Build physical arcade machine prototype.
