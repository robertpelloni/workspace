import os

def audit_instructions():
    root = os.getcwd()
    master_file = os.path.join(root, "docs", "UNIVERSAL_LLM_INSTRUCTIONS.md")
    if not os.path.exists(master_file):
        print(f"Master file not found: {master_file}")
        return

    submodules = []
    if os.path.exists(".gitmodules"):
        import configparser
        config = configparser.ConfigParser()
        config.read(".gitmodules")
        for section in config.sections():
            path = config.get(section, "path", fallback=None)
            if path:
                submodules.append(path)

    gaps = []
    for sub in submodules:
        sub_path = os.path.join(root, sub)
        if not os.path.isdir(sub_path):
            continue
            
        target = os.path.join(sub_path, "docs", "UNIVERSAL_LLM_INSTRUCTIONS.md")
        if not os.path.exists(target):
            # Check if it's in the sub-root instead of docs/
            target_root = os.path.join(sub_path, "UNIVERSAL_LLM_INSTRUCTIONS.md")
            if not os.path.exists(target_root):
                gaps.append(sub)

    if not gaps:
        print("Audit passed: Universal Instructions are mirrored in all active submodules.")
    else:
        print(f"Audit failed: {len(gaps)} submodules are missing the instructions mirror.")
        for gap in gaps:
            print(f" - {gap}")

if __name__ == "__main__":
    audit_instructions()
