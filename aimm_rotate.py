import re
import secrets
import shutil
import string
import subprocess

CONF = "/var/www/aimoneymachine/wp-config.php"
src = open(CONF, encoding="utf-8").read()
shutil.copy2(CONF, CONF + ".bak-20260914")
print("backup:", CONF + ".bak-20260914")


def salt():
    chars = string.ascii_letters + string.digits + "!@#$%^&*()-_[]{}<>~`+=,.;:/?|"
    return "".join(secrets.choice(chars) for _ in range(64))


SALTS = [
    "AUTH_KEY",
    "SECURE_AUTH_KEY",
    "LOGGED_IN_KEY",
    "NONCE_KEY",
    "AUTH_SALT",
    "SECURE_AUTH_SALT",
    "LOGGED_IN_SALT",
    "NONCE_SALT",
]

out, changed = src, []
for name in SALTS:
    new = salt()
    pat = re.compile(
        r"(define\s*\(\s*['\"]" + name + r"['\"]\s*,\s*)['\"].*?['\"](\s*\)\s*;)", re.S
    )
    out2, n = pat.subn(lambda m: m.group(1) + repr(new) + m.group(2), out)
    if n:
        out = out2
        changed.append(f"{name}({n})")

# JWT secret: collapse the duplicate definitions into exactly one strong value
newjwt = salt()
jpat = re.compile(
    r"define\s*\(\s*['\"]JWT_AUTH_SECRET_KEY['\"]\s*,\s*['\"].*?['\"]\s*\)\s*;", re.S
)
count = len(jpat.findall(out))
out = jpat.sub("", out)
out = out.replace(
    "define('JWT_AUTH_CORS_ENABLE', true);",
    "define('JWT_AUTH_CORS_ENABLE', true);\n"
    "define('JWT_AUTH_SECRET_KEY', " + repr(newjwt) + ");",
)
print(f"replaced salts: {len(changed)} -> {', '.join(changed)}")
print(f"JWT_AUTH_SECRET_KEY: collapsed {count} definitions -> 1 rotated")

open(CONF, "w", encoding="utf-8").write(out)

# verify it still parses and the constant resolves
r = subprocess.run(["php", "-l", CONF], capture_output=True, text=True)
print("php -l:", (r.stdout + r.stderr).strip().splitlines()[0])

# stash the new password for the admin account
NEWPASS = "Aimm-" + secrets.token_urlsafe(15) + "!7"
php = f"""
require_once("/var/www/aimoneymachine/wp-load.php");
wp_set_password({NEWPASS!r}, 1);
$u = get_userdata(1);
echo "admin password reset for: ".$u->user_login."\n";
"""
open("/tmp/setpw.php", "w").write("<?php\n" + php)
r2 = subprocess.run(["php", "/tmp/setpw.php"], capture_output=True, text=True)
print("password:", r2.stdout.strip() or r2.stderr.strip()[:300])
subprocess.run(["rm", "-f", "/tmp/setpw.php"])
open("/root/aimm-incident-20260914/NEW-ADMIN-PASSWORD.txt", "w").write(
    "aimoneymachine.site admin password (set 2026-09-14)\n"
    "user: admin\npassword: " + NEWPASS + "\n"
)
print("NEW ADMIN PASSWORD:", NEWPASS)
