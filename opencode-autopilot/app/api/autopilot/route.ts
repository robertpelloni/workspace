import { NextRequest, NextResponse } from 'next/server';
import { Council } from '@/lib/council';
import { SessionManager } from '@/lib/session-manager';

const sessionManager = new SessionManager();
// In a serverless environment, maintaining state in a global variable 
// (like sessionManager here) is not persistent across cold starts.
// For a production app, you'd need a database (Redis/Postgres) to store session state.
// For this conversion proof-of-concept, we'll try to keep it simple, but be aware of this limitation.

export async function POST(req: NextRequest) {
  try {
    const body = await req.json();
    const { action, sessionId, ...data } = body;

    if (action === 'start_session') {
      const session = sessionManager.createSession(data);
      return NextResponse.json({ sessionId: session.id });
    }

    if (action === 'chat') {
      if (!sessionId) {
        return NextResponse.json({ error: 'Session ID required' }, { status: 400 });
      }
      const session = sessionManager.getSession(sessionId);
      if (!session) {
        return NextResponse.json({ error: 'Session not found' }, { status: 404 });
      }
      
      const response = await session.chat(data.message);
      return NextResponse.json(response);
    }

    return NextResponse.json({ error: 'Invalid action' }, { status: 400 });
  } catch (error: any) {
    console.error('API Error:', error);
    return NextResponse.json({ error: error.message || 'Internal Server Error' }, { status: 500 });
  }
}
