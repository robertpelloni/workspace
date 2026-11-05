"""Build duplicate-slug -> keeper-slug redirect map for aimoneymachine.site.

Group posts by base slug (slug with any trailing -N removed). Within each group
keep the post with the most content (ties broken by earliest date) and redirect
the rest to it. This consolidates keyword-cannibalising near-duplicates.
"""

import json
import re
import subprocess
import collections

R = "/var/www/aimoneymachine"
pw = subprocess.run(
    ["bash", "-c", f'grep DB_PASSWORD {R}/wp-config.php | cut -d"\'" -f4'],
    capture_output=True,
    text=True,
).stdout.strip()
DB, U = "aimoneymachine_wp", "wp_aimoneymachine"

out = subprocess.run(
    [
        "mysql",
        "-u" + U,
        "-p" + pw,
        DB,
        "-N",
        "-B",
        "-e",
        "SELECT ID, post_name, post_date, CHAR_LENGTH(post_content) "
        "FROM wp_posts WHERE post_type='post' AND post_status='publish';",
    ],
    capture_output=True,
    text=True,
).stdout

rows = []
for l in out.strip().split("\n"):
    p = l.split("\t")
    if len(p) == 4 and p[3].isdigit():
        rows.append({"id": int(p[0]), "slug": p[1], "date": p[2], "len": int(p[3])})

groups = collections.defaultdict(list)
for r in rows:
    groups[re.sub(r"-\d+$", "", r["slug"])].append(r)

redirects = {}
kept, dropped = [], []
for base, members in groups.items():
    if len(members) == 1:
        continue
    # keeper: most content, then earliest date, then lowest id (stable)
    members.sort(key=lambda m: (-m["len"], m["date"], m["id"]))
    keep = members[0]
    kept.append(keep)
    for d in members[1:]:
        redirects[d["slug"]] = keep["slug"]
        dropped.append(d)

print(f"published posts        : {len(rows)}")
print(f"duplicate groups       : {sum(1 for m in groups.values() if len(m) > 1)}")
print(f"posts kept as canonical: {len(kept)}")
print(f"posts to 301-redirect  : {len(dropped)}")
print()

# write the map for the mu-plugin
path = "/root/aimm-incident-20260914/duplicate-redirects.json"
with open(path, "w", encoding="utf-8") as fh:
    json.dump(redirects, fh, indent=0, sort_keys=True)
print(f"wrote {len(redirects)} entries to {path}")
print()
print("sample:")
for k in sorted(redirects)[:8]:
    print(f"  /{k}\n     -> /{redirects[k]}")
