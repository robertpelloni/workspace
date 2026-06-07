import React, { useState, useEffect, useCallback, useMemo } from 'react';
import './App.css';
import { RateLimiterMetrics } from './RateLimiterMetrics';
import { SubmoduleList } from './components/SubmoduleList';
import { SubmoduleDetail } from './components/SubmoduleDetail';

// Status color and icon maps - defined outside component to avoid recreation
const STATUS_COLORS = {
  pending: '#ffa500',
  running: '#2196f3',
  awaiting_approval: '#ff9800',
  executing: '#4caf50',
  completed: '#4caf50',
  failed: '#f44336'
};

const STATUS_ICONS = {
  pending: '⏳',
  running: '🔄',
  awaiting_approval: '⏸️',
  executing: '⚡',
  completed: '✅',
  failed: '❌'
};

const RunningProcesses = ({ onSelectSubmodule }) => {
  const [processes, setProcesses] = useState([]);

  const fetchProcesses = () => {
    fetch('/api/submodules/processes')
      .then(res => res.json())
      .then(data => setProcesses(data))
      .catch(err => console.error('Failed to fetch processes', err));
  };

  useEffect(() => {
    fetchProcesses();
    const interval = setInterval(fetchProcesses, 5000);
    return () => clearInterval(interval);
  }, []);

  if (processes.length === 0) return null;

  return (
    <div className="running-processes-panel">
      <h3>Active Processes ({processes.length})</h3>
      <div className="process-list">
        {processes.map(p => (
          <div key={p.id} className="process-item">
            <span className="process-name">
              <strong>{p.submoduleName}</strong>: {p.scriptName}
            </span>
            <div className="process-actions">
              <button onClick={() => onSelectSubmodule(p.submoduleName)}>View</button>
            </div>
          </div>
        ))}
      </div>
      <style>{`
        .running-processes-panel {
            position: fixed;
            bottom: 20px;
            right: 20px;
            width: 300px;
            background: #2d2d2d;
            border: 1px solid #444;
            border-radius: 8px;
            box-shadow: 0 4px 6px rgba(0,0,0,0.3);
            color: #fff;
            z-index: 1000;
            padding: 10px;
        }
        .running-processes-panel h3 {
            margin: 0 0 10px 0;
            font-size: 1rem;
            border-bottom: 1px solid #444;
            padding-bottom: 5px;
        }
        .process-item {
            display: flex;
            justify-content: space-between;
            align-items: center;
            margin-bottom: 8px;
            font-size: 0.9rem;
        }
        .process-actions button {
            background: #2196f3;
            border: none;
            color: white;
            padding: 4px 8px;
            border-radius: 4px;
            cursor: pointer;
            font-size: 0.8rem;
        }
      `}</style>
    </div>
  );
};

