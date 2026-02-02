import os
import subprocess

def fix_git_ref(root_dir, old_name, new_name):
    print(f"Scanning {root_dir} to replace {old_name} with {new_name} in .git files...")
    count = 0
    for dirpath, dirnames, filenames in os.walk(root_dir):
        if ".git" in filenames:
            git_file = os.path.join(dirpath, ".git")
            try:
                # unhide/un-readonly
                subprocess.run(f"attrib -r -h {git_file}", shell=True, check=True)
                
                with open(git_file, "r") as f:
                    content = f.read()
                
                if old_name in content:
                    print(f"Fixing {git_file}")
                    new_content = content.replace(old_name, new_name)
                    with open(git_file, "w") as f:
                        f.write(new_content)
                    count += 1
            except Exception as e:
                print(f"Error processing {git_file}: {e}")
    print(f"Fixed {count} files in {root_dir}")

def main():
    cwd = os.getcwd()
    # fix bobsgameonlinejava
    fix_git_ref(os.path.join(cwd, "bobsgameonlinejava"), "BobsGameOnline", "bobsgameonlinejava")
    # fix bobeditpro
    fix_git_ref(os.path.join(cwd, "bobeditpro"), "audacity", "bobeditpro")
    # fix bobtrader
    fix_git_ref(os.path.join(cwd, "bobtrader"), "PowerTrader_AI", "bobtrader")

if __name__ == "__main__":
    main()
