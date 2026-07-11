# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added - Phase 4: Knowledge Base & RAG
- **Document Parser Service** - Support for parsing PDF, DOCX, DOC, and TXT files
- **Text Chunking Service** - Recursive character splitting with configurable overlap
- **Document Ingestion Service** - Complete pipeline for uploading documents
- **RAG Service** - Retrieval-Augmented Generation with context caching
- **Knowledge Base API Routes**:
  - POST /api/knowledge-base/upload - Upload documents (PDF, DOCX, TXT)
  - POST /api/knowledge-base/text - Ingest text content
  - GET /api/knowledge-base/documents - List all documents
  - GET /api/knowledge-base/documents/:docId - Get document details
  - DELETE /api/knowledge-base/documents/:docId - Delete document
  - POST /api/knowledge-base/search - Search knowledge base
  - GET /api/knowledge-base/stats - Get RAG statistics
  - GET /api/knowledge-base/ingestion-info - Get ingestion configuration
  - POST /api/knowledge-base/cache/clear - Clear RAG context cache
- **RAG Integration** - Automatic context injection into OpenAI Realtime conversations
- **Pinecone Integration** - Vector database for semantic search with OpenAI embeddings
- **Configuration Variables**:
  - PINECONE_API_KEY - Pinecone API key
  - PINECONE_INDEX_NAME - Pinecone index name (default: knowledge-base)
  - PINECONE_REGION - Pinecone region (default: us-east-1)
  - KNOWLEDGE_BASE_ENABLED - Enable/disable knowledge base features
  - DOCUMENT_STORAGE_DIR - Document storage directory (default: ./documents)
  - KNOWLEDGE_BASE_DIR - Knowledge base storage directory (default: ./knowledge-base)
  - EMBEDDING_MODEL - OpenAI embedding model (default: text-embedding-3-small)

### Changed
- **OpenAI Conversation Flow** - Now injects relevant knowledge base context during calls
- **System Prompt Augmentation** - Dynamic context injection based on conversation content
- **File Upload Support** - Added multer middleware for multipart file uploads

### Technical Details
- **Chunking Strategy**: Recursive character splitting with 10% overlap
- **Embedding Model**: text-embedding-3-small (1536 dimensions)
- **Search Algorithm**: Cosine similarity with metadata filtering
- **Context Limiting**: Max 3000 characters, top 3 results by default
- **Cache Strategy**: 60-second TTL, max 100 entries
- **File Size Limit**: 10MB max per document

## [1.4.0] - 2025-01-18

### Added - Phase 4: Knowledge Base & RAG
- Complete RAG implementation with Pinecone and OpenAI
- Document upload and ingestion pipeline
- Real-time context injection during phone calls
- Knowledge base management APIs

## [1.3.0] - Phase 3: Call Management

### Added
- Call recording system with Twilio integration
- Voicemail system with transcription
- Recording playback in dashboard
- Recording download functionality
- Voicemail management in dashboard
- Email notifications for new voicemails
- Retention policy configuration

## [1.2.0] - Phase 2: Monitoring & Analytics

### Added
- Real-time dashboard for active calls monitoring
- Live transcript display
- Call metrics tracking module
- Analytics with volume/duration tracking
- Cost tracking per call
- Analytics export to CSV/Excel
- Analytics APIs to backend

## [1.1.0] - Phase 1: Foundation & Stability

### Added
- Winston logging system
- Request validation for all endpoints
- Call data cleanup with TTL
- Memory leak prevention
- Connection timeout and retry logic
- OpenAI WebSocket reconnection with exponential backoff
- Keepalive ping/pong mechanism
- Graceful shutdown handlers
- Uncaught exception handling
- Unhandled rejection tracking

## [1.0.0] - Initial Release

### Added
- Inbound call handling with AI receptionist
- Outbound call campaign system
- OpenAI Realtime API integration
- Twilio Programmable Voice integration
- Real-time audio streaming
- Email transcript delivery
- Do Not Call (DNC) list support
- Business hours enforcement
- Customer management via JSON
- Health check endpoint
- Basic web dashboard
- Call status tracking
