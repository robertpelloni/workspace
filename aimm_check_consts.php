<?php
require_once('/var/www/aimoneymachine/wp-load.php');
$checks = ['JWT_AUTH_SECRET_KEY','JWT_AUTH_CORS_ENABLE','AUTH_KEY','SECURE_AUTH_KEY',
           'LOGGED_IN_KEY','NONCE_KEY','AUTH_SALT','SECURE_AUTH_SALT','LOGGED_IN_SALT',
           'NONCE_SALT','WP_CACHE','WPCACHEHOME','DISALLOW_FILE_EDIT'];
foreach ($checks as $c) {
    $d = defined($c);
    $v = '';
    if ($d) {
        $val = constant($c);
        $v = is_string($val) ? substr($val, 0, 8) . '...(' . strlen($val) . ' chars)' : var_export($val, true);
    }
    printf("  %-22s defined=%-5s %s\n", $c, $d ? 'YES' : 'NO', $v);
}
