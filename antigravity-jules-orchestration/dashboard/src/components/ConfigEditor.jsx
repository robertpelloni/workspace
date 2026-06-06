
import React, { useState, useEffect } from 'react';

export function ConfigEditor({ submoduleName, filename, onClose }) {
    const [content, setContent] = useState('');
    const [loading, setLoading] = useState(true);
    const [saving, setSaving] = useState(false);
    const [message, setMessage] = useState(null);

    useEffect(() => {
        fetch(`/api/submodules/${submoduleName}/config?file=${filename}`)
            .then(res => res.json())
            .then(data => {
                setContent(data.content);
                setLoading(false);
            })
            .catch(err => {
                setMessage({ type: 'error', text: err.message });
                setLoading(false);
            });
    }, [submoduleName, filename]);

    const handleSave = async () => {
        setSaving(true);
        setMessage(null);
        try {
            const res = await fetch(`/api/submodules/${submoduleName}/config`, {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ file: filename, content })
            });
            const data = await res.json();
            if (data.error) throw new Error(data.error);
            setMessage({ type: 'success', text: 'Saved successfully!' });
        } catch (err) {
            setMessage({ type: 'error', text: err.message });
        } finally {
            setSaving(false);
        }
    };

    if (loading) return <div>Loading config...</div>;

    return (
        <div className="config-editor-overlay">
            <div className="config-editor">
                <header>
                    <h3>Editing {filename} for {submoduleName}</h3>
                    <button onClick={onClose} className="close-btn">×</button>
                </header>
                {message && <div className={`message ${message.type}`}>{message.text}</div>}
                <textarea
                    value={content}
                    onChange={e => setContent(e.target.value)}
                    spellCheck="false"
                />
                <footer>
                    <button onClick={handleSave} disabled={saving}>
                        {saving ? 'Saving...' : 'Save Changes'}
                    </button>
                </footer>
            </div>
            <style>{`
        .config-editor-overlay {
          position: fixed;
          top: 0; left: 0; right: 0; bottom: 0;
          background: rgba(0,0,0,0.5);
          display: flex;
          align-items: center;
          justify-content: center;
          z-index: 1000;
        }
        .config-editor {
          background: white;
          width: 80%;
          height: 80%;
          display: flex;
          flex-direction: column;
          border-radius: 8px;
          box-shadow: 0 10px 25px rgba(0,0,0,0.2);
        }
        header {
          padding: 1rem;
          border-bottom: 1px solid #eee;
          display: flex;
          justify-content: space-between;
          align-items: center;
        }
        .close-btn {
          background: none;
          border: none;
          font-size: 1.5rem;
          cursor: pointer;
        }
        textarea {
          flex: 1;
          padding: 1rem;
          font-family: monospace;
          font-size: 14px;
          border: none;
          resize: none;
          outline: none;
        }
        footer {
          padding: 1rem;
          border-top: 1px solid #eee;
          text-align: right;
        }
        button {
          padding: 0.5rem 1rem;
          background: #2196f3;
          color: white;
          border: none;
          border-radius: 4px;
          cursor: pointer;
        }
        button:disabled {
          background: #ccc;
        }
        .message {
          padding: 0.5rem 1rem;
          font-size: 0.9rem;
        }
        .message.error { background: #ffebee; color: #c62828; }
        .message.success { background: #e8f5e9; color: #2e7d32; }
      `}</style>
        </div>
    );
}
