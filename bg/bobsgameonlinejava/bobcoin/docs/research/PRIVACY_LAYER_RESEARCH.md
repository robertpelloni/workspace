# Bobcoin Privacy Layer - Detailed Research Documentation

**Version**: 1.0.0  
**Status**: APPROVED  
**Category**: Core Infrastructure (P0)

---

## Executive Summary

Bobcoin implements a **privacy-by-default** architecture combining the best innovations from Monero, Zcash, and Firo. This document details each cryptographic primitive, its implementation requirements, and trade-offs.

---

## 1. Stealth Addresses

### 1.1 Overview

Stealth addresses ensure that **every transaction creates a unique one-time address** for the recipient. Even if someone knows your public address, they cannot link incoming transactions to you on the blockchain.

### 1.2 Cryptographic Foundation

**Dual-Key Stealth Address Protocol (DKSAP)**:

```
Recipient has:
  - Public View Key (A = aG)
  - Public Spend Key (B = bG)
  - Private view key (a)
  - Private spend key (b)

Sender:
  1. Generates random scalar r
  2. Computes R = rG (included in transaction)
  3. Computes shared secret: s = H(rA) = H(raG)
  4. Computes one-time address: P = H(s)G + B

Recipient:
  1. Scans blockchain for R values
  2. Computes s' = H(aR) = H(arG) = H(raG) = s
  3. Computes P' = H(s')G + B
  4. If P' matches output, recipient owns it
  5. Private key for P: x = H(s) + b
```

### 1.3 Implementation Specifications

| Parameter | Value | Rationale |
|-----------|-------|-----------|
| Curve | Curve25519 | Fast, constant-time, well-audited |
| Hash Function | Keccak-256 | Monero-compatible, quantum-resistant candidate |
| Key Derivation | HKDF-SHA256 | Standard, secure key expansion |

### 1.4 Rust Implementation Skeleton

```rust
use curve25519_dalek::{scalar::Scalar, ristretto::RistrettoPoint};
use sha3::{Keccak256, Digest};

pub struct StealthAddress {
    pub view_public: RistrettoPoint,
    pub spend_public: RistrettoPoint,
}

pub struct StealthKeys {
    pub view_private: Scalar,
    pub spend_private: Scalar,
    pub address: StealthAddress,
}

impl StealthKeys {
    pub fn generate() -> Self {
        let view_private = Scalar::random(&mut rand::thread_rng());
        let spend_private = Scalar::random(&mut rand::thread_rng());
        
        let view_public = &view_private * &RISTRETTO_BASEPOINT_TABLE;
        let spend_public = &spend_private * &RISTRETTO_BASEPOINT_TABLE;
        
        Self {
            view_private,
            spend_private,
            address: StealthAddress { view_public, spend_public },
        }
    }
    
    pub fn derive_onetime_address(&self, r: &Scalar) -> (RistrettoPoint, RistrettoPoint) {
        let R = r * &RISTRETTO_BASEPOINT_TABLE;
        let shared_secret = self.compute_shared_secret(&R);
        let P = &shared_secret * &RISTRETTO_BASEPOINT_TABLE + self.address.spend_public;
        (R, P)
    }
    
    fn compute_shared_secret(&self, R: &RistrettoPoint) -> Scalar {
        let dh = self.view_private * R;
        let mut hasher = Keccak256::new();
        hasher.update(dh.compress().as_bytes());
        Scalar::from_hash(hasher)
    }
}
```

### 1.5 View Keys for Optional Transparency

**Use Cases**:
- Leaderboard verification (prove you earned a score)
- Tax/audit compliance
- Exchange deposits

**Implementation**:
- Share `view_private` key to allow scanning incoming transactions
- Spend key remains private (cannot spend, only view)
- Can generate **per-transaction view keys** for granular disclosure

---

## 2. Ring Signatures (CLSAG)

### 2.1 Overview

