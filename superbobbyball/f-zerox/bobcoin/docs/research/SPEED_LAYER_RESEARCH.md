# Bobcoin Speed Layer - Detailed Research Documentation

**Version**: 1.0.0  
**Status**: APPROVED  
**Category**: Core Infrastructure (P0)

---

## Executive Summary

Bobcoin implements a **feeless, sub-second finality** transaction layer optimized for gaming and micro-tips. This document details the architecture combining Nano's Block Lattice, Avalanche's Snowball consensus, and Kaspa's GHOSTDAG for parallel block production.

---

## 1. Block Lattice Architecture (from Nano)

### 1.1 Overview

Traditional blockchains have a **single chain** where all transactions compete for space. Nano pioneered the **Block Lattice**: each account has its own blockchain (account-chain), enabling:

- **Asynchronous transactions**: No waiting for global consensus
- **No transaction fees**: No miners competing for fees
- **Instant finality**: Sender and receiver update their own chains

### 1.2 Structure

```
┌─────────────────────────────────────────────────────────────────────┐
│                        BLOCK LATTICE                                 │
├─────────────────────────────────────────────────────────────────────┤
│                                                                      │
│  Account A          Account B          Account C                     │
│  ┌─────┐           ┌─────┐           ┌─────┐                        │
│  │ A0  │           │ B0  │           │ C0  │  ← Genesis blocks      │
│  └──┬──┘           └──┬──┘           └──┬──┘                        │
│     │                 │                 │                            │
│  ┌──▼──┐           ┌──▼──┐           ┌──▼──┐                        │
│  │ A1  │──────────▶│ B1  │           │ C1  │  ← A sends to B        │
│  └──┬──┘  (send)   └──┬──┘ (receive) └──┬──┘                        │
│     │                 │                 │                            │
│  ┌──▼──┐           ┌──▼──┐           ┌──▼──┐                        │
│  │ A2  │           │ B2  │◀──────────│ C2  │  ← C sends to B        │
│  └─────┘           └─────┘  (receive)└─────┘                        │
│                                                                      │
└─────────────────────────────────────────────────────────────────────┘
```

### 1.3 Block Types

| Block Type | Purpose | Fields |
|------------|---------|--------|
| **Open** | First block, creates account | `source`, `representative`, `account` |
| **Send** | Deduct balance, reference recipient | `previous`, `destination`, `balance` |
| **Receive** | Credit from pending send | `previous`, `source` |
| **Change** | Update representative | `previous`, `representative` |

### 1.4 Bobcoin Modification: State Blocks

Nano later unified all block types into **State Blocks**. Bobcoin uses this approach with privacy extensions:

```rust
pub struct StateBlock {
    pub account: StealthAddress,
    pub previous: BlockHash,
    pub representative: PublicKey,
    pub balance_commitment: PedersenCommitment,  // Hidden balance
    pub link: BlockLink,  // Send destination OR receive source
    pub signature: RingSignature,  // CLSAG instead of plain signature
    pub work: ProofOfWork,  // Anti-spam
    
    // Privacy extensions
    pub ring_members: Vec<OutputReference>,
    pub range_proof: BulletproofPlus,
    pub key_image: KeyImage,
}

pub enum BlockLink {
    Nothing,  // Open/Change block
    SendTo(StealthAddress),
    ReceiveFrom(BlockHash),
}
```

### 1.5 Transaction Flow

```
1. SENDER creates Send block:
   - Decrements own balance
   - References recipient's stealth address
   - Signs with ring signature
   - Broadcasts to network

2. NETWORK validates:
   - Ring signature valid
   - Key image not seen (no double-spend)
   - Balance proof valid (Bulletproofs+)
   - Sufficient work attached

3. RECIPIENT creates Receive block:
   - Scans for stealth address match
   - Increments own balance
   - References sender's Send block
   - Signs and broadcasts

4. FINALITY via Avalanche Snowball:
   - Conflicting blocks resolved probabilistically
   - <500ms to finality
```

---

## 2. Avalanche Snowball Consensus

### 2.1 Overview

