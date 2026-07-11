import os

def document_builds():
    root_dir = '.'
    dirs = [d for d in os.listdir(root_dir) if os.path.isdir(d) and not d.startswith('.')]
    
    for d in dirs:
        success_marker = os.path.join(d, '.build_success')
        result_file = os.path.join(d, 'BUILD_RESULTS.md')
        
        if os.path.exists(success_marker):
            content = "# Build Results\n\nThis project was successfully built by the automated recursive build script. Binaries or build artifacts should be available in the respective output directories (e.g., `dist`, `build`, `target`, etc.).\n\n**Note**: Actions performed were non-destructive. Cross-platform builds (Windows/Linux) will be repeated as necessary."
            with open(result_file, 'w') as f:
                f.write(content)
            print(f"Documented success in {d}")
        else:
            # Check if there's any indication of a build attempt
            # For now, just mark it as pending or no build required if no build script was found
            project_indicators = ['package.json', 'CMakeLists.txt', 'Makefile', 'makefile', 'Cargo.toml', 'go.mod', 'pom.xml', 'build.gradle', 'pyproject.toml', 'setup.py', 'build.bat', 'build.sh']
            has_build = any(os.path.isfile(os.path.join(d, f)) for f in project_indicators)
            if has_build:
                content = "# Build Results\n\nThis project has build configurations but did not complete a successful build during the last automated run. Check `build_all.log` for details."
                with open(result_file, 'w') as f:
                    f.write(content)
                print(f"Documented pending/failure in {d}")

if __name__ == '__main__':
    document_builds()