function App() {
  const [workflows, setWorkflows] = useState([]);
  const [stats, setStats] = useState({ total: 0, running: 0, completed: 0, failed: 0 });
  const [executingWorkflow, setExecutingWorkflow] = useState(null);
  const [ws, setWs] = useState(null);

  // Submodule State
  const [showSubmodules, setShowSubmodules] = useState(false);
  const [selectedSubmodule, setSelectedSubmodule] = useState(null);

  useEffect(() => {
    // Fetch initial workflows
    fetch('/api/v1/workflows')
      .then(res => res.json())
      .then(data => setWorkflows(data))
      .catch(() => setWorkflows([])); // Graceful error handling

    // Connect WebSocket for real-time updates
    const websocket = new WebSocket('wss://agent.scarmonit.com/ws');

    websocket.onmessage = (event) => {
      const update = JSON.parse(event.data);

      if (update.type === 'workflow_update') {
        setWorkflows(prev =>
          prev.map(w => w.id === update.workflow_id
            ? { ...w, ...update.data }
            : w
          )
        );
      }

      if (update.type === 'stats_update') {
        setStats(update.data);
      }
    };

    setWs(websocket);

    return () => websocket.close();
  }, []);

  // Memoized callback to prevent recreation on every render
  const executeWorkflow = useCallback(async (templateName, context) => {
    setExecutingWorkflow(templateName);
    try {
      const response = await fetch('/api/v1/workflows/execute', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ template_name: templateName, context })
      });
      const data = await response.json();
      console.log(`Workflow ${data.workflow_id} started`); // Replace alert with console
    } catch (err) {
      console.error('Failed to execute workflow:', err);
    } finally {
      setExecutingWorkflow(null);
    }
  }, []);

  // Memoized helper functions - O(1) lookup
  const getStatusColor = useCallback((status) => STATUS_COLORS[status] || '#999', []);
  const getStatusIcon = useCallback((status) => STATUS_ICONS[status] || '•', []);

  const handleProcessSelect = (submoduleName) => {
    // Switch to submodule view and load the submodule
    setView('submodules');
    // We need to trigger the selection. If SubmoduleList is mounted, it has the list.
    // But if we switch views, SubmoduleList mounts and fetches.
    // We can pass `initialSelection` to SubmoduleList or SubmoduleView.
    setSelectedSubmodule(submoduleName);
  };

  return (
    <div className="App">
      <header>
        <div style={{ display: 'flex', alignItems: 'center', gap: '1rem' }}>
          <h1>🤖 Jules Orchestrator</h1>
          <button onClick={() => { setShowSubmodules(!showSubmodules); setSelectedSubmodule(null); }}>
            {showSubmodules ? 'View Workflows' : 'View Submodules'}
          </button>
        </div>
        {!showSubmodules && (
          <div className="stats">
            <div className="stat">
              <span className="label">Total</span>
              <span className="value">{stats.total}</span>
            </div>
            <div className="stat">
              <span className="label">Running</span>
              <span className="value running">{stats.running}</span>
            </div>
            <div className="stat">
              <span className="label">Completed</span>
              <span className="value completed">{stats.completed}</span>
            </div>
            <div className="stat">
              <span className="label">Failed</span>
              <span className="value failed">{stats.failed}</span>
            </div>
          </div>
        )}
      </header>

      <main>
        {showSubmodules ? (
          <section className="submodules-section">
            {/* We need a wrapper to handle finding the submodule object if only name is known */}
            <SubmoduleViewWrapper
              selectedName={selectedSubmodule}
              onClear={() => setSelectedSubmodule(null)}
            />
          </section>
        ) : (
          <>
            <RateLimiterMetrics />
            <section className="quick-actions">
              <h2>Quick Actions</h2>
              <div className="action-buttons">
                <button
                  onClick={() => executeWorkflow('dependency-update', { repo_name: 'scarmonit/jules-orchestrator' })}
                  disabled={executingWorkflow === 'dependency-update'}
                  aria-label="Update project dependencies"
                >
                  {executingWorkflow === 'dependency-update' ? '⏳ Starting...' : '📦 Update Dependencies'}
                </button>
                <button
                  onClick={() => executeWorkflow('documentation-sync', { repo_name: 'scarmonit/jules-orchestrator' })}
                  disabled={executingWorkflow === 'documentation-sync'}
                  aria-label="Synchronize documentation"
                >
                  {executingWorkflow === 'documentation-sync' ? '⏳ Syncing...' : '📝 Sync Docs'}
                </button>
                <button
                  onClick={() => executeWorkflow('security-patch', { repo_name: 'scarmonit/jules-orchestrator' })}
                  disabled={executingWorkflow === 'security-patch'}
                  aria-label="Run security scan"
                >
                  {executingWorkflow === 'security-patch' ? '⏳ Scanning...' : '🔒 Security Scan'}
                </button>
              </div>
            </section>

            <section className="workflows">
              <h2>Active Workflows</h2>
              <div className="workflow-list">
                {workflows.map(workflow => (
                  <div key={workflow.id} className="workflow-card">
                    <div className="workflow-header">
                      <span className="workflow-icon" style={{ color: getStatusColor(workflow.status) }}>
                        {getStatusIcon(workflow.status)}
                      </span>
                      <div className="workflow-info">
                        <h3>{workflow.context_json.repo_name}</h3>
                        <p className="workflow-title">{workflow.context_json.issue_title || workflow.template_name}</p>
                      </div>
                      <span className="workflow-status" style={{ backgroundColor: getStatusColor(workflow.status) }}>
                        {workflow.status}
                      </span>
                    </div>

                    <div className="workflow-details">
                      <div className="detail">
                        <span className="detail-label">Template:</span>
                        <span>{workflow.template_name}</span>
                      </div>
                      <div className="detail">
                        <span className="detail-label">Created:</span>
                        <span>{new Date(workflow.created_at).toLocaleString()}</span>
                      </div>
                      {workflow.pr_url && (
                        <div className="detail">
                          <a href={workflow.pr_url} target="_blank" rel="noopener noreferrer">
                            View PR →
                          </a>
                        </div>
                      )}
                    </div>

                    {workflow.status === 'awaiting_approval' && (
                      <div className="workflow-actions">
                        <button className="approve">✓ Approve</button>
                        <button className="reject">✗ Reject</button>
                      </div>
                    )}
                  </div>
                ))}
              </div>
            </section>

            <section className="templates">
              <h2>Workflow Templates</h2>
              <div className="template-grid">
                <div className="template-card">
                  <h3>🐛 Bug Fix</h3>
                  <p>Auto-fix from labeled issues</p>
                  <span className="template-trigger">Trigger: bug-auto label</span>
                </div>
                <div className="template-card">
                  <h3>✨ Feature</h3>
                  <p>Implement feature from spec</p>
                  <span className="template-trigger">Trigger: @tools\jules-mcp\dist\client\jules-client.js implement</span>
                </div>
                <div className="template-card">
                  <h3>📦 Dependencies</h3>
                  <p>Weekly update check</p>
                  <span className="template-trigger">Trigger: Monday 2 AM</span>
                </div>
                <div className="template-card">
                  <h3>🔒 Security</h3>
                  <p>Patch vulnerabilities</p>
                  <span className="template-trigger">Trigger: Scanner alert</span>
                </div>
                <div className="template-card">
                  <h3>📝 Docs</h3>
                  <p>Sync documentation</p>
                  <span className="template-trigger">Trigger: main push</span>
                </div>
              </div>
            </section>
          </>
        )}
      </main>

      <RunningProcesses onSelectSubmodule={handleProcessSelect} />
    </div>
  );
}

// Helper to manage submodule selection and data fetching
const SubmoduleViewWrapper = ({ selectedName, onClear }) => {
  const [submodules, setSubmodules] = useState([]);
  const [selectedObject, setSelectedObject] = useState(null);

  useEffect(() => {
    // Fetch list to find the object or just check if selectedName matches
    fetch('/api/submodules')
      .then(res => res.json())
      .then(data => {
        setSubmodules(data);
        if (selectedName) {
          // Try to find in list
          const found = data.find(s => s.name === selectedName);
          // If selectedName is an object (legacy), use it
          if (typeof selectedName === 'object' && selectedName !== null) {
            setSelectedObject(selectedName);
          } else if (found) {
            setSelectedObject(found);
          }
        } else {
          setSelectedObject(null);
        }
      })
      .catch(err => console.error('Failed to fetch submodules', err));
  }, [selectedName]);

  // Internal selection handler from List
  const handleListSelect = (sub) => {
    setSelectedObject(sub);
  };

  if (selectedObject) {
    return <SubmoduleDetail submodule={selectedObject} onBack={() => { setSelectedObject(null); onClear(); }} />;
  }

  return <SubmoduleList submodules={submodules} onSelect={handleListSelect} />;
};

export default App;
