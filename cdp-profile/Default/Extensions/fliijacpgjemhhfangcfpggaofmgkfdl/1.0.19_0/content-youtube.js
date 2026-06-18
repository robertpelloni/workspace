/**
 * YouTube Video Summarizer
 * Adds a button below YouTube videos to summarize them
 */
// Load the YouTube transcript extractor library
(function loadTranscriptLibrary() {
    const script = document.createElement('script');
    script.src = chrome.runtime.getURL('youtube-transcript.js');
    script.onload = () => console.log('[Get TLDR] YouTube transcript library loaded');
    script.onerror = () => console.error('[Get TLDR] Failed to load YouTube transcript library');
    (document.head || document.documentElement).appendChild(script);
})();
class YouTubeSummarizer {
    constructor() {
        this.button = null;
        this.isProcessing = false;
        this.observer = null;
        this.retryCount = 0;
        this.maxRetries = 10;
        this.retryTimeout = null;
        console.log('[Get TLDR] YouTube content script loaded');
        this.init();
    }
    parseMarkdown(text) {
        // Simple markdown parser for common formatting
        let html = text;
        // Headers
        html = html.replace(/^### (.*$)/gim, '<h3 style="font-size: 18px; font-weight: 600; color: #87a96b; margin: 16px 0 8px 0;">$1</h3>');
        html = html.replace(/^## (.*$)/gim, '<h2 style="font-size: 20px; font-weight: 600; color: #87a96b; margin: 18px 0 10px 0;">$1</h2>');
        html = html.replace(/^# (.*$)/gim, '<h1 style="font-size: 22px; font-weight: 700; color: #87a96b; margin: 20px 0 12px 0;">$1</h1>');
        // Bold
        html = html.replace(/\*\*(.*?)\*\*/g, '<strong style="font-weight: 600; color: #ffffff;">$1</strong>');
        html = html.replace(/__(.*?)__/g, '<strong style="font-weight: 600; color: #ffffff;">$1</strong>');
        // Italic
        html = html.replace(/\*(.*?)\*/g, '<em style="font-style: italic;">$1</em>');
        html = html.replace(/_(.*?)_/g, '<em style="font-style: italic;">$1</em>');
        // Code inline
        html = html.replace(/`(.*?)`/g, '<code style="background: rgba(135, 169, 107, 0.2); padding: 2px 6px; border-radius: 4px; font-family: monospace; font-size: 14px;">$1</code>');
        // Links
        html = html.replace(/\[([^\]]+)\]\(([^)]+)\)/g, '<a href="$2" style="color: #87a96b; text-decoration: underline;" target="_blank">$1</a>');
        // Bullet points
        html = html.replace(/^\* (.*$)/gim, '<li style="margin-left: 20px; margin-bottom: 8px;">$1</li>');
        html = html.replace(/^- (.*$)/gim, '<li style="margin-left: 20px; margin-bottom: 8px;">$1</li>');
        // Numbered lists
        html = html.replace(/^\d+\. (.*$)/gim, '<li style="margin-left: 20px; margin-bottom: 8px;">$1</li>');
        // Wrap consecutive list items in ul
        html = html.replace(/(<li[^>]*>.*<\/li>\s*)+/g, (match) => {
            return '<ul style="margin: 12px 0; padding-left: 0; list-style-position: inside;">' + match + '</ul>';
        });
        // Line breaks
        html = html.replace(/\n\n/g, '<br><br>');
        html = html.replace(/\n/g, '<br>');
        return html;
    }
    init() {
        console.log('[Get TLDR] Initializing YouTube summarizer');
        // Wait for YouTube to load
        if (document.readyState === 'loading') {
            document.addEventListener('DOMContentLoaded', () => this.setup());
        }
        else {
            this.setup();
        }
    }
    setup() {
        console.log('[Get TLDR] Setting up, current URL:', window.location.href);
        // Watch for navigation first (YouTube is a SPA)
        this.watchForNavigation();
        // Check if we're on a YouTube video page
        if (!this.isVideoPage()) {
            console.log('[Get TLDR] Not on video page, will wait for navigation');
            return;
        }
        console.log('[Get TLDR] On video page, adding button');
        // Add button when page loads - try immediately and let retry logic handle timing
        this.addButton();
    }
    isVideoPage() {
        return window.location.pathname === '/watch' && window.location.search.includes('v=');
    }
    watchForNavigation() {
        // YouTube uses pushState for navigation, so we need to watch for URL changes
        let lastUrl = location.href;
        const checkUrlChange = () => {
            const currentUrl = location.href;
            if (currentUrl !== lastUrl) {
                lastUrl = currentUrl;
                this.handleNavigation();
            }
        };
        // Check periodically for URL changes
        setInterval(checkUrlChange, YouTubeSummarizer.URL_CHECK_INTERVAL_MS);
        // Also watch for DOM changes in video container only
        if (this.observer) {
            this.observer.disconnect();
        }
        // Throttle the mutation observer callback to avoid excessive firing
        let observerTimeout = null;
        this.observer = new MutationObserver(() => {
            if (observerTimeout)
                return; // Skip if already scheduled
            observerTimeout = window.setTimeout(() => {
                observerTimeout = null;
                if (this.isVideoPage()) {
                    // Check if button was removed from DOM
                    if (this.button && !document.body.contains(this.button)) {
                        console.log('[Get TLDR] Button was removed from DOM, re-adding');
                        this.button = null;
                        this.retryCount = 0;
                    }
                    // Only add if we don't have a button and not already retrying
                    if (!this.button && this.retryCount === 0) {
                        this.addButton();
                    }
                }
            }, YouTubeSummarizer.MUTATION_THROTTLE_MS); // Throttle mutations
        });
        // Observe only the video player area, not the entire document
        const videoContainer = document.querySelector('#movie_player, .html5-video-player, #player-container');
        if (videoContainer) {
            this.observer.observe(videoContainer, {
                childList: true,
                subtree: true
            });
        }
        else {
            // Fallback to body if video container not found, but with limited scope
            this.observer.observe(document.body, {
                childList: true,
                subtree: false // Only direct children, not entire subtree
            });
        }
    }
    handleNavigation() {
        console.log('[Get TLDR] Navigation detected, current URL:', window.location.href);
        // Clear any pending retry
        if (this.retryTimeout) {
            clearTimeout(this.retryTimeout);
            this.retryTimeout = null;
        }
        if (this.isVideoPage()) {
            console.log('[Get TLDR] Navigated to video page');
            // Remove old button if exists
            if (this.button) {
                this.button.remove();
                this.button = null;
            }
            // Reset retry count for new page
            this.retryCount = 0;
            // Add new button with initial delay
            setTimeout(() => this.addButton(), YouTubeSummarizer.BUTTON_ADD_DELAY_MS);
        }
        else {
            console.log('[Get TLDR] Navigated away from video page');
            // Remove button if we're not on a video page
            if (this.button) {
                this.button.remove();
                this.button = null;
            }
            this.retryCount = 0;
        }
    }
    addButton() {
        console.log('[Get TLDR] Attempting to add button (attempt', this.retryCount + 1, ')');
        // Clear any pending retry
        if (this.retryTimeout) {
            clearTimeout(this.retryTimeout);
            this.retryTimeout = null;
        }
        // Don't add if button already exists
        if (this.button && document.body.contains(this.button)) {
            console.log('[Get TLDR] Button already exists');
            this.retryCount = 0;
            return;
        }
        // Find the video player container
        const videoContainer = this.findVideoContainer();
        if (!videoContainer) {
            console.log('[Get TLDR] Video container not found');
            // Retry with exponential backoff, up to maxRetries
            if (this.retryCount < this.maxRetries) {
                this.retryCount++;
                const delay = Math.min(YouTubeSummarizer.RETRY_BASE_DELAY_MS * this.retryCount, YouTubeSummarizer.RETRY_MAX_DELAY_MS);
                console.log('[Get TLDR] Retrying in', delay, 'ms (attempt', this.retryCount, 'of', this.maxRetries, ')');
                this.retryTimeout = window.setTimeout(() => this.addButton(), delay);
            }
            else {
                console.log('[Get TLDR] Max retries reached, giving up');
                this.retryCount = 0;
            }
            return;
        }
        console.log('[Get TLDR] Found video container:', videoContainer);
        // Create the button
        this.button = this.createButton();
        // Add button as floating overlay on video player
        videoContainer.appendChild(this.button);
        console.log('[Get TLDR] Button added successfully');
        this.retryCount = 0;
    }
    findVideoContainer() {
        // Find the video player container - this is stable and doesn't get re-rendered
        const selectors = [
            '#movie_player',
            '.html5-video-player',
            '#player-container'
        ];
        for (const selector of selectors) {
            const element = document.querySelector(selector);
            if (element) {
                console.log('[Get TLDR] Found video container with selector:', selector);
                return element;
            }
        }
        console.log('[Get TLDR] Could not find video container');
        return null;
    }
    createButton() {
        const button = document.createElement('button');
        button.id = 'tldr-youtube-button';
        button.className = 'tldr-yt-button';
        // Add critical inline styles for floating overlay positioning
        button.style.cssText = `
      display: inline-flex !important;
      align-items: center;
      justify-content: center;
      height: 36px;
      width: 36px;
      padding: 0;
      background: linear-gradient(135deg, #87a96b 0%, #6b9080 100%);
      border: none;
      border-radius: 50%;
      color: #ffffff;
      font-family: "Roboto", "Arial", sans-serif;
      font-size: 13px;
      font-weight: 500;
      cursor: pointer;
      box-shadow: 0 2px 12px rgba(0, 0, 0, 0.4);
      position: absolute !important;
      top: 16px;
      left: 16px;
      z-index: 9999 !important;
      transition: all 0.3s ease;
      backdrop-filter: blur(4px);
      overflow: hidden;
    `;
        button.innerHTML = `
      <div class="tldr-yt-button-content" style="display: flex; align-items: center; justify-content: center; gap: 0; position: relative; z-index: 1; width: 100%; height: 100%;">
        <svg class="tldr-yt-icon" viewBox="0 0 24 24" fill="none" xmlns="http://www.w3.org/2000/svg" style="width: 18px; height: 18px; flex-shrink: 0; display: block;">
          <path d="M9 5H7a2 2 0 00-2 2v12a2 2 0 002 2h10a2 2 0 002-2V7a2 2 0 00-2-2h-2M9 5a2 2 0 002 2h2a2 2 0 002-2M9 5a2 2 0 012-2h2a2 2 0 012 2m-3 7h3m-3 4h3m-6-4h.01M9 16h.01" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"/>
        </svg>
        <span class="tldr-yt-text" style="white-space: nowrap; font-weight: 500; opacity: 0; width: 0; transition: all 0.3s ease; overflow: hidden;">Summarize</span>
      </div>
    `;
        const textSpan = button.querySelector('.tldr-yt-text');
        const buttonContent = button.querySelector('.tldr-yt-button-content');
        // Add hover effect - expand to show text
        button.addEventListener('mouseenter', () => {
            button.style.width = 'auto';
            button.style.borderRadius = '18px';
            button.style.padding = '0 14px';
            button.style.transform = 'translateY(-2px)';
            button.style.boxShadow = '0 4px 16px rgba(0, 0, 0, 0.5)';
            if (buttonContent) {
                buttonContent.style.gap = '8px';
                buttonContent.style.justifyContent = 'flex-start';
            }
            if (textSpan) {
                textSpan.style.opacity = '1';
                textSpan.style.width = 'auto';
            }
        });
        button.addEventListener('mouseleave', () => {
            button.style.width = '36px';
            button.style.borderRadius = '50%';
            button.style.padding = '0';
            button.style.transform = 'translateY(0)';
            button.style.boxShadow = '0 2px 12px rgba(0, 0, 0, 0.4)';
            if (buttonContent) {
                buttonContent.style.gap = '0';
                buttonContent.style.justifyContent = 'center';
            }
            if (textSpan) {
                textSpan.style.opacity = '0';
                textSpan.style.width = '0';
            }
        });
        button.addEventListener('click', (e) => {
            e.preventDefault();
            e.stopPropagation();
            this.handleButtonClick();
        });
        return button;
    }
    async handleButtonClick() {
        if (this.isProcessing)
            return;
        // Check if extension context is valid
        if (!chrome?.runtime?.id) {
            console.error('[Get TLDR] Extension context invalidated');
            await this.showError('Extension was reloaded. Please refresh this page and try again.');
            return;
        }
        this.isProcessing = true;
        this.updateButtonState('loading');
        try {
            // Get video URL
            const videoUrl = window.location.href;
            const videoTitle = this.getVideoTitle();
            // Show loading in sidebar
            await this.showLoadingSidebar(videoTitle);
            // Send message to background script to summarize with default YouTube prompt
            const response = await chrome.runtime.sendMessage({
                type: 'SUMMARIZE_YOUTUBE_VIDEO',
                data: {
                    url: videoUrl,
                    title: videoTitle,
                    prompt: 'Provide a comprehensive summary of this YouTube video transcript, highlighting the main topics, key points, and important takeaways.'
                }
            });
            if (response.error) {
                throw new Error(response.error);
            }
            // Show summary in sidebar
            await this.showSummarySidebar({
                title: videoTitle,
                summary: response.summary,
                tokensUsed: response.tokensUsed,
                wordCount: response.wordCount
            });
            this.updateButtonState('success');
            // Reset button after 2 seconds
            setTimeout(() => this.updateButtonState('default'), YouTubeSummarizer.BUTTON_SUCCESS_DISPLAY_MS);
        }
        catch (error) {
            console.error('Failed to summarize video:', error);
            // Check if it's an extension context error
            if (error instanceof Error && error.message.includes('Extension context invalidated')) {
                await this.showError('Extension was reloaded. Please refresh this page and try again.');
            }
            else {
                await this.showError(error instanceof Error ? error.message : 'Failed to summarize video');
            }
            this.updateButtonState('error');
            setTimeout(() => this.updateButtonState('default'), 3000);
        }
        finally {
            this.isProcessing = false;
        }
    }
    getVideoTitle() {
        const titleElement = document.querySelector('h1.ytd-video-primary-info-renderer yt-formatted-string') ||
            document.querySelector('h1.title yt-formatted-string') ||
            document.querySelector('h1 yt-formatted-string');
        return titleElement?.textContent?.trim() || 'YouTube Video';
    }
    createSimpleSidebar(title, summary, stats, isLoading = false) {
        // Remove existing sidebar
        const existing = document.getElementById('tldr-yt-sidebar');
        if (existing) {
            existing.remove();
        }
        // Create sidebar
        const sidebar = document.createElement('div');
        sidebar.id = 'tldr-yt-sidebar';
        sidebar.style.cssText = `
      position: fixed;
      top: 0;
      right: 0;
      width: 450px;
      height: 100vh;
      background: linear-gradient(135deg, #0a0a0b 0%, #1a1a1d 100%);
      box-shadow: -4px 0 32px rgba(0, 0, 0, 0.5);
      z-index: 9999;
      overflow-y: auto;
      color: #ffffff;
      font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, sans-serif;
      animation: slideIn 0.3s ease-out;
    `;
        const style = document.createElement('style');
        style.textContent = `
      @keyframes slideIn {
        from { transform: translateX(100%); }
        to { transform: translateX(0); }
      }
      #tldr-yt-sidebar::-webkit-scrollbar {
        width: 8px;
      }
      #tldr-yt-sidebar::-webkit-scrollbar-thumb {
        background: rgba(135, 169, 107, 0.3);
        border-radius: 4px;
      }
    `;
        document.head.appendChild(style);
        // Header
        const header = document.createElement('div');
        header.style.cssText = 'display: flex; justify-content: space-between; align-items: center; padding: 20px; border-bottom: 1px solid rgba(135, 169, 107, 0.2);';
        const headerTitle = document.createElement('h2');
        headerTitle.textContent = 'Get TLDR';
        headerTitle.style.cssText = 'margin: 0; font-size: 24px; color: #87a96b;';
        const closeBtn = document.createElement('button');
        closeBtn.textContent = '×';
        closeBtn.style.cssText = 'background: transparent; border: 1px solid rgba(255, 255, 255, 0.2); color: #c0c0c0; width: 32px; height: 32px; border-radius: 8px; cursor: pointer; font-size: 24px; transition: all 0.2s;';
        closeBtn.onmouseover = () => closeBtn.style.background = 'rgba(212, 116, 116, 0.2)';
        closeBtn.onmouseout = () => closeBtn.style.background = 'transparent';
        closeBtn.onclick = () => sidebar.remove();
        header.appendChild(headerTitle);
        header.appendChild(closeBtn);
        sidebar.appendChild(header);
        // Content container
        const contentContainer = document.createElement('div');
        contentContainer.style.cssText = 'padding: 24px;';
        if (isLoading) {
            // Loading state
            const loadingDiv = document.createElement('div');
            loadingDiv.style.cssText = 'text-align: center; padding: 40px 20px;';
            const spinner = document.createElement('div');
            spinner.style.cssText = 'width: 48px; height: 48px; border: 4px solid rgba(135, 169, 107, 0.2); border-top: 4px solid #87a96b; border-radius: 50%; animation: spin 1s linear infinite; margin: 0 auto 20px;';
            const spinStyle = document.createElement('style');
            spinStyle.textContent = '@keyframes spin { 0% { transform: rotate(0deg); } 100% { transform: rotate(360deg); } }';
            document.head.appendChild(spinStyle);
            const loadingText = document.createElement('div');
            loadingText.textContent = 'Summarizing video...';
            loadingText.style.cssText = 'font-size: 16px; color: #c0c0c0; margin-bottom: 8px;';
            const loadingSubtext = document.createElement('div');
            loadingSubtext.textContent = title;
            loadingSubtext.style.cssText = 'font-size: 14px; color: #8a8a8a;';
            loadingDiv.appendChild(spinner);
            loadingDiv.appendChild(loadingText);
            loadingDiv.appendChild(loadingSubtext);
            contentContainer.appendChild(loadingDiv);
        }
        else {
            // Video title
            const videoTitle = document.createElement('div');
            videoTitle.textContent = title;
            videoTitle.style.cssText = 'font-size: 14px; color: #8a8a8a; margin-bottom: 20px; padding-bottom: 12px; border-bottom: 1px solid rgba(255, 255, 255, 0.1);';
            contentContainer.appendChild(videoTitle);
            // Summary label
            const summaryLabel = document.createElement('div');
            summaryLabel.textContent = '✨ AI Summary';
            summaryLabel.style.cssText = 'font-size: 12px; font-weight: 600; color: #87a96b; text-transform: uppercase; letter-spacing: 0.5px; margin-bottom: 12px;';
            contentContainer.appendChild(summaryLabel);
            // Summary box
            const summaryBox = document.createElement('div');
            summaryBox.style.cssText = 'background: linear-gradient(135deg, rgba(135, 169, 107, 0.1) 0%, rgba(107, 144, 128, 0.1) 100%); border: 1px solid rgba(135, 169, 107, 0.3); border-radius: 12px; padding: 20px; margin-bottom: 20px; position: relative; overflow: hidden;';
            const summaryTopBorder = document.createElement('div');
            summaryTopBorder.style.cssText = 'position: absolute; top: 0; left: 0; right: 0; height: 3px; background: linear-gradient(90deg, #87a96b 0%, #6b9080 100%);';
            summaryBox.appendChild(summaryTopBorder);
            const summaryText = document.createElement('div');
            summaryText.innerHTML = this.parseMarkdown(summary);
            summaryText.style.cssText = 'font-size: 15px; line-height: 1.7; color: #ffffff; word-wrap: break-word;';
            summaryBox.appendChild(summaryText);
            contentContainer.appendChild(summaryBox);
            // Stats
            if (stats) {
                const statsContainer = document.createElement('div');
                statsContainer.style.cssText = 'display: flex; gap: 16px; padding-top: 16px; border-top: 1px solid rgba(135, 169, 107, 0.2);';
                const createStat = (value, label) => {
                    const stat = document.createElement('div');
                    stat.style.cssText = 'flex: 1; text-align: center;';
                    const statValue = document.createElement('div');
                    statValue.textContent = value;
                    statValue.style.cssText = 'font-size: 20px; font-weight: 700; color: #87a96b; margin-bottom: 4px;';
                    const statLabel = document.createElement('div');
                    statLabel.textContent = label;
                    statLabel.style.cssText = 'font-size: 11px; color: #8a8a8a; text-transform: uppercase; letter-spacing: 0.5px;';
                    stat.appendChild(statValue);
                    stat.appendChild(statLabel);
                    return stat;
                };
                statsContainer.appendChild(createStat(stats.wordCount.toString(), 'Words'));
                statsContainer.appendChild(createStat(stats.tokensUsed.toString(), 'Tokens'));
                contentContainer.appendChild(statsContainer);
            }
        }
        sidebar.appendChild(contentContainer);
        document.body.appendChild(sidebar);
        return sidebar;
    }
    async showLoadingSidebar(title) {
        this.createSimpleSidebar(title, '', null, true);
    }
    async showSummarySidebar(data) {
        this.createSimpleSidebar(data.title, data.summary, { wordCount: data.wordCount, tokensUsed: data.tokensUsed }, false);
    }
    async showError(message) {
        this.createSimpleSidebar('Error', message, null, false);
    }
    updateButtonState(state) {
        if (!this.button)
            return;
        const content = this.button.querySelector('.tldr-yt-button-content');
        const text = this.button.querySelector('.tldr-yt-text');
        if (!content || !text)
            return;
        // Remove all state classes
        this.button.classList.remove('loading', 'success', 'error');
        switch (state) {
            case 'loading':
                this.button.classList.add('loading');
                text.textContent = 'Summarizing...';
                this.button.disabled = true;
                break;
            case 'success':
                this.button.classList.add('success');
                text.textContent = '✓ Summarized';
                this.button.disabled = false;
                break;
            case 'error':
                this.button.classList.add('error');
                text.textContent = '✗ Failed';
                this.button.disabled = false;
                break;
            default:
                text.textContent = 'Summarize Video';
                this.button.disabled = false;
        }
    }
}
// Configuration constants
YouTubeSummarizer.URL_CHECK_INTERVAL_MS = 500;
YouTubeSummarizer.MUTATION_THROTTLE_MS = 100;
YouTubeSummarizer.BUTTON_ADD_DELAY_MS = 500;
YouTubeSummarizer.RETRY_BASE_DELAY_MS = 500;
YouTubeSummarizer.RETRY_MAX_DELAY_MS = 2000;
YouTubeSummarizer.BUTTON_SUCCESS_DISPLAY_MS = 2000;
// Initialize when script loads
new YouTubeSummarizer();
