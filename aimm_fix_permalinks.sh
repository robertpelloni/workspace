#!/bin/bash
R=/var/www/aimoneymachine
echo "=== BEFORE: permalink_structure ==="
sudo -u www-data wp option get permalink_structure --path=$R 2>&1

echo "=== snapshot current rewrite rules (safety) ==="
PW=$(grep "DB_PASSWORD" $R/wp-config.php | cut -d"'" -f4)
DB=aimoneymachine_wp
U=wp_aimoneymachine
mysql -u$U -p$PW $DB -N -B -e "SELECT option_value FROM wp_options WHERE option_name='rewrite_rules';" 2>/dev/null | head -c 200
echo " ...(saved separately)"

python3 - <<'PY'
import subprocess
R="/var/www/aimoneymachine"
pw=subprocess.run(["bash","-c",f"grep DB_PASSWORD {R}/wp-config.php | cut -d\"'\" -f4"],capture_output=True,text=True).stdout.strip()
sql="SELECT option_value FROM wp_options WHERE option_name='rewrite_rules';"
out=subprocess.run(["mysql","-uwp_aimoneymachine","-p"+pw,"aimoneymachine_wp","-N","-B","-e",sql],capture_output=True,text=True).stdout
open("/root/aimm-incident-20260914/rewrite_rules.before.txt","w").write(out)
print("  saved", len(out), "bytes of rewrite rules")
PY

echo
echo "=== rewriting structure to match the URLs that actually resolve ==="
echo "    (working URL is /slug with no .htm and no trailing slash)"
sudo -u www-data wp option update permalink_structure '/%postname%' --path=$R 2>&1 | tail -2
sudo -u www-data wp rewrite flush --path=$R 2>&1 | tail -2

echo
echo "=== AFTER ==="
sudo -u www-data wp option get permalink_structure --path=$R 2>&1
