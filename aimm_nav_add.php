<?php
/**
 * Adds "Honest Work" to the site's block navigation, before Contact.
 * Idempotent: running twice will not duplicate the link.
 */
require_once '/var/www/aimoneymachine/wp-load.php';

$nav_id = 4;
$nav = get_post($nav_id);
if (!$nav) {
    echo "ERROR: navigation post {$nav_id} not found\n";
    exit(1);
}

if (strpos($nav->post_content, 'honest-work-desk') !== false) {
    echo "already present — no change\n";
    exit(0);
}

$link = '<!-- wp:navigation-link {"label":"Honest Work","type":"custom",'
      . '"url":"/honest-work-desk/","kind":"custom","isTopLevelLink":true} /-->';

$contact = '<!-- wp:navigation-link {"label":"Contact"';
if (strpos($nav->post_content, $contact) === false) {
    // fall back to appending
    $new = rtrim($nav->post_content) . "\n" . $link . "\n";
} else {
    $new = str_replace($contact, $link . "\n" . $contact, $nav->post_content);
}

$res = wp_update_post([
    'ID'           => $nav_id,
    'post_content' => $new,
], true);

if (is_wp_error($res)) {
    echo "ERROR: " . $res->get_error_message() . "\n";
    exit(1);
}
echo "navigation updated (ID {$nav_id})\n";
echo "links now:\n";
preg_match_all('/"label":"([^"]+)"/', $new, $m);
foreach ($m[1] as $l) {
    echo "  - {$l}\n";
}
