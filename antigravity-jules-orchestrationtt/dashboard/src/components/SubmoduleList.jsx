
import React, { useState, useEffect } from 'react';


export function SubmoduleList({ onSelect }) {
    const [submodules, setSubmodules] = useState([]);
    const [loading, setLoading] = useState(true);
    const [error, setError] = useState(null);

    useEffect(() => {
        fetch('/api/submodules')
            .then(res => res.json())
            .then(data => {
                setSubmodules(data);
                setLoading(false);
            })
            .catch(err => {
                setError(err.message);
                setLoading(false);
            });
    }, []);

    if (loading) return <div>Loading submodules...</div>;
    if (error) return <div className="error">Error: {error}</div>;

    return (
        <div className="submodule-list">
            <h2>Submodules ({submodules.length})</h2>
            <div className="grid">
                {submodules.map(module => (
                    <div key={module.name} className="card" onClick={() => onSelect(module)}>
                        <div className="card-header">
                            <h3>{module.name}</h3>
                            <span className={`tag type-${module.type}`}>{module.type}</span>
                        </div>

                        <div className="git-status-row">
                            {module.gitStatus && !module.gitStatus.error ? (
                                <>
                                    <span className="badge branch" title="Current Branch">
                                        Branch: {module.gitStatus.branch || 'HEAD'}
                                    </span>
                                    <span className="badge commit" title={`Commit: ${module.gitStatus.commit}`}>
                                        #{module.gitStatus.commit}
                                    </span>
                                    <span
                                        className={`badge status ${module.gitStatus.isDirty ? 'dirty' : 'clean'}`}
                                        title={module.gitStatus.isDirty ? 'Uncommitted changes' : 'Clean working directory'}
                                    >
                                        {module.gitStatus.isDirty ? '⚠️ Dirty' : '✅ Clean'}
                                    </span>
                                </>
                            ) : (
                                <span className="badge no-git" title="Not a git repository or git info unavailable">No Git</span>
                            )}
                        </div>

                        <div className="details">
                            <span>📄 {module.configFiles.length} configs</span>
                            <span>⚡ {Object.keys(module.scripts).length} scripts</span>
                        </div>
                    </div>
                ))}
            </div>
            <style>{`
        .submodule-list { padding: 1rem; }
        .grid { display: grid; grid-template-columns: repeat(auto-fill, minmax(300px, 1fr)); gap: 1rem; }
        .card { 
            border: 1px solid #ddd; 
            border-radius: 8px; 
            padding: 1rem; 
            cursor: pointer; 
            transition: transform 0.2s, box-shadow 0.2s;
            background: #fff;
        }
        .card:hover { transform: translateY(-2px); box-shadow: 0 4px 8px rgba(0,0,0,0.1); }
        .card-header { display: flex; justify-content: space-between; align-items: start; margin-bottom: 0.5rem; }
        .card h3 { margin: 0; font-size: 1.1rem; }
        .tag { font-size: 0.8rem; padding: 2px 6px; border-radius: 4px; background: #eee; }
        .tag.type-node { background: #e8f5e9; color: #2e7d32; }
        .tag.type-rust { background: #fff3e0; color: #ef6c00; }
        .tag.type-python { background: #e3f2fd; color: #1565c0; }
        
        .git-status-row { display: flex; gap: 0.5rem; flex-wrap: wrap; margin-bottom: 0.8rem; font-size: 0.8rem; }
        .badge { padding: 2px 6px; border-radius: 4px; border: 1px solid #eee; }
        .badge.branch { background: #e1f5fe; color: #0277bd; border-color: #b3e5fc; }
        .badge.commit { font-family: monospace; background: #f5f5f5; color: #616161; }
        .badge.status.clean { background: #e8f5e9; color: #2e7d32; border-color: #c8e6c9; }
        .badge.status.dirty { background: #fffde7; color: #f9a825; border-color: #fff9c4; }
        .badge.no-git { background: #fafafa; color: #9e9e9e; font-style: italic; }

        .details { display: flex; gap: 1rem; font-size: 0.9rem; color: #666; }
      `}</style>
        </div>
    );
}
