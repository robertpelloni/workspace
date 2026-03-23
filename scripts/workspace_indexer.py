import os
import sqlite3
import fnmatch
import time

DB_PATH = 'workspace_index.db'
IGNORED_DIRS = ['.git', 'node_modules', 'build', 'dist', 'target', '__pycache__', '.venv', '.venv_win', '.idea', '.vscode', '.agent', '.borg', 'build_output']
IGNORED_EXTS = ['.png', '.jpg', '.jpeg', '.gif', '.mp3', '.wav', '.mp4', '.mkv', '.zip', '.tar', '.gz', '.7z', '.exe', '.dll', '.so', '.dylib', '.bin', '.dat', '.db', '.sqlite']

def is_ignored(path):
    for d in IGNORED_DIRS:
        if f"/{d}/" in path or f"\\{d}\\" in path or path.endswith(f"/{d}") or path.endswith(f"\\{d}"):
            return True
    return False

def init_db():
    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()
    cursor.execute('''
        CREATE VIRTUAL TABLE IF NOT EXISTS files_fts USING fts5(
            path,
            content,
            tokenize='porter'
        )
    ''')
    cursor.execute('CREATE TABLE IF NOT EXISTS files_metadata (path TEXT PRIMARY KEY, mtime REAL)')
    conn.commit()
    return conn

def index_workspace():
    print("Starting Workspace Indexing...")
    start_time = time.time()
    conn = init_db()
    cursor = conn.cursor()
    
    # Get all currently indexed files to detect deleted ones
    cursor.execute("SELECT path, mtime FROM files_metadata")
    indexed_files = {row[0]: row[1] for row in cursor.fetchall()}
    current_files = set()
    
    processed = 0
    for root, _, files in os.walk('.'):
        if is_ignored(root):
            continue
            
        for file in files:
            ext = os.path.splitext(file)[1].lower()
            if ext in IGNORED_EXTS:
                continue
                
            full_path = os.path.join(root, file)
            # Normalize path
            full_path = full_path.replace('\\', '/')
            if full_path.startswith('./'):
                full_path = full_path[2:]
                
            if is_ignored('/' + full_path):
                continue
                
            current_files.add(full_path)
            
            try:
                mtime = os.path.getmtime(full_path)
                fsize = os.path.getsize(full_path)
            except OSError:
                continue
                
            # Skip files larger than 2MB
            if fsize > 2 * 1024 * 1024:
                continue
                
            # Skip if already indexed and unmodified
            if full_path in indexed_files and indexed_files[full_path] >= mtime:
                continue
                
            try:
                with open(full_path, 'r', encoding='utf-8') as f:
                    content = f.read()
            except UnicodeDecodeError:
                # Fallback to ignore errors if it's mostly text but has some binary garbage
                try:
                    with open(full_path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                except Exception:
                    continue
            except Exception:
                continue
                
            # Update index
            cursor.execute("DELETE FROM files_fts WHERE path = ?", (full_path,))
            cursor.execute("INSERT INTO files_fts (path, content) VALUES (?, ?)", (full_path, content))
            cursor.execute("INSERT OR REPLACE INTO files_metadata (path, mtime) VALUES (?, ?)", (full_path, mtime))
            processed += 1
            if processed % 1000 == 0:
                print(f"Indexed {processed} new/modified files...")
                conn.commit()
                
    # Remove deleted files from index
    deleted_files = set(indexed_files.keys()) - current_files
    for df in deleted_files:
        cursor.execute("DELETE FROM files_fts WHERE path = ?", (df,))
        cursor.execute("DELETE FROM files_metadata WHERE path = ?", (df,))
        
    conn.commit()
    conn.close()
    
    elapsed = time.time() - start_time
    print(f"Indexing complete in {elapsed:.2f} seconds. Processed {processed} files. Total indexed files: {len(current_files)}")

if __name__ == "__main__":
    index_workspace()
