import sqlite3
import sys

DB_PATH = 'workspace_index.db'

def search(query):
    if not os.path.exists(DB_PATH):
        print("Index database not found. Run workspace_indexer.py first.")
        return
        
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    
    try:
        # Wrap query in quotes to handle special characters for FTS5
        formatted_query = f'"{query}"'
        cursor.execute('''
            SELECT path, snippet(files_fts, -1, '\x1b[31;1m', '\x1b[0m', '...', 10) 
            FROM files_fts 
            WHERE files_fts MATCH ? 
            ORDER BY rank 
            LIMIT 20
        ''', (formatted_query,))
        
        results = cursor.fetchall()
        if not results:
            print(f"No results found for '{query}'")
            return
            
        print(f"Found {len(results)} results (showing top 20):\n")
        for path, snippet in results:
            print(f"\x1b[32;1m{path}\x1b[0m")
            print(f"{snippet}\n")
            
    except sqlite3.OperationalError as e:
        print(f"Search error: {e}")
        print("Try formatting your query differently (e.g., wrap in quotes for exact phrases)")
    finally:
        conn.close()

if __name__ == "__main__":
    import os
    if len(sys.argv) < 2:
        print("Usage: python search_workspace.py <query>")
        sys.exit(1)
        
    search(sys.argv[1])
