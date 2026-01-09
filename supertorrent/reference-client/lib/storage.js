import sodium from 'sodium-native'
import crypto from 'crypto' // for SHA256 (sodium has it too but standard lib is fine for hashing)

const CHUNK_SIZE = 1024 * 1024 // 1MB chunks

// Helper to hash a buffer
function sha256 (buffer) {
  const hash = crypto.createHash('sha256')
  hash.update(buffer)
  return hash.digest('hex')
}

/**
 * Ingests a file buffer and returns a FileEntry (for manifest) and a list of Blobs (to store).
 *
 * @param {Buffer} fileBuffer
 * @param {string} fileName
 * @returns { fileEntry, blobs }
 */
export function ingest (fileBuffer, fileName) {
  const totalSize = fileBuffer.length
  const chunks = []
  const blobs = []

  let offset = 0
  while (offset < totalSize) {
    const end = Math.min(offset + CHUNK_SIZE, totalSize)
    const chunkData = fileBuffer.slice(offset, end)

    // 1. Generate Encryption Params
    const key = Buffer.alloc(sodium.crypto_aead_chacha20poly1305_ietf_KEYBYTES)
    const nonce = Buffer.alloc(sodium.crypto_aead_chacha20poly1305_ietf_NPUBBYTES)
    sodium.randombytes_buf(key)
    sodium.randombytes_buf(nonce)

    // 2. Encrypt
    const ciphertext = Buffer.alloc(chunkData.length + sodium.crypto_aead_chacha20poly1305_ietf_ABYTES)
    sodium.crypto_aead_chacha20poly1305_ietf_encrypt(
      ciphertext,
      chunkData,
      null, // aad
      null, // nsec
      nonce,
      key
    )

    // 3. Create Blob (In this ref impl, 1 Encrypted Chunk = 1 Blob. Future: Muxing)
    const blobBuffer = ciphertext
    const blobId = sha256(blobBuffer)

    blobs.push({
      id: blobId,
      buffer: blobBuffer
    })

    // 4. Record Metadata
    chunks.push({
      blobId,
      offset: 0, // 1:1 mapping for now
      length: blobBuffer.length, // length includes auth tag
      key: key.toString('hex'),
      nonce: nonce.toString('hex')
    })

    offset = end
  }

  return {
    fileEntry: {
      name: fileName,
      size: totalSize,
      chunks
    },
    blobs
  }
}

/**
 * Reassembles a file from a FileEntry and a getBlob function.
 *
 * @param {Object} fileEntry
 * @param {Function} getBlobFn - async (blobId) -> Buffer
 * @returns {Promise<Buffer>}
 */
export async function reassemble (fileEntry, getBlobFn) {
  const parts = []

  for (const chunkMeta of fileEntry.chunks) {
    // 1. Fetch Blob
    const blobBuffer = await getBlobFn(chunkMeta.blobId)
    if (!blobBuffer) throw new Error(`Blob ${chunkMeta.blobId} not found`)

    // 2. Extract Encrypted Chunk (Handle Muxing logic here if/when implemented)
    // For now, it's 1:1
    const ciphertext = blobBuffer.slice(chunkMeta.offset, chunkMeta.offset + chunkMeta.length)

    // 3. Decrypt
    const key = Buffer.from(chunkMeta.key, 'hex')
    const nonce = Buffer.from(chunkMeta.nonce, 'hex')
    const plaintext = Buffer.alloc(ciphertext.length - sodium.crypto_aead_chacha20poly1305_ietf_ABYTES)

    try {
      sodium.crypto_aead_chacha20poly1305_ietf_decrypt(
        plaintext,
        null,
        ciphertext,
        null,
        nonce,
        key
      )
    } catch (err) {
      throw new Error(`Decryption failed for blob ${chunkMeta.blobId}`)
    }

    parts.push(plaintext)
  }

  return Buffer.concat(parts)
}