Avalanche pioneered **probabilistic consensus** using repeated random sampling. It achieves:

- **Sub-second finality**: ~400-500ms
- **High throughput**: 4,500+ TPS
- **Leaderless**: No designated block producer
- **Scalable**: O(log n) message complexity

### 2.2 Snow Protocol Family

```
Slush → Snowflake → Snowball → Avalanche
  ↓         ↓           ↓           ↓
Simple   Memory    Confidence   DAG-based
```

**Bobcoin uses Snowball** for transaction finality within the Block Lattice.

### 2.3 Snowball Algorithm

```rust
pub struct SnowballState {
    preference: Option<BlockHash>,
    last_preference: Option<BlockHash>,
    confidence: u32,
    finalized: bool,
}

impl SnowballState {
    const SAMPLE_SIZE: usize = 20;      // k
    const QUORUM_SIZE: usize = 14;      // α (>50% of k)
    const DECISION_THRESHOLD: u32 = 20; // β
    
    pub async fn query_round(&mut self, peers: &[Peer], conflict_set: &[BlockHash]) {
        // Sample k random peers
        let sample: Vec<&Peer> = peers
            .choose_multiple(&mut rand::thread_rng(), Self::SAMPLE_SIZE)
            .collect();
        
        // Query each peer for their preference
        let responses: Vec<BlockHash> = futures::future::join_all(
            sample.iter().map(|p| p.query_preference(conflict_set))
        ).await;
        
        // Count votes
        let mut counts: HashMap<BlockHash, usize> = HashMap::new();
        for response in responses {
            *counts.entry(response).or_insert(0) += 1;
        }
        
        // Check for quorum
        for (block, count) in counts {
            if count >= Self::QUORUM_SIZE {
                if self.preference == Some(block) {
                    self.confidence += 1;
                } else {
                    self.preference = Some(block);
                    if self.last_preference == Some(block) {
                        self.confidence += 1;
                    } else {
                        self.confidence = 1;
                    }
                }
                self.last_preference = Some(block);
                
                if self.confidence >= Self::DECISION_THRESHOLD {
                    self.finalized = true;
                }
                return;
            }
        }
        
        // No quorum reached, reset confidence
        self.confidence = 0;
    }
}
```

### 2.4 Conflict Resolution

In the Block Lattice, conflicts occur when:
1. **Double-spend**: Two Send blocks from same account spending same balance
2. **Fork**: Two blocks with same `previous` hash

Snowball resolves conflicts by converging on one preference:

```
Time 0: Network split 50/50 on Block A vs Block B
Time 1: Random sampling begins
Time 2: Slight majority for A (52%)
Time 3: Majority grows (60%)
Time 4: Supermajority (80%)
Time 5: Finalized on A (95%+ confidence)
```

### 2.5 Parameters for Gaming

| Parameter | Value | Rationale |
|-----------|-------|-----------|
| Sample size (k) | 20 | Balance speed vs security |
| Quorum (α) | 14 (70%) | High threshold for security |
| Decision (β) | 20 rounds | ~400ms to finality |
| Query interval | 20ms | Fast convergence |

---

## 3. GHOSTDAG Parallel Blocks (from Kaspa)

### 3.1 Overview

Traditional blockchains discard simultaneous blocks (orphans). **GHOSTDAG** (Greedy Heaviest Observed SubTree DAG) includes all valid blocks in a DAG structure:

- **No orphans**: All honest work counts
- **Higher throughput**: Multiple blocks per "slot"
- **Faster confirmations**: More blocks = more security faster

### 3.2 DAG Structure

```
┌─────────────────────────────────────────────────────────────────────┐
│                         GHOSTDAG                                     │
├─────────────────────────────────────────────────────────────────────┤
│                                                                      │
│  Time 0:        [Genesis]                                           │
│                     │                                                │
│  Time 1:    ┌───────┼───────┐                                       │
│             ▼       ▼       ▼                                       │
│           [B1]    [B2]    [B3]    ← All 3 blocks valid              │
│             │       │       │                                        │
│  Time 2:    └───────┼───────┘                                       │
│                     ▼                                                │
│                   [B4]  ← References all 3 parents                   │
│                     │                                                │
│  Time 3:        ┌───┼───┐                                           │
│                 ▼   ▼   ▼                                           │
│               [B5] [B6] [B7]                                        │
│                                                                      │
└─────────────────────────────────────────────────────────────────────┘
```

