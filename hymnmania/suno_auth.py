"""Reliably fetch the current Suno API JWT.

Suno's auth is confusing and has moved a few times:
  - Clerk SDK removed (typeof Clerk == undefined), so Clerk.session.getToken() is dead.
  - The __session cookie LOOKS like the JWT and worked once, but it ROTATES independently
    from the real API token. Verified 2026-09-23: __session cookie -> 401, while the JWT
    the page sends in 'Authorization: Bearer <jwt>' -> 200.

So the ONLY reliable source is the Authorization header the page itself sends on its
studio-api requests. This helper captures it via a request listener.

    from suno_auth import get_jwt
    tok = get_jwt(page)
"""
import time


def get_jwt(page, navigate=True, timeout_s=30):
    """Capture the API JWT from a studio-api request made by `page`.

    If navigate=True (default), reload /create to force the page to fire studio-api calls,
    then wait for the first Authorization header.
    """
    jwt = {}

    def on_req(req):
        if "studio-api" in req.url and not jwt:
            a = req.headers.get("authorization", "") or ""
            if a.startswith("Bearer "):
                jwt["v"] = a[7:]

    page.on("request", on_req)
    if navigate:
        try:
            page.goto("https://suno.com/create", wait_until="domcontentloaded", timeout=30000)
        except Exception:
            pass
    deadline = time.time() + timeout_s
    while time.time() < deadline and not jwt:
        try:
            page.wait_for_timeout(500)
        except Exception:
            break
    return jwt.get("v")