Ring signatures hide the **true sender** among a group of decoys. CLSAG (Compact Linkable Spontaneous Anonymous Group) is Monero's current signature scheme, offering:
- **Anonymity**: Sender hidden among ring members
- **Linkability**: Prevents double-spending via key images
- **Compactness**: ~50% smaller than previous MLSAG

### 2.2 How It Works

```
Transaction Input:
  - True spend key: x (private)
  - Ring of public keys: {P_0, P_1, ..., P_n} (one is yours)
  - Key Image: I = xH(P) (unique per private key)

Signature proves:
  1. Signer knows private key for ONE of the ring members
  2. This specific private key hasn't been used before (via key image)
  
Verifier cannot determine WHICH ring member signed.
```

### 2.3 Ring Size Selection

| Ring Size | Anonymity Set | Signature Size | Verification Time |
|-----------|---------------|----------------|-------------------|
| 11 (Monero) | 1-in-11 | ~1.5 KB | ~3ms |
| 16 (Bobcoin) | 1-in-16 | ~2.1 KB | ~4ms |
| 32 | 1-in-32 | ~4.0 KB | ~8ms |

**Recommendation**: Ring size **16** balances anonymity and performance for gaming transactions.

### 2.4 Decoy Selection Algorithm

**Critical**: Poor decoy selection can deanonymize users.

```rust
pub fn select_decoys(
    real_output: &OutputReference,
    blockchain: &BlockchainState,
    ring_size: usize,
) -> Vec<OutputReference> {
    let mut decoys = Vec::with_capacity(ring_size - 1);
    
    // Gamma distribution mimics real spending patterns
    // Recent outputs more likely to be spent
    let gamma = Gamma::new(19.28, 1.0 / 1.61);
    
    while decoys.len() < ring_size - 1 {
        let age_blocks = gamma.sample(&mut rand::thread_rng()) as u64;
        let target_height = blockchain.height().saturating_sub(age_blocks);
        
        if let Some(output) = blockchain.random_output_at_height(target_height) {
            if output != *real_output && !decoys.contains(&output) {
                decoys.push(output);
            }
        }
    }
    
    // Insert real output at random position
    let real_index = rand::thread_rng().gen_range(0..ring_size);
    decoys.insert(real_index, real_output.clone());
    
    decoys
}
```

### 2.5 Key Image Database

**Purpose**: Prevent double-spending without revealing which output was spent.

```rust
pub struct KeyImageStore {
    images: HashSet<CompressedRistretto>,
}

impl KeyImageStore {
    pub fn check_and_insert(&mut self, key_image: CompressedRistretto) -> Result<(), DoubleSpendError> {
        if self.images.contains(&key_image) {
            return Err(DoubleSpendError::KeyImageExists);
        }
        self.images.insert(key_image);
        Ok(())
    }
}
```

---

## 3. Bulletproofs+ (Range Proofs)

### 3.1 Overview

Bulletproofs+ prove that **transaction amounts are valid** (positive, no overflow) without revealing the actual amounts. This is essential for confidential transactions.

### 3.2 What They Prove

```
For each output amount v:
  - v ≥ 0 (non-negative)
  - v < 2^64 (no overflow)
  - Sum of inputs = Sum of outputs (balance)
```

### 3.3 Size Comparison

| Proof Type | Size (1 output) | Size (2 outputs) | Size (16 outputs) |
|------------|-----------------|------------------|-------------------|
| Borromean | 6.2 KB | 12.4 KB | 99.2 KB |
| Bulletproofs | 704 bytes | 768 bytes | 928 bytes |
| Bulletproofs+ | 576 bytes | 640 bytes | 800 bytes |

**Bulletproofs+** are ~15% smaller than original Bulletproofs with faster verification.

### 3.4 Pedersen Commitments

Amounts are hidden using **Pedersen commitments**:

```
Commitment: C = vG + rH

Where:
  v = amount (hidden)
  r = random blinding factor
  G, H = generator points (nothing-up-my-sleeve)
  
Properties:
  - Hiding: Cannot determine v from C
  - Binding: Cannot open C to different v
  - Homomorphic: C1 + C2 = (v1 + v2)G + (r1 + r2)H
```

