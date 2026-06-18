(function() {
  "use strict";
  const CONTEXT_MENU_ID = "get-tldr-summarize-selection";
  chrome.runtime.onInstalled.addListener((details) => {
    console.log("Get TLDR Extension installed/updated:", details.reason);
    if (details.reason === "install") {
      console.log("Welcome to Get TLDR!");
    } else if (details.reason === "update") {
      console.log("Get TLDR updated to version:", chrome.runtime.getManifest().version);
    }
    chrome.contextMenus.create({
      id: CONTEXT_MENU_ID,
      title: "Summarize selected text with Get TLDR",
      contexts: ["selection"]
    });
  });
  chrome.action.onClicked.addListener((tab) => {
    console.log("Extension icon clicked on tab:", tab.url);
  });
  chrome.contextMenus.onClicked.addListener((info, tab) => {
    if (info.menuItemId === CONTEXT_MENU_ID && info.selectionText) {
      handleTextSelection(info.selectionText, tab);
    }
  });
  async function handleTextSelection(selectedText, tab) {
    try {
      if (!selectedText || selectedText.trim().length === 0) {
        console.error("No text selected");
        return;
      }
      const trimmedText = selectedText.trim();
      if (trimmedText.length < 10) {
        showNotification("Selection too short", "Please select at least 10 characters to summarize.");
        return;
      }
      if (trimmedText.length > 5e4) {
        showNotification("Selection too long", "Please select less than 50,000 characters.");
        return;
      }
      const apiKey = await getStoredApiKey();
      if (!apiKey) {
        showNotification("API Key Required", "Please set your API key in the extension popup first.");
        return;
      }
      const tabUrl = tab?.url || "Unknown";
      const tabTitle = tab?.title || "Unknown";
      const lastPrompt = await getLastSelectedPrompt();
      showNotification("Processing...", "Summarizing selected text...");
      const summary = await summarizeSelectedText(apiKey, trimmedText, tabUrl, lastPrompt);
      await saveSummaryToStorage(summary, tabTitle, tabUrl, trimmedText.split(/\s+/).length);
      if (tab?.id) {
        await openSidebarWithSummary(tab.id, {
          summary: summary.summary,
          selectedText: trimmedText,
          tokensUsed: summary.tokensUsed,
          wordCount: summary.wordCount,
          url: tabUrl,
          title: tabTitle
        });
      } else {
        showNotification("Summary Complete", "Summary saved. Open the extension popup to view it.");
      }
    } catch (error) {
      console.error("Failed to summarize selected text:", error);
      showNotification("Summarization Failed", error instanceof Error ? error.message : "An error occurred");
    }
  }
  async function openSidebarWithSummary(tabId, data) {
    try {
      try {
        await chrome.scripting.executeScript({
          target: { tabId },
          files: ["marked.min.js"]
        });
        console.log("Marked library injected successfully");
      } catch (e) {
        console.log("Marked library injection skipped (might already be injected):", e);
      }
      let scriptInjected = false;
      try {
        const injectionResults = await chrome.scripting.executeScript({
          target: { tabId },
          files: ["content-sidebar.js"]
        });
        console.log("Sidebar content script injected successfully, results:", injectionResults);
        scriptInjected = true;
      } catch (e) {
        console.log("Sidebar script injection skipped (might already be injected):", e);
        scriptInjected = false;
      }
      try {
        await chrome.scripting.insertCSS({
          target: { tabId },
          files: ["content-sidebar.css"]
        });
        console.log("Sidebar CSS injected successfully");
      } catch (e) {
        console.log("Sidebar CSS injection skipped (might already be injected):", e);
      }
      await new Promise((resolve) => setTimeout(resolve, 300));
      console.log("Sending SHOW_SIDEBAR_SUMMARY message to tab", tabId);
      try {
        const response = await chrome.tabs.sendMessage(tabId, {
          type: "SHOW_SIDEBAR_SUMMARY",
          data
        });
        console.log("Message sent successfully, response:", response);
      } catch (messageError) {
        console.error("Failed to send message to content script:", messageError);
        console.log("Retrying message send after delay...");
        await new Promise((resolve) => setTimeout(resolve, 500));
        try {
          const retryResponse = await chrome.tabs.sendMessage(tabId, {
            type: "SHOW_SIDEBAR_SUMMARY",
            data
          });
          console.log("Retry successful, response:", retryResponse);
        } catch (retryError) {
          console.error("Retry failed:", retryError);
          console.log("Attempting direct sidebar invocation as final fallback...");
          try {
            await chrome.scripting.executeScript({
              target: { tabId },
              world: "MAIN",
              func: (summaryData) => {
                console.log("[TLDR Fallback] Direct invocation, checking window.tldrSidebar:", typeof window.tldrSidebar);
                if (window.tldrSidebar) {
                  console.log("[TLDR Fallback] Calling showSummary directly");
                  window.tldrSidebar.showSummary(summaryData);
                } else {
                  console.error("[TLDR Fallback] window.tldrSidebar not found!");
                }
              },
              args: [data]
            });
            console.log("Direct invocation attempted");
          } catch (directError) {
            console.error("Direct invocation also failed:", directError);
            throw retryError;
          }
        }
      }
    } catch (error) {
      console.error("Failed to open sidebar:", error);
      showNotification("Summary Complete", "Summary saved. View it in the extension popup or refresh the page and try again.");
    }
  }
  async function getStoredApiKey() {
    return new Promise((resolve) => {
      chrome.storage.local.get(["get_tldr_api_key"], (result) => {
        resolve(result.get_tldr_api_key || null);
      });
    });
  }
  async function getLastSelectedPrompt() {
    return new Promise((resolve) => {
      chrome.storage.local.get(["get_tldr_last_prompt", "get_tldr_api_key"], async (result) => {
        const promptId = result.get_tldr_last_prompt;
        const apiKey = result.get_tldr_api_key;
        if (!promptId) {
          resolve("Provide a concise summary of the main points in this selected text.");
          return;
        }
        if (apiKey) {
          try {
            const response = await fetch("https://www.get-tldr.com/api/v1/prompts", {
              method: "GET",
              headers: {
                "X-API-Key": apiKey,
                "Content-Type": "application/json"
              }
            });
            if (response.ok) {
              const data = await response.json();
              if (data.prompts && Array.isArray(data.prompts)) {
                const apiPrompt = data.prompts.find((p) => p.id === promptId);
                if (apiPrompt) {
                  resolve(apiPrompt.content || apiPrompt.prompt || "Provide a concise summary of the main points in this selected text.");
                  return;
                }
              }
            }
          } catch (error) {
            console.error("Failed to fetch prompts:", error);
          }
        }
        const defaultPrompts = {
          "default": "Provide a concise summary of the main points in this content.",
          "bullet-points": "Summarize this content as bullet points highlighting the key information.",
          "executive": "Create an executive summary focusing on business implications and key decisions.",
          "technical": "Summarize the technical aspects, implementation details, and key technical points.",
          "action-items": "Extract actionable items, tasks, and next steps from this content."
        };
        resolve(defaultPrompts[promptId] || "Provide a concise summary of the main points in this selected text.");
      });
    });
  }
  async function summarizeSelectedText(apiKey, text, sourceUrl, customPrompt) {
    const API_BASE_URL = "https://www.get-tldr.com/api/v1";
    const response = await fetch(`${API_BASE_URL}/summarize`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        "X-API-Key": apiKey
      },
      body: JSON.stringify({
        input: text,
        system_prompt: customPrompt,
        metadata: {
          source_url: sourceUrl,
          source_type: "text_selection"
        }
      })
    });
    if (!response.ok) {
      const errorData = await response.json().catch(() => ({}));
      throw new Error(errorData.message || `API request failed with status ${response.status}`);
    }
    const data = await response.json();
    const tokensUsed = typeof data.total_tokens === "number" && data.total_tokens || (typeof data.input_tokens === "number" && typeof data.output_tokens === "number" ? data.input_tokens + data.output_tokens : 0);
    const wordCount = typeof data.summary === "string" ? data.summary.trim().split(/\s+/).length : 0;
    return {
      summary: data.summary,
      tokensUsed,
      wordCount
    };
  }
  async function handleYouTubeSummarization(data, _tab, saveToStorage = false) {
    try {
      const apiKey = await getStoredApiKey();
      if (!apiKey) {
        throw new Error("API key not found. Please set your API key in the extension popup.");
      }
      const promptText = data.prompt || "Provide a comprehensive summary of this YouTube video, highlighting the main topics, key points, and important takeaways.";
      const summary = await summarizeYouTubeUrl(apiKey, data.url, promptText);
      if (saveToStorage) {
        await saveSummaryToStorage(summary, data.title, data.url, summary.wordCount);
      }
      return {
        summary: summary.summary,
        tokensUsed: summary.tokensUsed,
        wordCount: summary.wordCount
      };
    } catch (error) {
      console.error("YouTube summarization failed:", error instanceof Error ? error.message : String(error));
      throw error;
    }
  }
  async function summarizeYouTubeUrl(apiKey, videoUrl, customPrompt) {
    const API_BASE_URL = "https://www.get-tldr.com/api/v1";
    const response = await fetch(`${API_BASE_URL}/summarize`, {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
        "X-API-Key": apiKey
      },
      body: JSON.stringify({
        input: videoUrl,
        // Send the YouTube URL; the API extracts the transcript itself
        system_prompt: customPrompt
      })
    });
    if (!response.ok) {
      const errorData = await response.json().catch(() => ({}));
      throw new Error(errorData.message || `API request failed with status ${response.status}`);
    }
    const data = await response.json();
    const tokensUsed = typeof data.total_tokens === "number" && data.total_tokens || (typeof data.input_tokens === "number" && typeof data.output_tokens === "number" ? data.input_tokens + data.output_tokens : 0);
    const wordCount = typeof data.summary === "string" ? data.summary.trim().split(/\s+/).length : 0;
    return {
      summary: data.summary,
      tokensUsed,
      wordCount
    };
  }
  async function saveSummaryToStorage(summary, title, url, originalWordCount) {
    return new Promise((resolve, reject) => {
      chrome.storage.local.get(["get_tldr_saved_summaries", "get_tldr_user_stats"], (result) => {
        const existingSummaries = result.get_tldr_saved_summaries || [];
        const userStats = result.get_tldr_user_stats || {
          totalSummaries: 0,
          wordsProcessed: 0,
          tokensUsed: 0,
          lastUpdated: (/* @__PURE__ */ new Date()).toISOString()
        };
        const newSummary = {
          id: `summary_${Date.now()}_${Math.random().toString(36).substr(2, 9)}`,
          title: `[Selected Text] ${title}`,
          url,
          summary: summary.summary,
          prompt: "Context menu - selected text summary",
          tokensUsed: summary.tokensUsed,
          wordCount: summary.wordCount,
          createdAt: (/* @__PURE__ */ new Date()).toISOString(),
          tags: ["context-menu", "text-selection"]
        };
        const updatedSummaries = [newSummary, ...existingSummaries].slice(0, 1e3);
        const updatedStats = {
          totalSummaries: userStats.totalSummaries + 1,
          wordsProcessed: userStats.wordsProcessed + originalWordCount,
          tokensUsed: userStats.tokensUsed + summary.tokensUsed,
          lastUpdated: (/* @__PURE__ */ new Date()).toISOString()
        };
        chrome.storage.local.set({
          get_tldr_saved_summaries: updatedSummaries,
          get_tldr_user_stats: updatedStats
        }, () => {
          if (chrome.runtime.lastError) {
            reject(chrome.runtime.lastError);
          } else {
            resolve(newSummary);
          }
        });
      });
    });
  }
  function showNotification(title, message) {
    chrome.notifications.create({
      type: "basic",
      iconUrl: "icons/icon128.png",
      title,
      message,
      priority: 2
    });
  }
  chrome.runtime.onMessage.addListener((request, _sender, sendResponse) => {
    console.log("Background received message:", request);
    switch (request.type) {
      case "GET_TAB_INFO":
        chrome.tabs.query({ active: true, currentWindow: true }, (tabs) => {
          if (tabs[0]) {
            sendResponse({
              url: tabs[0].url,
              title: tabs[0].title,
              id: tabs[0].id
            });
          } else {
            sendResponse({ error: "No active tab found" });
          }
        });
        return true;
      // Keep message channel open for async response
      case "SUMMARIZE_YOUTUBE_VIDEO":
        (async () => {
          try {
            let tab = _sender.tab;
            const isFromContentScript = !!tab;
            if (!tab) {
              const [activeTab] = await chrome.tabs.query({ active: true, currentWindow: true });
              tab = activeTab;
            }
            const result = await handleYouTubeSummarization(request.data, tab, isFromContentScript);
            sendResponse(result);
          } catch (error) {
            sendResponse({ error: error instanceof Error ? error.message : "Unknown error" });
          }
        })();
        return true;
      // Keep message channel open for async response
      case "LOG_USAGE":
        console.log("Usage logged:", request.data);
        sendResponse({ success: true });
        break;
      default:
        console.log("Unknown message type:", request.type);
        sendResponse({ error: "Unknown message type" });
    }
  });
  chrome.storage.onChanged.addListener((changes, namespace) => {
    console.log("Storage changed in", namespace, ":", changes);
  });
  chrome.tabs.onUpdated.addListener((_tabId, changeInfo, tab) => {
    if (changeInfo.status === "complete" && tab.url) {
      console.log("Tab updated:", tab.url);
    }
  });
})();
//# sourceMappingURL=background.js.map
