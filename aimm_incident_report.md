# Incident Report — aimoneymachine.site compromise

**Date remediated:** 2026-09-14
**Site:** aimoneymachine.site (WordPress, Twenty Twenty-Five, nginx + php8.4-fpm)
**Threat actor:** "Kamikaze" defacement crew (`https://t.me/kamikaze_root`)
**Impact:** 40 rogue administrator accounts, one full-page defacement published

---

## What the visitor saw

The homepage rendered a **full-viewport black overlay** (`#kzfp`,
`position:fixed; z-index:2147483647`) with red scanlines, a snow effect and the
Kamikaze logo — served from a published post titled **"Kamikaze"** (slug `kz`,
204 KB of HTML/CSS/JS), advertising `https://t.me/kamikaze_root`.

---

## Root cause

`/var/www/aimoneymachine/wp-config.php` was **structurally broken**. An
unterminated docblock swallowed a block of `define()` statements:

```php
/**
 * ...
 * * Database table prefix
define('WP_CACHE', true);              // ← inside the comment
define( 'WPCACHEHOME', '...' );        // ← inside the comment
define('JWT_AUTH_CORS_ENABLE', true);  // ← inside the comment
define('JWT_AUTH_SECRET_KEY', '...');  // ← inside the comment
 * * ABSPATH
 * ...
 */
```

The comment opens on line 2 and does not close until line 25, so **none of those
constants were ever defined**. The `/**#@+ ... /**#@-*/` authentication-salt
block was also empty.

Verified with `defined()`:

| Constant | Before | After |
|---|---|---|
| `JWT_AUTH_SECRET_KEY` | ❌ **NO** | ✅ 64 chars |
| `AUTH_KEY`, `SECURE_AUTH_KEY`, `LOGGED_IN_KEY`, `NONCE_KEY` | ❌ **NO** | ✅ 64 chars each |
| `AUTH_SALT`, `SECURE_AUTH_SALT`, `LOGGED_IN_SALT`, `NONCE_SALT` | ❌ **NO** | ✅ 64 chars each |
| `WP_CACHE` | defined but `false` | `true` |

**Consequences:**

1. **JWT plugin fell back to its built-in default secret.** The plugin does
   `defined('JWT_AUTH_SECRET_KEY') ? JWT_AUTH_SECRET_KEY : false`. With the
   constant undefined, anyone knowing the plugin's hardcoded fallback could
   **forge a valid administrator JWT**.
2. **WordPress had no auth salts**, so login cookies and nonces were generated
   from predictable defaults.

---

## Attack chain (from nginx logs + DB)

1. `POST /wp-json/jwt-auth/v1/token` — probing the JWT endpoint
2. `POST /wp-json/batch/v1` — **the REST API batch endpoint**, used repeatedly
   (hundreds of hits across Aug 31 – Sep 10)
3. Forged/crafted auth → **40 administrator accounts created** between
   2026-07-20 and 2026-09-02
4. `POST /wp-json/wp/v2/posts` with `Host: excellegacyrealtygroup.site`
   → published the defacement on 2026-09-02 17:59:12

Rogue account naming matches a **"wp2shell"** exploit toolkit:

```
wp2_10d231                       wp2_10d231@wp2shell.invalid
wp2_0ee8acbff874                 wp2_0ee8acbff874@wp2shell.invalid
w2s_e5c445618abc … w2s_52ed5a2f147c   @wp2shell.local   (×30+)
w2s_5deda2c26880                 @shellcode.lol
wp_service_aae37d                @service.localhost
admins2e181d                     @excellegacyrealtygroup.site   ← posted "Kamikaze"
```

Every one of the 40 had a `wp_capabilities` value of `administrator` and a live
`session_tokens` entry proving authenticated access.

---

## Remediation performed

**1. Database**

- Deleted the "Kamikaze" post (ID 6064) and its meta
- Deleted **all 40 rogue users** (`user_id > 1`) and their `usermeta`
- Purged transients

**2. Files** — quarantined to `/root/aimm-incident-20260914/quarantine/`

- `test-auth.php` (was **publicly reachable**, dumped request headers)
- `test-rest-filter.php` (was **publicly reachable**)
- `test-wp-auth.php` (application-password oracle)
- `update_post.php`, `regenerate-posts.php`

**3. nginx** (`/etc/nginx/sites-available/aimoneymachine`, backup `.bak-20260914`)

```nginx
location ~* ^/wp-json/batch(/|$)          { deny all; return 403; }  # attack vector
location ~* ^/xmlrpc\.php$                { deny all; return 403; }
location ~* ^/wp-content/uploads/.*\.php$  { deny all; return 403; }
location ~* ^/wp-content/cache/.*\.php$    { deny all; return 403; }
location ~* ^/wp-content/upgrade/.*\.php$  { deny all; return 403; }
location = /wp-json/wp/v2/users           { deny all; return 403; }
```

**4. wp-config.php** — fully rewritten (backup: `.BROKEN-20260914`)

- 8 fresh 64-char authentication keys + salts
- Fresh 64-char `JWT_AUTH_SECRET_KEY` (duplicate definition removed)
- `JWT_AUTH_CORS_ENABLE` set to `false`
- `WP_CACHE` actually enabled, `DISALLOW_FILE_EDIT` retained

**5. Credentials**

- Admin password reset; salt rotation invalidated **all** existing sessions
- New password: `/root/aimm-incident-20260914/NEW-ADMIN-PASSWORD.txt`
- New secrets: `/root/aimm-incident-20260914/NEW-SECRETS.txt`

**6. Cache** — purged wp-super-cache trees so no cached copy of the defacement
could be served

---

## Verification

| Check | Result |
|---|---|
| Users | 1 (`admin`) |
| Administrators | 1 |
| `users_can_register` | `0` |
| Published posts | 398 |
| Defacement markers in DB | 0 |
| `kamikaze_root` / `KZFULL` on disk | none |
| `/wp-json/batch/v1` | **403** |
| `/xmlrpc.php` | **403** |
| `/test-auth.php` | 404 |
| Admin login with new password | OK |
| Homepage | 200, clean |

**Also swept:** `/srv/www/robertpelloni.com` — all salts present, no trapped
defines, 1 user, no rogue accounts. **Not compromised.** (It lacks the JWT
constant, but does not have the JWT plugin installed, so that is harmless.)

---

## Backups / artefacts

```
/root/aimm-incident-20260914/
├── aimoneymachine_wp-CHAINSAW-BACKUP.sql.gz   # full DB dump, pre-cleanup
├── NEW-ADMIN-PASSWORD.txt
├── NEW-SECRETS.txt
├── quarantine/                                # removed web-root scripts
└── (config backups)
/var/www/aimoneymachine/wp-config.php.BROKEN-20260914
/var/www/aimoneymachine/wp-config.php.bak-20260914
/etc/nginx/sites-available/aimoneymachine.bak-20260914
```

---

## Outstanding recommendations

1. **Deactivate `jwt-authentication-for-wp-rest-api` v1.5.0** if nothing uses it.
   It is no longer exploitable (the secret is now real and unique), but it is an
   old plugin and pure attack surface on a simple blog.
2. **Update the plugin** if it is needed.
3. **Check the other site admins**: `robertpelloni.com` was clean, but the same
   malformed-config mistake suggests a habit worth auditing across all installs.
4. **Consider blocking the attacker IPs** and/or adding fail2ban for
   `/wp-login.php` and `/wp-json/`.
5. The `wp-super-cache` + `WP_CACHE` combination was inactive before; it is now
   enabled — confirm the site still renders correctly for logged-in users.
