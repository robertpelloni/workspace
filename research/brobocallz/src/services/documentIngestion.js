import fs from 'fs';
import path from 'path';
import * as documentParser from './documentParser.js';
import * as textChunker from './textChunker.js';
import * as knowledgeBase from './knowledgeBase.js';
import logger from '../utils/logger.js';

const MAX_FILE_SIZE = 10 * 1024 * 1024;
const STORAGE_DIR = process.env.DOCUMENT_STORAGE_DIR || './documents';

function ensureStorageDir() {
  if (!fs.existsSync(STORAGE_DIR)) {
    fs.mkdirSync(STORAGE_DIR, { recursive: true });
    logger.info('Created document storage directory', { storageDir: STORAGE_DIR });
  }
}

function getDocumentStoragePath(documentId, originalName) {
  ensureStorageDir();
  const ext = path.extname(originalName);
  return path.join(STORAGE_DIR, `${documentId}${ext}`);
}

function generateDocumentId() {
  return `doc_${Date.now()}_${Math.random().toString(36).substring(2, 9)}`;
}

function validateFile(file) {
  if (!file) {
    return { valid: false, error: 'No file provided' };
  }

  if (file.size > MAX_FILE_SIZE) {
    const maxSizeMB = MAX_FILE_SIZE / (1024 * 1024);
    return {
      valid: false,
      error: `File size exceeds maximum of ${maxSizeMB}MB`
    };
  }

  if (!documentParser.isSupportedFormat(file.originalname || file.name)) {
    const supported = documentParser.getSupportedFormats().join(', ');
    return {
      valid: false,
      error: `Unsupported file format. Supported: ${supported}`
    };
  }

  return { valid: true };
}

export async function ingestDocument(file, metadata = {}) {
  try {
    const validation = validateFile(file);
    if (!validation.valid) {
      return { success: false, error: validation.error };
    }

    if (!knowledgeBase.isKnowledgeBaseEnabled()) {
      return { success: false, error: 'Knowledge base is not enabled' };
    }

    const documentId = generateDocumentId();
    const originalName = file.originalname || file.name || 'document';

    logger.info('Starting document ingestion', {
      documentId,
      originalName,
      fileSize: file.size
    });

    const storagePath = getDocumentStoragePath(documentId, originalName);

    fs.writeFileSync(storagePath, file.buffer);

    logger.info('Document file saved', { documentId, storagePath });

    const parseResult = await documentParser.parseDocument(storagePath);

    if (!parseResult.success) {
      fs.unlinkSync(storagePath);
      return { success: false, error: parseResult.error };
    }

    const docMetadata = {
      ...metadata,
      documentId,
      originalName,
      fileSize: file.size,
      fileType: path.extname(originalName),
      createdAt: new Date().toISOString()
    };

    const chunks = textChunker.chunkDocuments([
      {
        content: parseResult.text,
        metadata: docMetadata,
        documentId
      }
    ]);

    logger.info('Document chunked', {
      documentId,
      chunkCount: chunks.length
    });

    const results = { success: true, added: [], failed: [], total: chunks.length };

    for (const chunk of chunks) {
      try {
        const result = await knowledgeBase.addDocument(chunk.content, chunk.metadata);
        if (result.success) {
          results.added.push(result.documentId);
        } else {
          results.failed.push({ error: result.error });
        }
      } catch (err) {
        results.failed.push({ error: err.message });
      }
    }

    if (results.failed.length > 0) {
      results.success = false;
      logger.warn('Some chunks failed to add to knowledge base', {
        failed: results.failed.length,
        total: results.total
      });
    } else {
      logger.info('Document successfully ingested', {
        documentId,
        chunksAdded: results.added.length
      });
    }

    return {
      ...results,
      documentId,
      originalName,
      chunkCount: chunks.length
    };
  } catch (err) {
    logger.error('Failed to ingest document', { error: err.message });
    return { success: false, error: err.message };
  }
}

export async function ingestText(text, metadata = {}) {
  try {
    if (!knowledgeBase.isKnowledgeBaseEnabled()) {
      return { success: false, error: 'Knowledge base is not enabled' };
    }

    if (!text || text.trim().length === 0) {
      return { success: false, error: 'Text content is empty' };
    }

    const documentId = generateDocumentId();

    logger.info('Starting text ingestion', {
      documentId,
      textLength: text.length
    });

    const docMetadata = {
      ...metadata,
      documentId,
      sourceType: 'text',
      createdAt: new Date().toISOString()
    };

    const chunks = textChunker.chunkDocuments([
      {
        content: text,
        metadata: docMetadata,
        documentId
      }
    ]);

    logger.info('Text chunked', {
      documentId,
      chunkCount: chunks.length
    });

    const results = { success: true, added: [], failed: [], total: chunks.length };

    for (const chunk of chunks) {
      try {
        const result = await knowledgeBase.addDocument(chunk.content, chunk.metadata);
        if (result.success) {
          results.added.push(result.documentId);
        } else {
          results.failed.push({ error: result.error });
        }
      } catch (err) {
        results.failed.push({ error: err.message });
      }
    }

    if (results.failed.length > 0) {
      results.success = false;
      logger.warn('Some chunks failed to add', {
        failed: results.failed.length,
        total: results.total
      });
    }

    return {
      ...results,
      documentId,
      chunkCount: chunks.length
    };
  } catch (err) {
    logger.error('Failed to ingest text', { error: err.message });
    return { success: false, error: err.message };
  }
}

export function getIngestionStats() {
  return {
    maxFileSize: MAX_FILE_SIZE,
    supportedFormats: documentParser.getSupportedFormats(),
    defaultChunkSize: 512,
    defaultChunkOverlap: 50
  };
}
