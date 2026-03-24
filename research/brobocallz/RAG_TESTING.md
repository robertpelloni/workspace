# RAG Integration Testing Guide

This document provides comprehensive testing procedures for the BrobocallZ RAG (Retrieval-Augmented Generation) system.

## Prerequisites

1. **Pinecone Account**: Create account at https://app.pinecone.io
2. **Pinecone Index**: Create index named `knowledge-base` with 1536 dimensions
3. **Environment Setup**: Copy `.env.example` to `.env` and configure:
   ```
   PINECONE_API_KEY=your-pinecone-api-key
   KNOWLEDGE_BASE_ENABLED=true
   ```

## Test Categories

### 1. Document Upload Tests

#### Test 1.1: Upload PDF Document
```bash
# Sample PDF
curl -X POST http://localhost:3000/api/knowledge-base/upload \
  -F "file=@test-document.pdf" \
  -F "category=policies" \
  -F "title=Employee Handbook"

# Expected: Success response with documentId and chunkCount
```

#### Test 1.2: Upload DOCX Document
```bash
curl -X POST http://localhost:3000/api/knowledge-base/upload \
  -F "file=@test-doc.docx" \
  -F "category=services" \
  -F "tags=lawnmowers,chainsaws"

# Expected: Success with documentId
```

#### Test 1.3: Upload TXT File
```bash
curl -X POST http://localhost:3000/api/knowledge-base/upload \
  -F "file=@notes.txt" \
  -F "category=notes"

# Expected: Success response
```

#### Test 1.4: Text Ingestion (No File)
```bash
curl -X POST http://localhost:3000/api/knowledge-base/text \
  -H "Content-Type: application/json" \
  -d '{
    "text": "Business hours are Monday-Friday 8am-6pm",
    "category": "hours",
    "title": "Business Hours"
  }'

# Expected: Success with documentId and chunkCount
```

#### Test 1.5: Invalid File Type
```bash
curl -X POST http://localhost:3000/api/knowledge-base/upload \
  -F "file=@test.exe"

# Expected: Error "Invalid file type. Allowed: .pdf, .docx, .doc, .txt"
```

#### Test 1.6: Oversized File (>10MB)
```bash
# Create large file
dd if=/dev/zero of=large.txt bs=11M count=1

curl -X POST http://localhost:3000/api/knowledge-base/upload \
  -F "file=@large.txt"

# Expected: Error "File size exceeds maximum of 10MB"
```

### 2. Document Management Tests

#### Test 2.1: List All Documents
```bash
curl http://localhost:3000/api/knowledge-base/documents

# Expected: JSON with documents array and count
```

#### Test 2.2: Get Specific Document
```bash
curl http://localhost:3000/api/knowledge-base/documents/doc_123456

# Expected: Document details with content and metadata
```

#### Test 2.3: Delete Document
```bash
curl -X DELETE http://localhost:3000/api/knowledge-base/documents/doc_123456

# Expected: Success response with documentId
```

#### Test 2.4: Get Non-Existent Document
```bash
curl http://localhost:3000/api/knowledge-base/documents/doc_nonexistent

# Expected: 404 error "Document not found"
```

### 3. Search and Retrieval Tests

#### Test 3.1: Basic Search
```bash
curl -X POST http://localhost:3000/api/knowledge-base/search \
  -H "Content-Type: application/json" \
  -d '{
    "query": "What are your business hours?",
    "topK": 3
  }'

# Expected: Results with relevant context and scores
```

#### Test 3.2: Category Filtered Search
```bash
curl -X POST http://localhost:3000/api/knowledge-base/search \
  -H "Content-Type: application/json" \
  -d '{
    "query": "services",
    "category": "services",
    "topK": 5
  }'

# Expected: Results only from "services" category
```

#### Test 3.3: Low Relevance Query
```bash
curl -X POST http://localhost:3000/api/knowledge-base/search \
  -H "Content-Type: application/json" \
  -d '{
    "query": "What about quantum physics?",
    "topK": 3
  }'

# Expected: Empty results or very low scores (<0.5)
```

#### Test 3.4: Empty Query
```bash
curl -X POST http://localhost:3000/api/knowledge-base/search \
  -H "Content-Type: application/json" \
  -d '{
    "query": "",
    "topK": 3
  }'

# Expected: 400 error "Query is required"
```

### 4. Real-Time RAG Integration Tests

#### Test 4.1: Call with RAG Context
1. Configure phone with: `BUSINESS_NAME=Test Business`
2. Add knowledge base: business hours, services, pricing
3. Make test call to Twilio number
4. Ask: "What are your hours?"
5. Check logs for: "RAG context injected"
6. Verify AI response uses knowledge base data

