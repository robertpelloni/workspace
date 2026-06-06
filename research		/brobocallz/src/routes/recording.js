export async function createRecording(req, res) {
  try {
    const { callSid, format = 'wav' } = req.body;

    if (!callSid) {
      return res.status(400).json({ error: 'Missing callSid' });
    }

    logger.info('Creating recording', { callSid, format });

    const audioData = Buffer.alloc(0);
    
    const result = await saveRecording(callSid, audioData, format);
    
    res.json({
      success: result.success,
      filePath: result.filePath,
      url: result.url
    });
  } catch (err) {
    logger.error('Error creating recording', { callSid, error: err.message });
    res.status(500).json({ error: 'Failed to create recording' });
  }
}

export async function listRecordings(req, res) {
  try {
    const { limit = 50 } = req.query;
    const limitNum = parseInt(limit) || 50;

    logger.info('Listing recordings', { limit: limitNum });

    const result = await getAllRecordings();
    
    if (!result.success) {
      return res.status(500).json({ error: result.error });
    }

    const recordingsList = result.recordings.slice(0, limitNum);
    
    res.json({
      success: true,
      count: result.count,
      totalSize: result.totalSize,
      recordings: recordingsList
    });
  } catch (err) {
    logger.error('Error listing recordings', { error: err.message });
    res.status(500).json({ error: 'Failed to list recordings' });
  }
}

export async function downloadRecording(req, res) {
  try {
    const { callSid } = req.params;

    if (!callSid) {
      return res.status(400).json({ error: 'Missing callSid parameter' });
    }

    logger.info('Downloading recording', { callSid });

    const recordingInfo = getRecording(callSid);
    
    if (!recordingInfo.exists) {
      return res.status(404).json({ error: 'Recording not found' });
    }

    res.download(recordingInfo.filePath, `recording_${callSid}.wav`);
    
    logger.info('Recording download initiated', { callSid, path: recordingInfo.filePath });
  } catch (err) {
    logger.error('Error downloading recording', { callSid, error: err.message });
    res.status(500).json({ error: 'Failed to download recording' });
  }
}

export async function deleteRecording(req, res) {
  try {
    const { callSid } = req.params;

    if (!callSid) {
      return res.status(400).json({ error: 'Missing callSid parameter' });
    }

    logger.info('Deleting recording', { callSid });

    const result = await deleteRecording(callSid);
    
    res.json(result);
  } catch (err) {
    logger.error('Error deleting recording', { callSid, error: err.message });
    res.status(500).json({ error: 'Failed to delete recording' });
  }
}

export async function getStats(req, res) {
  try {
    const stats = getRecordingStats();
    
    res.json({
      success: true,
      data: stats
    });
  } catch (err) {
    logger.error('Error getting recording stats', { error: err.message });
    res.status(500).json({ error: 'Failed to get recording stats' });
  }
}

export async function cleanupRecordings(req, res) {
  try {
    const retentionDays = parseInt(req.query.days || process.env.RECORDING_RETENTION_DAYS || '30');
    
    logger.info('Cleaning up old recordings', { retentionDays });

    const deletedCount = await cleanupOldRecordings();
    
    res.json({
      success: true,
      data: {
        deletedCount,
        retentionDays,
        remaining: recordings.size
      }
    });
  } catch (err) {
    logger.error('Error cleaning recordings', { error: err.message });
    res.status(500).json({ error: 'Failed to clean recordings' });
  }
}
