<?php
require_once('/var/www/aimoneymachine/wp-load.php');
$t = get_option('wpseo_titles');
if (!is_array($t)) { echo "ERROR: wpseo_titles not an array\n"; exit(1); }
$before = $t['noindex-author-wpseo'] ?? null;
$t['noindex-author-wpseo'] = true;   // single-author blog: archive duplicates the blog
$t['noindex-author-noposts-wpseo'] = true;
$t['noindex-archive-wpseo'] = true;  // date archives stay out
update_option('wpseo_titles', $t);
$after = get_option('wpseo_titles');
printf("noindex-author-wpseo : %s -> %s\n",
    var_export($before, true), var_export($after['noindex-author-wpseo'], true));
printf("noindex-archive-wpseo: %s\n", var_export($after['noindex-archive-wpseo'], true));
printf("disable-attachment   : %s\n", var_export($after['disable-attachment'], true));
echo "saved\n";