**Expected**: AI answers with specific hours from knowledge base

#### Test 4.2: Call Without RAG Match
1. Make test call
2. Ask: "Tell me about quantum physics"
3. Check logs for: No relevant information found

**Expected**: AI says "I don't have information about that"

#### Test 4.3: Multiple RAG Context Updates
1. Call and ask: "What services do you offer?"
2. Wait 5+ seconds
3. Ask: "What about pricing?"
4. Check logs for multiple "RAG context injected" events

**Expected**: Context updates for each topic change

### 5. Statistics and Cache Tests

#### Test 5.1: Get Knowledge Base Stats
```bash
curl http://localhost:3000/api/knowledge-base/stats

# Expected: Stats with enabled, totalDocuments, searchStats, cache info
```

#### Test 5.2: Get Ingestion Info
```bash
curl http://localhost:3000/api/knowledge-base/ingestion-info

# Expected: Configuration with maxFileSize, supportedFormats
```

#### Test 5.3: Clear RAG Cache
```bash
# Make a search call to populate cache
curl -X POST http://localhost:3000/api/knowledge-base/search \
  -H "Content-Type: application/json" \
  -d '{"query":"test","topK":3}'

# Clear cache
curl -X POST http://localhost:3000/api/knowledge-base/cache/clear

# Expected: Success "RAG context cache cleared"
```

### 6. UI Testing

#### Test 6.1: Access Knowledge Base Page
1. Start server: `npm run dev`
2. Open: `http://localhost:3000/knowledge-base.html`
3. Verify:
   - Page loads without errors
   - All sections visible
   - Stats display correctly
   - Forms are accessible

#### Test 6.2: Upload via UI
1. Drag & drop a PDF file
2. Enter metadata (category, title, tags)
3. Click "Upload Document"
4. Verify success message appears
5. Check document list shows new item

#### Test 6.3: Search via UI
1. Enter query in search box
2. Click "Test Search"
3. Verify results appear with scores
4. Check context is formatted correctly

#### Test 6.4: Delete via UI
1. Find document in list
2. Click delete button
3. Confirm deletion
4. Verify document removed from list

#### Test 6.5: Clear Cache via UI
1. Click "Clear RAG Cache"
2. Verify success message
3. Check cache count resets to 0

### 7. Edge Cases and Error Handling

#### Test 7.1: Knowledge Base Disabled
1. Set `.env`: `KNOWLEDGE_BASE_ENABLED=false`
2. Restart server
3. Try to upload document
4. Try search

**Expected**: All endpoints return "Knowledge base is not enabled"

#### Test 7.2: Missing Pinecone API Key
1. Remove `.env`: `PINECONE_API_KEY`
2. Restart server
3. Check startup logs

**Expected**: "Knowledge base not initialized - missing API key"

#### Test 7.3: Rapid Sequential Calls
1. Make call 1: Ask "What are your hours?"
2. End call
3. Immediately make call 2: Ask "What services do you offer?"
4. Check logs for RAG context injection

**Expected**: RAG context retrieved successfully for both calls

#### Test 7.4: Large Document Ingestion
1. Upload 100-page PDF (~1MB)
2. Check chunk count (should be 100-200 chunks)
3. Search for content
4. Verify retrieval works

**Expected**: Document chunked and embedded correctly

### 8. Performance Tests

#### Test 8.1: Search Latency
```bash
# Measure search response time
time curl -X POST http://localhost:3000/api/knowledge-base/search \
  -H "Content-Type: application/json" \
  -d '{"query":"test query","topK":5}'

# Expected: <500ms for cached results
# Expected: <2s for new queries
```

#### Test 8.2: Upload Latency
```bash
# Measure upload time
time curl -X POST http://localhost:3000/api/knowledge-base/upload \
  -F "file=@medium-doc.pdf"

# Expected: Varies by document size (500ms-3s typical)
```

#### Test 8.3: Cache Hit Rate
1. Clear cache
2. Make 10 identical searches
3. Check logs for cache hits

**Expected**: 9/10 searches hit cache (90% hit rate)

## Test Data Preparation

Create test documents with the following content:

### `business-hours.txt`
```
Cliff's Small Engine Repair Business Hours

Monday through Friday: 8:00 AM - 6:00 PM
Saturday: 8:00 AM - 2:00 PM
Sunday: Closed

Holiday exceptions: Closed on major holidays (Thanksgiving, Christmas, New Year's Day)
```

