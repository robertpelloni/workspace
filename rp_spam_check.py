import subprocess

R = "/srv/www/robertpelloni.com"
pw = subprocess.run(
    ["bash", "-c", f'grep DB_PASSWORD {R}/wp-config.php | cut -d"\'" -f4'],
    capture_output=True,
    text=True,
).stdout.strip()
DB, U = "rp_wp", "robertpelloni"


def q(sql):
    return subprocess.run(
        ["mysql", "-u" + U, "-p" + pw, DB, "-N", "-B", "-e", sql],
        capture_output=True,
        text=True,
    ).stdout


print("=== authors of published posts ===")
print(
    q(
        "SELECT u.user_login, COUNT(*) FROM wp_posts p LEFT JOIN wp_users u ON p.post_author=u.ID "
        "WHERE p.post_type='post' AND p.post_status='publish' GROUP BY u.user_login;"
    )
)

print("=== posts matching the 'Play ... MP3 Download' spam pattern ===")
rows = q(
    "SELECT ID,post_author,post_date,LEFT(post_title,72),CHAR_LENGTH(post_content) "
    "FROM wp_posts WHERE post_type='post' AND post_status='publish' "
    "AND (post_title LIKE 'Play %Download%' OR post_title LIKE '%MP3 Download%' "
    "     OR post_title REGEXP '^Play[A-Z]') ORDER BY post_date;"
)
print(rows or "(none)")

print("=== how many thin posts (< 1000 chars)? ===")
print(
    q(
        "SELECT COUNT(*) FROM wp_posts WHERE post_type='post' AND post_status='publish' AND CHAR_LENGTH(post_content) < 1000;"
    )
)

print("=== lengths distribution ===")
print(
    q(
        "SELECT CASE WHEN CHAR_LENGTH(post_content)<300 THEN 'a <300' "
        "WHEN CHAR_LENGTH(post_content)<1000 THEN 'b 300-1000' "
        "WHEN CHAR_LENGTH(post_content)<5000 THEN 'c 1k-5k' "
        "WHEN CHAR_LENGTH(post_content)<50000 THEN 'd 5k-50k' "
        "ELSE 'e >50k' END AS bucket, COUNT(*) "
        "FROM wp_posts WHERE post_type='post' AND post_status='publish' GROUP BY bucket ORDER BY bucket;"
    )
)

print("=== sample of the shortest posts (full title + body head) ===")
for line in (
    q(
        "SELECT ID, LEFT(post_title,60), CHAR_LENGTH(post_content) FROM wp_posts "
        "WHERE post_type='post' AND post_status='publish' ORDER BY CHAR_LENGTH(post_content) ASC LIMIT 12;"
    )
    .strip()
    .split("\n")
):
    if line.strip():
        print("  ", line)

print()
print("=== body of post 41799 (104 chars) ===")
print(q("SELECT post_content FROM wp_posts WHERE ID=41799;"))
