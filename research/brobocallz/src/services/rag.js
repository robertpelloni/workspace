import * as knowledgeBase from './knowledgeBase.js';
import logger from '../utils/logger.js';

const MAX_CONTEXT_LENGTH = 3000;
const DEFAULT_TOP_K = 3;
const MIN_SCORE_THRESHOLD = 0.5;

const ragContextCache = new Map();

export async function searchAndFormat(query, options = {}) {
  try {
    if (!knowledgeBase.isKnowledgeBaseEnabled()) {
      return { success: false, error: 'Knowledge base is not enabled', context: '' };
    }

    const topK = options.topK || DEFAULT_TOP_K;
    const minScore = options.minScore || MIN_SCORE_THRESHOLD;
    const maxLength = options.maxLength || MAX_CONTEXT_LENGTH;

    logger.info('Searching for RAG context', { query, topK, minScore });

    const searchResult = await knowledgeBase.searchKnowledge(query, { topK });

    if (!searchResult.success) {
      return { success: false, error: searchResult.error, context: '' };
    }

    const relevantResults = searchResult.results.filter(
      result => result.score >= minScore
    );

    logger.info('RAG search results', {
      totalFound: searchResult.results.length,
      relevant: relevantResults.length
    });

    if (relevantResults.length === 0) {
      return {
        success: true,
        context: '',
        results: [],
        message: 'No relevant information found in knowledge base'
      };
    }

    let formattedContext = '';

    for (let i = 0; i < relevantResults.length; i++) {
      const result = relevantResults[i];
      const section = result.content;

      if (formattedContext.length + section.length <= maxLength) {
        formattedContext += `[${i + 1}] ${section}\n\n`;
      } else {
        break;
      }
    }

    logger.info('RAG context formatted', {
      contextLength: formattedContext.length,
      sectionsUsed: formattedContext.split('\n\n').filter(s => s.length > 0).length
    });

    return {
      success: true,
      context: formattedContext.trim(),
      results: relevantResults
    };
  } catch (err) {
    logger.error('RAG search failed', { query, error: err.message });
    return { success: false, error: err.message, context: '' };
  }
}

export function augmentSystemPrompt(basePrompt, context) {
  if (!context || context.length === 0) {
    return basePrompt;
  }

  const ragInstruction = `
IMPORTANT - Use the following information from your knowledge base to answer questions:
---
${context}
---

If the answer is not in the provided context, say you don't have that information. Do not make up or guess answers.
`;

  return `${basePrompt}\n\n${ragInstruction}`;
}

export async function getContextForQuery(query, options = {}) {
  const cacheKey = `${query}_${options.topK || DEFAULT_TOP_K}`;

  if (ragContextCache.has(cacheKey)) {
    const cached = ragContextCache.get(cacheKey);
    if (Date.now() - cached.timestamp < 60000) {
      logger.debug('RAG context cache hit', { cacheKey });
      return cached;
    }
  }

  const result = await searchAndFormat(query, options);

  const cacheEntry = {
    ...result,
    timestamp: Date.now()
  };

  ragContextCache.set(cacheKey, cacheEntry);

  if (ragContextCache.size > 100) {
    const oldestKey = ragContextCache.keys().next().value;
    ragContextCache.delete(oldestKey);
  }

  return cacheEntry;
}

export function clearContextCache() {
  const size = ragContextCache.size;
  ragContextCache.clear();
  logger.info('RAG context cache cleared', { entriesCleared: size });
}

export function getCacheStats() {
  return {
    size: ragContextCache.size,
    maxSize: 100
  };
}

export async function searchKnowledgeBase(query, options = {}) {
  return await searchAndFormat(query, options);
}

export function getRAGStats() {
  return {
    ...knowledgeBase.getStats(),
    cache: getCacheStats(),
    maxContextLength: MAX_CONTEXT_LENGTH,
    defaultTopK: DEFAULT_TOP_K,
    minScoreThreshold: MIN_SCORE_THRESHOLD
  };
}