### 3.3 Ordering (Blue Set Selection)

GHOSTDAG orders blocks by selecting a "blue" anticone (honest blocks):

```rust
pub fn select_blue_set(dag: &BlockDAG, block: &Block) -> HashSet<BlockHash> {
    const K: usize = 18;  // Anticone size parameter
    
    let mut blue_set = HashSet::new();
    let past = dag.past_of(block);
    
    // Greedily select blocks with small blue anticone
    for candidate in past.iter().sorted_by_key(|b| dag.blue_score(b)).rev() {
        let anticone = dag.anticone_of(candidate);
        let blue_anticone: Vec<_> = anticone.iter()
            .filter(|b| blue_set.contains(*b))
            .collect();
        
        if blue_anticone.len() <= K {
            blue_set.insert(candidate.hash());
        }
    }
    
    blue_set
}
```

### 3.4 Integration with Block Lattice

Bobcoin combines Block Lattice (per-account chains) with GHOSTDAG (global ordering):

```
┌─────────────────────────────────────────────────────────────────────┐
│                    BOBCOIN HYBRID STRUCTURE                          │
├─────────────────────────────────────────────────────────────────────┤
│                                                                      │
│  Layer 1: Block Lattice (Account Chains)                            │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │  Account A    Account B    Account C    Account D    ...    │    │
│  │     │            │            │            │                │    │
│  │     ▼            ▼            ▼            ▼                │    │
│  │  [blocks]     [blocks]     [blocks]     [blocks]            │    │
│  └─────────────────────────────────────────────────────────────┘    │
│                              │                                       │
│                              ▼                                       │
│  Layer 2: GHOSTDAG Ordering (Validators)                            │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │  Validators observe account blocks, create ordering blocks   │    │
│  │  that reference sets of account blocks for global ordering  │    │
│  └─────────────────────────────────────────────────────────────┘    │
│                              │                                       │
│                              ▼                                       │
│  Layer 3: Snowball Finality                                         │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │  Conflicting orderings resolved via Snowball consensus      │    │
│  └─────────────────────────────────────────────────────────────┘    │
│                                                                      │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 4. Feeless Transactions

### 4.1 Anti-Spam: Proof of Work

Without fees, spam prevention uses **client-side Proof of Work**:

```rust
pub struct ProofOfWork {
    pub nonce: u64,
    pub difficulty: u64,
}

impl ProofOfWork {
    pub fn generate(block_hash: &BlockHash, difficulty: u64) -> Self {
        let mut nonce = 0u64;
        loop {
            let work_hash = blake2b(&[block_hash.as_bytes(), &nonce.to_le_bytes()].concat());
            let work_value = u64::from_le_bytes(work_hash[..8].try_into().unwrap());
            
            if work_value >= difficulty {
                return Self { nonce, difficulty };
            }
            nonce += 1;
        }
    }
    
    pub fn verify(&self, block_hash: &BlockHash) -> bool {
        let work_hash = blake2b(&[block_hash.as_bytes(), &self.nonce.to_le_bytes()].concat());
        let work_value = u64::from_le_bytes(work_hash[..8].try_into().unwrap());
        work_value >= self.difficulty
    }
}
```

### 4.2 Dynamic Difficulty

Difficulty adjusts based on network load:

| Network State | Difficulty | PoW Time | Use Case |
|---------------|------------|----------|----------|
| Low load (<10%) | 1x | ~0.5s | Normal tips |
| Medium (10-50%) | 4x | ~2s | Busy period |
| High (50-90%) | 16x | ~8s | Spam deterrent |
| Overload (>90%) | 64x | ~30s | Emergency |

### 4.3 Priority Lanes

For gaming, some transactions need guaranteed fast processing:

```rust
pub enum TransactionPriority {
    Free,           // Standard PoW
    Priority,       // Higher PoW OR small fee
    Instant,        // Fee required
}