### 3.5 Rust Implementation

```rust
use bulletproofs::{BulletproofGens, PedersenGens, RangeProof};
use curve25519_dalek::scalar::Scalar;

pub struct ConfidentialAmount {
    pub commitment: RistrettoPoint,
    pub proof: RangeProof,
}

impl ConfidentialAmount {
    pub fn create(amount: u64, blinding: Scalar) -> Result<Self, ProofError> {
        let pc_gens = PedersenGens::default();
        let bp_gens = BulletproofGens::new(64, 1);
        
        let mut transcript = Transcript::new(b"Bobcoin-RangeProof");
        
        let (proof, commitment) = RangeProof::prove_single(
            &bp_gens,
            &pc_gens,
            &mut transcript,
            amount,
            &blinding,
            64, // bits
        )?;
        
        Ok(Self { commitment, proof })
    }
    
    pub fn verify(&self) -> Result<(), ProofError> {
        let pc_gens = PedersenGens::default();
        let bp_gens = BulletproofGens::new(64, 1);
        let mut transcript = Transcript::new(b"Bobcoin-RangeProof");
        
        self.proof.verify_single(
            &bp_gens,
            &pc_gens,
            &mut transcript,
            &self.commitment,
            64,
        )
    }
}
```

### 3.6 Batch Verification

Bulletproofs+ support **batch verification** for significant speedup:

| Batch Size | Speedup vs Individual |
|------------|----------------------|
| 10 proofs | 2.5x faster |
| 100 proofs | 5x faster |
| 1000 proofs | 8x faster |

---

## 4. Dandelion++ (Network Privacy)

### 4.1 Problem

Even with on-chain privacy, **network-level surveillance** can deanonymize users:
- First node to broadcast likely created the transaction
- ISP/adversary can correlate IP addresses with transactions

### 4.2 Solution: Dandelion++

Two-phase propagation:
1. **Stem Phase**: Transaction hops through a random path (3-10 nodes)
2. **Fluff Phase**: Normal flooding propagation

```
          [Creator]
              │
              ▼ (stem)
          [Node A]
              │
              ▼ (stem)
          [Node B]
              │
              ▼ (stem)
          [Node C] ──────► FLUFF (broadcast to all)
              │
    ┌─────────┼─────────┐
    ▼         ▼         ▼
 [Node D] [Node E] [Node F] ...
```

### 4.3 Implementation Parameters

| Parameter | Value | Rationale |
|-----------|-------|-----------|
| Stem probability | 90% | High stem ratio before fluff |
| Stem timeout | 60 seconds | Fallback to fluff if stem stalls |
| Epoch duration | 10 minutes | Rotate stem paths periodically |
| Stem length | 3-10 hops | Randomized for unpredictability |

### 4.4 Rust Implementation

```rust
pub enum PropagationPhase {
    Stem { next_hop: PeerId, hops_remaining: u8 },
    Fluff,
}

pub struct DandelionRouter {
    stem_successor: Option<PeerId>,
    epoch_start: Instant,
    epoch_duration: Duration,
}

impl DandelionRouter {
    pub fn route_transaction(&mut self, tx: Transaction, peers: &[PeerId]) -> PropagationPhase {
        self.maybe_rotate_epoch(peers);
        
        // 90% stem, 10% fluff
        if rand::random::<f64>() < 0.9 {
            if let Some(successor) = &self.stem_successor {
                return PropagationPhase::Stem {
                    next_hop: successor.clone(),
                    hops_remaining: rand::thread_rng().gen_range(3..=10),
                };
            }
        }
        
        PropagationPhase::Fluff
    }
    
    fn maybe_rotate_epoch(&mut self, peers: &[PeerId]) {
        if self.epoch_start.elapsed() > self.epoch_duration {
            self.stem_successor = peers.choose(&mut rand::thread_rng()).cloned();
            self.epoch_start = Instant::now();
        }
    }
}
```

