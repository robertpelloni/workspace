import { Pinecone } from '@pinecone-database/pinecone';
import OpenAI from 'openai';
import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';
import logger from '../utils/logger.js';

const __dirname = path.dirname(fileURLToPath(import.meta.url));

// Initialize Pinecone client
const pinecone = process.env.PINECONE_API_KEY
  ? new Pinecone({ apiKey: process.env.PINECONE_API_KEY })
  : null;

// Initialize OpenAI client for embeddings
const openai = process.env.OPENAI_API_KEY
  ? new OpenAI({ apiKey: process.env.OPENAI_API_KEY })
  : null;

// Constants
const INDEX_NAME = process.env.PINECONE_INDEX_NAME || 'knowledge-base';
const EMBEDDING_MODEL = process.env.EMBEDDING_MODEL || 'text-embedding-3-small';
const EMBEDDING_DIMENSION = 1536;
const STORAGE_DIR = process.env.KNOWLEDGE_BASE_DIR || './knowledge-base';

// In-memory metadata cache
const knowledgeMap = new Map();
const searchStats = {
  totalSearches: 0,
  successfulSearches: 0,
  failedSearches: 0,
  lastSearchTime: null
};

export function isKnowledgeBaseEnabled() {
  return process.env.KNOWLEDGE_BASE_ENABLED === 'true' && pinecone !== null && openai !== null;
}

function ensureStorageDir() {
  if (!fs.existsSync(STORAGE_DIR)) {
    fs.mkdirSync(STORAGE_DIR, { recursive: true });
    logger.info('Created knowledge base storage directory', { storageDir: STORAGE_DIR });
  }
}

async function initializeIndex() {
  if (!pinecone) {
    logger.warn('Pinecone not initialized - missing API key');
    return false;
  }

  try {
    const existingIndexes = await pinecone.listIndexes();
    const indexExists = existingIndexes.indexes?.some(idx => idx.name === INDEX_NAME);

    if (!indexExists) {
      logger.info('Creating Pinecone index', { indexName: INDEX_NAME, dimension: EMBEDDING_DIMENSION });
      
      await pinecone.createIndex({
        name: INDEX_NAME,
        dimension: EMBEDDING_DIMENSION,
        metric: 'cosine',
        spec: {
          serverless: {
            cloud: 'aws',
            region: process.env.PINECONE_REGION || 'us-east-1'
          }
        }
      });

      await new Promise(resolve => setTimeout(resolve, 20000));
      logger.info('Pinecone index created successfully', { indexName: INDEX_NAME });
    } else {
      logger.info('Pinecone index already exists', { indexName: INDEX_NAME });
    }

    return true;
  } catch (err) {
    logger.error('Failed to initialize Pinecone index', { error: err.message });
    return false;
  }
}

function getIndex() {
  if (!pinecone) return null;
  return pinecone.index(INDEX_NAME);
}

async function generateEmbedding(text) {
  if (!openai) {
    throw new Error('OpenAI client not initialized');
  }

  try {
    const response = await openai.embeddings.create({
      model: EMBEDDING_MODEL,
      input: text,
      encoding_format: 'float'
    });

    return response.data[0].embedding;
  } catch (err) {
    logger.error('Failed to generate embedding', { error: err.message });
    throw err;
  }
}

function generateDocId() {
  return `doc_${Date.now()}_${Math.random().toString(36).substring(2, 9)}`;
}

function saveDocumentFile(docId, content, metadata) {
  ensureStorageDir();
  
  const date = new Date();
  const year = date.getFullYear();
  const month = String(date.getMonth() + 1).padStart(2, '0');
  
  const yearDir = path.join(STORAGE_DIR, String(year));
  const monthDir = path.join(yearDir, month);
  
  if (!fs.existsSync(yearDir)) fs.mkdirSync(yearDir, { recursive: true });
  if (!fs.existsSync(monthDir)) fs.mkdirSync(monthDir, { recursive: true });
  
  const filePath = path.join(monthDir, `${docId}.json`);
  
  const document = {
    id: docId,
    content,
    metadata,
    createdAt: date.toISOString(),
    updatedAt: date.toISOString()
  };
  
  fs.writeFileSync(filePath, JSON.stringify(document, null, 2));
  
  return filePath;
}

function loadDocumentFile(docId) {
  try {
    const files = fs.readdirSync(STORAGE_DIR, { recursive: true });
    const docFile = files.find(f => f.endsWith(`${docId}.json`));
    
    if (!docFile) return null;
    
    const filePath = path.join(STORAGE_DIR, docFile);
    const content = fs.readFileSync(filePath, 'utf-8');
    return JSON.parse(content);
  } catch (err) {
    logger.error('Failed to load document file', { docId, error: err.message });
    return null;
  }
}

function deleteDocumentFile(docId) {
  try {
    const files = fs.readdirSync(STORAGE_DIR, { recursive: true });
    const docFile = files.find(f => f.endsWith(`${docId}.json`));
    
    if (docFile) {
      const filePath = path.join(STORAGE_DIR, docFile);
      fs.unlinkSync(filePath);
      logger.info('Document file deleted', { docId, filePath });
      return true;
    }
    return false;
  } catch (err) {
    logger.error('Failed to delete document file', { docId, error: err.message });
    return false;
  }
}