pub struct PriorityConfig {
    pub free_pow_difficulty: u64,
    pub priority_pow_difficulty: u64,  // 4x base
    pub instant_fee: u64,              // 0.0001 BOB
}
```

---

## 5. Representatives and Voting Weight

### 5.1 Open Representative Voting (ORV)

Accounts delegate voting weight to **representatives** who participate in consensus:

```rust
pub struct Representative {
    pub address: PublicKey,
    pub delegated_weight: u128,  // Sum of all delegators' balances
    pub online: bool,
    pub uptime: f64,
}

impl Representative {
    pub fn voting_power(&self) -> u128 {
        if self.online && self.uptime > 0.95 {
            self.delegated_weight
        } else {
            0  // Offline reps don't vote
        }
    }
}
```

### 5.2 Delegation

```rust
pub fn delegate(account: &mut Account, representative: PublicKey) -> StateBlock {
    StateBlock {
        account: account.address.clone(),
        previous: account.head,
        representative,  // New representative
        balance_commitment: account.balance_commitment,
        link: BlockLink::Nothing,
        signature: account.sign(),
        work: ProofOfWork::generate(&account.head, DIFFICULTY),
        ..Default::default()
    }
}
```

### 5.3 Validator Requirements (Bobcoin Extension)

Unlike Nano, Bobcoin adds **Proof of Storage** requirements for representatives:

| Requirement | Threshold | Purpose |
|-------------|-----------|---------|
| Storage | 100 GB seeding | Proof of Useful Stake |
| Uptime | 95%+ | Reliability |
| Stake | 10,000 BOB | Skin in the game |
| Bandwidth | 100 Mbps | Fast propagation |

---

## 6. Performance Targets

### 6.1 Throughput

| Metric | Target | Comparison |
|--------|--------|------------|
| Theoretical max TPS | 100,000+ | Nano: 7,000, Visa: 24,000 |
| Realistic TPS | 10,000+ | With privacy overhead |
| Block time | N/A (async) | Per-account, instant |
| Finality | <500ms | Snowball convergence |

### 6.2 Latency Breakdown

| Phase | Time | Notes |
|-------|------|-------|
| PoW generation | 0-500ms | Client-side, adjustable |
| Network propagation | 50-100ms | Dandelion++ stem |
| Signature verification | 5ms | CLSAG ring-16 |
| Bulletproof verification | 10ms | Per transaction |
| Snowball finality | 400ms | 20 rounds × 20ms |
| **Total** | **<1 second** | Tip confirmed |

### 6.3 Storage Requirements

| Node Type | Storage | Purpose |
|-----------|---------|---------|
| Full Node | 50-100 GB | Complete lattice + DAG |
| Pruned Node | 10-20 GB | Recent state only |
| Light Client | <100 MB | Account chain + proofs |
| Validator | 100+ GB | Full + seeded files |

---

## 7. Rust Implementation Skeleton

### 7.1 Core Types

```rust
pub struct BlockLattice {
    accounts: HashMap<AccountId, AccountChain>,
    pending: HashMap<BlockHash, PendingReceive>,
    representatives: HashMap<PublicKey, Representative>,
}

pub struct AccountChain {
    pub head: BlockHash,
    pub blocks: Vec<StateBlock>,
    pub balance: PedersenCommitment,
    pub representative: PublicKey,
}

pub struct GhostDag {
    blocks: HashMap<BlockHash, DagBlock>,
    tips: HashSet<BlockHash>,
    blue_score: HashMap<BlockHash, u64>,
}

