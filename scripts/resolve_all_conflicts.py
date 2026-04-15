import os
import re

def resolve_conflicts(directory):
    print(f"Resolving conflicts in: {directory}")
    for root, dirs, files in os.walk(directory):
        # Skip .git and node_modules
        if '.git' in dirs:
            dirs.remove('.git')
        if 'node_modules' in dirs:
            dirs.remove('node_modules')
            
        for file in files:
            if file.endswith(('.ts', '.tsx', '.js', '.jsx', '.json', '.md', '.py', '.c', '.cpp', '.h', '.hpp', '.txt', '.yml', '.yaml', '.sh', '.bat')):
                filepath = os.path.join(root, file)
                try:
                    with open(filepath, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    
                    if "<<<<<<< HEAD" in content:
                        print(f"  Conflict found in: {filepath}")
                        # Pattern to match git conflict markers and keep HEAD version
                        # This is a broad "ours" strategy for file content
                        new_content = re.sub(r'<<<<<<< HEAD[\s\S]*?=======([\s\S]*?)>>>>>>>.*', r'', content) # This is risky, let's be more precise
                        
                        # Better approach: split by lines and filter
                        lines = content.splitlines()
                        new_lines = []
                        skip = False
                        found = False
                        for line in lines:
                            if line.startswith("<<<<<<< HEAD"):
                                skip = False # Keep HEAD
                                found = True
                                continue
                            if line.startswith("======="):
                                skip = True # Skip the other side
                                continue
                            if line.startswith(">>>>>>>"):
                                skip = False
                                continue
                            if not skip:
                                new_lines.append(line)
                        
                        if found:
                            with open(filepath, 'w', encoding='utf-8') as f:
                                f.write("\n".join(new_lines) + ("\n" if content.endswith("\n") else ""))
                            print(f"    Fixed.")
                except Exception as e:
                    print(f"    Error processing {filepath}: {e}")

if __name__ == "__main__":
    # Target specific directories first to be safe
    workspace_root = os.getcwd()
    resolve_conflicts(workspace_root)
