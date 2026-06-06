from fastmcp import FastMCP
import sqlite3
import os

# Create an MCP server
mcp = FastMCP("WorkspaceSearch")

DB_PATH = 'workspace_index.db'

@mcp.tool()
def search_workspace(query: str, limit: int = 20) -> str:
    """
    Search the entire Omni-Workspace for a pattern using SQLite FTS5.
    Returns ranked results with snippets of matching code.
    """
    if not os.path.exists(DB_PATH):
        return "Error: Index database not found. Please run scripts/workspace_indexer.py first."

    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    
    try:
        # Wrap query in quotes to handle special characters for FTS5
        # If user provided complex query, try to use it as is first
        formatted_query = f'"{query}"' if " " in query and not query.startswith('"') else query
        
        cursor.execute('''
            SELECT path, snippet(files_fts, -1, '[[', ']]', '...', 10) 
            FROM files_fts 
            WHERE files_fts MATCH ? 
            ORDER BY rank 
            LIMIT ?
        ''', (formatted_query, limit))
        
        results = cursor.fetchall()
        if not results:
            return f"No results found for query: {query}"
            
        output = [f"Found {len(results)} matches for '{query}':\n"]
        for path, snippet in results:
            output.append(f"--- {path} ---")
            output.append(f"{snippet}\n")
            
        return "\n".join(output)
            
    except sqlite3.OperationalError as e:
        return f"Search error: {e}. Try a simpler query or wrap in double quotes."
    finally:
        conn.close()

@mcp.tool()
def get_index_status() -> str:
    """Get the current status of the workspace search index."""
    if not os.path.exists(DB_PATH):
        return "Status: Index database missing."
        
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    cursor.execute("SELECT COUNT(*) FROM files_metadata")
    count = cursor.fetchone()[0]
    
    mtime = os.path.getmtime(DB_PATH)
    import datetime
    last_updated = datetime.datetime.fromtimestamp(mtime).strftime('%Y-%m-%d %H:%M:%S')
    
    conn.close()
    return f"Status: Index active.\nFiles Indexed: {count}\nLast Updated: {last_updated}"

if __name__ == "__main__":
    mcp.run()
