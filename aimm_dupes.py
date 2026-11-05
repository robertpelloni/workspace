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


def q(sql):
    return subprocess.run(
        ["mysql", "-u" + U, "-p" + pw, DB, "-N", "-B", "-e", sql],
        capture_output=True,
        text=True,
    ).stdout


rows = [
    l.split("\t")
    for l in q(
        "SELECT ID, post_title, post_name, post_date, CHAR_LENGTH(post_content) "
        "FROM wp_posts WHERE post_type='post' AND post_status='publish' ORDER BY post_name;"
    )
    .strip()
    .split("\n")
    if l.strip()
]

base = collections.defaultdict(list)
for r in rows:
    if len(r) < 5:
        continue
    b = re.sub(r"-\d+$", "", r[2])
    base[b].append(r)

groups = {k: v for k, v in base.items() if len(v) > 1}
print(f"total published posts : {len(rows)}")
print(f"duplicate groups      : {len(groups)}")
print(f"excess posts          : {sum(len(v) - 1 for v in groups.values())}")
print()

# Which group members look like the best keeper? Longest content, earliest date.
print("=== duplicate groups (keeping the LONGEST / earliest) ===")
reclaim = 0
for k, v in sorted(groups.items(), key=lambda x: -len(x[1]))[:14]:
    v2 = sorted(v, key=lambda x: (-int(x[4]), x[3]))
    keep = v2[0]
    drop = v2[1:]
    reclaim += len(drop)
    print(f"\n  {len(v)}x  {k[:64]}")
    print(
        f"      KEEP id={keep[0]} {keep[3][:10]} {int(keep[4]):>7} chars  {keep[1][:50]}"
    )
    for d in drop:
        print(f"      drop id={d[0]} {d[3][:10]} {int(d[4]):>7} chars  {d[1][:50]}")

print()
print(f"=== total droppable in top 14 groups: {reclaim} ===")
print(
    f"=== all groups would drop: {sum(len(v) - 1 for v in groups.values())} posts ==="
)
