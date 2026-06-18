// Modern Saved Summaries JavaScript
let allSummaries = [];
let filteredSummaries = [];
let currentFilter = 'all';

// Initialize the application
document.addEventListener('DOMContentLoaded', () => {
  console.log('Modern Saved Summaries - Initializing...');
  initializeApp();
});

function initializeApp() {
  loadSummaries();
  setupEventListeners();
  setupKeyboardShortcuts();
}

function setupEventListeners() {
  // Search functionality
  const searchInput = document.getElementById('search-input');
  searchInput.addEventListener('input', debounce(handleSearch, 300));
  
  // Filter buttons
  const filterButtons = document.querySelectorAll('.filter-btn');
  filterButtons.forEach(btn => {
    btn.addEventListener('click', () => handleFilterChange(btn.dataset.filter));
  });
  
  // Action buttons
  document.getElementById('export-btn').addEventListener('click', exportSummaries);
  document.getElementById('clear-btn').addEventListener('click', clearAllSummaries);
}

function setupKeyboardShortcuts() {
  document.addEventListener('keydown', (e) => {
    // Ctrl/Cmd + F to focus search
    if ((e.ctrlKey || e.metaKey) && e.key === 'f') {
      e.preventDefault();
      document.getElementById('search-input').focus();
    }
    
    // Escape to clear search
    if (e.key === 'Escape') {
      const searchInput = document.getElementById('search-input');
      if (searchInput.value) {
        searchInput.value = '';
        handleSearch();
      }
    }
  });
}

async function loadSummaries() {
  console.log('Loading summaries from chrome.storage.local...');
  
  try {
    // Load from chrome.storage.local (used by the extension)
    const result = await chrome.storage.local.get(['get_tldr_saved_summaries']);
    
    if (result.get_tldr_saved_summaries && result.get_tldr_saved_summaries.length > 0) {
      allSummaries = result.get_tldr_saved_summaries;
      console.log(`Loaded ${allSummaries.length} summaries from chrome.storage.local`);
    } else {
      console.log('No stored summaries found');
      allSummaries = [];
    }
    
    // Ensure summaries have required fields
    allSummaries = allSummaries.map(summary => {
      // Handle date parsing safely
      let createdAt;
      if (summary.createdAt) {
        const date = new Date(summary.createdAt);
        createdAt = isNaN(date.getTime()) ? new Date().toISOString() : date.toISOString();
      } else if (summary.timestamp) {
        const date = new Date(summary.timestamp);
        createdAt = isNaN(date.getTime()) ? new Date().toISOString() : date.toISOString();
      } else {
        createdAt = new Date().toISOString();
      }
      
      return {
        id: summary.id || `summary_${Date.now()}_${Math.random().toString(36).substr(2, 9)}`,
        title: summary.title || 'Untitled Summary',
        url: summary.url || '',
        summary: summary.summary || summary.content || '',
        prompt: summary.prompt || 'Default summarization',
        tokensUsed: summary.tokensUsed || 0,
        wordCount: summary.wordCount || summary.summary?.split(' ').length || 0,
        createdAt: createdAt,
        tags: summary.tags || []
      };
    });
    
    filteredSummaries = [...allSummaries];
    renderSummaries();
    updateStats();
    
  } catch (error) {
    console.error('Error loading summaries:', error);
    showToast('Error loading summaries', 'error');
    allSummaries = [];
    filteredSummaries = [];
    renderEmptyState();
  }
}

// Sample data function removed - now loading from chrome.storage.local only

function renderSummaries() {
  const container = document.getElementById('summaries-grid');
  
  if (filteredSummaries.length === 0) {
    renderEmptyState();
    return;
  }
  
  const summariesHTML = filteredSummaries.map(summary => createSummaryCard(summary)).join('');
  container.innerHTML = summariesHTML;
  
  // Add event listeners to action buttons
  setupSummaryActions();
}

function createSummaryCard(summary) {
  const createdDate = new Date(summary.createdAt);
  const isValidDate = !isNaN(createdDate.getTime());
  
  const formattedDate = isValidDate ? createdDate.toLocaleDateString('en-US', {
    year: 'numeric',
    month: 'short',
    day: 'numeric'
  }) : 'Unknown date';
  
  const timeAgo = isValidDate ? getTimeAgo(createdDate) : 'Unknown';
  
  const tagsHTML = summary.tags && summary.tags.length > 0 
    ? summary.tags.map(tag => `<span class="tag">${escapeHtml(tag)}</span>`).join('')
    : '';
  
  // Render markdown for summary content
  const summaryHTML = marked.parse(summary.summary);
  
  return `
    <div class="summary-card" data-id="${summary.id}">
      <div class="summary-header">
        <h3 class="summary-title">${escapeHtml(summary.title)}</h3>
        <div class="summary-actions">
          <button class="action-btn expand" title="Expand summary" data-action="expand">
            <i class="fas fa-expand-alt"></i>
          </button>
          <button class="action-btn copy" title="Copy summary" data-action="copy">
            <i class="fas fa-copy"></i>
          </button>
          <button class="action-btn delete" title="Delete summary" data-action="delete">
            <i class="fas fa-trash"></i>
          </button>
        </div>
      </div>
      
      <div class="summary-content markdown-content">${summaryHTML}</div>
      
      <div class="summary-meta">
        <span title="${formattedDate}">${timeAgo}</span>
        <a href="${summary.url}" target="_blank" class="summary-url" title="${summary.url}">
          ${truncateUrl(summary.url, 30)}
        </a>
      </div>
      
      ${tagsHTML ? `<div class="summary-tags">${tagsHTML}</div>` : ''}
    </div>
  `;
}

