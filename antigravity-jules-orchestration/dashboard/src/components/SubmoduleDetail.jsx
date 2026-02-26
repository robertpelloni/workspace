import React, { useState, useEffect, useRef } from 'react';
import { ConfigEditor } from './ConfigEditor';
import ReactMarkdown from 'react-markdown';

export function SubmoduleDetail({ submodule, onBack }) {
    const [activeTab, setActiveTab] = useState('info');
    const [executionOutput, setExecutionOutput] = useState([]);
    const [executing, setExecuting] = useState(false);
    const [editingFile, setEditingFile] = useState(null);
    const [docContent, setDocContent] = useState('');
    const [loadingDoc, setLoadingDoc] = useState(false);
    const [activeScript, setActiveScript] = useState(null);
    const wsRef = useRef(null);
    const outputEndRef = useRef(null);

    useEffect(() => {
        // Check for existing running processes for this submodule
        fetch('/api/submodules/processes')
            .then(res => res.json())
            .then(processes => {
                const running = processes.find(p => p.submoduleName === submodule.name);
                if (running) {
                    // Auto-attach
                    setActiveTab('actions');
                    handleExecute(running.scriptName, null, true); // true = isReattach
                }
            })
            .catch(err => console.error('Failed to check running processes', err));

        return () => {
            if (wsRef.current) {
                wsRef.current.close();
            }
        };
    }, [submodule.name]);

    useEffect(() => {
        if (outputEndRef.current) {
            outputEndRef.current.scrollIntoView({ behavior: 'smooth' });
        }
    }, [executionOutput]);

    useEffect(() => {
        if (activeTab === 'doc') {
            const readme = submodule.configFiles.find(f => f.toLowerCase() === 'readme.md');
            const architecture = submodule.configFiles.find(f => f.toLowerCase() === 'architecture.md');
            const targetFile = readme || architecture;

            if (targetFile) {
                setLoadingDoc(true);
                fetch(`/api/submodules/${submodule.name}/config?file=${targetFile}`)
                    .then(res => res.json())
                    .then(data => {
                        setDocContent(data.content || 'No content');
                        setLoadingDoc(false);
                    })
                    .catch(err => {
                        console.error('Failed to load doc', err);
                        setDocContent('Failed to load documentation');
                        setLoadingDoc(false);
                    });
            } else {
                setDocContent('No README.md or ARCHITECTURE.md found.');
            }
        }
    }, [activeTab, submodule]);

    const handleExecute = (scriptId, command, isReattach = false) => {
        setExecuting(true);
        setActiveScript(scriptId);
        setExecutionOutput([]); // Clear previous output

        // Construct WebSocket URL
        const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
        const host = window.location.hostname;
        const wsUrl = `wss://agent.scarmonit.com/ws/submodules/execute?name=${encodeURIComponent(submodule.name)}&script=${encodeURIComponent(scriptId)}`;

        const ws = new WebSocket(wsUrl);
        wsRef.current = ws;

        ws.onopen = () => {
            if (!isReattach) {
                setExecutionOutput(prev => [...prev, { type: 'system', data: `Starting ${scriptId}...\n` }]);
            } else {
                setExecutionOutput(prev => [...prev, { type: 'system', data: `Re-attaching to ${scriptId}...\n` }]);
            }
        };

        ws.onmessage = (event) => {
            try {
                const msg = JSON.parse(event.data);
                setExecutionOutput(prev => [...prev, msg]);

                if (msg.type === 'exit') {
                    setExecuting(false);
                    setActiveScript(null);
                    ws.close();
                }
                if (msg.type === 'error') {
                    setExecuting(false);
                    setActiveScript(null);
                    ws.close();
                }
            } catch (e) {
                console.error('Failed to parse WS message', event.data);
            }
        };

        ws.onclose = () => {
            setExecuting(false);
            setActiveScript(null);
            setExecutionOutput(prev => [...prev, { type: 'system', data: '\nConnection closed.' }]);
            wsRef.current = null;
        };

        ws.onerror = (err) => {
            console.error('WebSocket error', err);
            setExecutionOutput(prev => [...prev, { type: 'error', data: 'WebSocket connection failed.' }]);
            setExecuting(false);
            setActiveScript(null);
        };
    };

    const stopExecution = () => {
        if (activeScript) {
            const processId = `${submodule.name}:${activeScript}`;
            fetch(`/api/submodules/processes/${encodeURIComponent(processId)}`, { method: 'DELETE' })
                .then(() => {
                    setExecutionOutput(prev => [...prev, { type: 'system', data: '\nProcess terminated by user.' }]);
                    if (wsRef.current) wsRef.current.close();
                    setExecuting(false);
                    setActiveScript(null);
                })
                .catch(err => console.error('Failed to kill process', err));
        }
    };

    return (
        <div className="submodule-detail">
            <header>
                <button onClick={onBack} className="back-btn" title="Return to list">← Back</button>
                <h2>{submodule.name} <span className="type-badge">{submodule.type}</span></h2>
            </header>

            <div className="tabs">
                <button className={activeTab === 'info' ? 'active' : ''} onClick={() => setActiveTab('info')} title="General Information">Info</button>
                <button className={activeTab === 'doc' ? 'active' : ''} onClick={() => setActiveTab('doc')} title="Project Documentation">Documentation</button>
                <button className={activeTab === 'config' ? 'active' : ''} onClick={() => setActiveTab('config')} title="Edit Configuration Files">Configuration</button>
                <button className={activeTab === 'actions' ? 'active' : ''} onClick={() => setActiveTab('actions')} title="Execute Scripts">Actions</button>
            </div>

            <div className="tab-content">
                {activeTab === 'info' && (
                    <div className="info-tab">
                        <p><strong>Path:</strong> {submodule.path}</p>
                        <p><strong>Type:</strong> {submodule.type}</p>
                        <p><strong>Config Files:</strong> {submodule.configFiles.join(', ')}</p>
                        {submodule.gitStatus && (
                            <div className="git-info">
                                <h3>Git Status</h3>
                                <p><strong>Branch:</strong> {submodule.gitStatus.branch}</p>
                                <p><strong>Commit:</strong> <code>{submodule.gitStatus.commit}</code></p>
                                <p><strong>Status:</strong> {submodule.gitStatus.isDirty ? '⚠️ Uncommitted Changes' : '✅ Clean'}</p>
                            </div>
                        )}
                    </div>
                )}

                {activeTab === 'doc' && (
                    <div className="doc-tab markdown-body">
                        {loadingDoc ? <p>Loading documentation...</p> : (
                            <ReactMarkdown>{docContent}</ReactMarkdown>
                        )}
                    </div>
                )}

                {activeTab === 'config' && (
                    <div className="config-tab">
                        <h3>Configuration Files</h3>
                        <div className="file-list">
                            {submodule.configFiles.map(file => (
                                <div key={file} className="file-item">
                                    <span>{file}</span>
                                    <button onClick={() => setEditingFile(file)} title={`Edit ${file}`}>Edit</button>
                                </div>
                            ))}
                        </div>
                        {editingFile && (
                            <ConfigEditor
                                submoduleName={submodule.name}
                                filename={editingFile}
                                onClose={() => setEditingFile(null)}
                            />
                        )}
                    </div>
                )}

                {activeTab === 'actions' && (
                    <div className="actions-tab">
                        <h3>Available Scripts</h3>
                        <div className="script-list">
                            {Object.entries(submodule.scripts).map(([name, cmd]) => (
                                <div key={name} className="script-item">
                                    <div className="script-info">
                                        <strong>{name}</strong>
                                        <code>{cmd}</code>
                                    </div>
                                    <div>
                                        {executing && wsRef.current ? (
                                            <button onClick={stopExecution} className="stop-btn" title="Stop running process">Stop</button>
                                        ) : (
                                            <button onClick={() => handleExecute(name, cmd)} disabled={executing} title={`Run ${name}`}>Run</button>
                                        )}
                                    </div>
                                </div>
                            ))}
                        </div>

                        <div className={`execution-output`}>
                            <h4>Execution Output</h4>
                            <div className="terminal-window">
                                {executionOutput.map((item, i) => (
                                    <span key={i} className={`output-line ${item.type}`}>{item.data}</span>
                                ))}
                                <div ref={outputEndRef} />
                            </div>
                        </div>
                    </div>
                )}
            </div>

            <style>{`
        .submodule-detail { padding: 1rem; }
        header { display: flex; align-items: center; gap: 1rem; margin-bottom: 1rem; }
        .back-btn { background: none; border: 1px solid #ccc; padding: 5px 10px; cursor: pointer; border-radius: 4px; }
        .type-badge { font-size: 0.8rem; background: #eee; padding: 2px 6px; border-radius: 4px; vertical-align: middle; }
        .tabs { border-bottom: 1px solid #ddd; margin-bottom: 1rem; }
        .tabs button { background: none; border: none; padding: 10px 20px; cursor: pointer; border-bottom: 2px solid transparent; }
        .tabs button.active { border-bottom-color: #2196f3; color: #2196f3; font-weight: bold; }
        .file-item, .script-item { display: flex; justify-content: space-between; align-items: center; padding: 10px; border-bottom: 1px solid #eee; }
        .script-info { display: flex; flex-direction: column; }
        .execution-output { margin-top: 1rem; padding: 0.5rem; background: #1e1e1e; color: #f0f0f0; border-radius: 4px; font-family: 'Consolas', monospace; }
        .terminal-window { max-height: 400px; overflow-y: auto; white-space: pre-wrap; word-break: break-all; font-size: 0.9rem; }
        .output-line { display: inline; }
        .output-line.stderr { color: #ff8a80; }
        .output-line.error { color: #ff5252; font-weight: bold; }
        .output-line.system { color: #90caf9; font-style: italic; }
        .stop-btn { background: #d32f2f; color: white; border: none; padding: 5px 10px; border-radius: 4px; cursor: pointer; }
        .doc-tab { line-height: 1.6; max-width: 900px; }
        .doc-tab h1, .doc-tab h2, .doc-tab h3 { margin-top: 1.5rem; }
        .doc-tab code { background: #f5f5f5; padding: 2px 4px; border-radius: 3px; }
        .doc-tab pre { background: #f5f5f5; padding: 1rem; border-radius: 4px; overflow-x: auto; }
        .git-info { margin-top: 1rem; border-top: 1px solid #eee; padding-top: 1rem; }
        .git-info h3 { font-size: 1rem; margin-bottom: 0.5rem; }
        .git-info p { margin: 0.2rem 0; }
      `}</style>
        </div>
    );
}
