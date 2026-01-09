
## 6. Obfuscated Storage Protocol (Phase 2)
To achieve plausible deniability and distributed redundancy, data is not stored as "files" but as "Blobs" of high-entropy data.

### Concepts
*   **Blob**: A fixed-size (or variable) container stored by a Host. To the Host, it is just random bytes.
*   **Chunk**: A segment of a user's file.
*   **Encryption**: Each Chunk is encrypted with a *unique* random key (ChaCha20-Poly1305) before being placed into a Blob.
*   **Muxing**: A Blob may contain multiple Chunks (potentially from different files) or padding.

### Data Structure: The `FileEntry`
This structure replaces the simple "magnet link" in the Megatorrent Manifest.

```json
{
  "name": "episode1.mkv",
  "mime": "video/x-matroska",
  "size": 104857600,
  "chunks": [
    {
      "blobId": "<SHA256 Hash of the Blob>",
      "offset": 0,         // Byte offset in the Blob
      "length": 1048576,   // Length of the encrypted chunk
      "key": "<32-byte Hex Key>",
      "nonce": "<12-byte Hex Nonce>",
      "authTag": "<16-byte Hex Tag>"
    },
    ...
  ]
}
```

### Process
1.  **Ingest**:
    *   File is split into N chunks.
    *   For each chunk:
        *   Generate random Key & Nonce.
        *   Encrypt Chunk -> EncryptedChunk.
        *   (Simplification for Ref Impl) EncryptedChunk becomes a "Blob" directly (or is wrapped).
        *   Blob ID = SHA256(Blob).
    *   Result: A list of Blobs (to be uploaded) and a `FileEntry` (to be put in the Manifest).

2.  **Access**:
    *   Subscriber receives Manifest.
    *   Parses `FileEntry`.
    *   Requests Blob(ID) from the network (simulated via local dir or tracker relay).
    *   Extracts bytes at `offset` for `length`.
    *   Decrypts using `key` and `nonce`.
    *   Reassembles file.
