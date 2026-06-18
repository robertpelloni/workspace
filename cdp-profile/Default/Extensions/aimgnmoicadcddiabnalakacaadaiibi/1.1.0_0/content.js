/**
 * Threadline - Chat TOC Extension
 * Adds a navigable table of contents sidebar to Claude.ai and ChatGPT chat threads
 */

(function() {
  'use strict';

  // Detect which site we're on
  const SITE = (() => {
    const hostname = location.hostname;
    if (hostname.includes('claude.ai')) return 'claude';
    if (hostname.includes('chatgpt.com') || hostname.includes('chat.openai.com')) return 'chatgpt';
    return 'unknown';
  })();

  console.log('[Threadline] Extension loaded on:', SITE, window.location.href);

  // Site-specific configurations
  const SITE_CONFIG = {
    claude: {
      chatPathPattern: /^\/chat\//,
      userMessageSelectors: [
        '[data-testid="user-message"]',
        '[data-testid*="human"]',
        '[data-testid*="user"]'
      ],
      userClassPatterns: ['human', 'Human', 'user-message', 'font-user'],
      assistantPatterns: ['assistant', 'claude', 'bot'],
      sidebarSelectors: ['nav', 'aside', 'div'],
      themeClassLight: ['light'],
      themeClassDark: ['dark']
    },
    chatgpt: {
      chatPathPattern: /^\/(c|g)\//,
      userMessageSelectors: [
        '[data-message-author-role="user"]',
        '[data-testid*="user"]',
        '[class*="user-message"]'
      ],
      userClassPatterns: ['user', 'human'],
      assistantPatterns: ['assistant', 'gpt', 'bot'],
      sidebarSelectors: ['nav', 'aside', 'div'],
      themeClassLight: ['light'],
      themeClassDark: ['dark']
    }
  };

  // Get current site config (fallback to claude if unknown)
  const siteConfig = SITE_CONFIG[SITE] || SITE_CONFIG.claude;

  // Configuration
  const CONFIG = {
    TITLE_MAX_LENGTH: 55,
    PREVIEW_LINES: 3,
    LAZY_LOAD_THRESHOLD: 100,
    SCROLL_OFFSET: 100,
    DEBOUNCE_DELAY: 150,
    INTERSECTION_THRESHOLD: 0.3
  };

  // State
  let tocContainer = null;
  let tocList = null;
  let tooltip = null;
  let sections = [];
  let activeSection = null;
  let observer = null;
  let scrollTimeout = null;
  let isInitialized = false;

  /**
   * Initialize the TOC extension
   */
  function init() {
    if (isInitialized) return;

    // Only show TOC on chat pages, not on home or other pages
    const pathname = location.pathname;
    const isChatPage = siteConfig.chatPathPattern.test(pathname);

    console.log('[Threadline] Initializing on path:', pathname, 'isChatPage:', isChatPage, 'site:', SITE);

    if (!isChatPage) {
      console.log('[Threadline] Not a chat page, skipping initialization');
      // Clean up any existing TOC
      const existing = document.getElementById('claude-toc-sidebar');
      if (existing) existing.remove();
      return;
    }

    // Wait for main content to be available
    waitForElement('main', (mainEl) => {
      console.log('[Threadline] Main element found, setting up TOC');
      createTOCSidebar();
      createTooltip();

      // Initial scan with delay to let page fully render
      setTimeout(() => {
        scanForSections();
        console.log('[Threadline] Found', sections.length, 'sections');
      }, 1500);

      setupMutationObserver();
      setupScrollListener();
      isInitialized = true;
    });
  }

  /**
   * Wait for an element to appear in the DOM
   */
  function waitForElement(selector, callback, maxAttempts = 50) {
    let attempts = 0;

    const check = () => {
      // Try multiple selectors
      const selectors = ['main', '[role="main"]', '#main', '.main', 'div[class*="main"]', 'body'];
      let element = null;

      for (const sel of selectors) {
        element = document.querySelector(sel);
        if (element && element.children.length > 0) {
          console.log('[Threadline] Found container with selector:', sel);
          break;
        }
      }

      if (element) {
        callback(element);
        return;
      }

      attempts++;
      console.log('[Threadline] Waiting for main element, attempt:', attempts);

      if (attempts < maxAttempts) {
        setTimeout(check, 200);
      } else {
        console.log('[Threadline] Max attempts reached, using body as fallback');
        callback(document.body);
      }
    };

    check();
  }

  /**
   * Create the TOC sidebar container
   */
  function createTOCSidebar() {
    console.log('[Threadline] Creating sidebar...');

    // Remove existing TOC if present
    const existing = document.getElementById('claude-toc-sidebar');
    if (existing) {
      console.log('[Threadline] Removing existing sidebar');
      existing.remove();
    }

    // Create sidebar container
    tocContainer = document.createElement('div');
    tocContainer.id = 'claude-toc-sidebar';
    console.log('[Claude TOC] Sidebar element created');
    tocContainer.innerHTML = `
      <div class="toc-header">
        <span class="toc-title">Contents</span>
        <button class="toc-toggle" aria-label="Toggle TOC">
          <svg width="16" height="16" viewBox="0 0 16 16" fill="currentColor">
            <path d="M4 4h8v1H4V4zm0 3h8v1H4V7zm0 3h6v1H4v-1z"/>
          </svg>
        </button>
      </div>
      <div class="toc-content">
        <ul class="toc-list"></ul>
      </div>
      <div class="toc-empty">
        <span>No sections yet</span>
      </div>
    `;

    document.body.appendChild(tocContainer);
    console.log('[Threadline] Sidebar appended to body');

    tocList = tocContainer.querySelector('.toc-list');

    // Setup toggle button
    const toggleBtn = tocContainer.querySelector('.toc-toggle');
    toggleBtn.addEventListener('click', () => {
      tocContainer.classList.toggle('collapsed');
    });

    // Detect Claude's sidebar state and adjust position
    detectClaudeSidebar();
    setupSidebarObserver();

    // Verify sidebar is in DOM
    const verify = document.getElementById('claude-toc-sidebar');
    console.log('[Threadline] Sidebar in DOM:', !!verify, 'Display:', verify ? getComputedStyle(verify).display : 'N/A');
  }

  /**
   * Detect site sidebar and position TOC dynamically (works for Claude and ChatGPT)
   */
  function detectClaudeSidebar() {
    if (!tocContainer) return;

    let sidebarWidth = 0;

    if (SITE === 'chatgpt') {
      // ChatGPT-specific sidebar detection
      // ChatGPT sidebar: fully open (~260px via --sidebar-width), collapsed rail (~56px via --sidebar-rail-width)

      // Get the computed CSS variable values from ChatGPT
      const rootStyles = getComputedStyle(document.documentElement);
      const sidebarWidthVar = rootStyles.getPropertyValue('--sidebar-width').trim();
      const sidebarRailVar = rootStyles.getPropertyValue('--sidebar-rail-width').trim();

      // Find the main chat area and check its left offset
      const mainContent = document.querySelector('main');
      if (mainContent) {
        const mainRect = mainContent.getBoundingClientRect();
        // The main content's left edge tells us where the sidebar ends
        if (mainRect.left > 10) {
          sidebarWidth = mainRect.left;
        }
      }

      // Fallback: scan for left-anchored elements
      if (sidebarWidth === 0) {
        const allElements = document.querySelectorAll('nav, aside, div');
        allElements.forEach(el => {
          const rect = el.getBoundingClientRect();
          // Look for elements at left edge with significant height
          // Could be full sidebar (~260px) or rail (~56px)
          if (rect.left < 2 && rect.height > window.innerHeight * 0.5 && rect.width > 30 && rect.width < 300) {
            if (rect.right > sidebarWidth) {
              sidebarWidth = rect.right;
            }
          }
        });
      }

    } else {
      // Claude and other sites - original detection logic
      const allElements = document.querySelectorAll('nav, aside, div');

      allElements.forEach(el => {
        const rect = el.getBoundingClientRect();
        // Element must start at left edge (x < 10) and have reasonable height
        if (rect.left < 10 && rect.height > 300 && rect.width > 40 && rect.width < 350) {
          const rightEdge = rect.right;
          if (rightEdge > sidebarWidth) {
            sidebarWidth = rightEdge;
          }
        }
      });
    }

    // Apply dynamic positioning
    if (sidebarWidth > 0) {
      // Position TOC 8px to the right of the sidebar
      const tocLeft = sidebarWidth + 8;
      tocContainer.style.left = `${tocLeft}px`;

      // Check if sidebar is collapsed (icon-only mode, typically < 80px)
      if (sidebarWidth < 80) {
        tocContainer.classList.add('sidebar-collapsed');
      } else {
        tocContainer.classList.remove('sidebar-collapsed');
      }
    } else {
      // No sidebar detected - position at left edge with small margin
      tocContainer.style.left = '16px';
      tocContainer.classList.add('sidebar-collapsed');
    }
  }

  /**
   * Detect site theme (light or dark) - works for Claude and ChatGPT
   */
  function detectTheme() {
    if (!tocContainer) return;

    const html = document.documentElement;
    const body = document.body;

    // Method 1: Check for explicit theme classes (works for both Claude and ChatGPT)
    // ChatGPT uses html.dark or html.light
    // Claude uses various class patterns
    const hasLightClass = html.classList.contains('light') ||
                          body.classList.contains('light') ||
                          html.dataset.theme === 'light' ||
                          body.dataset.theme === 'light' ||
                          html.getAttribute('data-color-mode') === 'light';

    const hasDarkClass = html.classList.contains('dark') ||
                         body.classList.contains('dark') ||
                         html.dataset.theme === 'dark' ||
                         body.dataset.theme === 'dark' ||
                         html.getAttribute('data-color-mode') === 'dark';

    // Method 2: Check background color luminance
    const isLightBg = (color) => {
      if (!color || color === 'transparent' || color === 'rgba(0, 0, 0, 0)') return null;

      const match = color.match(/rgba?\((\d+),\s*(\d+),\s*(\d+)/);
      if (match) {
        const r = parseInt(match[1]);
        const g = parseInt(match[2]);
        const b = parseInt(match[3]);
        const luminance = (0.299 * r + 0.587 * g + 0.114 * b);
        return luminance > 128;
      }
      return null;
    };

    const bodyBg = getComputedStyle(body).backgroundColor;
    const htmlBg = getComputedStyle(html).backgroundColor;
    const main = document.querySelector('main');
    const mainBg = main ? getComputedStyle(main).backgroundColor : null;

    // Determine theme
    let isLight = false;

    // Priority: explicit classes > color scheme preference > background analysis
    if (hasLightClass && !hasDarkClass) {
      isLight = true;
    } else if (hasDarkClass && !hasLightClass) {
      isLight = false;
    } else {
      // Check backgrounds as fallback
      const mainLight = isLightBg(mainBg);
      const bodyLight = isLightBg(bodyBg);
      const htmlLight = isLightBg(htmlBg);

      if (mainLight !== null) {
        isLight = mainLight;
      } else if (bodyLight !== null) {
        isLight = bodyLight;
      } else if (htmlLight !== null) {
        isLight = htmlLight;
      }
    }

    // Apply theme class
    if (isLight) {
      tocContainer.classList.add('light-theme');
      tocContainer.classList.remove('dark-theme');
    } else {
      tocContainer.classList.remove('light-theme');
      tocContainer.classList.add('dark-theme');
    }
  }

  /**
   * Watch for sidebar and theme changes
   */
  function setupSidebarObserver() {
    // Initial detection
    detectClaudeSidebar();
    detectTheme();

    // Check periodically for changes
    setInterval(() => {
      detectClaudeSidebar();
      detectTheme();
    }, 500);
  }

  /**
   * Create the tooltip element
   */
  function createTooltip() {
    tooltip = document.createElement('div');
    tooltip.id = 'claude-toc-tooltip';
    tooltip.innerHTML = `
      <div class="tooltip-title"></div>
      <div class="tooltip-preview"></div>
    `;
    document.body.appendChild(tooltip);
  }

  /**
   * Scan the page for message sections
   */
  function scanForSections() {
    sections = [];

    // Try multiple detection strategies
    let messageContainers = findHumanMessages();

    messageContainers.forEach((messageEl, index) => {
      const section = createSectionFromMessage(messageEl, index);
      if (section) {
        sections.push(section);
      }
    });

    renderTOC();
    updateActiveSection();
  }

  /**
   * Find human/user messages using multiple strategies
   */
  function findHumanMessages() {
    let messages = [];

    console.log('[Threadline] Searching for messages on', SITE, '...');

    // Strategy 1: Use site-specific selectors first
    for (const selector of siteConfig.userMessageSelectors) {
      try {
        const found = document.querySelectorAll(selector);
        if (found.length > 0) {
          console.log('[Threadline] Found via site selector:', selector, found.length);
          messages = Array.from(found);
          return messages;
        }
      } catch (e) {
        // Invalid selector, skip
      }
    }

    // Strategy 2: Look for class patterns based on site config
    const classSelectors = siteConfig.userClassPatterns.flatMap(pattern => [
      `[class*="${pattern}"]`,
      `.${pattern}`,
      `[class*="${pattern}-message"]`
    ]);

    for (const selector of classSelectors) {
      try {
        const found = document.querySelectorAll(selector);
        if (found.length > 0) {
          console.log('[Threadline] Found via class:', selector, found.length);
          messages = Array.from(found);
          return messages;
        }
      } catch (e) {
        // Invalid selector, skip
      }
    }

    // Strategy 3: Look for message containers by role or structure
    const roleSelectors = [
      '[role="article"]',
      '[role="listitem"]',
      '[role="presentation"]',
      '[class*="message"]',
      '[class*="Message"]'
    ];

    for (const selector of roleSelectors) {
      const found = document.querySelectorAll(selector);
      // Filter to only human messages (every other one, starting from first)
      if (found.length >= 2) {
        console.log('[Threadline] Found via role/message:', selector, found.length);
        const filtered = Array.from(found).filter((el, idx) => {
          const text = typeof el.className === 'string' ? el.className : '';
          // Skip if clearly assistant message using site-specific patterns
          for (const pattern of siteConfig.assistantPatterns) {
            if (text.toLowerCase().includes(pattern)) return false;
          }
          // Take human messages (usually has user class or alternating)
          for (const pattern of siteConfig.userClassPatterns) {
            if (text.toLowerCase().includes(pattern)) return true;
          }
          return idx % 2 === 0;
        });
        if (filtered.length > 0) {
          messages = filtered;
          return messages;
        }
      }
    }

    // Strategy 4: Find by DOM structure analysis
    messages = findMessagesByDOMStructure();
    console.log('[Threadline] Found via DOM structure:', messages.length);

    return messages;
  }

  /**
   * Check if an element is a human message
   */
  function isHumanMessage(element) {
    const classList = (typeof element.className === 'string' ? element.className : '').toLowerCase();
    const testId = element.getAttribute('data-testid') || '';
    const authorRole = element.getAttribute('data-message-author-role') || '';

    // ChatGPT uses data-message-author-role attribute
    if (authorRole === 'user') return true;
    if (authorRole === 'assistant') return false;

    // Positive signals using site-specific patterns
    for (const pattern of siteConfig.userClassPatterns) {
      if (classList.includes(pattern.toLowerCase()) || testId.includes(pattern.toLowerCase())) {
        return true;
      }
    }

    // Negative signals - exclude assistant messages
    for (const pattern of siteConfig.assistantPatterns) {
      if (classList.includes(pattern) || testId.includes(pattern)) {
        return false;
      }
    }

    return false;
  }

  /**
   * Find messages by analyzing the DOM structure
   */
  function findMessagesByDOMStructure() {
    const messages = [];

    // Get the main content area
    const main = document.querySelector('main');
    if (!main) {
      console.log('[Threadline] No main element found');
      return messages;
    }

    // Strategy A: Look for divs that contain user text directly
    const allDivs = main.querySelectorAll('div');

    // Find divs that look like message containers
    const potentialMessages = [];

    allDivs.forEach(div => {
      // Check for common message container patterns
      const className = typeof div.className === 'string' ? div.className : '';
      const hasMessageClass = /\b(message|turn|chat|response|query|prompt)\b/i.test(className);
      const hasProseClass = className.includes('prose') || className.includes('whitespace') || className.includes('markdown');

      // Check if div has substantial text content
      const directText = Array.from(div.childNodes)
        .filter(n => n.nodeType === Node.TEXT_NODE)
        .map(n => n.textContent.trim())
        .join('');

      const hasTextContent = div.textContent && div.textContent.trim().length > 20;

      if ((hasMessageClass || hasProseClass) && hasTextContent) {
        potentialMessages.push(div);
      }
    });

    console.log('[Threadline] Found potential message divs:', potentialMessages.length);

    // Try to identify human vs assistant messages
    const seen = new Set();

    potentialMessages.forEach((msg, idx) => {
      const parent = msg.parentElement;
      const grandparent = parent ? parent.parentElement : null;

      // Use ancestor as dedup key
      const key = grandparent || parent || msg;

      if (!seen.has(key)) {
        const className = ((typeof msg.className === 'string' ? msg.className : '') + ' ' +
                          (parent && typeof parent.className === 'string' ? parent.className : '')).toLowerCase();

        // Check for user patterns
        let isUser = false;
        let isAssistant = false;

        for (const pattern of siteConfig.userClassPatterns) {
          if (className.includes(pattern.toLowerCase())) {
            isUser = true;
            break;
          }
        }

        for (const pattern of siteConfig.assistantPatterns) {
          if (className.includes(pattern)) {
            isAssistant = true;
            break;
          }
        }

        if (isUser && !isAssistant) {
          seen.add(key);
          messages.push(msg);
        } else if (isAssistant) {
          // Skip assistant messages
          seen.add(key);
        } else {
          // Alternating pattern fallback
          if (idx % 2 === 0) {
            seen.add(key);
            messages.push(msg);
          }
        }
      }
    });

    // Fallback: just get first-level children of scrollable area
    if (messages.length === 0) {
      const scrollArea = main.querySelector('[class*="overflow"]') || main;
      const children = scrollArea.children;

      for (let i = 0; i < children.length; i += 2) {
        if (children[i] && children[i].textContent.trim().length > 10) {
          messages.push(children[i]);
        }
      }
    }

    return messages;
  }

  /**
   * Create a section object from a message element
   */
  function createSectionFromMessage(messageEl, index) {
    if (!messageEl) return null;

    // Get the text content of the user message
    const textContent = extractTextContent(messageEl);
    if (!textContent.trim()) return null;

    // Generate title from first part of message
    const title = generateTitle(textContent);

    // Get preview text
    const preview = generatePreview(textContent);

    // Create unique ID for the section
    const sectionId = `toc-section-${index}`;

    // Add data attribute to the message for scrolling
    messageEl.setAttribute('data-toc-section', sectionId);

    return {
      id: sectionId,
      index: index + 1,
      title: title,
      fullTitle: textContent.substring(0, 200),
      preview: preview,
      element: messageEl,
      timestamp: new Date().toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' })
    };
  }

  /**
   * Extract text content from a message element
   */
  function extractTextContent(element) {
    // Try to find the actual text content, avoiding code blocks
    const textNodes = [];
    const walker = document.createTreeWalker(
      element,
      NodeFilter.SHOW_TEXT,
      {
        acceptNode: (node) => {
          // Skip code blocks and hidden elements
          const parent = node.parentElement;
          if (parent && (
            parent.tagName === 'CODE' ||
            parent.tagName === 'PRE' ||
            parent.closest('pre') ||
            parent.closest('code')
          )) {
            return NodeFilter.FILTER_REJECT;
          }
          return NodeFilter.FILTER_ACCEPT;
        }
      }
    );

    let node;
    while (node = walker.nextNode()) {
      textNodes.push(node.textContent);
    }

    return textNodes.join(' ').replace(/\s+/g, ' ').trim();
  }

  /**
   * Generate a concise title from text content
   */
  function generateTitle(text) {
    // Clean and truncate
    let title = text.trim();

    // Remove common prefixes
    title = title.replace(/^(hey|hi|hello|please|can you|could you|I want to|I need to|help me)/i, '').trim();

    // Truncate to max length
    if (title.length > CONFIG.TITLE_MAX_LENGTH) {
      // Try to break at a word boundary
      const truncated = title.substring(0, CONFIG.TITLE_MAX_LENGTH);
      const lastSpace = truncated.lastIndexOf(' ');
      title = lastSpace > CONFIG.TITLE_MAX_LENGTH - 20
        ? truncated.substring(0, lastSpace) + '...'
        : truncated + '...';
    }

    return title || 'Untitled section';
  }

  /**
   * Generate preview text
   */
  function generatePreview(text) {
    const lines = text.split(/[.!?]\s+/).slice(0, CONFIG.PREVIEW_LINES);
    return lines.join('. ').substring(0, 200);
  }

  /**
   * Render the TOC list
   */
  function renderTOC() {
    if (!tocList) return;

    tocList.innerHTML = '';

    const emptyState = tocContainer.querySelector('.toc-empty');

    if (sections.length === 0) {
      emptyState.style.display = 'flex';
      return;
    }

    emptyState.style.display = 'none';

    // Implement lazy loading for large conversations
    const renderCount = sections.length > CONFIG.LAZY_LOAD_THRESHOLD
      ? CONFIG.LAZY_LOAD_THRESHOLD
      : sections.length;

    sections.slice(0, renderCount).forEach((section, idx) => {
      const item = createTOCItem(section, idx === sections.length - 1);
      tocList.appendChild(item);
    });

    // Add "load more" button if needed
    if (sections.length > CONFIG.LAZY_LOAD_THRESHOLD) {
      const loadMore = document.createElement('li');
      loadMore.className = 'toc-load-more';
      loadMore.innerHTML = `<button>Load ${sections.length - CONFIG.LAZY_LOAD_THRESHOLD} more sections</button>`;
      loadMore.querySelector('button').addEventListener('click', () => {
        renderAllSections();
        loadMore.remove();
      });
      tocList.appendChild(loadMore);
    }
  }

  /**
   * Render all sections (after clicking load more)
   */
  function renderAllSections() {
    tocList.innerHTML = '';
    sections.forEach((section, idx) => {
      const item = createTOCItem(section, idx === sections.length - 1);
      tocList.appendChild(item);
    });
  }

  /**
   * Create a TOC list item
   */
  function createTOCItem(section, isLast) {
    const li = document.createElement('li');
    li.className = 'toc-item';
    li.setAttribute('data-section-id', section.id);

    li.innerHTML = `
      <div class="toc-item-connector">
        <div class="toc-item-dot"></div>
        ${!isLast ? '<div class="toc-item-line"></div>' : ''}
      </div>
      <div class="toc-item-content">
        <span class="toc-item-number">${section.index}</span>
        <span class="toc-item-title">${escapeHtml(section.title)}</span>
      </div>
    `;

    // Click handler
    li.addEventListener('click', () => {
      scrollToSection(section);
    });

    // Hover handlers for tooltip
    li.addEventListener('mouseenter', (e) => {
      showTooltip(section, e);
    });

    li.addEventListener('mouseleave', () => {
      hideTooltip();
    });

    return li;
  }

  /**
   * Scroll to a section
   */
  function scrollToSection(section) {
    if (!section.element) {
      console.log('[Threadline] No element for section:', section.id);
      return;
    }

    console.log('[Threadline] Scrolling to section:', section.id);

    // Method 1: Use scrollIntoView (most reliable)
    try {
      section.element.scrollIntoView({
        behavior: 'smooth',
        block: 'start'
      });

      // Add a highlight effect temporarily
      section.element.style.transition = 'background-color 0.3s ease';
      section.element.style.backgroundColor = 'rgba(212, 165, 116, 0.2)';
      setTimeout(() => {
        section.element.style.backgroundColor = '';
      }, 1500);

    } catch (e) {
      console.log('[Threadline] scrollIntoView failed, trying alternative');

      // Method 2: Find scrollable parent and scroll manually
      const scrollParent = findScrollParent(section.element);
      if (scrollParent) {
        const elementRect = section.element.getBoundingClientRect();
        const parentRect = scrollParent.getBoundingClientRect();
        const scrollTop = scrollParent.scrollTop + elementRect.top - parentRect.top - 100;

        scrollParent.scrollTo({
          top: scrollTop,
          behavior: 'smooth'
        });
      }
    }

    // Update active section
    setActiveSection(section.id);
  }

  /**
   * Find the scrollable parent of an element
   */
  function findScrollParent(element) {
    let parent = element.parentElement;

    while (parent) {
      const style = getComputedStyle(parent);
      const overflowY = style.overflowY;

      if ((overflowY === 'auto' || overflowY === 'scroll') && parent.scrollHeight > parent.clientHeight) {
        return parent;
      }

      parent = parent.parentElement;
    }

    return document.documentElement;
  }

  /**
   * Show tooltip for a section
   */
  function showTooltip(section, event) {
    if (!tooltip) return;

    const titleEl = tooltip.querySelector('.tooltip-title');
    const previewEl = tooltip.querySelector('.tooltip-preview');

    titleEl.textContent = section.fullTitle;
    previewEl.textContent = section.preview;

    // Position tooltip
    const itemRect = event.currentTarget.getBoundingClientRect();
    const tooltipWidth = 300;

    tooltip.style.left = `${itemRect.right + 10}px`;
    tooltip.style.top = `${itemRect.top}px`;

    // Ensure tooltip stays in viewport
    const viewportWidth = window.innerWidth;
    if (itemRect.right + tooltipWidth + 20 > viewportWidth) {
      tooltip.style.left = `${itemRect.left - tooltipWidth - 10}px`;
    }

    tooltip.classList.add('visible');
  }

  /**
   * Hide tooltip
   */
  function hideTooltip() {
    if (tooltip) {
      tooltip.classList.remove('visible');
    }
  }

  /**
   * Set up scroll listener to track active section
   */
  function setupScrollListener() {
    const handleScroll = () => {
      if (scrollTimeout) {
        cancelAnimationFrame(scrollTimeout);
      }

      scrollTimeout = requestAnimationFrame(() => {
        updateActiveSection();
      });
    };

    // Listen on window and also try to find scrollable containers
    window.addEventListener('scroll', handleScroll, { passive: true });
    document.addEventListener('scroll', handleScroll, { passive: true, capture: true });

    // Also listen on any scrollable divs
    document.querySelectorAll('div').forEach(div => {
      const style = getComputedStyle(div);
      if ((style.overflowY === 'auto' || style.overflowY === 'scroll') && div.scrollHeight > div.clientHeight) {
        div.addEventListener('scroll', handleScroll, { passive: true });
      }
    });
  }

  /**
   * Update the active section based on scroll position
   */
  function updateActiveSection() {
    if (sections.length === 0) return;

    const viewportTop = 150; // Distance from top to consider "active"

    let closestSection = null;
    let closestDistance = Infinity;

    sections.forEach(section => {
      if (!section.element) return;

      const rect = section.element.getBoundingClientRect();
      const distance = Math.abs(rect.top - viewportTop);

      // Find section closest to the top of viewport
      if (rect.top <= viewportTop + 100 && rect.top > -rect.height) {
        if (distance < closestDistance) {
          closestDistance = distance;
          closestSection = section;
        }
      }
    });

    // If no section near top, find the first visible one
    if (!closestSection) {
      for (const section of sections) {
        if (!section.element) continue;
        const rect = section.element.getBoundingClientRect();
        if (rect.top >= 0 && rect.top < window.innerHeight) {
          closestSection = section;
          break;
        }
      }
    }

    if (closestSection) {
      setActiveSection(closestSection.id);
    }
  }

  /**
   * Set the active section in the TOC
   */
  function setActiveSection(sectionId) {
    if (activeSection === sectionId) return;

    activeSection = sectionId;

    // Update visual state
    const items = tocList.querySelectorAll('.toc-item');
    items.forEach(item => {
      if (item.getAttribute('data-section-id') === sectionId) {
        item.classList.add('active');
        // Scroll TOC item into view if needed
        item.scrollIntoView({ behavior: 'smooth', block: 'nearest' });
      } else {
        item.classList.remove('active');
      }
    });
  }

  /**
   * Set up MutationObserver to detect new messages
   */
  function setupMutationObserver() {
    const targetNode = document.body;

    const config = {
      childList: true,
      subtree: true,
      characterData: false,
      attributes: false
    };

    let debounceTimer = null;
    let lastMessageCount = 0;

    // Build site-specific selector for counting messages
    const primarySelector = siteConfig.userMessageSelectors[0];

    observer = new MutationObserver((mutations) => {
      // Debounce updates
      if (debounceTimer) {
        clearTimeout(debounceTimer);
      }

      debounceTimer = setTimeout(() => {
        // Check current message count using site-specific selector
        const currentMessages = document.querySelectorAll(primarySelector);
        const currentCount = currentMessages.length;

        // If message count changed, rescan
        if (currentCount !== lastMessageCount) {
          console.log('[Threadline] Message count changed:', lastMessageCount, '->', currentCount);
          lastMessageCount = currentCount;
          scanForSections();
          return;
        }

        // Also check for any new nodes that look like messages
        let shouldRescan = false;

        mutations.forEach(mutation => {
          if (mutation.addedNodes.length > 0) {
            mutation.addedNodes.forEach(node => {
              if (node.nodeType === Node.ELEMENT_NODE) {
                // Check if node is or contains a user message using site-specific selector
                if (node.matches && node.matches(primarySelector)) {
                  shouldRescan = true;
                } else if (node.querySelector && node.querySelector(primarySelector)) {
                  shouldRescan = true;
                }

                // Also check for class-based detection using site-specific patterns
                const className = typeof node.className === 'string' ? node.className : '';
                for (const pattern of siteConfig.userClassPatterns) {
                  if (className.toLowerCase().includes(pattern.toLowerCase())) {
                    shouldRescan = true;
                    break;
                  }
                }
              }
            });
          }
        });

        if (shouldRescan) {
          console.log('[Threadline] New message detected via mutation');
          scanForSections();
        }
      }, 500); // Slightly longer debounce to let DOM settle
    });

    observer.observe(targetNode, config);

    // Also poll periodically as a fallback
    setInterval(() => {
      const currentMessages = document.querySelectorAll(primarySelector);
      const currentCount = currentMessages.length;

      if (currentCount !== lastMessageCount && currentCount > 0) {
        console.log('[Threadline] Polling detected new messages:', lastMessageCount, '->', currentCount);
        lastMessageCount = currentCount;
        scanForSections();
      }
    }, 2000); // Check every 2 seconds
  }

  /**
   * Escape HTML to prevent XSS
   */
  function escapeHtml(text) {
    const div = document.createElement('div');
    div.textContent = text;
    return div.innerHTML;
  }

  /**
   * Clean up on page unload
   */
  function cleanup() {
    if (observer) {
      observer.disconnect();
    }
    if (tocContainer) {
      tocContainer.remove();
    }
    if (tooltip) {
      tooltip.remove();
    }
  }

  // Handle page navigation in SPA
  let lastUrl = location.href;
  let lastPathname = location.pathname;

  function checkForNavigation() {
    const currentUrl = location.href;
    const currentPathname = location.pathname;

    if (currentPathname !== lastPathname) {
      console.log('[Threadline] Navigation detected:', lastPathname, '->', currentPathname);
      lastUrl = currentUrl;
      lastPathname = currentPathname;

      // Reset and re-initialize on navigation
      isInitialized = false;
      cleanup();

      // Wait for new page content to load
      setTimeout(() => {
        console.log('[Threadline] Re-initializing after navigation');
        init();
      }, 1000);
    }
  }

  // Check for URL changes periodically (more reliable for SPAs)
  setInterval(checkForNavigation, 500);

  // Also use MutationObserver as backup
  new MutationObserver(() => {
    checkForNavigation();
  }).observe(document.body, { subtree: true, childList: true });

  // Initialize when DOM is ready
  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', init);
  } else {
    init();
  }

  // Cleanup on unload
  window.addEventListener('unload', cleanup);

})();
