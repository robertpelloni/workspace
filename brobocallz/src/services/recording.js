import fs from 'fs';
import path from 'path';
import { fileURLToPath } from 'url';
import Twilio from 'twilio';
import logger from '../utils/logger.js';

const __dirname = path.dirname(fileURLToPath(import.meta.url));

// Initialize Twilio client
const twilioClient = process.env.TWILIO_ACCOUNT_SID && process.env.TWILIO_AUTH_TOKEN
  ? Twilio(process.env.TWILIO_ACCOUNT_SID, process.env.TWILIO_AUTH_TOKEN)
  : null;

// Recording status enum
const RecordingStatus = {
  RECORDING: 'recording',
  PROCESSING: 'processing',
  COMPLETED: 'completed',
  FAILED: 'failed'
};

// Recording storage map for tracking active recordings
const recordingMap = new Map();

/**
 * Get recording storage directory
 */
function getStorageDir() {
  return process.env.RECORDING_STORAGE_DIR || './recordings';
}

/**
 * Get retention period in days
 */
function getRetentionDays() {
  return parseInt(process.env.RECORDING_RETENTION_DAYS || '30', 10);
}

/**
 * Get recording format
 */
function getRecordingFormat() {
  return process.env.RECORDING_FORMAT || 'wav';
}

/**
 * Check if call recording is enabled
 */
export function isRecordingEnabled() {
  return process.env.RECORD_CALLS === 'true' && twilioClient !== null;
}

/**
 * Ensure recordings directory exists
 */
function ensureStorageDir() {
  const storageDir = getStorageDir();
  if (!fs.existsSync(storageDir)) {
    fs.mkdirSync(storageDir, { recursive: true });
    logger.info('Created recordings storage directory', { storageDir });
  }
}

/**
 * Get organized directory path for a call
 */
function getRecordingPath(callSid) {
  const date = new Date();
  const year = date.getFullYear();
  const month = String(date.getMonth() + 1).padStart(2, '0');

  const yearDir = path.join(getStorageDir(), String(year));
  const monthDir = path.join(yearDir, month);

  // Ensure directories exist
  if (!fs.existsSync(yearDir)) {
    fs.mkdirSync(yearDir, { recursive: true });
  }
  if (!fs.existsSync(monthDir)) {
    fs.mkdirSync(monthDir, { recursive: true });
  }

  return path.join(monthDir, `${callSid}.${getRecordingFormat()}`);
}

/**
 * Initialize recording for a call
 */
export function initializeRecording(callSid, callData) {
  if (!isRecordingEnabled()) {
    logger.debug('Recording is disabled', { callSid });
    return null;
  }

  try {
    const recordingInfo = {
      callSid,
      from: callData.from,
      to: callData.to,
      direction: callData.direction,
      startTime: new Date(),
      status: RecordingStatus.RECORDING,
      recordingSid: null,
      recordingUrl: null,
      localPath: null
    };

    recordingMap.set(callSid, recordingInfo);
    logger.info('Recording initialized', { callSid });
    return recordingInfo;
  } catch (err) {
    logger.error('Failed to initialize recording', { callSid, error: err.message });
    return null;
  }
}

/**
 * Update recording with Twilio recording details
 */
export function updateRecordingDetails(callSid, recordingSid, recordingUrl) {
  if (!recordingMap.has(callSid)) {
    logger.warn('Recording not found for update', { callSid });
    return;
  }

  const recordingInfo = recordingMap.get(callSid);
  recordingInfo.recordingSid = recordingSid;
  recordingInfo.recordingUrl = recordingUrl;
  recordingInfo.status = RecordingStatus.PROCESSING;

  logger.info('Recording details updated', { callSid, recordingSid });
}

/**
 * Download recording from Twilio and save locally
 */
export async function downloadRecording(callSid) {
  if (!isRecordingEnabled()) {
    return null;
  }

  const recordingInfo = recordingMap.get(callSid);
  if (!recordingInfo || !recordingInfo.recordingUrl) {
    logger.warn('No recording info or URL found for download', { callSid });
    return null;
  }

  try {
    logger.info('Starting recording download', { callSid, recordingSid: recordingInfo.recordingSid });

    // Get recording data from Twilio
    const recording = await twilioClient.recordings(recordingInfo.recordingSid).fetch();

    if (!recording || !recording.mediaUrl) {
      throw new Error('Invalid recording data from Twilio');
    }

    // Download recording
    const response = await fetch(recording.mediaUrl);
    if (!response.ok) {
      throw new Error(`Failed to download recording: ${response.statusText}`);
    }

    const buffer = await response.arrayBuffer();

    // Save to local filesystem
    ensureStorageDir();
    const localPath = getRecordingPath(callSid);
    fs.writeFileSync(localPath, Buffer.from(buffer));

    // Update recording info
    recordingInfo.localPath = localPath;
    recordingInfo.status = RecordingStatus.COMPLETED;
    recordingInfo.downloadTime = new Date();
    recordingInfo.fileSize = Buffer.byteLength(buffer);

    logger.info('Recording downloaded successfully', {
      callSid,
      recordingSid: recordingInfo.recordingSid,
      localPath,
      fileSize: recordingInfo.fileSize
    });

    return recordingInfo;
  } catch (err) {
    logger.error('Failed to download recording', { callSid, error: err.message });
    if (recordingMap.has(callSid)) {
      recordingMap.get(callSid).status = RecordingStatus.FAILED;
    }
    return null;
  }
}

