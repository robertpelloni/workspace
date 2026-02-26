import os
import subprocess
import sys

log_file = open('build_all.log', 'w', encoding='utf-8')

def log(msg):
    print(msg, flush=True)
    log_file.write(msg + '\n')
    log_file.flush()

def build_dir(d):
    log(f"--> Checking {d}...")
    
    # Node.js
    if os.path.isfile(os.path.join(d, 'package.json')):
        log(f"    Building Node project in {d}...")
        subprocess.run('npm install --no-fund --no-audit --loglevel=error', cwd=d, shell=True, stdout=log_file, stderr=log_file)
        subprocess.run('npm run build', cwd=d, shell=True, stdout=log_file, stderr=log_file)
        
    # Rust
    if os.path.isfile(os.path.join(d, 'Cargo.toml')):
        log(f"    Building Rust project in {d}...")
        subprocess.run('cargo build --release', cwd=d, shell=True, stdout=log_file, stderr=log_file)
        
    # Java (Maven)
    if os.path.isfile(os.path.join(d, 'pom.xml')):
        log(f"    Building Maven project in {d}...")
        subprocess.run('mvn package -DskipTests -q', cwd=d, shell=True, stdout=log_file, stderr=log_file)
        
    # Java (Gradle)
    if os.path.isfile(os.path.join(d, 'build.gradle')):
        log(f"    Building Gradle project in {d}...")
        gradlew = 'gradlew' if os.name == 'nt' else './gradlew'
        if os.path.isfile(os.path.join(d, gradlew.replace('./', ''))):
            subprocess.run(f'{gradlew} build -x test -q', cwd=d, shell=True, stdout=log_file, stderr=log_file)
        
    # C/C++ (CMake)
    if os.path.isfile(os.path.join(d, 'CMakeLists.txt')):
        log(f"    Building CMake project in {d}...")
        subprocess.run('cmake -B build -DCMAKE_BUILD_TYPE=Release', cwd=d, shell=True, stdout=log_file, stderr=log_file)
        subprocess.run('cmake --build build --config Release', cwd=d, shell=True, stdout=log_file, stderr=log_file)
        
    # Go
    if os.path.isfile(os.path.join(d, 'go.mod')):
        log(f"    Building Go project in {d}...")
        subprocess.run('go build', cwd=d, shell=True, stdout=log_file, stderr=log_file)
        
    # Python
    if os.path.isfile(os.path.join(d, 'pyproject.toml')):
        log(f"    Building Python project in {d}...")
        subprocess.run('python -m build', cwd=d, shell=True, stdout=log_file, stderr=log_file)
        # Also try pyinstaller if it's an app
        if os.path.isfile(os.path.join(d, 'main.py')):
            log(f"    Building PyInstaller executable in {d}...")
            subprocess.run('pyinstaller --onefile main.py', cwd=d, shell=True, stdout=log_file, stderr=log_file)

def explore(root_dir, depth):
    if depth < 0: return
    try:
        items = os.listdir(root_dir)
    except Exception as e:
        log(f"Error accessing {root_dir}: {e}")
        return
        
    for item in items:
        if item.startswith('.') or item in ['node_modules', 'build', 'dist', 'target', 'scripts', 'docs', 'logs', 'venv', 'env', '__pycache__', 'out']:
            continue
        full_path = os.path.join(root_dir, item)
        if os.path.isdir(full_path):
            build_dir(full_path)
            explore(full_path, depth - 1)

if __name__ == "__main__":
    log("Starting global build script...")
    explore('.', 2)
    log("Finished global build script.")
    log_file.close()
