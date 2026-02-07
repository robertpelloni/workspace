# Bobcoin Smart Contract Layer - Detailed Research Documentation

**Version**: 1.0.0  
**Status**: APPROVED  
**Category**: Core Infrastructure (P1)

---

## Executive Summary

Bobcoin implements a **UTXO-based smart contract model** inspired by Fuel, with parallel execution capabilities from Solana's Sealevel. This document details the VM architecture, programming model, and gaming-specific primitives.

---

## 1. VM Architecture: FuelVM-Inspired UTXO Model

### 1.1 Why UTXO over Account Model?

| Feature | UTXO Model (Fuel/Bitcoin) | Account Model (Ethereum/Solana) |
|---------|---------------------------|--------------------------------|
| Parallelism | Native (independent UTXOs) | Requires explicit declaration |
| Privacy | Better (no global state) | Harder (shared state) |
| Fraud Proofs | Simpler | Complex |
| State Growth | Bounded per tx | Unbounded |
| Composability | Via predicates | Via contract calls |

**Bobcoin Choice**: UTXO for privacy + parallelism, with predicate-based composability.

### 1.2 Core Concepts

#### 1.2.1 Coins (UTXOs)

```rust
pub struct Coin {
    pub owner: OwnershipPredicate,
    pub amount: u64,
    pub asset_id: AssetId,
    pub maturity: BlockHeight,
    pub witness_index: u8,
}

pub enum OwnershipPredicate {
    PublicKeyHash(Hash),
    Script(PredicateCode),
    Multisig { threshold: u8, keys: Vec<PublicKey> },
}
```

#### 1.2.2 Predicates (Stateless Smart Contracts)

Predicates are **pure functions** that return true/false. They unlock coins without requiring on-chain state:

```rust
pub struct Predicate {
    pub bytecode: Vec<u8>,
    pub data: Vec<u8>,
}

impl Predicate {
    pub fn evaluate(&self, tx: &Transaction, inputs: &[Input]) -> bool {
        let vm = PredicateVM::new(self.bytecode.clone());
        vm.execute(tx, inputs, &self.data)
    }
}
```

#### 1.2.3 Scripts (Transaction Logic)

Scripts run **once per transaction**, can read all inputs/outputs:

```rust
pub struct Script {
    pub bytecode: Vec<u8>,
    pub data: Vec<u8>,
    pub gas_limit: u64,
}
```

#### 1.2.4 Contracts (Stateful, Optional)

For gaming that needs state (leaderboards, inventories):

```rust
pub struct Contract {
    pub id: ContractId,
    pub bytecode: Vec<u8>,
    pub storage_slots: HashMap<Bytes32, Bytes32>,
    pub balance: HashMap<AssetId, u64>,
}
```

### 1.3 Execution Model

```
┌─────────────────────────────────────────────────────────────────────┐
│                    BOBCOIN VM EXECUTION                              │
├─────────────────────────────────────────────────────────────────────┤
│                                                                      │
│  Transaction                                                         │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │  Inputs: [Coin1, Coin2, ...]   (UTXOs being spent)          │    │
│  │  Outputs: [Coin3, Coin4, ...]  (new UTXOs created)          │    │
│  │  Witnesses: [Sig1, Sig2, ...]  (proofs of authorization)    │    │
│  │  Script: Optional              (custom logic)                │    │
│  └─────────────────────────────────────────────────────────────┘    │
│                              │                                       │
│                              ▼                                       │
│  Phase 1: Predicate Evaluation (Parallel)                           │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │  For each input coin:                                        │    │
│  │    - Execute owner predicate with witnesses                  │    │
│  │    - Must return TRUE to spend                               │    │
│  │  All predicates run in parallel (no shared state)            │    │
│  └─────────────────────────────────────────────────────────────┘    │
│                              │                                       │
│                              ▼                                       │
│  Phase 2: Script Execution (Sequential)                             │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │  If script present:                                          │    │
│  │    - Execute with full tx context                            │    │
│  │    - Can call contracts, emit logs                           │    │
│  │    - Returns success/failure + receipts                      │    │
│  └─────────────────────────────────────────────────────────────┘    │
│                              │                                       │
│                              ▼                                       │
│  Phase 3: Validation                                                │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │  - Sum(inputs) >= Sum(outputs) + fees                        │    │
│  │  - All predicates passed                                     │    │
│  │  - Script succeeded (if present)                             │    │
│  │  - Gas limit not exceeded                                    │    │
│  └─────────────────────────────────────────────────────────────┘    │
│                                                                      │
└─────────────────────────────────────────────────────────────────────┘
```

