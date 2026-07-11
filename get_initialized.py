import subprocess
import os

def main():
    out = subprocess.run("git submodule status", shell=True, capture_output=True, text=True).stdout
    initialized = []
    for line in out.splitlines():
        if not line.startswith('-'):
            parts = line.strip().split()
            if len(parts) >= 2:
                initialized.append(parts[1])
    
    with open("initialized_submodules.txt", "w") as f:
        f.write("\n".join(initialized))

if __name__ == "__main__":
    main()