function setupSummaryActions() {
  const actionButtons = document.querySelectorAll('.action-btn');
  
  actionButtons.forEach(btn => {
    btn.addEventListener('click', (e) => {
      e.stopPropagation();
      const action = btn.dataset.action;
      const summaryCard = btn.closest('.summary-card');
      const summaryId = summaryCard.dataset.id;
      
      if (action === 'copy') {
        copySummary(summaryId);
      } else if (action === 'delete') {
        deleteSummary(summaryId);
      } else if (action === 'expand') {
        toggleSummaryExpansion(summaryCard, btn);
      }
    });
  });
}

function toggleSummaryExpansion(summaryCard, button) {
  const summaryContent = summaryCard.querySelector('.summary-content');
  const icon = button.querySelector('i');
  
  if (summaryContent.classList.contains('expanded')) {
    // Collapse
    summaryContent.classList.remove('expanded');
    icon.className = 'fas fa-expand-alt';
    button.title = 'Expand summary';
  } else {
    // Expand
    summaryContent.classList.add('expanded');
    icon.className = 'fas fa-compress-alt';
    button.title = 'Collapse summary';
  }
}

function copySummary(summaryId) {
  const summary = allSummaries.find(s => s.id === summaryId);
  if (!summary) return;
  
  const textToCopy = `${summary.title}\n\n${summary.summary}\n\nSource: ${summary.url}`;
  
  navigator.clipboard.writeText(textToCopy).then(() => {
    showToast('Summary copied to clipboard!', 'success');
  }).catch(() => {
    // Fallback for older browsers
    const textArea = document.createElement('textarea');
    textArea.value = textToCopy;
    document.body.appendChild(textArea);
    textArea.select();
    document.execCommand('copy');
    document.body.removeChild(textArea);
    showToast('Summary copied to clipboard!', 'success');
  });
}

async function deleteSummary(summaryId) {
  if (!confirm('Are you sure you want to delete this summary? This action cannot be undone.')) {
    return;
  }
  
  try {
    // Remove from arrays
    allSummaries = allSummaries.filter(s => s.id !== summaryId);
    filteredSummaries = filteredSummaries.filter(s => s.id !== summaryId);
    
    // Update storage
    await chrome.storage.local.set({ 'get_tldr_saved_summaries': allSummaries });
    
    // Re-render
    renderSummaries();
    updateStats();
    
    showToast('Summary deleted successfully', 'success');
  } catch (error) {
    console.error('Error deleting summary:', error);
    showToast('Error deleting summary', 'error');
  }
}

function handleSearch() {
  const query = document.getElementById('search-input').value.toLowerCase().trim();
  
  if (!query) {
    filteredSummaries = [...allSummaries];
  } else {
    filteredSummaries = allSummaries.filter(summary => 
      summary.title.toLowerCase().includes(query) ||
      summary.summary.toLowerCase().includes(query) ||
      summary.url.toLowerCase().includes(query) ||
      (summary.tags && summary.tags.some(tag => tag.toLowerCase().includes(query)))
    );
  }
  
  applyCurrentFilter();
  renderSummaries();
}

function handleFilterChange(filter) {
  currentFilter = filter;
  
  // Update active filter button
  document.querySelectorAll('.filter-btn').forEach(btn => {
    btn.classList.toggle('active', btn.dataset.filter === filter);
  });
  
  applyCurrentFilter();
  renderSummaries();
}

function applyCurrentFilter() {
  const now = new Date();
  const today = new Date(now.getFullYear(), now.getMonth(), now.getDate());
  const weekAgo = new Date(today.getTime() - 7 * 24 * 60 * 60 * 1000);
  const monthAgo = new Date(today.getTime() - 30 * 24 * 60 * 60 * 1000);
  
  switch (currentFilter) {
    case 'today':
      filteredSummaries = filteredSummaries.filter(summary => {
        const summaryDate = new Date(summary.createdAt);
        return summaryDate >= today;
      });
      break;
    case 'week':
      filteredSummaries = filteredSummaries.filter(summary => {
        const summaryDate = new Date(summary.createdAt);
        return summaryDate >= weekAgo;
      });
      break;
    case 'month':
      filteredSummaries = filteredSummaries.filter(summary => {
        const summaryDate = new Date(summary.createdAt);
        return summaryDate >= monthAgo;
      });
      break;
    case 'all':
    default:
      // No additional filtering needed
      break;
  }
}

