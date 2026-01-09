import sodium from 'sodium-native'

export function generateKeypair () {
  const publicKey = Buffer.alloc(sodium.crypto_sign_PUBLICKEYBYTES)
  const secretKey = Buffer.alloc(sodium.crypto_sign_SECRETKEYBYTES)
  sodium.crypto_sign_keypair(publicKey, secretKey)
  return { publicKey, secretKey }
}

export function sign (message, secretKey) {
  const signature = Buffer.alloc(sodium.crypto_sign_BYTES)
  const msgBuffer = Buffer.isBuffer(message) ? message : Buffer.from(message)
  sodium.crypto_sign_detached(signature, msgBuffer, secretKey)
  return signature
}

export function verify (message, signature, publicKey) {
  const msgBuffer = Buffer.isBuffer(message) ? message : Buffer.from(message)
  return sodium.crypto_sign_verify_detached(signature, msgBuffer, publicKey)
}