export async function addDocument(content, metadata = {}) {
  if (!isKnowledgeBaseEnabled()) {
    return { success: false, error: 'Knowledge base is not enabled' };
  }

  try {
    const docId = generateDocId();
    
    logger.info('Generating embedding for document', { docId, contentLength: content.length });
    const embedding = await generateEmbedding(content);
    
    const docMetadata = {
      ...metadata,
      contentLength: content.length,
      createdAt: new Date().toISOString()
    };
    
    const filePath = saveDocumentFile(docId, content, docMetadata);
    
    const index = getIndex();
    await index.upsert([{
      id: docId,
      values: embedding,
      metadata: docMetadata
    }]);
    
    knowledgeMap.set(docId, {
      id: docId,
      content,
      metadata: docMetadata,
      filePath
    });
    
    logger.info('Document added to knowledge base', { docId, category: metadata.category });
    
    return { success: true, documentId: docId, content, metadata: docMetadata };
  } catch (err) {
    logger.error('Failed to add document', { error: err.message });
    return { success: false, error: err.message };
  }
}

export async function addDocuments(documents) {
  if (!isKnowledgeBaseEnabled()) {
    return { success: false, error: 'Knowledge base is not enabled' };
  }

  const results = { success: true, added: [], failed: [], total: documents.length };

  for (const doc of documents) {
    try {
      const result = await addDocument(doc.content, doc.metadata);
      if (result.success) results.added.push(result.documentId);
      else results.failed.push({ error: result.error });
    } catch (err) {
      results.failed.push({ error: err.message });
    }
  }

  if (results.failed.length > 0) {
    results.success = false;
    logger.warn('Some documents failed to add', { failed: results.failed.length, total: results.total });
  }

  return results;
}

export async function searchKnowledge(query, options = {}) {
  if (!isKnowledgeBaseEnabled()) {
    return { success: false, error: 'Knowledge base is not enabled', results: [] };
  }

  try {
    searchStats.totalSearches++;
    searchStats.lastSearchTime = new Date();

    const topK = options.topK || 5;
    const filter = options.filter || {};
    
    logger.info('Searching knowledge base', { query, topK });
    
    const embedding = await generateEmbedding(query);
    
    const index = getIndex();
    const response = await index.query({
      vector: embedding,
      topK,
      includeMetadata: true,
      includeValues: false,
      filter: Object.keys(filter).length > 0 ? filter : undefined
    });
    
    searchStats.successfulSearches++;
    
    const results = response.matches.map(match => {
      const cachedDoc = knowledgeMap.get(match.id);
      return {
        documentId: match.id,
        score: match.score,
        metadata: match.metadata,
        content: cachedDoc?.content || loadDocumentFile(match.id)?.content
      };
    }).filter(r => r.content !== undefined);
    
    logger.info('Knowledge base search completed', { query, results: results.length });
    
    return { success: true, results };
  } catch (err) {
    searchStats.failedSearches++;
    logger.error('Failed to search knowledge base', { query, error: err.message });
    return { success: false, error: err.message, results: [] };
  }
}

export async function deleteDocument(docId) {
  if (!isKnowledgeBaseEnabled()) {
    return { success: false, error: 'Knowledge base is not enabled' };
  }

  try {
    const index = getIndex();
    await index.deleteOne(docId);

    const fileDeleted = deleteDocumentFile(docId);
    knowledgeMap.delete(docId);

    logger.info('Document deleted from knowledge base', { docId, fileDeleted });

    return { success: true, documentId: docId };
  } catch (err) {
    logger.error('Failed to delete document', { docId, error: err.message });
    return { success: false, error: err.message };
  }
}

export async function getDocument(docId) {
  if (!isKnowledgeBaseEnabled()) {
    return { success: false, error: 'Knowledge base is not enabled', document: null };
  }

  try {
    const cachedDoc = knowledgeMap.get(docId);
    if (cachedDoc) {
      return { success: true, document: cachedDoc };
    }

    const doc = loadDocumentFile(docId);
    if (doc) {
      return { success: true, document: doc };
    }

    return { success: false, error: 'Document not found', document: null };
  } catch (err) {
    logger.error('Failed to get document', { docId, error: err.message });
    return { success: false, error: err.message, document: null };
  }
}

export async function listDocuments(options = {}) {
  if (!isKnowledgeBaseEnabled()) {
    return { success: false, error: 'Knowledge base is not enabled', documents: [] };
  }

  try {
    const index = getIndex();
    const response = await index.listPaginated({ limit: options.limit || 100 });

    const documents = response.vectors.map(vec => {
      const cachedDoc = knowledgeMap.get(vec.id);
      return {
        documentId: vec.id,
        metadata: vec.metadata,
        content: cachedDoc?.content || loadDocumentFile(vec.id)?.content
      };
    }).filter(doc => doc.content !== undefined);

    logger.info('Listed knowledge base documents', { count: documents.length });

    return { success: true, documents };
  } catch (err) {
    logger.error('Failed to list documents', { error: err.message });
    return { success: false, error: err.message, documents: [] };
  }
}

export function getStats() {
  return {
    enabled: isKnowledgeBaseEnabled(),
    totalDocuments: knowledgeMap.size,
    searchStats: { ...searchStats }
  };
}

export async function initialize() {
  if (!isKnowledgeBaseEnabled()) {
    logger.info('Knowledge base is not enabled in configuration');
    return false;
  }

  logger.info('Initializing knowledge base service', {
    indexName: INDEX_NAME,
    embeddingModel: EMBEDDING_MODEL
  });

  const indexInitialized = await initializeIndex();
  if (!indexInitialized) {
    logger.error('Failed to initialize Pinecone index');
    return false;
  }

  // Load existing documents into cache
  try {
    const result = await listDocuments();
    if (result.success) {
      for (const doc of result.documents) {
        knowledgeMap.set(doc.documentId, doc);
      }
      logger.info('Loaded documents into cache', { count: knowledgeMap.size });
    }
  } catch (err) {
    logger.warn('Failed to load documents into cache', { error: err.message });
  }

  logger.info('Knowledge base service initialized successfully');
  return true;
}
