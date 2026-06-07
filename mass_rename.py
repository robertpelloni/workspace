import os

def rename_in_file(filepath):
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            content = f.read()
        
        new_content = content.replace('hypercodehq/hypercode-go', 'hypernexushq/hypernexus-go')
        new_content = new_content.replace('hypercode', 'hypernexus')
        new_content = new_content.replace('Hypercode', 'HyperNexus')
        
        if new_content != content:
            with open(filepath, 'w', encoding='utf-8') as f:
                f.write(new_content)
            return True
    except Exception as e:
        print(f"Error processing {filepath}: {e}")
    return False

def main():
    root_dir = r'C:\Users\jakeg\workspace\borg'
    for root, dirs, files in os.walk(root_dir):
        if '.git' in dirs:
            dirs.remove('.git')
        if 'node_modules' in dirs:
            dirs.remove('node_modules')
            
        for file in files:
            if file.endswith(('.go', '.mod', '.ts', '.tsx', '.json', '.md', '.bat', '.sh')):
                filepath = os.path.join(root, file)
                if rename_in_file(filepath):
                    print(f"Updated {filepath}")

if __name__ == '__main__':
    main()