### `services.txt`
```
Our Services

We repair and maintain all types of small engines:
- Lawnmowers (push and riding)
- Chainsaws and pole saws
- Weed eaters and trimmers
- Generators (portable and standby)
- Leaf blowers
- Pressure washers

Additional services:
- Free pickup and delivery within 20 miles
- Emergency repairs available
- Seasonal maintenance packages
```

### `pricing.txt`
```
Pricing Information

Labor rate: $60/hour
Minimum charge: 1 hour
Free estimates available
Parts are additional cost

Example repairs:
- Lawnmower tune-up: $60-120
- Chainsaw sharpening: $30-50
- Generator diagnosis: $60

Payment methods: Cash, credit card, local checks
```

## Success Criteria

### Core Functionality
- [ ] Documents upload successfully (PDF, DOCX, TXT)
- [ ] Text ingestion works
- [ ] Documents list correctly
- [ ] Search returns relevant results
- [ ] Scores reflect relevance (0.0-1.0)
- [ ] Context formatted properly
- [ ] Cache reduces repeated queries

### Integration
- [ ] RAG context injected during calls
- [ ] AI uses knowledge base in responses
- [ ] Context updates on topic change
- [ ] No RAG errors in production logs

### UI
- [ ] Knowledge base page loads
- [ ] All forms work
- [ ] Error messages display
- [ ] Success notifications appear
- [ ] Statistics update in real-time

### Performance
- [ ] Search latency <2 seconds
- [ ] Upload latency <5 seconds
- [ ] Cache hit rate >80%
- [ ] No memory leaks in 100-call test

## Automated Testing Script

For automated testing, use this Node.js script:

```javascript
// test-rag.js - Run with: node test-rag.js

import http from 'http';

const BASE_URL = 'http://localhost:3000';

async function request(method, path, data = null) {
  return new Promise((resolve, reject) => {
    const req = http.request(`${BASE_URL}${path}`, {
      method,
      headers: {
        'Content-Type': 'application/json'
      }
    }, (res) => {
      let body = '';
      res.on('data', chunk => body += chunk);
      res.on('end', () => {
        resolve(JSON.parse(body));
      });
    });

    req.on('error', reject);
    if (data) req.write(JSON.stringify(data));
    req.end();
  });
}

async function runTests() {
  console.log('Starting RAG integration tests...\n');

  // Test 1: Get stats
  const stats = await request('GET', '/api/knowledge-base/stats');
  console.log('✓ Stats endpoint:', stats.success ? 'PASS' : 'FAIL');

  // Test 2: Search
  const search = await request('POST', '/api/knowledge-base/search', {
    query: 'test',
    topK: 3
  });
  console.log('✓ Search endpoint:', search.success ? 'PASS' : 'FAIL');

  // Test 3: Text ingestion
  const ingest = await request('POST', '/api/knowledge-base/text', {
    text: 'Test document content',
    category: 'test'
  });
  console.log('✓ Ingestion endpoint:', ingest.success ? 'PASS' : 'FAIL');

  console.log('\nTests complete!');
}

runTests().catch(console.error);
```

## Known Limitations

1. **Requires Pinecone Account**: Free tier available, but production needs paid tier
2. **OpenAI API Costs**: Embeddings generate API charges (~$0.0001/1K tokens)
3. **Document Size Limit**: 10MB per file for performance
4. **No Versioning**: Document updates replace existing (no history)
5. **No RBAC**: No multi-user permissions (all share same knowledge base)

## Troubleshooting

### Issue: "Knowledge base is not enabled"
**Solution**: Check `.env` has `PINECONE_API_KEY` and `KNOWLEDGE_BASE_ENABLED=true`

### Issue: "Pinecone index not found"
**Solution**: Create index manually at https://app.pinecone.io with:
- Name: `knowledge-base`
- Dimension: `1536`
- Metric: `cosine`
- Cloud: `aws` / `us-east-1`

### Issue: "No context injected during calls"
**Solution**: Check logs for "RAG context injected" - if missing:
1. Verify knowledge base has documents
2. Check query relevance
3. Verify Pinecone API key is valid
4. Check `ragEnabled` flag in mediaStream.js

### Issue: High embedding costs
**Solution**:
1. Use larger chunk sizes (default 512)
2. Reduce chunk overlap (default 50)
3. Filter searches to only relevant categories

## Next Steps After Testing

1. **Monitor Production**: Track search latency, hit rates, and costs
2. **Optimize Chunks**: Adjust chunk size based on typical document lengths
3. **Add More Content**: Populate knowledge base with business documentation
4. **Fine-Tune Prompts**: Adjust system prompt for better RAG utilization
5. **Add Analytics**: Track which queries fail (no relevant content found)
