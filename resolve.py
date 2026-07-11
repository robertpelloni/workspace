import os
import re
import subprocess

def apply_renames(text):
    text = text.replace('hypercodehq/hypercode-go', 'hypernexushq/hypernexus-go')
    text = text.replace('hypercode', 'hypernexus')
    text = text.replace('Hypercode', 'HyperNexus')
    return text

def main():
    root_dir = r'C:\Users\jakeg\workspace\borg'
    
    # get all unmerged files
    try:
        output = subprocess.check_output(['git', 'diff', '--name-only', '--diff-filter=U'], text=True)
    except subprocess.CalledProcessError:
        output = ""
    files = output.splitlines()

    # Also search for files with conflict markers that might have been partially staged
    for root, dirs, files_in_dir in os.walk(root_dir):
        if '.git' in dirs:
            dirs.remove('.git')
        if 'node_modules' in dirs:
            dirs.remove('node_modules')
        for file in files_in_dir:
            if file.endswith(('.go', '.mod', '.ts', '.tsx', '.json', '.md')):
                filepath = os.path.join(root, file)
                files.append(filepath)

    files = list(set(files))

    for file in files:
        if not os.path.exists(file):
            continue
            
        try:
            with open(file, 'r', encoding='utf-8', errors='ignore') as f:
                content = f.read()
        except:
            continue

        if '<<<<<' in content:
            print(f"Resolving conflicts in {file}")
            # Robust conflict marker matching (handles 7 or more chars)
            pattern = re.compile(r'<{7,}[^\n]*\n(.*?)\n={7,}\n(.*?)\n>{7,}[^\n]*\n', re.DOTALL)
            
            def replacer(match):
                head_text = match.group(1)
                their_text = match.group(2)
                
                their_renamed = apply_renames(their_text)
                
                # If they are effectively the same after renaming, pick head
                if their_renamed.strip() == head_text.strip():
                    return head_text + '\n'
                
                # Default to picking head for now to ensure monorepo structure, 
                # but this is where we'd merge features if we had more logic.
                return head_text + '\n'
            
            new_content = pattern.sub(replacer, content)
            
            if new_content != content:
                with open(file, 'w', encoding='utf-8') as f:
                    f.write(new_content)
                print(f"Fixed {file}")
                # Try to add if it's in a git repo
                subprocess.run(['git', 'add', file], cwd=os.path.dirname(file))

if __name__ == '__main__':
    main()