pub struct SnowballConsensus {
    conflicts: HashMap<ConflictId, SnowballState>,
    finalized: HashSet<BlockHash>,
}
```

### 7.2 Transaction Processing

```rust
impl BlockLattice {
    pub async fn process_block(&mut self, block: StateBlock) -> Result<(), BlockError> {
        // 1. Validate signature (ring signature)
        block.verify_signature()?;
        
        // 2. Check key image (no double-spend)
        if self.key_images.contains(&block.key_image) {
            return Err(BlockError::DoubleSpend);
        }
        
        // 3. Verify range proof (valid balance)
        block.range_proof.verify(&block.balance_commitment)?;
        
        // 4. Verify PoW (anti-spam)
        if !block.work.verify(&block.hash()) {
            return Err(BlockError::InsufficientWork);
        }
        
        // 5. Add to account chain
        let account = self.accounts.entry(block.account.clone()).or_default();
        if block.previous != account.head {
            // Fork detected, defer to Snowball
            self.conflicts.insert(block.hash());
            return Ok(());
        }
        
        account.blocks.push(block.clone());
        account.head = block.hash();
        
        // 6. Handle send/receive
        match &block.link {
            BlockLink::SendTo(recipient) => {
                self.pending.insert(block.hash(), PendingReceive {
                    source: block.hash(),
                    recipient: recipient.clone(),
                });
            }
            BlockLink::ReceiveFrom(source) => {
                self.pending.remove(source);
            }
            BlockLink::Nothing => {}
        }
        
        // 7. Trigger Snowball finality
        self.snowball.finalize(block.hash()).await?;
        
        Ok(())
    }
}
```

---

## 8. Network Protocol

### 8.1 Message Types

```rust
pub enum NetworkMessage {
    // Block propagation
    PublishBlock(StateBlock),
    RequestBlock(BlockHash),
    BlockResponse(StateBlock),
    
    // Account sync
    AccountSubscribe(AccountId),
    AccountUpdate(AccountId, StateBlock),
    
    // Snowball consensus
    SnowballQuery(ConflictId, Vec<BlockHash>),
    SnowballResponse(ConflictId, BlockHash),
    
    // Representative voting
    VoteRequest(BlockHash),
    Vote(BlockHash, Signature, VotingWeight),
    
    // Peer discovery
    PeerList(Vec<PeerInfo>),
    Keepalive,
}
```

### 8.2 Peer-to-Peer Layer

```rust
pub struct P2PConfig {
    pub listen_addr: SocketAddr,
    pub max_peers: usize,           // 50
    pub bootstrap_nodes: Vec<Multiaddr>,
    pub dandelion_epoch: Duration,  // 10 minutes
}

// Using libp2p
pub async fn start_p2p(config: P2PConfig) -> Result<Swarm, Error> {
    let transport = libp2p::tcp::tokio::Transport::new(tcp::Config::default())
        .upgrade(Version::V1)
        .authenticate(noise::NoiseConfig::xx(keypair.clone()).into_authenticated())
        .multiplex(yamux::YamuxConfig::default())
        .boxed();
    
    let behaviour = BobcoinBehaviour {
        gossipsub: gossipsub::Gossipsub::new(/* ... */),
        kademlia: kad::Kademlia::new(/* ... */),
        request_response: request_response::Behaviour::new(/* ... */),
    };
    
    Ok(Swarm::new(transport, behaviour, peer_id))
}
```

---

## 9. Comparison Matrix

| Feature | Bobcoin | Nano | IOTA | Solana | Kaspa |
|---------|---------|------|------|--------|-------|
| Structure | Lattice+DAG | Lattice | Tangle | Chain | BlockDAG |
| Finality | <500ms | <1s | ~10s | ~400ms | ~10s |
| Fees | Zero/Minimal | Zero | Zero | Low | Low |
| Privacy | Full | None | None | None | None |
| Smart Contracts | Yes | No | Yes | Yes | No |
| TPS | 10,000+ | 7,000 | 1,000 | 65,000 | 100 |

---

## 10. References

1. Nano Protocol Documentation
2. Avalanche Consensus Whitepaper
3. GHOSTDAG: A Scalable Generalization of Nakamoto Consensus
4. Snowball to Avalanche: A Novel Metastable Consensus Protocol
5. libp2p Specifications

---

**Next Document**: [Smart Contract Layer - Fuel/Solana/Move Research](./SMART_CONTRACT_LAYER_RESEARCH.md)
