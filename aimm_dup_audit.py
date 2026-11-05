import re
import subprocess
import collections

R = "/var/www/aimoneymachine"
pw = subprocess.run(
    ["bash", "-c", f'grep DB_PASSWORD {R}/wp-config.php | cut -d"\'" -f4'],
    capture_output=True,
    text=True,
).stdout.strip()

q = """
SELECT ID, post_title, post_name, post_status, post_date,
       CHAR_LENGTH(post_content)
FROM wp_posts
WHERE post_type='post' AND post_status IN ('publish','draft')
ORDER BY post_date;
"""
r = subprocess.run(
    [
        "mysql",
        "-uwp_aimoneymachine",
        f"-p{pw}",
        "aimoneymachine_wp",
        "-N",
        "-B",
        "-e",
        q,
    ],
    capture_output=True,
    text=True,
)
rows = [l.split("\t") for l in r.stdout.strip().split("\n") if l.strip()]
print(f"total posts (publish+draft): {len(rows)}")

# content hashes to find true duplicates
q2 = "SELECT ID, MD5(post_content) FROM wp_posts WHERE post_type='post' AND post_status IN ('publish','draft');"
r2 = subprocess.run(
    [
        "mysql",
        "-uwp_aimoneymachine",
        f"-p{pw}",
        "aimoneymachine_wp",
        "-N",
        "-B",
        "-e",
        q2,
    ],
    capture_output=True,
    text=True,
)
h = {}
for l in r2.stdout.strip().split("\n"):
    if not l.strip():
        continue
    pid, md5 = l.split("\t")
    h.setdefault(md5, []).append(pid)

dup_groups = {k: v for k, v in h.items() if len(v) > 1}
n_dup_posts = sum(len(v) - 1 for v in dup_groups.values())
print(f"identical-content duplicate groups: {len(dup_groups)}")
print(f"redundant posts that could be dropped: {n_dup_posts}")
print()

# base-title duplicates (the "-2"/"-3" suffix pattern)
base = collections.Counter()
for row in rows:
    if len(row) < 3:
        continue
    slug = row[2]
    b = re.sub(r"-\d+$", "", slug)
    base[b] += 1
suffix_dupes = {k: v for k, v in base.items() if v > 1}
print(f"slugs sharing a base (the -2/-3 pattern): {len(suffix_dupes)}")
print(f"extra posts from that pattern: {sum(v - 1 for v in suffix_dupes.values())}")
print()
print("top repeated bases:")
for k, v in sorted(suffix_dupes.items(), key=lambda x: -x[1])[:12]:
    print(f"  {v}x  {k[:66]}")
print()
lens = [int(x[5]) for x in rows if len(x) > 5 and x[5].isdigit()]
if lens:
    lens.sort()
    print(
        f"content length: min={lens[0]}  median={lens[len(lens) // 2]}  max={lens[-1]}"
    )
    short = sum(1 for n in lens if n < 1500)
    print(f"posts under 1500 chars (thin): {short} ({short * 100 // len(lens)}%)")