---

## 2. Parallel Execution (from Solana Sealevel)

### 2.1 Overview

Solana's Sealevel runtime achieves 65,000 TPS by executing non-conflicting transactions in parallel. Bobcoin adapts this for UTXOs:

### 2.2 UTXO Parallelism

UTXOs are **inherently parallel** - each coin can only be spent once:

```rust
pub fn execute_block_parallel(txs: Vec<Transaction>) -> Vec<Receipt> {
    // Build dependency graph based on UTXO references
    let graph = build_dependency_graph(&txs);
    
    // Find independent transaction sets
    let independent_sets = graph.find_independent_sets();
    
    // Execute each set in parallel
    let results: Vec<Receipt> = independent_sets
        .par_iter()
        .flat_map(|set| {
            set.par_iter().map(|tx| execute_transaction(tx))
        })
        .collect();
    
    results
}

fn build_dependency_graph(txs: &[Transaction]) -> DependencyGraph {
    let mut graph = DependencyGraph::new();
    
    for (i, tx) in txs.iter().enumerate() {
        for input in &tx.inputs {
            // Find any tx that creates this UTXO as output
            for (j, other_tx) in txs.iter().enumerate() {
                if other_tx.outputs.iter().any(|o| o.id() == input.utxo_id) {
                    graph.add_dependency(i, j); // tx[i] depends on tx[j]
                }
            }
        }
    }
    
    graph
}
```

### 2.3 Contract State Parallelism

For stateful contracts, declare read/write sets upfront:

```rust
pub struct ContractCall {
    pub contract_id: ContractId,
    pub function: String,
    pub args: Vec<u8>,
    pub read_keys: Vec<StorageKey>,   // Declare reads
    pub write_keys: Vec<StorageKey>,  // Declare writes
}

impl ContractCall {
    pub fn can_parallelize_with(&self, other: &ContractCall) -> bool {
        // No write-write conflicts
        let write_conflict = self.write_keys.iter()
            .any(|k| other.write_keys.contains(k));
        
        // No read-write conflicts
        let read_write_conflict = self.read_keys.iter()
            .any(|k| other.write_keys.contains(k))
            || other.read_keys.iter()
            .any(|k| self.write_keys.contains(k));
        
        !write_conflict && !read_write_conflict
    }
}
```

---

## 3. Programming Language: BobScript (Rust DSL)

### 3.1 Design Principles

1. **Rust-based**: Leverage Rust's safety guarantees
2. **No Reentrancy**: UTXO model prevents by design
3. **Explicit Effects**: All state changes declared upfront
4. **Gas Efficient**: Compile to optimized bytecode

### 3.2 Predicate Example

```rust
#[bobcoin::predicate]
fn timelock_predicate(
    ctx: PredicateContext,
    unlock_time: u64,
    owner_pubkey: PublicKey,
) -> bool {
    // Check time has passed
    if ctx.block_height < unlock_time {
        return false;
    }
    
    // Check signature
    ctx.verify_signature(owner_pubkey)
}
```

### 3.3 Script Example

```rust
#[bobcoin::script]
fn atomic_swap(
    ctx: ScriptContext,
    secret_hash: Hash,
    alice: PublicKey,
    bob: PublicKey,
    timeout: u64,
) -> Result<(), ScriptError> {
    // Alice can claim with secret
    if let Some(secret) = ctx.witness::<Vec<u8>>(0) {
        if hash(&secret) == secret_hash && ctx.verify_signature(alice) {
            return Ok(());
        }
    }
    
    // Bob can refund after timeout
    if ctx.block_height > timeout && ctx.verify_signature(bob) {
        return Ok(());
    }
    
    Err(ScriptError::Unauthorized)
}
```

### 3.4 Contract Example

