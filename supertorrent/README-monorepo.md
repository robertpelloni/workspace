# Megatorrent Monorepo

This repository contains the reference implementation for the Megatorrent protocol, a decentralized, mutable successor to BitTorrent.

## Structure

*   `docs/`: Architecture and Protocol Specifications.
*   `tracker/`: Node.js implementation of the Tracker and Reference Client (the root of this repo, historically).
*   `qbittorrent/`: C++ Client Fork (Submodule).

## Getting Started

### Node.js Tracker & Reference Client
Run the tracker and client tests:
```bash
npm install
npm test
```

### qBittorrent Client
See `qbittorrent/README.md` for C++ build instructions.
