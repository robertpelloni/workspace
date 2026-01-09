import test from 'tape'
import Server from '../server.js'
import WebSocket from 'ws'
import { generateKeypair, sign } from '../reference-client/lib/crypto.js'
import stringify from 'fast-json-stable-stringify'

function createTracker (opts, cb) {
  const server = new Server(opts)
  server.on('listening', () => cb(server))
  server.listen(0)
}

test('Megatorrent: Validation and Cleanup', function (t) {
  t.plan(5)

  createTracker({ udp: false, http: false, ws: true, stats: false }, function (server) {
    const port = server.ws.address().port
    const trackerUrl = `ws://localhost:${port}`
    const keypair = generateKeypair()

    const publisher = new WebSocket(trackerUrl)

    publisher.on('open', () => {
        // Test 1: Invalid Signature
        const invalidManifest = {
            publicKey: keypair.publicKey.toString('hex'),
            sequence: 1,
            timestamp: Date.now(),
            collections: [],
            signature: Buffer.alloc(64).toString('hex') // invalid sig
        }

        publisher.send(JSON.stringify({
            action: 'publish',
            manifest: invalidManifest
        }))
    })

    publisher.on('message', (data) => {
        const msg = JSON.parse(data)

        if (msg['failure reason']) {
            // We expect failures for invalid inputs
            if (msg['failure reason'].includes('Invalid signature') || msg['failure reason'].includes('validation failed')) {
                t.pass('Rejected invalid signature/manifest')

                // Now proceed to clean up test
                publisher.close()

                // Test 2: Memory Leak / Cleanup Check
                // Create a subscriber that subscribes and then disconnects
                const subscriber = new WebSocket(trackerUrl)
                subscriber.on('open', () => {
                    const k = keypair.publicKey.toString('hex')
                    subscriber.send(JSON.stringify({ action: 'subscribe', key: k }))

                    // Allow server to process
                    setTimeout(() => {
                        t.ok(server.subscriptions[k], 'Subscription active')
                        t.equal(server.subscriptions[k].size, 1, 'One subscriber')

                        subscriber.close()

                        // Wait for cleanup
                        setTimeout(() => {
                           if (!server.subscriptions[k]) {
                               t.pass('Subscription Set removed after last subscriber left')
                           } else {
                               t.equal(server.subscriptions[k].size, 0, 'Subscriber removed from set')
                           }

                           // Test 3: Cache Existence
                           t.ok(server.manifests, 'LRU Cache exists')

                           server.close()
                        }, 100)
                    }, 100)
                })
            }
        }
    })
  })
})