```rust
#[bobcoin::contract]
mod game_leaderboard {
    use bobcoin::storage::StorageMap;
    
    #[storage]
    struct Leaderboard {
        scores: StorageMap<PublicKey, u64>,
        top_player: Option<PublicKey>,
        top_score: u64,
    }
    
    #[callable]
    fn submit_score(ctx: &Context, score: u64, proof: ZkProof) -> Result<()> {
        // Verify ZK proof of score
        require!(verify_score_proof(&proof, score), "Invalid proof");
        
        // Update player's score
        let player = ctx.caller();
        let current = storage::scores.get(&player).unwrap_or(0);
        
        if score > current {
            storage::scores.insert(player, score);
            
            // Update top player
            if score > storage::top_score {
                storage::top_player = Some(player);
                storage::top_score = score;
            }
        }
        
        emit!(ScoreSubmitted { player, score });
        Ok(())
    }
    
    #[view]
    fn get_top_player() -> Option<(PublicKey, u64)> {
        storage::top_player.map(|p| (p, storage::top_score))
    }
}
```

---

## 4. Native Assets

### 4.1 First-Class Token Support

Unlike Ethereum (ERC-20 contracts), Bobcoin has **native multi-asset support**:

```rust
pub struct AssetId(Hash);

impl AssetId {
    pub const BOB: AssetId = AssetId(Hash::zero()); // Native token
    
    pub fn new(contract_id: ContractId, sub_id: Bytes32) -> Self {
        AssetId(hash(&[contract_id.as_bytes(), sub_id.as_bytes()].concat()))
    }
}

pub struct Coin {
    pub asset_id: AssetId,  // Can be BOB or any token
    pub amount: u64,
    pub owner: Predicate,
}
```

### 4.2 Minting New Assets

```rust
#[bobcoin::contract]
mod game_token {
    #[callable]
    fn mint(ctx: &Context, recipient: Address, amount: u64) -> Result<()> {
        require!(ctx.caller() == GAME_ADMIN, "Unauthorized");
        
        // Mint new tokens as UTXOs
        ctx.mint(AssetId::from_contract(ctx.contract_id()), amount, recipient)?;
        
        Ok(())
    }
    
    #[callable]
    fn burn(ctx: &Context, amount: u64) -> Result<()> {
        // Burn tokens from caller
        ctx.burn(AssetId::from_contract(ctx.contract_id()), amount)?;
        
        Ok(())
    }
}
```

---

## 5. Gaming-Specific Primitives

### 5.1 Verifiable Random Function (VRF)

For fair loot drops, matchmaking, and randomness:

```rust
pub struct VrfOutput {
    pub value: [u8; 32],
    pub proof: VrfProof,
}

impl VrfOutput {
    pub fn generate(secret_key: &SecretKey, input: &[u8]) -> Self {
        // Generate deterministic random output
        let (value, proof) = vrf_prove(secret_key, input);
        Self { value, proof }
    }
    
    pub fn verify(&self, public_key: &PublicKey, input: &[u8]) -> bool {
        vrf_verify(public_key, input, &self.value, &self.proof)
    }
    
    pub fn to_u64(&self) -> u64 {
        u64::from_le_bytes(self.value[..8].try_into().unwrap())
    }
}

#[bobcoin::contract]
mod loot_box {
    #[callable]
    fn open_box(ctx: &Context, vrf_proof: VrfOutput) -> Result<Item> {
        // Verify VRF was generated by authorized oracle
        require!(vrf_proof.verify(&ORACLE_PUBKEY, &ctx.tx_id()), "Invalid VRF");
        
        // Deterministic random item selection
        let roll = vrf_proof.to_u64() % 1000;
        let item = match roll {
            0..=10 => Item::Legendary,    // 1.1%
            11..=60 => Item::Epic,        // 5%
            61..=200 => Item::Rare,       // 14%
            _ => Item::Common,            // 80%
        };
        
        ctx.mint_nft(item.asset_id(), ctx.caller())?;
        Ok(item)
    }
}
```

### 5.2 Score Commitment (Anti-Cheat)

Commit-reveal scheme for competitive gaming:

