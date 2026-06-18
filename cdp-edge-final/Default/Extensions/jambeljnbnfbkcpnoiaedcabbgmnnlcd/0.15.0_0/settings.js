const defaultSettings = {
  testIdAttributeName: "data-testid",
  targetLanguage: "playwright-test",
  sidepanel: true,
  experimental: false,
  playInIncognito: false
};
async function loadSettings() {
  const [isAllowedIncognitoAccess, loadedPreferences] = await Promise.all([
    chrome.extension.isAllowedIncognitoAccess(),
    chrome.storage.sync.get(["testIdAttributeName", "targetLanguage", "sidepanel", "playInIncognito", "experimental"])
  ]);
  return { ...defaultSettings, ...loadedPreferences, playInIncognito: !!loadedPreferences.playInIncognito && isAllowedIncognitoAccess };
}
async function storeSettings(settings) {
  await chrome.storage.sync.set(settings);
}
const listeners = /* @__PURE__ */ new Map();
function addSettingsChangedListener(listener) {
  const wrappedListener = ({ testIdAttributeName, targetLanguage, sidepanel, playInIncognito, experimental }) => {
    if (!testIdAttributeName && !targetLanguage && sidepanel && playInIncognito && experimental)
      return;
    loadSettings().then(listener).catch(() => {
    });
  };
  listeners.set(listener, wrappedListener);
  chrome.storage.sync.onChanged.addListener(wrappedListener);
}
function removeSettingsChangedListener(listener) {
  const wrappedListener = listeners.get(listener);
  if (!wrappedListener)
    return;
  chrome.storage.sync.onChanged.removeListener(wrappedListener);
}
export {
  addSettingsChangedListener as a,
  defaultSettings as d,
  loadSettings as l,
  removeSettingsChangedListener as r,
  storeSettings as s
};
//# sourceMappingURL=settings.js.map
