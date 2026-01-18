import multer from 'multer';
import * as documentIngestion from '../services/documentIngestion.js';
import * as knowledgeBase from '../services/knowledgeBase.js';
import * as rag from '../services/rag.js';
import logger from '../utils/logger.js';

const upload = multer({
  storage: multer.memoryStorage(),
  limits: {
    fileSize: 10 * 1024 * 1024,
    files: 1
  },
  fileFilter: (req, file, cb) => {
    const allowedExtensions = ['.pdf', '.docx', '.doc', '.txt'];
    const ext = '.' + file.originalname.split('.').pop().toLowerCase();

    if (!allowedExtensions.includes(ext)) {
      return cb(new Error(`Invalid file type. Allowed: ${allowedExtensions.join(', ')}`), false);
    }

    cb(null, true);
  }
});

export function setupKnowledgeBaseRoutes(app) {
  app.post('/api/knowledge-base/upload', upload.single('file'), async (req, res) => {
    if (!req.file) {
      return res.status(400).json({ success: false, error: 'No file provided' });
    }

    try {
      const metadata = {};

      if (req.body.category) {
        metadata.category = req.body.category;
      }

      if (req.body.title) {
        metadata.title = req.body.title;
      }

      if (req.body.tags) {
        try {
          metadata.tags = JSON.parse(req.body.tags);
        } catch {
          metadata.tags = req.body.tags.split(',').map(t => t.trim());
        }
      }

      const result = await documentIngestion.ingestDocument(req.file, metadata);

      if (!result.success) {
        return res.status(400).json(result);
      }

      res.json({
        success: true,
        data: {
          documentId: result.documentId,
          originalName: result.originalName,
          chunkCount: result.chunkCount,
          chunksAdded: result.added.length,
          failed: result.failed.length
        }
      });
    } catch (err) {
      logger.error('Failed to upload document', { error: err.message });
      res.status(500).json({ success: false, error: err.message });
    }
  });

  app.post('/api/knowledge-base/text', async (req, res) => {
    const { text, category, title, tags } = req.body;

    if (!text) {
      return res.status(400).json({ success: false, error: 'Text content is required' });
    }

    try {
      const metadata = {
        sourceType: 'text'
      };

      if (category) {
        metadata.category = category;
      }

      if (title) {
        metadata.title = title;
      }

      if (tags) {
        try {
          metadata.tags = typeof tags === 'string' ? JSON.parse(tags) : tags;
        } catch {
          metadata.tags = tags.split(',').map(t => t.trim());
        }
      }

      const result = await documentIngestion.ingestText(text, metadata);

      if (!result.success) {
        return res.status(400).json(result);
      }

      res.json({
        success: true,
        data: {
          documentId: result.documentId,
          chunkCount: result.chunkCount,
          chunksAdded: result.added.length
        }
      });
    } catch (err) {
      logger.error('Failed to ingest text', { error: err.message });
      res.status(500).json({ success: false, error: err.message });
    }
  });

  app.get('/api/knowledge-base/documents', async (req, res) => {
    try {
      const limit = parseInt(req.query.limit || '100', 10);
      const result = await knowledgeBase.listDocuments({ limit });

      if (!result.success) {
        return res.status(500).json(result);
      }

      res.json({
        success: true,
        data: {
          documents: result.documents,
          count: result.documents.length
        }
      });
    } catch (err) {
      logger.error('Failed to list documents', { error: err.message });
      res.status(500).json({ success: false, error: err.message });
    }
  });

  app.get('/api/knowledge-base/documents/:docId', async (req, res) => {
    const { docId } = req.params;

    try {
      const result = await knowledgeBase.getDocument(docId);

      if (!result.success) {
        return res.status(404).json(result);
      }

      res.json({
        success: true,
        data: result.document
      });
    } catch (err) {
      logger.error('Failed to get document', { docId, error: err.message });
      res.status(500).json({ success: false, error: err.message });
    }
  });

  app.delete('/api/knowledge-base/documents/:docId', async (req, res) => {
    const { docId } = req.params;

    try {
      const result = await knowledgeBase.deleteDocument(docId);

      if (!result.success) {
        return res.status(404).json(result);
      }

      res.json({
        success: true,
        data: { documentId: result.documentId }
      });
    } catch (err) {
      logger.error('Failed to delete document', { docId, error: err.message });
      res.status(500).json({ success: false, error: err.message });
    }
  });

  app.post('/api/knowledge-base/search', async (req, res) => {
    const { query, topK, category } = req.body;

    if (!query) {
      return res.status(400).json({ success: false, error: 'Query is required' });
    }

    try {
      const options = {};

      if (topK) {
        options.topK = parseInt(topK, 10);
      }

      if (category) {
        options.filter = { category };
      }

      const result = await rag.searchKnowledgeBase(query, options);

      if (!result.success) {
        return res.status(500).json(result);
      }

      res.json({
        success: true,
        data: {
          query,
          results: result.results,
          context: result.context,
          count: result.results.length
        }
      });
    } catch (err) {
      logger.error('Failed to search knowledge base', { query, error: err.message });
      res.status(500).json({ success: false, error: err.message });
    }
  });

  app.get('/api/knowledge-base/stats', async (req, res) => {
    try {
      const stats = rag.getRAGStats();

      res.json({
        success: true,
        data: stats
      });
    } catch (err) {
      logger.error('Failed to get stats', { error: err.message });
      res.status(500).json({ success: false, error: err.message });
    }
  });

  app.get('/api/knowledge-base/ingestion-info', (req, res) => {
    try {
      const info = documentIngestion.getIngestionStats();

      res.json({
        success: true,
        data: info
      });
    } catch (err) {
      logger.error('Failed to get ingestion info', { error: err.message });
      res.status(500).json({ success: false, error: err.message });
    }
  });

  app.post('/api/knowledge-base/cache/clear', (req, res) => {
    try {
      rag.clearContextCache();

      res.json({
        success: true,
        message: 'RAG context cache cleared'
      });
    } catch (err) {
      logger.error('Failed to clear cache', { error: err.message });
      res.status(500).json({ success: false, error: err.message });
    }
  });

  logger.info('Knowledge base API routes registered');
}