```rust
#[bobcoin::contract]
mod tournament {
    #[storage]
    struct TournamentState {
        commitments: StorageMap<PublicKey, Hash>,
        revealed_scores: StorageMap<PublicKey, u64>,
        phase: TournamentPhase,
    }
    
    #[callable]
    fn commit_score(ctx: &Context, commitment: Hash) -> Result<()> {
        require!(storage::phase == TournamentPhase::Commit, "Wrong phase");
        storage::commitments.insert(ctx.caller(), commitment);
        Ok(())
    }
    
    #[callable]
    fn reveal_score(ctx: &Context, score: u64, nonce: [u8; 32], zk_proof: ZkProof) -> Result<()> {
        require!(storage::phase == TournamentPhase::Reveal, "Wrong phase");
        
        // Verify commitment
        let expected = hash(&[score.to_le_bytes().as_slice(), &nonce].concat());
        require!(storage::commitments.get(&ctx.caller()) == Some(expected), "Bad commitment");
        
        // Verify ZK proof of score
        require!(verify_game_proof(&zk_proof, score), "Invalid proof");
        
        storage::revealed_scores.insert(ctx.caller(), score);
        Ok(())
    }
}
```

### 5.3 Soulbound Tokens (Achievements)

Non-transferable tokens for achievements:

```rust
#[bobcoin::contract]
mod achievements {
    #[storage]
    struct AchievementRegistry {
        achievements: StorageMap<(PublicKey, AchievementId), bool>,
    }
    
    #[callable]
    fn grant_achievement(ctx: &Context, player: PublicKey, achievement: AchievementId) -> Result<()> {
        require!(ctx.caller() == GAME_CONTRACT, "Unauthorized");
        require!(!storage::achievements.get(&(player, achievement)).unwrap_or(false), "Already has");
        
        storage::achievements.insert((player, achievement), true);
        
        // Mint soulbound NFT (non-transferable)
        ctx.mint_soulbound(achievement.asset_id(), player)?;
        
        emit!(AchievementUnlocked { player, achievement });
        Ok(())
    }
    
    #[view]
    fn has_achievement(player: PublicKey, achievement: AchievementId) -> bool {
        storage::achievements.get(&(player, achievement)).unwrap_or(false)
    }
}
```

### 5.4 Streaming Payments (Subscriptions)

Per-second payment streams for subscriptions:

```rust
#[bobcoin::contract]
mod payment_stream {
    #[storage]
    struct Stream {
        sender: PublicKey,
        recipient: PublicKey,
        rate_per_second: u64,
        start_time: u64,
        deposited: u64,
        withdrawn: u64,
    }
    
    #[callable]
    fn create_stream(ctx: &Context, recipient: PublicKey, rate: u64, duration: u64) -> Result<StreamId> {
        let total = rate * duration;
        ctx.transfer_in(AssetId::BOB, total)?;
        
        let stream = Stream {
            sender: ctx.caller(),
            recipient,
            rate_per_second: rate,
            start_time: ctx.timestamp(),
            deposited: total,
            withdrawn: 0,
        };
        
        let id = storage::streams.insert(stream);
        Ok(id)
    }
    
    #[callable]
    fn withdraw(ctx: &Context, stream_id: StreamId) -> Result<u64> {
        let stream = storage::streams.get_mut(&stream_id)?;
        require!(ctx.caller() == stream.recipient, "Not recipient");
        
        let elapsed = ctx.timestamp() - stream.start_time;
        let earned = elapsed * stream.rate_per_second;
        let available = earned.min(stream.deposited) - stream.withdrawn;
        
        stream.withdrawn += available;
        ctx.transfer_out(AssetId::BOB, available, stream.recipient)?;
        
        Ok(available)
    }
}
```

---

## 6. Gas Model

### 6.1 Compute Units

```rust
pub struct GasSchedule {
    // Basic operations
    pub base_tx_cost: u64,           // 21,000
    pub per_byte_cost: u64,          // 16
    pub signature_verify: u64,        // 3,000
    
    // Predicate costs
    pub predicate_base: u64,         // 1,000
    pub predicate_per_op: u64,       // 1
    
    // Contract costs
    pub contract_call: u64,          // 2,100
    pub storage_read: u64,           // 200
    pub storage_write: u64,          // 5,000
    pub storage_delete: u64,         // 5,000 (refunds 4,800)
    
    // Crypto costs
    pub hash_per_word: u64,          // 6
    pub ecrecover: u64,              // 3,000
    pub vrf_verify: u64,             // 10,000
    pub zk_verify: u64,              // 50,000
}
```

### 6.2 Fee Calculation

