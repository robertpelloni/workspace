import json
import os
import re
import subprocess
import csv
from datetime import datetime


def run_command(command):
    try:
        result = subprocess.run(command, capture_output=True, text=True, shell=True)
        return result.stdout.strip()
    except Exception:
        return "Unknown"


def get_csv_metadata():
    csv_path = "aios/docs/SUBMODULE_INDEX.csv"
    metadata = {}

    if not os.path.exists(csv_path):
        print(f"Warning: {csv_path} not found. Skipping metadata enrichment.")
        return metadata

    try:
        with open(csv_path, "r", encoding="utf-8") as f:
            reader = csv.DictReader(f)
            for row in reader:
                if "path" in row and row["path"]:
                    metadata[row["path"]] = row
    except Exception as e:
        print(f"Error reading CSV: {e}")

    return metadata


def get_submodules():
    submodules = []
    if os.path.exists(".gitmodules"):
        with open(".gitmodules", "r") as f:
            content = f.read()

        matches = re.finditer(
            r'\[submodule "(.*?)"\]\s*path = (.*?)\s*url = (.*?)\s',
            content,
            re.MULTILINE | re.DOTALL,
        )
        for match in matches:
            name = match.group(1).strip()
            path = match.group(2).strip()
            url = match.group(3).strip()
            submodules.append({"name": name, "path": path, "url": url})
    return submodules


def generate_json(submodules):
    print("Generating submodules.json...")

    csv_data = get_csv_metadata()

    data = {"lastUpdated": datetime.now().isoformat(), "submodules": []}

    for sub in submodules:
        path = sub["path"]

        entry = {
            "name": sub["name"],
            "path": path,
            "url": sub["url"],
            "status": "missing",
            "commit": "unknown",
            "category": "Other",
            "role": "Unknown",
            "description": "",
            "rationale": "",
            "integrationStrategy": "",
            "isInstalled": False,
        }

        if path in csv_data:
            meta = csv_data[path]
            entry["category"] = meta.get("category", "Other")
            entry["role"] = meta.get("role", "Unknown")
            entry["description"] = meta.get("description", "")
            entry["rationale"] = meta.get("rationale", "")
            entry["integrationStrategy"] = meta.get("integrationStrategy", "")

        if os.path.exists(path):
            entry["isInstalled"] = True
            commit_hash = run_command(f'git -C "{path}" rev-parse --short HEAD')
            if commit_hash:
                entry["commit"] = commit_hash

            status_out = run_command(f'git -C "{path}" status --porcelain')
            entry["status"] = "clean" if not status_out else "modified"
        else:
            entry["isInstalled"] = False

        data["submodules"].append(entry)

    output_path = "aios/packages/ui/public/submodules.json"
    os.makedirs(os.path.dirname(output_path), exist_ok=True)

    with open(output_path, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=2)
    print(f"{output_path} created with {len(data['submodules'])} entries.")


if __name__ == "__main__":
    submodules = get_submodules()
    generate_json(submodules)
