/**
 * Get TLDR Sidebar Content Script
 * Displays summarized text in a beautiful sidebar
 */
class TLDRSidebar {
    constructor() {
        this.sidebar = null;
        this.isOpen = false;
        this.escapeHandler = null;
        this.init();
    }
    init() {
        console.log('[TLDR Sidebar] Initializing sidebar content script');
        // Listen for messages from background script (only if chrome API is available)
        if (typeof chrome !== 'undefined' && chrome.runtime && chrome.runtime.onMessage) {
            chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
                console.log('[TLDR Sidebar] Received message:', message.type);
                if (message.type === 'SHOW_SIDEBAR_SUMMARY') {
                    console.log('[TLDR Sidebar] Showing summary with data:', message.data);
                    this.showSummary(message.data);
                    sendResponse({ success: true });
                }
                else if (message.type === 'SHOW_LOADING_SIDEBAR') {
                    console.log('[TLDR Sidebar] Showing loading state');
                    this.showLoading(message.data.title);
                    sendResponse({ success: true });
                }
                else if (message.type === 'SHOW_SIDEBAR_ERROR') {
                    console.log('[TLDR Sidebar] Showing error:', message.data.message);
                    this.showError(message.data.message);
                    sendResponse({ success: true });
                }
                return true;
            });
            console.log('[TLDR Sidebar] Message listener registered');
        }
        else {
            console.warn('[TLDR Sidebar] Chrome runtime API not available');
        }
        // Always listen for window messages (from YouTube content script)
        window.addEventListener('message', (event) => {
            // Only accept messages from same origin
            if (event.source !== window)
                return;
            const message = event.data;
            if (message.type === 'TLDR_SHOW_SIDEBAR_SUMMARY') {
                this.showSummary(message.data);
            }
            else if (message.type === 'TLDR_SHOW_LOADING_SIDEBAR') {
                this.showLoading(message.data.title);
            }
            else if (message.type === 'TLDR_SHOW_SIDEBAR_ERROR') {
                this.showError(message.data.message);
            }
        });
    }
    showLoading(title) {
        if (!this.sidebar) {
            this.createSidebar();
        }
        const content = this.sidebar.querySelector('#tldr-sidebar-content');
        if (!content)
            return;
        // Clear content
        content.textContent = '';
        // Create loading elements
        const loading = document.createElement('div');
        loading.className = 'tldr-loading';
        const spinner = document.createElement('div');
        spinner.className = 'tldr-spinner';
        const loadingText = document.createElement('div');
        loadingText.className = 'tldr-loading-text';
        loadingText.textContent = 'Summarizing video...';
        const loadingSubtext = document.createElement('div');
        loadingSubtext.className = 'tldr-loading-subtext';
        loadingSubtext.textContent = title;
        loading.appendChild(spinner);
        loading.appendChild(loadingText);
        loading.appendChild(loadingSubtext);
        content.appendChild(loading);
        this.open();
    }
    createSidebar() {
        // Remove existing sidebar if any
        const existing = document.getElementById('get-tldr-sidebar');
        if (existing) {
            existing.remove();
        }
        // Get icon URL safely
        let iconUrl = '';
        if (typeof chrome !== 'undefined' && chrome.runtime && chrome.runtime.getURL) {
            iconUrl = chrome.runtime.getURL('icons/icon48.png');
        }
        // Create sidebar container using DOM methods (avoid innerHTML for CSP)
        const sidebar = document.createElement('div');
        sidebar.id = 'get-tldr-sidebar';
        sidebar.setAttribute('data-theme', 'dark'); // Default to dark
        // Fetch theme preference dynamically from storage
        if (typeof chrome !== 'undefined' && chrome.storage && chrome.storage.local) {
            chrome.storage.local.get(['get_tldr_theme_pref'], (result) => {
                const userTheme = result['get_tldr_theme_pref'] || 'dark';
                sidebar.setAttribute('data-theme', userTheme);
            });
        }
        // Create header
        const header = document.createElement('div');
        header.className = 'tldr-sidebar-header';
        const title = document.createElement('h2');
        title.className = 'tldr-sidebar-title';
        if (iconUrl) {
            const logo = document.createElement('img');
            logo.src = iconUrl;
            logo.alt = 'Get TLDR';
            logo.className = 'tldr-sidebar-logo';
            title.appendChild(logo);
        }
        const titleText = document.createElement('span');
        titleText.textContent = 'Get TLDR';
        title.appendChild(titleText);
        const closeBtn = document.createElement('button');
        closeBtn.className = 'tldr-close-btn';
        closeBtn.id = 'tldr-close-btn';
        closeBtn.title = 'Close sidebar';
        closeBtn.textContent = '×';
        header.appendChild(title);
        header.appendChild(closeBtn);
        // Create content area
        const content = document.createElement('div');
        content.className = 'tldr-sidebar-content';
        content.id = 'tldr-sidebar-content';
        const loading = document.createElement('div');
        loading.className = 'tldr-loading';
        const spinner = document.createElement('div');
        spinner.className = 'tldr-spinner';
        const loadingText = document.createElement('div');
        loadingText.className = 'tldr-loading-text';
        loadingText.textContent = 'Preparing your summary...';
        const loadingSubtext = document.createElement('div');
        loadingSubtext.className = 'tldr-loading-subtext';
        loadingSubtext.textContent = 'This will just take a moment';
        loading.appendChild(spinner);
        loading.appendChild(loadingText);
        loading.appendChild(loadingSubtext);
        content.appendChild(loading);
        sidebar.appendChild(header);
        sidebar.appendChild(content);
        document.body.appendChild(sidebar);
        this.sidebar = sidebar;
        // Add event listeners
        closeBtn.addEventListener('click', () => this.close());
        // Close on Escape key - store handler for cleanup
        this.escapeHandler = (e) => {
            if (e.key === 'Escape' && this.isOpen) {
                this.close();
            }
        };
        document.addEventListener('keydown', this.escapeHandler);
        return sidebar;
    }
    // Public method to show summary (can be called from window.tldrSidebar.showSummary())
    showSummary(data) {
        console.log('[TLDR Sidebar] showSummary called with data:', data);
        if (!this.sidebar) {
            console.log('[TLDR Sidebar] Creating new sidebar');
            this.createSidebar();
        }
        const content = this.sidebar.querySelector('#tldr-sidebar-content');
        if (!content) {
            console.error('[TLDR Sidebar] Could not find sidebar content element');
            return;
        }
        // Clear content
        while (content.firstChild) {
            content.removeChild(content.firstChild);
        }
        // Calculate stats
        const selectedWordCount = data.selectedText ? data.selectedText.split(/\s+/).length : 0;
        const selectedCharCount = data.selectedText ? data.selectedText.length : 0;
        // Render summary content
        const selectedTextSection = data.selectedText ? `
      <div class="tldr-section">
        <div class="tldr-section-label">
          <span class="tldr-section-icon">📝</span>
          Selected Text
        </div>
        <div class="tldr-selected-text">${this.escapeHtml(data.selectedText)}</div>
        <div class="tldr-text-meta">
          <span>${selectedWordCount} words</span>
          <span>•</span>
          <span>${selectedCharCount} characters</span>
        </div>
      </div>
    ` : '';
        const compressionRatio = selectedWordCount > 0
            ? Math.round((data.wordCount / selectedWordCount) * 100)
            : 0;
        content.innerHTML = `
      ${selectedTextSection}

      <div class="tldr-section">
        <div class="tldr-section-label">
          <span class="tldr-section-icon">✨</span>
          AI Summary
        </div>
        <div class="tldr-summary-box">
          <div class="tldr-summary-text markdown-content">${this.renderMarkdown(data.summary)}</div>
          <div class="tldr-stats">
            <div class="tldr-stat">
              <span class="tldr-stat-value">${data.wordCount}</span>
              <span class="tldr-stat-label">Words</span>
            </div>
            <div class="tldr-stat">
              <span class="tldr-stat-value">${data.tokensUsed}</span>
              <span class="tldr-stat-label">Tokens</span>
            </div>
            ${compressionRatio > 0 ? `
            <div class="tldr-stat">
              <span class="tldr-stat-value">${compressionRatio}%</span>
              <span class="tldr-stat-label">Compression</span>
            </div>
            ` : ''}
          </div>
        </div>
      </div>

      <div class="tldr-section">
        <div class="tldr-actions">
          <button class="tldr-btn tldr-btn-primary" id="tldr-copy-btn">
            <span class="tldr-btn-icon">📋</span>
            Copy Summary
          </button>
          <button class="tldr-btn tldr-btn-secondary" id="tldr-share-btn">
            <span class="tldr-btn-icon">🔗</span>
            Share
          </button>
        </div>
      </div>

      <div class="tldr-source">
        <span class="tldr-source-icon">🌐</span>
        <span class="tldr-source-text">${this.escapeHtml(data.title)}</span>
      </div>
    `;
        // Add action button listeners
        const copyBtn = content.querySelector('#tldr-copy-btn');
        copyBtn?.addEventListener('click', () => this.copySummary(data.summary));
        const shareBtn = content.querySelector('#tldr-share-btn');
        shareBtn?.addEventListener('click', () => this.shareSummary(data));
        // Open sidebar
        console.log('[TLDR Sidebar] Opening sidebar');
        this.open();
    }
    open() {
        console.log('[TLDR Sidebar] open() called, sidebar exists:', !!this.sidebar);
        if (this.sidebar) {
            this.sidebar.classList.add('open');
            this.isOpen = true;
            document.body.style.overflow = 'hidden';
            console.log('[TLDR Sidebar] Sidebar opened successfully, isOpen:', this.isOpen);
        }
        else {
            console.error('[TLDR Sidebar] Cannot open - sidebar element does not exist');
        }
    }
    close() {
        if (this.sidebar) {
            this.sidebar.classList.remove('open');
            this.isOpen = false;
            document.body.style.overflow = '';
            // Remove escape key handler to prevent memory leak
            if (this.escapeHandler) {
                document.removeEventListener('keydown', this.escapeHandler);
                this.escapeHandler = null;
            }
            // Remove sidebar after animation
            setTimeout(() => {
                this.sidebar?.remove();
                this.sidebar = null;
            }, TLDRSidebar.ANIMATION_DURATION_MS);
        }
    }
    async copySummary(summary) {
        try {
            await navigator.clipboard.writeText(summary);
            this.showToast('✅ Summary copied to clipboard!');
        }
        catch (error) {
            console.error('Failed to copy:', error);
            this.showToast('❌ Failed to copy summary');
        }
    }
    async shareSummary(data) {
        const shareText = `Summary of "${data.title}":\n\n${data.summary}\n\nSource: ${data.url}`;
        try {
            if (navigator.share) {
                await navigator.share({
                    title: 'AI Summary',
                    text: shareText,
                    url: data.url
                });
            }
            else {
                // Fallback: copy to clipboard
                await navigator.clipboard.writeText(shareText);
                this.showToast('✅ Summary copied for sharing!');
            }
        }
        catch (error) {
            console.error('Failed to share:', error);
        }
    }
    showToast(message) {
        const toast = document.createElement('div');
        toast.className = 'tldr-toast';
        toast.innerHTML = `
      <span class="tldr-toast-icon">✨</span>
      <span class="tldr-toast-message">${this.escapeHtml(message)}</span>
    `;
        document.body.appendChild(toast);
        // Trigger animation
        setTimeout(() => toast.classList.add('show'), 10);
        // Remove after display duration
        setTimeout(() => {
            toast.classList.remove('show');
            setTimeout(() => toast.remove(), TLDRSidebar.TOAST_FADE_MS);
        }, TLDRSidebar.TOAST_DISPLAY_MS);
    }
    escapeHtml(text) {
        const div = document.createElement('div');
        div.textContent = text;
        return div.innerHTML;
    }
    renderMarkdown(text) {
        // Check if marked is available
        if (typeof marked !== 'undefined' && marked.parse) {
            try {
                return marked.parse(text);
            }
            catch (error) {
                console.error('Failed to parse markdown:', error);
                return this.escapeHtml(text);
            }
        }
        // Fallback to escaped HTML if marked is not available
        return this.escapeHtml(text);
    }
    showError(message) {
        if (!this.sidebar) {
            this.createSidebar();
        }
        const content = this.sidebar.querySelector('#tldr-sidebar-content');
        if (!content)
            return;
        content.innerHTML = `
      <div class="tldr-error">
        <div class="tldr-error-icon">⚠️</div>
        <div class="tldr-error-title">Summarization Failed</div>
        <div class="tldr-error-message">${this.escapeHtml(message)}</div>
      </div>
    `;
        this.open();
        // Auto-close after 5 seconds
        setTimeout(() => this.close(), 5000);
    }
}
// Configuration constants
TLDRSidebar.ANIMATION_DURATION_MS = 300;
TLDRSidebar.TOAST_DISPLAY_MS = 3000;
TLDRSidebar.TOAST_FADE_MS = 300;
// Initialize sidebar only if not already initialized
if (!window.tldrSidebar) {
    console.log('[TLDR Sidebar] Creating new TLDRSidebar instance');
    window.tldrSidebar = new TLDRSidebar();
    console.log('[TLDR Sidebar] TLDRSidebar instance created and assigned to window.tldrSidebar');
}
else {
    console.log('[TLDR Sidebar] TLDRSidebar already initialized, reusing existing instance');
}
