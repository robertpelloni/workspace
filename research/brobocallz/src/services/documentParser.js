import pdfParse from 'pdf-parse';
import mammoth from 'mammoth';
import fs from 'fs';
import path from 'path';
import logger from '../utils/logger.js';

export async function parsePDF(filePath) {
  try {
    const dataBuffer = fs.readFileSync(filePath);
    const data = await pdfParse(dataBuffer);

    logger.info('PDF parsed successfully', {
      filePath,
      pageCount: data.numpages,
      textLength: data.text.length
    });

    return {
      success: true,
      text: data.text,
      metadata: {
        pages: data.numpages,
        info: data.info
      }
    };
  } catch (err) {
    logger.error('Failed to parse PDF', { filePath, error: err.message });
    return { success: false, error: err.message };
  }
}

export async function parseWord(filePath) {
  try {
    const dataBuffer = fs.readFileSync(filePath);
    const result = await mammoth.extractRawText({ buffer: dataBuffer });

    if (result.messages && result.messages.length > 0) {
      const warnings = result.messages.filter(m => m.type === 'warning');
      if (warnings.length > 0) {
        logger.warn('Word parsing warnings', {
          filePath,
          warnings: warnings.map(w => w.message)
        });
      }
    }

    logger.info('Word document parsed successfully', {
      filePath,
      textLength: result.value.length
    });

    return {
      success: true,
      text: result.value,
      metadata: {
        messages: result.messages
      }
    };
  } catch (err) {
    logger.error('Failed to parse Word document', { filePath, error: err.message });
    return { success: false, error: err.message };
  }
}

export async function parsePlainText(filePath) {
  try {
    const text = fs.readFileSync(filePath, 'utf-8');

    logger.info('Plain text file parsed successfully', {
      filePath,
      textLength: text.length
    });

    return {
      success: true,
      text,
      metadata: {}
    };
  } catch (err) {
    logger.error('Failed to parse plain text file', { filePath, error: err.message });
    return { success: false, error: err.message };
  }
}

export function getFileExtension(filePath) {
  return path.extname(filePath).toLowerCase();
}

export async function parseDocument(filePath) {
  const ext = getFileExtension(filePath);

  switch (ext) {
    case '.pdf':
      return await parsePDF(filePath);

    case '.docx':
    case '.doc':
      return await parseWord(filePath);

    case '.txt':
      return await parsePlainText(filePath);

    default:
      logger.error('Unsupported file format', { filePath, ext });
      return {
        success: false,
        error: `Unsupported file format: ${ext}. Supported formats: PDF, DOCX, TXT`
      };
  }
}

export function getSupportedFormats() {
  return ['.pdf', '.docx', '.doc', '.txt'];
}

export function isSupportedFormat(filePath) {
  const ext = getFileExtension(filePath);
  return getSupportedFormats().includes(ext);
}