---

## 5. Optional: Halo 2 Shielded Pool (P2)

### 5.1 Overview

For users requiring **maximum privacy**, Bobcoin offers an optional Zcash-style shielded pool using **Halo 2** recursive proofs.

### 5.2 Advantages over Ring Signatures

| Feature | Ring Signatures | Halo 2 Shielded |
|---------|-----------------|-----------------|
| Anonymity Set | 16 (ring size) | All shielded users |
| Sender Privacy | ✅ | ✅ |
| Recipient Privacy | ✅ (stealth) | ✅ |
| Amount Privacy | ✅ (Bulletproofs) | ✅ |
| Trusted Setup | None | None (Halo 2) |
| Proof Size | ~2.5 KB | ~1.5 KB |
| Verification | ~5ms | ~10ms |

### 5.3 When to Use

- **Default (Ring + Stealth)**: Gaming transactions, tips, daily use
- **Shielded Pool**: Large transfers, maximum privacy requirements

### 5.4 Unified Address Format

```
bobcoin:<base58-encoded-address>

Where address contains:
  - Version byte (0x01)
  - Stealth public keys (view + spend)
  - Optional: Shielded payment address
  - Checksum
  
Example: bobcoin:Bo8mT4xKLcG7HjQwN2yRtF5sV9pBnE3kA...
```

---

## 6. Privacy Feature Matrix

| Transaction Type | Sender | Recipient | Amount | Network | Use Case |
|-----------------|--------|-----------|--------|---------|----------|
| **Standard Private** | Ring-16 | Stealth | Bulletproofs+ | Dandelion++ | Default |
| **View Key Disclosed** | Ring-16 | Known | Known | Dandelion++ | Leaderboards |
| **Shielded Pool** | Hidden | Hidden | Hidden | Dandelion++ | Max privacy |
| **Transparent** | Public | Public | Public | Standard | Exchange deposits |

---

## 7. Regulatory Considerations

### 7.1 Compliance Tools

1. **View Keys**: Prove incoming transactions for audits
2. **Payment Proofs**: Cryptographic proof of payment to specific address
3. **Selective Disclosure**: Reveal specific transactions without exposing others

### 7.2 Exchange Integration

```rust
pub struct PaymentProof {
    pub tx_hash: Hash,
    pub recipient: StealthAddress,
    pub amount: u64,
    pub proof: Signature,
}

impl PaymentProof {
    pub fn generate(tx: &Transaction, recipient_view_key: &Scalar) -> Self {
        // Generate proof that specific amount was sent to specific address
        // Verifiable by recipient without revealing to third parties
    }
}
```

---

## 8. Performance Benchmarks (Target)

| Operation | Target Time | Notes |
|-----------|-------------|-------|
| Stealth address derivation | <1ms | Per output |
| Ring signature creation (16) | <50ms | Per input |
| Ring signature verification (16) | <5ms | Per input |
| Bulletproof+ creation | <100ms | Per transaction |
| Bulletproof+ verification | <10ms | Per transaction |
| Bulletproof+ batch verify (100) | <200ms | Amortized |

---

## 9. Dependencies

```toml
[dependencies]
curve25519-dalek = { version = "4", features = ["serde"] }
bulletproofs = "4.0"
sha3 = "0.10"
rand = "0.8"
merlin = "3.0"  # Transcript for Fiat-Shamir
```

---

## 10. Security Considerations

| Attack | Mitigation |
|--------|------------|
| Timing attacks | Constant-time implementations (dalek) |
| Decoy selection bias | Gamma distribution matching real patterns |
| Key image grinding | Proper hash-to-curve implementation |
| Network deanon | Dandelion++ + Tor/I2P support |
| Quantum attacks | Future: Lattice-based signatures (research) |

---

**Next Document**: [Speed Layer - Nano/Avalanche/Kaspa Research](./SPEED_LAYER_RESEARCH.md)
