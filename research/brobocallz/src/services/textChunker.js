import logger from '../utils/logger.js';

const DEFAULT_CHUNK_SIZE = 512;
const DEFAULT_CHUNK_OVERLAP = 50;

const SEPARATORS = ['\n\n', '\n', '. ', '? ', '! ', ', ', ' ', ''];

export function chunkText(text, options = {}) {
  const chunkSize = options.chunkSize || DEFAULT_CHUNK_SIZE;
  const chunkOverlap = options.chunkOverlap || DEFAULT_CHUNK_OVERLAP;
  const separators = options.separators || SEPARATORS;

  if (!text || text.length === 0) {
    return [];
  }

  if (text.length <= chunkSize) {
    return [text];
  }

  const chunks = [];
  let currentText = text;
  let currentSeparatorIndex = 0;

  while (currentText.length > 0) {
    const chunk = splitAtSeparator(currentText, chunkSize, separators, currentSeparatorIndex);

    if (chunk === currentText) {
      if (currentText.length > chunkSize) {
        const trimmedChunk = currentText.substring(0, chunkSize);
        chunks.push(trimmedChunk);
        currentText = currentText.substring(chunkSize);
      } else {
        chunks.push(currentText);
        break;
      }
    } else {
      chunks.push(chunk);
      const remainingLength = currentText.length - chunk.length;
      const overlapStart = Math.max(0, chunk.length - chunkOverlap);
      currentText = currentText.substring(overlapStart);
    }
  }

  logger.info('Text chunked', {
    originalLength: text.length,
    chunkCount: chunks.length,
    chunkSize,
    chunkOverlap
  });

  return chunks;
}

function splitAtSeparator(text, maxLength, separators, separatorIndex = 0) {
  if (maxLength >= text.length) {
    return text;
  }

  const searchRange = text.substring(0, maxLength);

  for (let i = separatorIndex; i < separators.length; i++) {
    const separator = separators[i];
    const lastSeparatorPos = searchRange.lastIndexOf(separator);

    if (lastSeparatorPos > 0) {
      return text.substring(0, lastSeparatorPos + separator.length);
    }
  }

  return text.substring(0, maxLength);
}

export function chunkDocuments(documents, options = {}) {
  const chunkedDocuments = [];

  for (const doc of documents) {
    const chunks = chunkText(doc.content, options);

    for (let i = 0; i < chunks.length; i++) {
      chunkedDocuments.push({
        content: chunks[i],
        metadata: {
          ...doc.metadata,
          documentId: doc.documentId,
          chunkIndex: i,
          totalChunks: chunks.length,
          chunkOffset: doc.chunkOffset || 0
        }
      });
    }
  }

  logger.info('Documents chunked', {
    documentCount: documents.length,
    totalChunks: chunkedDocuments.length
  });

  return chunkedDocuments;
}

export function mergeChunks(chunks) {
  if (!chunks || chunks.length === 0) {
    return '';
  }

  if (chunks.length === 1) {
    return chunks[0];
  }

  return chunks.join(' ');
}

export function getChunkContext(chunks, targetIndex, contextSize = 1) {
  const startIndex = Math.max(0, targetIndex - contextSize);
  const endIndex = Math.min(chunks.length - 1, targetIndex + contextSize);

  return chunks.slice(startIndex, endIndex + 1);
}
