import subprocess
import os

def run_command(cmd, cwd=None):
    try:
        process = subprocess.Popen(cmd, shell=True, cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        return process.returncode, stdout.decode().strip(), stderr.decode().strip()
    except Exception as e:
        return -1, "", str(e)

def main():
    print("Fetching root...")
    code, out, err = run_command("git fetch --all --tags")
    print(f"Root fetch code: {code}")

    submodules_raw_code, submodules_raw, _ = run_command("git submodule foreach --recursive \"pwd\"")
    if submodules_raw_code != 0:
        print("Failed to list submodules")
        return

    for line in submodules_raw.splitlines():
        if line.startswith("Entering '"):
            sub_path = line[10:-1]
            print(f"\nFetching {sub_path}...")
            code, out, err = run_command("git fetch --all --tags", cwd=sub_path)
            if code != 0:
                print(f"  FAILED: {err}")
            else:
                print(f"  SUCCESS")

if __name__ == "__main__":
    main()