```rust
pub fn calculate_fee(tx: &Transaction, gas_used: u64, gas_price: u64) -> u64 {
    // Base fee (burned)
    let base_fee = gas_used * BASE_FEE_PER_GAS;
    
    // Priority fee (to validators)
    let priority_fee = gas_used * (gas_price - BASE_FEE_PER_GAS);
    
    base_fee + priority_fee
}
```

### 6.3 Feeless for Simple Transfers

Simple BOB transfers (no scripts) can use PoW instead of fees:

```rust
pub fn validate_fee_or_pow(tx: &Transaction) -> Result<(), ValidationError> {
    if tx.script.is_none() && tx.fee > 0 {
        // Paid fee, OK
        return Ok(());
    }
    
    if tx.script.is_none() && tx.proof_of_work.is_some() {
        // PoW provided, verify difficulty
        let pow = tx.proof_of_work.as_ref().unwrap();
        if pow.verify(&tx.hash(), MIN_POW_DIFFICULTY) {
            return Ok(());
        }
    }
    
    if tx.fee > 0 {
        // Script tx, must pay fee
        return Ok(());
    }
    
    Err(ValidationError::InsufficientFeeOrWork)
}
```

---

## 7. Bytecode Format

### 7.1 Instruction Set

```rust
pub enum Opcode {
    // Stack operations
    Push(u64),
    Pop,
    Dup,
    Swap,
    
    // Arithmetic
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    
    // Bitwise
    And,
    Or,
    Xor,
    Not,
    Shl,
    Shr,
    
    // Comparison
    Eq,
    Lt,
    Gt,
    
    // Control flow
    Jump(u32),
    JumpIf(u32),
    Call(u32),
    Return,
    Revert,
    
    // Memory
    MLoad,
    MStore,
    
    // Storage (contracts only)
    SLoad,
    SStore,
    
    // Context
    Caller,
    CallValue,
    BlockHeight,
    Timestamp,
    TxId,
    
    // Crypto
    Hash,
    VerifySig,
    VerifyVrf,
    VerifyZk,
    
    // Assets
    Mint,
    Burn,
    Transfer,
}
```

### 7.2 Compilation Pipeline

```
BobScript (Rust DSL)
        │
        ▼
    HIR (High-level IR)
        │
        ▼
    MIR (Mid-level IR)
        │
        ▼
    Optimization Passes
        │
        ▼
    BobcoinVM Bytecode
```

---

## 8. Security Considerations

### 8.1 No Reentrancy

UTXO model prevents reentrancy by design:
- Coins are consumed atomically
- No external calls during predicate evaluation
- Contract calls are sequential within a transaction

### 8.2 Integer Overflow Protection

```rust
// All arithmetic uses checked operations
pub fn safe_add(a: u64, b: u64) -> Result<u64, ArithmeticError> {
    a.checked_add(b).ok_or(ArithmeticError::Overflow)
}
```

### 8.3 Gas Limits

```rust
pub const MAX_GAS_PER_TX: u64 = 30_000_000;
pub const MAX_GAS_PER_BLOCK: u64 = 100_000_000;
```

---

## 9. Comparison with Other VMs

| Feature | BobcoinVM | EVM | SVM | FuelVM | MoveVM |
|---------|-----------|-----|-----|--------|--------|
| Model | UTXO | Account | Account | UTXO | Resource |
| Parallelism | Native | No | Declared | Native | Native |
| Reentrancy Safe | Yes | No | Yes | Yes | Yes |
| Native Assets | Yes | No | Yes | Yes | Yes |
| Language | Rust DSL | Solidity | Rust | Sway | Move |
| Privacy Compatible | Yes | Hard | Hard | Yes | Hard |

---

## 10. Implementation Roadmap

### Phase 1: Predicates Only (Month 1-2)
- Basic predicate VM
- Signature verification
- Timelock predicates
- Multisig predicates

### Phase 2: Scripts (Month 3-4)
- Full script execution
- Atomic swaps
- VRF integration
- ZK proof verification

### Phase 3: Contracts (Month 5-6)
- Stateful contract support
- Storage operations
- Cross-contract calls
- Gaming primitives

---

**Next Document**: [Novel Features - Account Abstraction, SBTs, etc.](./NOVEL_FEATURES_RESEARCH.md)