/**
 * Get recording info for a call
 */
export function getRecording(callSid) {
  return recordingMap.get(callSid) || null;
}

/**
 * List all recordings
 */
export function listRecordings() {
  return Array.from(recordingMap.values()).map(r => ({
    callSid: r.callSid,
    from: r.from,
    to: r.to,
    direction: r.direction,
    startTime: r.startTime,
    status: r.status,
    localPath: r.localPath,
    recordingUrl: r.recordingUrl,
    fileSize: r.fileSize
  }));
}

/**
 * Clean up old recordings based on retention policy
 */
export function cleanupOldRecordings() {
  try {
    const retentionDays = getRetentionDays();
    const cutoffDate = new Date(Date.now() - retentionDays * 24 * 60 * 60 * 1000);
    const storageDir = getStorageDir();

    if (!fs.existsSync(storageDir)) {
      logger.info('No recordings directory to clean up', { storageDir });
      return { deletedCount: 0, freedSpace: 0 };
    }

    let deletedCount = 0;
    let freedSpace = 0;

    function processDirectory(dir) {
      const files = fs.readdirSync(dir);

      for (const file of files) {
        const filePath = path.join(dir, file);
        const stat = fs.statSync(filePath);

        if (stat.isDirectory()) {
          processDirectory(filePath);
        } else if (file.endsWith('.wav') || file.endsWith('.mp3')) {
          const fileDate = stat.mtime;
          if (fileDate < cutoffDate) {
            const fileSize = stat.size;
            fs.unlinkSync(filePath);
            deletedCount++;
            freedSpace += fileSize;

            logger.debug('Deleted old recording file', { filePath, fileDate, fileSize });
          }
        }
      }
    }

    processDirectory(storageDir);

    logger.info('Recording cleanup completed', {
      retentionDays,
      deletedCount,
      freedSpaceBytes: freedSpace,
      freedSpaceMB: (freedSpace / 1024 / 1024).toFixed(2)
    });

    return { deletedCount, freedSpace };
  } catch (err) {
    logger.error('Failed to cleanup old recordings', { error: err.message });
    return { deletedCount: 0, freedSpace: 0 };
  }
}

/**
 * Delete a specific recording
 */
export function deleteRecording(callSid) {
  const recordingInfo = recordingMap.get(callSid);
  if (!recordingInfo) {
    return { success: false, message: 'Recording not found' };
  }

  try {
    if (recordingInfo.localPath && fs.existsSync(recordingInfo.localPath)) {
      fs.unlinkSync(recordingInfo.localPath);
      logger.info('Deleted recording file', { callSid, localPath: recordingInfo.localPath });
    }

    recordingMap.delete(callSid);
    logger.info('Recording entry removed', { callSid });

    return { success: true, message: 'Recording deleted successfully' };
  } catch (err) {
    logger.error('Failed to delete recording', { callSid, error: err.message });
    return { success: false, message: err.message };
  }
}

/**
 * Get recording statistics
 */
export function getRecordingStats() {
  const recordings = listRecordings();
  const now = new Date();

  const totalRecordings = recordings.length;
  const completedRecordings = recordings.filter(r => r.status === RecordingStatus.COMPLETED);
  const failedRecordings = recordings.filter(r => r.status === RecordingStatus.FAILED);

  let totalFileSize = 0;
  const recentRecordings = recordings.filter(r => {
    const daysSinceStart = (now - r.startTime) / (1000 * 60 * 60 * 24);
    return daysSinceStart <= 7;
  });

  for (const recording of completedRecordings) {
    if (recording.fileSize) {
      totalFileSize += recording.fileSize;
    }
  }

  const avgFileSize = completedRecordings.length > 0
    ? totalFileSize / completedRecordings.length
    : 0;

  return {
    summary: {
      total: totalRecordings,
      completed: completedRecordings.length,
      failed: failedRecordings.length,
      recent: recentRecordings.length
    },
    storage: {
      totalFileSizeBytes: totalFileSize,
      totalFileSizeMB: (totalFileSize / 1024 / 1024).toFixed(2),
      avgFileSizeBytes: avgFileSize,
      avgFileSizeKB: (avgFileSize / 1024).toFixed(2)
    },
    retentionDays: getRetentionDays(),
    recordingEnabled: isRecordingEnabled()
  };
}

/**
 * Get recordings for a date range
 */
export function getRecordingsByDateRange(startDate, endDate) {
  const recordings = listRecordings();
  const start = new Date(startDate);
  const end = new Date(endDate);

  return recordings.filter(r => r.startTime >= start && r.startTime <= end);
}
