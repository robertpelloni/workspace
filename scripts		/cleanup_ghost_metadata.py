import json
import os

def cleanup_metadata():
    print("[*] Cleaning up ghost metadata from JSON reports...")
    
    files_to_clean = ['workspace_health.json', 'workspace_graph.json']
    
    for filename in files_to_clean:
        if not os.path.exists(filename):
            continue
            
        print(f"  [+] Processing {filename}...")
        with open(filename, 'r', encoding='utf-8') as f:
            data = json.load(f)
            
        original_count = len(data)
        cleaned_data = {}
        
        for key, value in data.items():
            if key == "ROOT":
                cleaned_data[key] = value
                continue
                
            # For graph, the path is inside the object
            path = key
            if filename == 'workspace_graph.json' and isinstance(value, dict) and 'path' in value:
                path = value['path']
                
            if os.path.exists(path):
                cleaned_data[key] = value
            else:
                print(f"    [-] Removing ghost entry: {key} (path {path} not found)")
                
        if len(cleaned_data) < original_count:
            with open(filename, 'w', encoding='utf-8') as f:
                json.dump(cleaned_data, f, indent=4)
            print(f"  [OK] {filename} cleaned. Removed {original_count - len(cleaned_data)} ghost entries.")
        else:
            print(f"  [OK] {filename} is already clean.")

if __name__ == "__main__":
    cleanup_metadata()
