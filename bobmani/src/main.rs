pub mod arrowvortex;
pub mod ffr_diff_model;
pub mod beatoraja;
pub mod server;

#[tokio::main]
async fn main() {
    println!("Phase 2 Consolidation - Unified Rust Backend Starting");

    // Start WebSocket Server
    server::run_server().await;
}
