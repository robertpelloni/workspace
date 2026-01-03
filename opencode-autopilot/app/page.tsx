"use client";

import { useState } from 'react';

export default function Home() {
  const [input, setInput] = useState('');
  const [sessionId, setSessionId] = useState<string | null>(null);
  const [messages, setMessages] = useState<any[]>([]);
  const [loading, setLoading] = useState(false);

  const startSession = async () => {
    setLoading(true);
    try {
      const res = await fetch('/api/autopilot', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ action: 'start_session' }),
      });
      const data = await res.json();
      if (data.sessionId) {
        setSessionId(data.sessionId);
        setMessages([{ role: 'system', content: `Session started: ${data.sessionId}` }]);
      }
    } catch (err) {
      console.error(err);
    } finally {
      setLoading(false);
    }
  };

  const sendMessage = async () => {
    if (!input.trim() || !sessionId) return;
    
    const userMsg = { role: 'user', content: input };
    setMessages(prev => [...prev, userMsg]);
    setInput('');
    setLoading(true);

    try {
      const res = await fetch('/api/autopilot', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ 
          action: 'chat', 
          sessionId, 
          message: input 
        }),
      });
      const data = await res.json();
      
      const botMsg = { role: 'assistant', content: JSON.stringify(data, null, 2) };
      setMessages(prev => [...prev, botMsg]);
    } catch (err) {
      console.error(err);
      setMessages(prev => [...prev, { role: 'error', content: 'Failed to send message' }]);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="flex flex-col h-screen max-w-3xl mx-auto p-4 font-sans text-black dark:text-white">
      <header className="mb-4 border-b pb-2">
        <h1 className="text-2xl font-bold">OpenCode Autopilot</h1>
        <p className="text-gray-500">Next.js Deployment</p>
      </header>

      <div className="flex-1 overflow-y-auto mb-4 border rounded p-4 bg-gray-50 dark:bg-zinc-900">
        {messages.length === 0 ? (
          <div className="text-center text-gray-400 mt-20">Start a session to begin</div>
        ) : (
          messages.map((msg, idx) => (
            <div key={idx} className={`mb-3 ${msg.role === 'user' ? 'text-right' : 'text-left'}`}>
              <div className={`inline-block p-2 rounded-lg ${
                msg.role === 'user' ? 'bg-blue-600 text-white' : 
                msg.role === 'error' ? 'bg-red-100 text-red-600' : 'bg-white dark:bg-zinc-800 border shadow-sm'
              }`}>
                <div className="text-xs opacity-70 mb-1 capitalize">{msg.role}</div>
                <pre className="whitespace-pre-wrap font-sans text-sm">{msg.content}</pre>
              </div>
            </div>
          ))
        )}
      </div>

      <div className="flex gap-2">
        {!sessionId ? (
          <button 
            onClick={startSession} 
            disabled={loading}
            className="w-full bg-green-600 text-white p-3 rounded hover:bg-green-700 disabled:opacity-50"
          >
            {loading ? 'Starting...' : 'Start New Session'}
          </button>
        ) : (
          <>
            <input 
              value={input}
              onChange={e => setInput(e.target.value)}
              onKeyDown={e => e.key === 'Enter' && sendMessage()}
              placeholder="Type your message..."
              className="flex-1 p-3 border rounded focus:outline-none focus:ring-2 focus:ring-blue-500 bg-white dark:bg-zinc-800"
              disabled={loading}
            />
            <button 
              onClick={sendMessage}
              disabled={loading || !input.trim()}
              className="bg-blue-600 text-white px-6 rounded hover:bg-blue-700 disabled:opacity-50"
            >
              Send
            </button>
          </>
        )}
      </div>
    </div>
  );
}
