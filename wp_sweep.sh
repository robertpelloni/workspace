#!/bin/bash
echo "=== WordPress installs found ==="
mapfile -t CONFIGS < <(find /var/www /srv/www -maxdepth 3 -name wp-config.php 2>/dev/null)
for c in "${CONFIGS[@]}"; do
	echo
	echo "############################################################"
	echo "# $c"
	echo "############################################################"
	d=$(dirname "$c")
	php -r '
    $f = $argv[1];
    $src = file_get_contents($f);
    // count define() lines that sit INSIDE an open /* comment
    $inComment = false; $trapped = [];
    foreach (explode("\n", $src) as $i => $line) {
      $t = trim($line);
      if (preg_match("#/\*#", $line) && !preg_match("#\*/#", $line)) $inComment = true;
      elseif (preg_match("#\*/#", $line)) { $inComment = false; continue; }
      if ($inComment && strpos($t, "define(") === 0) $trapped[] = ($i+1) . ": " . substr($t,0,60);
    }
    echo "  trapped define() inside comments: " . (count($trapped) ? implode(" | ", $trapped) : "none") . "\n";
  ' "$c" 2>/dev/null

	# which security constants actually resolve?
	php -r '
    $root = $argv[1];
    $cfg  = $argv[2];
    // parse constants textually (do not load WP, avoid side effects)
    $src = file_get_contents($cfg);
    foreach (["AUTH_KEY","SECURE_AUTH_KEY","LOGGED_IN_KEY","NONCE_KEY","AUTH_SALT","SECURE_AUTH_SALT","LOGGED_IN_SALT","NONCE_SALT","JWT_AUTH_SECRET_KEY"] as $k) {
      $present = preg_match("/define\s*\(\s*[\"'"'"']" . preg_quote($k, "/") . "[\"'"'"']/", $src);
      printf("  %-22s %s\n", $k, $present ? "present" : "MISSING");
    }
  ' "$d" "$c" 2>/dev/null

	# user accounts
	PW=$(grep "DB_PASSWORD" "$c" | cut -d"'" -f4)
	DB=$(grep "DB_NAME" "$c" | cut -d"'" -f4)
	U=$(grep "DB_USER" "$c" | cut -d"'" -f4)
	if [ -n "$PW" ]; then
		echo "  --- users ---"
		mysql -u"$U" -p"$PW" "$DB" -N -B -e "SELECT CONCAT('    ',ID,'  ',user_login,'  ',user_email) FROM wp_users ORDER BY ID;" 2>/dev/null | head -50
		echo "  total users: $(mysql -u"$U" -p"$PW" "$DB" -N -B -e 'SELECT COUNT(*) FROM wp_users;' 2>/dev/null)"
		echo "  admins: $(mysql -u"$U" -p"$PW" "$DB" -N -B -e "SELECT COUNT(*) FROM wp_usermeta WHERE meta_key='wp_capabilities' AND meta_value LIKE '%administrator%';" 2>/dev/null)"
		echo "  users_can_register: $(mysql -u"$U" -p"$PW" "$DB" -N -B -e "SELECT option_value FROM wp_options WHERE option_name='users_can_register';" 2>/dev/null)"
	fi
done
