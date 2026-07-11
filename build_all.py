import os
import subprocess
import sys
import json

log_file = open('build_all.log', 'a', encoding='utf-8')

def log(msg):
    print(msg, flush=True)
    log_file.write(msg + '\n')
    log_file.flush()

def run_cmd(cmd, cwd, timeout=600):
    log(f"      Executing: {cmd} in {cwd}")
    try:
        result = subprocess.run(cmd, cwd=cwd, shell=True, stdout=log_file, stderr=log_file, text=True, timeout=timeout)
        return result.returncode == 0
    except subprocess.TimeoutExpired:
        log(f"      TIMEOUT: {cmd} in {cwd}")
        return False
    except Exception as e:
        log(f"      ERROR: {e}")
        return False

def build_dir(d):
    norm_d = os.path.normpath(d)
    success_marker = os.path.join(d, '.build_success')
    if os.path.isfile(success_marker):
        log(f"--> Skipping {norm_d} (already built).")
        return

    log(f"--> Building {norm_d}...")
    
    # 1. Custom Build Scripts (High priority)
    for build_script in ['build.bat', 'build.sh', 'ci_build.bat', 'ci_build.sh']:
        if os.path.isfile(os.path.join(d, build_script)):
            log(f"    Found custom build script: {build_script}")
            run_cmd(build_script if os.name == 'nt' else f'./{build_script}', d)

    # 2. Node.js
    if os.path.isfile(os.path.join(d, 'package.json')):
        log(f"    Building Node project...")
        if run_cmd('npm install --no-fund --no-audit --loglevel=error', d):
            with open(os.path.join(d, 'package.json'), 'r') as f:
                try:
                    pkg = json.load(f)
                    scripts = pkg.get('scripts', {})
                    for s in ['build', 'compile', 'package', 'bundle']:
                        if s in scripts:
                            log(f"    Running npm run {s}...")
                            run_cmd(f'npm run {s}', d)
                except:
                    # Fallback if JSON parsing fails
                    run_cmd('npm run build', d)
                    run_cmd('npm run compile', d)
        
    # 3. Rust
    if os.path.isfile(os.path.join(d, 'Cargo.toml')):
        log(f"    Building Rust project...")
        run_cmd('cargo build --release', d)
        
    # 4. Java (Maven)
    if os.path.isfile(os.path.join(d, 'pom.xml')):
        log(f"    Building Maven project...")
        run_cmd('mvn package -DskipTests -q', d)
        
    # 5. Java (Gradle)
    if os.path.isfile(os.path.join(d, 'build.gradle')):
        log(f"    Building Gradle project...")
        gradlew = 'gradlew.bat' if os.name == 'nt' else './gradlew'
        if os.path.isfile(os.path.join(d, gradlew if os.name != 'nt' else 'gradlew.bat')):
            run_cmd(f'{gradlew} build -x test -q', d)
        else:
            run_cmd('gradle build -x test -q', d)
        
    # 6. C/C++ (CMake)
    if os.path.isfile(os.path.join(d, 'CMakeLists.txt')):
        log(f"    Building CMake project...")
        # Avoid nested builds if possible or use a dedicated build dir
        build_path = os.path.join(d, 'build_output')
        if not os.path.exists(build_path): os.makedirs(build_path)
        if run_cmd(f'cmake -B build_output -DCMAKE_BUILD_TYPE=Release', d):
            run_cmd(f'cmake --build build_output --config Release', d)
            
    # 7. Makefile
    if os.path.isfile(os.path.join(d, 'Makefile')) or os.path.isfile(os.path.join(d, 'makefile')):
        log(f"    Building Makefile project...")
        run_cmd('make -j4', d)
        
    # 8. Go
    if os.path.isfile(os.path.join(d, 'go.mod')):
        log(f"    Building Go project...")
        run_cmd('go build ./...', d)
        
    # 9. Python
    if os.path.isfile(os.path.join(d, 'pyproject.toml')) or os.path.isfile(os.path.join(d, 'setup.py')):
        log(f"    Building Python project...")
        run_cmd('python -m build', d)
        # Also try pyinstaller if it's an app
        for main_file in ['main.py', 'app.py', 'cli.py']:
            if os.path.isfile(os.path.join(d, main_file)):
                log(f"    Building PyInstaller executable from {main_file}...")
                run_cmd(f'pyinstaller --onefile {main_file}', d)
    
    # Mark as success
    with open(success_marker, 'w') as f:
        f.write('success')

def main():
    log("Starting comprehensive recursive build script...")
    
    processed = set()
    
    # We'll walk the entire tree, but limit depth to avoid infinite loops with symlinks
    for root, dirs, files in os.walk('.', followlinks=False):
        # Skip common non-source directories
        skip_dirs = ['.git', '.github', 'node_modules', 'build', 'dist', 'target', 'venv', 'env', '__pycache__', 'out', '.agent', '.cursor', '.vscode', 'docs', 'logs']
        dirs[:] = [d for d in dirs if d not in skip_dirs and not d.startswith('.')]
        
        # Check if this directory is a project root
        project_indicators = ['package.json', 'CMakeLists.txt', 'Makefile', 'makefile', 'Cargo.toml', 'go.mod', 'pom.xml', 'build.gradle', 'pyproject.toml', 'setup.py', 'build.bat', 'build.sh']
        if any(os.path.isfile(os.path.join(root, f)) for f in project_indicators):
            build_dir(root)
            # We don't necessarily want to skip subdirectories here because they might be nested submodules
            # but we should be careful about building the same thing twice if a project has multiple indicators
            
    log("Finished comprehensive recursive build script.")
    log_file.close()

if __name__ == "__main__":
    main()
