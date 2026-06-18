(() => {
  if (globalThis.__RTRVR_OFFSCREEN_PING_BOOTSTRAP__) return;
  globalThis.__RTRVR_OFFSCREEN_PING_BOOTSTRAP__ = true;

  chrome.runtime.onMessage.addListener(message => {
    if (message?.type !== 'PING') return false;

    try {
      chrome.runtime.sendMessage({ type: 'PONG', pingId: message.pingId, bootstrap: true });
    } catch {
      // The service worker may have gone away between ping and response.
    }

    return false;
  });
})();
