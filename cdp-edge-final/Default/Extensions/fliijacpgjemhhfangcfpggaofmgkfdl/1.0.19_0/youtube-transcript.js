(() => {
const _sleep = (ms) => new Promise((r) => setTimeout(r, ms));

async function waitForYouTubeVideo({ timeoutMs = 10000 } = {}) {
  const start = Date.now();
  while (Date.now() - start < timeoutMs) {
    const v = document.querySelector('video');
    if (v && v.readyState >= 1) return v;
    await _sleep(100);
  }
  return null;
}

/**
 * Opens the transcript panel by clicking the "Show transcript" button.
 * YouTube (April 2026): the button is hidden inside the collapsed description
 * so we must first expand it via the "...more" button, then click the
 * transcript button that appears.
 */
async function _findAndOpenTranscriptPanel({ waitAfterClickMs = 2000 } = {}) {
  // Step 1 (April 2026): expand the description if it's collapsed so
  // the "Show transcript" button becomes available in the DOM.
  const expandSelectors = [
    'tp-yt-paper-button#more',
    '#description-inline-expander #expand',
    'ytd-text-inline-expander tp-yt-paper-button',
    '[aria-label="More"]',
    'yt-description-preview-vm button',
  ];
  for (const s of expandSelectors) {
    const btn = document.querySelector(s);
    if (btn && btn.offsetParent !== null) {
      btn.click();
      await _sleep(600); // short wait for DOM to update
      break;
    }
  }

  // Step 2: find and click the Show transcript button.
  // Ordered from most-specific (April 2026) to broadest fallback.
  const transcriptSelectors = [
    // April 2026: button inside the engagement-panel trigger area
    'ytd-video-description-transcript-section-renderer button',
    // aria-label based (most reliable across A/B variants)
    '[aria-label="Show transcript"]',
    'button[aria-label="Show transcript"]',
    '[aria-label*="transcript" i]',
    'button[aria-label*="Transcript" i]',
  ];

  for (const s of transcriptSelectors) {
    const btn = document.querySelector(s);
    if (btn) {
      btn.click();
      await _sleep(waitAfterClickMs);
      return true;
    }
  }
  return false;
}

/**
 * Waits for any of the known transcript containers to appear in the DOM.
 * April 2026: YouTube now uses an engagement-panel with a stable target-id.
 */
async function _waitForTranscriptContainer({ timeoutMs = 8000 } = {}) {
  const selectors = [
    // April 2026: engagement-panel with stable target-id (most reliable)
    'ytd-engagement-panel-section-list-renderer[target-id="engagement-panel-searchable-transcript"]',
    // mid-2026 possible new variant
    '[target-id="engagement-panel-searchable-transcript"]',
    // 2025 macro-markers panel (kept as fallback)
    'ytd-macro-markers-list-renderer #contents',
    'ytd-macro-markers-list-renderer',
    // Older selectors kept as fallback
    '#segments-container',
    'ytd-transcript-segment-list-renderer',
    'ytd-transcript-body-renderer',
  ];

  const start = Date.now();
  while (Date.now() - start < timeoutMs) {
    for (const s of selectors) {
      const el = document.querySelector(s);
      if (el) return el;
    }
    await _sleep(150);
  }
  return null;
}

/**
 * Extracts text from individual transcript segment elements.
 * April 2026: YouTube's new panel uses .segment-text elements.
 * Falls back through several older patterns for compatibility.
 */
function _extractTextFromContainer(container) {
  // --- April 2026: .segment-text inside engagement-panel ---
  const segmentTextNodes = container.querySelectorAll('.segment-text');
  if (segmentTextNodes && segmentTextNodes.length) {
    const text = Array.from(segmentTextNodes)
      .map((n) => (n.textContent || '').replace(/\s+/g, ' ').trim())
      .filter(Boolean)
      .join(' ')
      .replace(/\s+/g, ' ')
      .trim();
    if (text) return text;
  }

  // --- April 2026 alternate: yt-formatted-string inside segment rows ---
  const segmentRows = container.querySelectorAll('ytd-transcript-segment-renderer yt-formatted-string');
  if (segmentRows && segmentRows.length) {
    const text = Array.from(segmentRows)
      .map((n) => (n.textContent || '').replace(/\s+/g, ' ').trim())
      .filter(Boolean)
      .join(' ')
      .replace(/\s+/g, ' ')
      .trim();
    if (text) return text;
  }

  // --- 2025 view-model selectors (kept as fallback) ---
  const newSegmentSelectors = [
    'transcript-segment-view-model yt-formatted-string',
    'transcript-segment-view-model span.yt-core-attributed-string',
    'transcript-segment-view-model span[role="text"]',
    'transcript-segment-view-model span',
    'macro-markers-panel-item-view-model yt-formatted-string',
    'macro-markers-panel-item-view-model span.yt-core-attributed-string',
  ];

  for (const sel of newSegmentSelectors) {
    const nodes = container.querySelectorAll(sel);
    if (nodes && nodes.length) {
      const text = Array.from(nodes)
        .map((n) => (n.textContent || '').replace(/\s+/g, ' ').trim())
        .filter(Boolean)
        .join(' ')
        .replace(/\s+/g, ' ')
        .trim();
      if (text) return text;
    }
  }

  // --- Old selector: [data-text] ---
  const segs = container.querySelectorAll('[data-text]');
  if (segs && segs.length) {
    const text = Array.from(segs)
      .map((n) => n.getAttribute('data-text') || n.textContent || '')
      .join(' ')
      .replace(/\s+/g, ' ')
      .trim();
    if (text) return text;
  }

  // --- Final fallback: raw textContent, stripping timestamps ---
  const rawText = (container.textContent || '')
    .replace(/\b\d{1,2}:\d{2}(?::\d{2})?\b/g, ' ')
    .replace(/[\n\r]+/g, ' ')
    .replace(/\s+/g, ' ')
    .trim();
  return rawText || null;
}

async function extractTranscriptFromDOM({ minLength = 50 } = {}) {
  await _findAndOpenTranscriptPanel({});
  const container = await _waitForTranscriptContainer({});
  if (!container) return null;

  const text = _extractTextFromContainer(container);
  if (text && text.length >= minLength) return text;
  return null;
}

function _injectAndGetCaptions() {
  return new Promise((resolve) => {
    const script = document.createElement('script');
    script.textContent = `(() => { try { const r = window.ytInitialPlayerResponse; const c = r && r.captions ? r.captions : null; window.postMessage({ type: 'YT_PLAYER_RESPONSE', data: c }, '*'); } catch (e) { window.postMessage({ type: 'YT_PLAYER_RESPONSE', data: null }, '*'); } })();`;

    const handler = (ev) => {
      if (ev && ev.data && ev.data.type === 'YT_PLAYER_RESPONSE') {
        window.removeEventListener('message', handler);
        if (script.parentNode) script.parentNode.removeChild(script);
        resolve(ev.data.data || null);
      }
    };

    window.addEventListener('message', handler);
    document.documentElement.appendChild(script);
    setTimeout(() => {
      window.removeEventListener('message', handler);
      if (script.parentNode) script.parentNode.removeChild(script);
      resolve(null);
    }, 3000);
  });
}

async function getCaptionTracksFromPage() {
  const captionsData = await _injectAndGetCaptions();
  const tracklist = captionsData && captionsData.playerCaptionsTracklistRenderer;
  const tracks = tracklist && Array.isArray(tracklist.captionTracks)
    ? tracklist.captionTracks
    : [];
  return tracks;
}

function _addOrUpdateUrlParam(url, key, value) {
  const u = new URL(url);
  u.searchParams.set(key, value);
  return u.toString();
}

function _formatMs(ms) {
  const s = Math.floor(ms / 1000);
  const h = Math.floor(s / 3600);
  const m = Math.floor((s % 3600) / 60);
  const sec = s % 60;
  if (h > 0) return `${h}:${String(m).padStart(2, '0')}:${String(sec).padStart(2, '0')}`;
  return `${m}:${String(sec).padStart(2, '0')}`;
}

function _parseJson3ToText(json, { includeTimestamps = false } = {}) {
  const events = Array.isArray(json?.events) ? json.events : [];
  const parts = [];
  for (const e of events) {
    if (!e) continue;
    const segs = Array.isArray(e.segs) ? e.segs : [];
    const text = segs.map((s) => s?.utf8 || '').join('').replace(/\s+/g, ' ').trim();
    if (!text) continue;
    if (includeTimestamps) {
      const t = _formatMs(e.tStartMs || 0);
      parts.push(`[${t}] ${text}`);
    } else {
      parts.push(text);
    }
  }
  return parts.join(' ').replace(/\s+/g, ' ').trim();
}

function _parseXmlToText(xmlString, { includeTimestamps = false } = {}) {
  let doc;
  try {
    doc = new DOMParser().parseFromString(xmlString, 'text/xml');
  } catch {
    return '';
  }
  const nodes = Array.from(doc.querySelectorAll('text, p'));
  const parts = [];
  for (const n of nodes) {
    const raw = (n.textContent || '').replace(/\s+/g, ' ').trim();
    if (!raw) continue;
    if (includeTimestamps) {
      const start = Number(n.getAttribute('start') || n.getAttribute('t') || 0) * (n.hasAttribute('t') ? 1 : 1000);
      const t = _formatMs(isNaN(start) ? 0 : start);
      parts.push(`[${t}] ${raw}`);
    } else {
      parts.push(raw);
    }
  }
  return parts.join(' ').replace(/\s+/g, ' ').trim();
}

async function fetchTranscriptFromCaptionTrack(track, {
  includeTimestamps = false,
  translateTo = null,
  fetchFn = fetch,
} = {}) {
  if (!track || !track.baseUrl) return null;
  let url = track.baseUrl;
  if (!/([?&])fmt=/.test(url)) url = _addOrUpdateUrlParam(url, 'fmt', 'json3');
  if (translateTo) url = _addOrUpdateUrlParam(url, 'tlang', translateTo);

  // YouTube (mid-2025) requires session cookies on the caption endpoint.
  // Using 'include' sends the browser's existing youtube.com cookies,
  // which works for the extension's content-script context since it runs
  // on the youtube.com origin.
  let res;
  try {
    res = await fetchFn(url, { credentials: 'include' });
  } catch (e) {
    return null;
  }

  if (!res.ok) {
    // If 'include' fails (e.g. logged-out user), fall back to 'omit'
    // so we at least try public captions.
    try {
      res = await fetchFn(url, { credentials: 'omit' });
    } catch (e) {
      return null;
    }
    if (!res.ok) return null;
  }

  const ct = res.headers.get('content-type') || '';
  if (ct.includes('application/json')) {
    const data = await res.json();
    const text = _parseJson3ToText(data, { includeTimestamps });
    return text || null;
  }
  const txt = await res.text();
  try {
    const asJson = JSON.parse(txt);
    const text = _parseJson3ToText(asJson, { includeTimestamps });
    if (text) return text;
  } catch {}
  const text = _parseXmlToText(txt, { includeTimestamps });
  return text || null;
}

function pickBestCaptionTrack(tracks, {
  preferLangs = (typeof navigator !== 'undefined' && navigator.languages) ? navigator.languages : [
    (typeof navigator !== 'undefined' && navigator.language) ? navigator.language : 'en',
    'en'
  ],
  preferHuman = true,
} = {}) {
  if (!Array.isArray(tracks) || tracks.length === 0) return null;
  const norm = (s) => (s || '').toLowerCase();
  const langs = preferLangs.map(norm);

  if (preferHuman) {
    const human = tracks.filter((t) => norm(t.kind) !== 'asr');
    for (const l of langs) {
      const m = human.find((t) => norm(t.languageCode || t.languageName?.simpleText).startsWith(l));
      if (m) return m;
    }
    if (human[0]) return human[0];
  }
  for (const l of langs) {
    const m = tracks.find((t) => norm(t.languageCode || t.languageName?.simpleText).startsWith(l));
    if (m) return m;
  }
  return tracks[0];
}

async function getYouTubeVideoMetadata() {
  const title = document.querySelector('h1.ytd-watch-metadata yt-formatted-string')?.textContent
    || document.querySelector('h1.title')?.textContent
    || document.title;
  const channel = document.querySelector('#text.ytd-channel-name a')?.textContent
    || document.querySelector('.ytd-channel-name a')?.textContent
    || null;
  return { title: (title || '').trim(), channel: channel ? channel.trim() : null, url: location.href };
}

async function extractYouTubeTranscript({
  method = 'auto',
  minLength = 50,
  includeTimestamps = false,
  preferLangs,
  translateTo = null,
  fetchFn = fetch,
  waitForVideo = true,
} = {}) {
  if (waitForVideo) await waitForYouTubeVideo({});

  if (method === 'dom' || method === 'auto') {
    const domText = await extractTranscriptFromDOM({ minLength });
    if (domText && domText.length >= minLength) return domText;
    if (method === 'dom') return null;
  }

  const tracks = await getCaptionTracksFromPage();
  if (!tracks || !tracks.length) return null;
  const track = pickBestCaptionTrack(tracks, { preferLangs });
  if (!track) return null;
  const text = await fetchTranscriptFromCaptionTrack(track, { includeTimestamps, translateTo, fetchFn });
  if (text && text.length >= minLength) return text;
  return null;
}

const api = {
  waitForYouTubeVideo,
  extractTranscriptFromDOM,
  getCaptionTracksFromPage,
  fetchTranscriptFromCaptionTrack,
  pickBestCaptionTrack,
  getYouTubeVideoMetadata,
  extractYouTubeTranscript,
};

if (typeof window !== 'undefined') {
  window.YouTubeTranscriptExtractor = api;
}
if (typeof self !== 'undefined' && !('window' in self)) {
  self.YouTubeTranscriptExtractor = api;
}
if (typeof module !== 'undefined' && module.exports) {
  module.exports = api;
}
})();
