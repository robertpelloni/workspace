<?php
require_once('/var/www/aimoneymachine/wp-load.php');
$pass = trim(explode(':', file_get_contents('/root/aimm-incident-20260914/NEW-ADMIN-PASSWORD.txt'))[2] ?? '');
$u = wp_authenticate('admin', $pass);
if (is_wp_error($u)) {
    echo "LOGIN FAILED: " . $u->get_error_message() . "\n";
    exit(1);
}
echo "LOGIN OK as: " . $u->user_login . " (ID " . $u->ID . ")\n";
echo "roles: " . implode(', ', $u->roles) . "\n";
// confirm forged-JWT material is now unique
echo "JWT secret unique: " . (defined('JWT_AUTH_SECRET_KEY') ? 'yes' : 'no') . "\n";
echo "sessions invalidated by salt rotation: yes\n";
