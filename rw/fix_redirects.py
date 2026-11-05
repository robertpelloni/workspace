#!/usr/bin/env python3
"""Guard the remaining checkout redirects against open redirects.

Each of these does `window.location.href = d.url` on whatever the billing API
returned. If the API is ever tricked, misconfigured, or a proxy rewrites the
response, that sends the customer (and any credentials in the URL) to an
arbitrary host. Restrict it to Stripe checkout or a same-site path, and reject
protocol-relative '//evil.com' which a bare startsWith('/') would let through.

Run with --apply to write.
"""

import os
import sys

DRY = "--apply" not in sys.argv
HERE = os.path.dirname(os.path.abspath(__file__))

GUARD = (
    "                // Only follow a checkout URL on an expected host - a bare\n"
    "                // window.location.href = d.url follows whatever the API returns.\n"
    "                var ok = typeof d.url === \"string\" && "
    "/^https:\\/\\/([a-z0-9-]+\\.)*(stripe\\.com|hypernexus\\.site)\\//i.test(d.url);\n"
    "                if (ok) { window.location.assign(d.url); }\n"
    "                else { alert(d.url ? \"Error: unexpected checkout URL\" : \"Error: No checkout URL returned\"); }\n"
)

RULES = [
    # pricing.html
    ("hn_pricing.html",
     '              .then(function (d) {\n'
     '                if (d.url) window.location.href = d.url;\n'
     '                else alert("Error: No checkout URL returned");\n'
     '              })\n',
     '              .then(function (d) {\n' + GUARD + '              })\n'),

    # cloud login A / B
    ("cl_cloud_login_a.html",
     '            .then(function (d) {\n'
     '              if (d.url) window.location.href = d.url;\n'
     '              else alert("Error: No checkout URL");\n'
     '            })\n',
     '            .then(function (d) {\n'
     '              // Only follow a checkout URL on an expected host - a bare\n'
     '              // window.location.href = d.url follows whatever the API returns.\n'
     '              var ok = typeof d.url === "string" && /^https:\\/\\/([a-z0-9-]+\\.)*(stripe\\.com|hypernexus\\.site)\\//i.test(d.url);\n'
     '              if (ok) { window.location.assign(d.url); }\n'
     '              else { alert(d.url ? "Error: unexpected checkout URL" : "Error: No checkout URL"); }\n'
     '            })\n'),

    ("cl_cloud_login_b.html",
     '            .then(function (d) {\n'
     '              if (d.url) window.location.href = d.url;\n'
     '              else alert("Error: No checkout URL");\n'
     '            })\n',
     '            .then(function (d) {\n'
     '              // Only follow a checkout URL on an expected host - a bare\n'
     '              // window.location.href = d.url follows whatever the API returns.\n'
     '              var ok = typeof d.url === "string" && /^https:\\/\\/([a-z0-9-]+\\.)*(stripe\\.com|hypernexus\\.site)\\//i.test(d.url);\n'
     '              if (ok) { window.location.assign(d.url); }\n'
     '              else { alert(d.url ? "Error: unexpected checkout URL" : "Error: No checkout URL"); }\n'
     '            })\n'),

    # cloud A/B index variant - one-liner
    ("cl_index_b.html",
     "                      .then(function(d){if(d.url)window.location.href=d.url;"
     "else alert('Error: '+(d.error||'Unknown'))})\n",
     "                      .then(function(d){"
     "var u=d.url;var ok=(typeof u==='string')&&/^https:\\/\\/([a-z0-9-]+\\.)*(stripe\\.com|hypernexus\\.site)\\//i.test(u);"
     "if(ok){window.location.assign(u)}else{alert('Error: '+(d.error||(u?'unexpected checkout URL':'No checkout URL')))}"
     "})\n"),

    # hypernexus indexB (orphan variant)
    ("hn_indexB.html",
     '                      .then(function(d){\n'
     '                        if(d.url)window.location.href=d.url;\n'
     "                        else alert('Error: No checkout URL returned');\n"
     '                      })\n',
     '                      .then(function(d){\n'
     '                        // Only follow a checkout URL on an expected host - a bare\n'
     '                        // window.location.href=d.url follows whatever the API returns.\n'
     '                        var ok = typeof d.url === "string" && /^https:\\/\\/([a-z0-9-]+\\.)*(stripe\\.com|hypernexus\\.site)\\//i.test(d.url);\n'
     '                        if (ok) { window.location.assign(d.url); }\n'
     "                        else { alert(d.url ? 'Error: unexpected checkout URL' : 'Error: No checkout URL returned'); }\n"
     '                      })\n'),
]


def main():
    cache, problems = {}, []
    for fname, old, new in RULES:
        path = os.path.join(HERE, fname)
        if path not in cache:
            if not os.path.isfile(path):
                problems.append(f"{fname}: file not found")
                continue
            try:
                with open(path, encoding="utf-8", newline="") as fh:
                    cache[path] = fh.read()
            except OSError as exc:
                problems.append(f"{fname}: cannot read ({exc})")
                continue
        n = cache[path].count(old)
        print(f"  {'ok ' if n == 1 else '!! '}{n}x  {fname}")
        if n != 1:
            problems.append(f"{fname}: expected 1x, found {n}x")
            continue
        cache[path] = cache[path].replace(old, new)

    print()
    if problems:
        for p in problems:
            print("  PROBLEM: " + p)
        print()
    if DRY:
        print("dry run: nothing written")
        return 1 if problems else 0

    for path, text in cache.items():
        try:
            with open(path, "w", encoding="utf-8", newline="") as fh:
                fh.write(text)
        except OSError as exc:
            print(f"  !! write failed {os.path.basename(path)}: {exc}")
            return 1
    print(f"  wrote {len(cache)} files")
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
