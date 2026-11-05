import re
import secrets
import shutil
import string
import subprocess

CONF = "/var/www/aimoneymachine/wp-config.php"
src = open(CONF, encoding="utf-8").read()
shutil.copy2(CONF, CONF + ".BROKEN-20260914")
print("broken config backed up:", CONF + ".BROKEN-20260914")


def grab(name, default=""):
    m = re.search(
        r"define\s*\(\s*['\"]" + name + r"['\"]\s*,\s*['\"](.*?)['\"]\s*\)", src, re.S
    )
    return m.group(1) if m else default


DB_NAME = grab("DB_NAME", "aimoneymachine_wp")
DB_USER = grab("DB_USER", "wp_aimoneymachine")
DB_PASS = grab("DB_PASSWORD")
DB_HOST = grab("DB_HOST", "localhost")
DB_CHARSET = grab("DB_CHARSET", "utf8mb4")
DB_COLLATE = grab("DB_COLLATE", "")


def salt():
    chars = string.ascii_letters + string.digits + "!@#$%^&*()-_[]{}<>~`+=,.;:/?|"
    return "".join(secrets.choice(chars) for _ in range(64))


K = {
    n: salt()
    for n in [
        "AUTH_KEY",
        "SECURE_AUTH_KEY",
        "LOGGED_IN_KEY",
        "NONCE_KEY",
        "AUTH_SALT",
        "SECURE_AUTH_SALT",
        "LOGGED_IN_SALT",
        "NONCE_SALT",
    ]
}
JWT = salt()

cfg = f"""<?php
/**
 * WordPress configuration for aimoneymachine.site
 *
 * Rewritten 2026-09-14. The previous file had the WP_CACHE / JWT_AUTH_* lines
 * and the authentication-salt block trapped INSIDE an unterminated docblock,
 * so none of them were ever defined. With JWT_AUTH_SECRET_KEY undefined the JWT
 * plugin fell back to its built-in default secret and the auth salts were
 * predictable, which is how 40 rogue administrator accounts were created and
 * the "Kamikaze" defacement was published.
 *
 * @package WordPress
 */

// ** Database settings ** //
define( 'DB_NAME', '{DB_NAME}' );
define( 'DB_USER', '{DB_USER}' );
define( 'DB_PASSWORD', '{DB_PASS}' );
define( 'DB_HOST', '{DB_HOST}' );
define( 'DB_CHARSET', '{DB_CHARSET}' );
define( 'DB_COLLATE', '{DB_COLLATE}' );

/**#@+
 * Authentication unique keys and salts.
 *
 * Generated fresh on 2026-09-14; changing these invalidates all existing
 * cookies and logs every session out.
 */
define( 'AUTH_KEY',         '{K["AUTH_KEY"]}' );
define( 'SECURE_AUTH_KEY',  '{K["SECURE_AUTH_KEY"]}' );
define( 'LOGGED_IN_KEY',    '{K["LOGGED_IN_KEY"]}' );
define( 'NONCE_KEY',        '{K["NONCE_KEY"]}' );
define( 'AUTH_SALT',        '{K["AUTH_SALT"]}' );
define( 'SECURE_AUTH_SALT', '{K["SECURE_AUTH_SALT"]}' );
define( 'LOGGED_IN_SALT',   '{K["LOGGED_IN_SALT"]}' );
define( 'NONCE_SALT',       '{K["NONCE_SALT"]}' );
/**#@-*/

/**
 * WordPress database table prefix.
 */
$table_prefix = 'wp_';

// ** Custom values ** //

// Cache (wp-super-cache is active)
define( 'WP_CACHE', true );
define( 'WPCACHEHOME', '/var/www/aimoneymachine/wp-content/plugins/wp-super-cache/' );

// JWT REST authentication — now a real, unique secret
define( 'JWT_AUTH_SECRET_KEY', '{JWT}' );
define( 'JWT_AUTH_CORS_ENABLE', false );

// Hardening
define( 'DISALLOW_FILE_EDIT', true );
define( 'WP_APPLICATION_PASSWORDS', true );
define( 'WP_AUTO_UPDATE_CORE', true );
define( 'WP_POST_REVISIONS', 0 );
define( 'WP_DEBUG', false );
define( 'WP_DEBUG_LOG', true );
define( 'WP_DEBUG_DISPLAY', false );

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {{
	define( 'ABSPATH', __DIR__ . '/' );
}}

require_once ABSPATH . 'wp-settings.php';
"""

open(CONF, "w", encoding="utf-8").write(cfg)
subprocess.run(["chown", "root:root", CONF])
subprocess.run(["chmod", "644", CONF])

r = subprocess.run(["php", "-l", CONF], capture_output=True, text=True)
print("php -l:", (r.stdout + r.stderr).strip().splitlines()[0])

# store the secrets in the incident dir so they are not lost
open("/root/aimm-incident-20260914/NEW-SECRETS.txt", "w").write(
    "aimoneymachine.site regenerated secrets (2026-09-14)\n\n"
    + "\n".join(f"{k} = {v}" for k, v in K.items())
    + f"\nJWT_AUTH_SECRET_KEY = {JWT}\n"
)
print("secrets saved to /root/aimm-incident-20260914/NEW-SECRETS.txt")
