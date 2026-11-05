<?php
/**
 * Plugin Name: Duplicate Post Consolidation
 * Description: Consolidates keyword-cannibalising duplicate posts and removes spurious front-page pagination (aimoneymachine.site).
 * Version:     1.0.0
 * Author:      ops
 *
 * BACKGROUND (2026-09-14)
 * -----------------------
 * Search Console showed 339 "Crawled - currently not indexed" pages.
 *
 * Two separate defects were responsible:
 *
 * 1. A PERMALINK MISMATCH (fixed in the database, not here).
 *    permalink_structure was "/%postname%.htm", so get_permalink() produced
 *    "/slug.htm" and Yoast published 398 sitemap entries in that form — but
 *    every one of those URLs returned 404, and every post's <link rel=canonical>
 *    pointed at its own 404. Google could not index anything.
 *    The structure is now "/%postname%", which matches the URLs that actually
 *    resolve (200) and preserves the URLs Google already knew.
 *
 * 2. DUPLICATE CONTENT.
 *    398 published posts collapse to 94 real topics: the same article was
 *    regenerated 3-5 times with -2/-3/-4/-5 slug suffixes
 *    (e.g. "best-ai-tools-for-document-processing-and-extraction" exists 5x).
 *    That is textbook keyword cannibalisation — Google indexes one and ignores
 *    the rest.
 *
 *    The map in wp-content/aimm-redirects.json pairs each redundant slug with
 *    the keeper (the longest / earliest variant of that topic). Those URLs are
 *    301-redirected to the keeper, which consolidates ranking signals instead of
 *    discarding them, and preserves any inbound links.
 *
 * 3. SPURIOUS FRONT-PAGE PAGINATION.
 *    "/" is a static page with no post loop, yet /page/2/ … /page/40/ all
 *    returned 200 as near-identical copies. Yoast canonicalised them to "/" but
 *    they were still crawlable, wasting crawl budget. Now 301 -> "/".
 */

if ( ! defined( 'ABSPATH' ) ) {
	exit;
}

/**
 * Load the duplicate -> keeper slug map.
 *
 * @return array<string,string>
 */
function aimm_redirect_map() {
	static $map = null;
	if ( null !== $map ) {
		return $map;
	}

	$map  = array();
	$file = WP_CONTENT_DIR . '/aimm-redirects.json';

	if ( is_readable( $file ) ) {
		$raw = file_get_contents( $file );
		if ( false !== $raw ) {
			$data = json_decode( $raw, true );
			if ( is_array( $data ) ) {
				foreach ( $data as $from => $to ) {
					if ( is_string( $from ) && is_string( $to ) && '' !== $from && '' !== $to ) {
						$map[ $from ] = $to;
					}
				}
			}
		}
	}
	return $map;
}

/* -------------------------------------------------------------------------
 * 1. Consolidate duplicates: 301 the redundant variant to its keeper.
 * ---------------------------------------------------------------------- */
add_action(
	'template_redirect',
	function () {
		if ( is_admin() || is_feed() || is_robots() || is_favicon() ) {
			return;
		}
		if ( ! is_singular( 'post' ) ) {
			return;
		}

		$post = get_queried_object();
		if ( ! $post instanceof WP_Post ) {
			return;
		}

		$map = aimm_redirect_map();
		if ( isset( $map[ $post->post_name ] ) ) {
			wp_safe_redirect( home_url( '/' . $map[ $post->post_name ] ), 301, 'duplicate-post' );
			exit;
		}
	},
	1
);

/* -------------------------------------------------------------------------
 * 2. Remove spurious front-page pagination (/page/N/ -> /).
 *
 * Only matches root-level /page/N. The blog's real pagination lives at
 * /blog/page/N, which is untouched.
 * ---------------------------------------------------------------------- */
add_action(
	'template_redirect',
	function () {
		if ( is_admin() || is_robots() || is_favicon() || is_feed() ) {
			return;
		}
		if ( ! get_option( 'page_on_front' ) ) {
			return;
		}

		$uri = isset( $_SERVER['REQUEST_URI'] ) ? (string) $_SERVER['REQUEST_URI'] : '';
		if ( '' === $uri ) {
			return;
		}

		$path = strtok( $uri, '?' );
		$path = rtrim( rawurldecode( (string) $path ), '/' );

		if ( preg_match( '#^/page/\d+$#', (string) $path ) ) {
			wp_safe_redirect( home_url( '/' ), 301, 'front-page-pagination' );
			exit;
		}
	},
	0
);