async function updateStats() {
  const totalCount = document.getElementById('total-count');
  const storageUsed = document.getElementById('storage-used');
  const recentCount = document.getElementById('recent-count');
  
  // Total summaries
  totalCount.textContent = allSummaries.length;
  
  // Storage usage - use chrome.storage.local quota
  try {
    const bytesInUse = await chrome.storage.local.getBytesInUse();
    const quota = chrome.storage.local.QUOTA_BYTES || 10485760; // 10MB default
    const usagePercent = Math.round((bytesInUse / quota) * 100);
    storageUsed.textContent = `${usagePercent}%`;
  } catch (error) {
    storageUsed.textContent = 'N/A';
  }
  
  // Recent summaries (this week)
  const weekAgo = new Date(Date.now() - 7 * 24 * 60 * 60 * 1000);
  const recentSummaries = allSummaries.filter(summary => {
    const summaryDate = new Date(summary.createdAt);
    return summaryDate >= weekAgo;
  });
  recentCount.textContent = recentSummaries.length;
}

function renderEmptyState() {
  const container = document.getElementById('summaries-grid');
  const query = document.getElementById('search-input').value;
  
  const emptyHTML = `
    <div class="empty-state">
      <div class="empty-icon">
        <i class="fas fa-file-text"></i>
      </div>
      <h3 class="empty-title">
        ${query ? 'No summaries found' : 'No summaries yet'}
      </h3>
      <p class="empty-description">
        ${query 
          ? 'Try adjusting your search terms or filters to find what you\'re looking for.' 
          : 'Start summarizing web pages with the Get TLDR extension to see them saved here automatically.'}
      </p>
    </div>
  `;
  
  container.innerHTML = emptyHTML;
}

function exportSummaries() {
  if (allSummaries.length === 0) {
    showToast('No summaries to export', 'error');
    return;
  }
  
  try {
    const exportData = {
      exportDate: new Date().toISOString(),
      totalSummaries: allSummaries.length,
      summaries: allSummaries
    };
    
    const dataStr = JSON.stringify(exportData, null, 2);
    const dataBlob = new Blob([dataStr], { type: 'application/json' });
    const url = URL.createObjectURL(dataBlob);
    
    const link = document.createElement('a');
    link.href = url;
    link.download = `get-tldr-summaries-${new Date().toISOString().split('T')[0]}.json`;
    link.click();
    
    URL.revokeObjectURL(url);
    showToast('Summaries exported successfully!', 'success');
  } catch (error) {
    console.error('Error exporting summaries:', error);
    showToast('Error exporting summaries', 'error');
  }
}

async function clearAllSummaries() {
  if (allSummaries.length === 0) {
    showToast('No summaries to clear', 'error');
    return;
  }
  
  const confirmMessage = `Are you sure you want to delete all ${allSummaries.length} summaries? This action cannot be undone.`;
  
  if (!confirm(confirmMessage)) {
    return;
  }
  
  try {
    await chrome.storage.local.remove(['get_tldr_saved_summaries']);
    allSummaries = [];
    filteredSummaries = [];
    
    renderSummaries();
    updateStats();
    
    showToast('All summaries cleared successfully', 'success');
  } catch (error) {
    console.error('Error clearing summaries:', error);
    showToast('Error clearing summaries', 'error');
  }
}

function showToast(message, type = 'success') {
  const toast = document.getElementById('toast');
  const toastMessage = document.getElementById('toast-message');
  
  toastMessage.textContent = message;
  toast.className = `toast ${type} show`;
  
  setTimeout(() => {
    toast.classList.remove('show');
  }, 3000);
}

// Utility functions
function escapeHtml(text) {
  const div = document.createElement('div');
  div.textContent = text;
  return div.innerHTML;
}

function truncateUrl(url, maxLength = 50) {
  if (!url) return '';
  if (url.length <= maxLength) return url;
  
  try {
    const urlObj = new URL(url);
    const domain = urlObj.hostname;
    if (domain.length <= maxLength) return domain;
    return domain.substring(0, maxLength - 3) + '...';
  } catch {
    return url.substring(0, maxLength - 3) + '...';
  }
}

function getTimeAgo(date) {
  // Ensure we have a valid Date object
  if (!(date instanceof Date) || isNaN(date.getTime())) {
    return 'Unknown';
  }
  
  const now = new Date();
  const diffInSeconds = Math.floor((now - date) / 1000);
  
  if (diffInSeconds < 60) return 'Just now';
  if (diffInSeconds < 3600) return `${Math.floor(diffInSeconds / 60)}m ago`;
  if (diffInSeconds < 86400) return `${Math.floor(diffInSeconds / 3600)}h ago`;
  if (diffInSeconds < 604800) return `${Math.floor(diffInSeconds / 86400)}d ago`;
  
  return date.toLocaleDateString('en-US', { month: 'short', day: 'numeric' });
}

function debounce(func, wait) {
  let timeout;
  return function executedFunction(...args) {
    const later = () => {
      clearTimeout(timeout);
      func(...args);
    };
    clearTimeout(timeout);
    timeout = setTimeout(later, wait);
  };
}

// Export functions for potential external use
window.SavedSummariesApp = {
  loadSummaries,
  exportSummaries,
  clearAllSummaries,
  showToast
};