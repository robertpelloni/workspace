<?php
/**
 * Plugin Name: SEO Indexation Fixes
 * Description: Fixes indexation problems reported in Google Search Console (robertpelloni.com).
 * Version:     2.1.0
 * Author:      ops
 *
 * Search Console (2026-10): "Blocked by robots.txt" — caused by WordPress
 * advertising URLs in <head> and in HTTP Link: headers that robots.txt blocks.
 * See section 8.
 *
 * Search Console (2026-09): 219 "Crawled - currently not indexed", 24 "Not found
 * (404)", 9 "Soft 404", 3 "Page with redirect", 1 "Duplicate without
 * user-selected canonical".
 *
 * SITE STRUCTURE (important context)
 * ----------------------------------
 *   show_on_front = page
 *   page_on_front = 41027  ("Front Page", slug front-page, no post loop)
 *   page_for_posts = 12572 ("Posts Page", slug posts)  -> the blog lives at /posts/
 *
 * So "/" is a static landing page with NO posts, and /posts/ is the blog.
 *
 * DEFECTS FOUND
 * -------------
 * 1. posts_per_page was 300, so the blog (and every archive) rendered ALL 191
 *    posts on a single page. That produced:
 *      - one ~400 KB blog page with no pagination to distribute crawling
 *      - /author/robertpelloni/ being a 99.3% duplicate of /posts/
 *      - /category/uncategorized/ being a 191-post duplicate of /posts/
 *    (fixed in the database: posts_per_page 300 -> 12)
 *
 * 2. posts_per_rss was 5000, producing a 394 KB /feed/.
 *    (fixed in the database: posts_per_rss 5000 -> 20)
 *
 * 3. /page/2/ … /page/8/ returned 200 and were ~99.5% identical to "/", with
 *    only the <title> changed. They are spurious pagination of a static front
 *    page that contains no posts. Core's wp_get_canonical_url() also made them
 *    declare a canonical of "/2/" — a 404. Now 301-redirected to "/".
 *
 * 4. Archives were indexable even when empty (3 empty categories, empty date
 *    archives) -> soft 404s / 404s.
 *
 * 5. Every post advertised a comment RSS feed <link> in <head>, so Google
 *    discovered and crawled /<post>/feed/ URLs.
 */

if ( ! defined( 'ABSPATH' ) ) {
	exit;
}

/* -------------------------------------------------------------------------
 * Request path helper
 * ---------------------------------------------------------------------- */

/**
 * Normalised request path with no query string, leading '/', no trailing '/'.
 *
 * @return string
 */
function rp_request_path() {
	$uri = isset( $_SERVER['REQUEST_URI'] ) ? (string) $_SERVER['REQUEST_URI'] : '';
	if ( '' === $uri ) {
		return '';
	}

	$path = strtok( $uri, '?' );
	$path = strtok( (string) $path, '#' );
	$path = rawurldecode( (string) $path );

	$home_path = (string) wp_parse_url( home_url( '/' ), PHP_URL_PATH );
	if ( '' !== $home_path && '/' !== $home_path && 0 === strpos( $path, $home_path ) ) {
		$path = substr( $path, strlen( $home_path ) );
	}

	$path = preg_replace( '#/+#', '/', '/' . ltrim( $path, '/' ) );
	return rtrim( (string) $path, '/' );
}

/* -------------------------------------------------------------------------
 * 1. Kill the spurious front-page pagination
 *
 * With a static front page there is no page 2. /page/N/ was serving a
 * near-identical copy of "/" (only the <title> differed) and claiming a
 * canonical of "/N/" which 404s.
 * ---------------------------------------------------------------------- */

add_action(
	'template_redirect',
	function () {
		if ( is_admin() || is_robots() || is_favicon() || is_feed() ) {
			return;
		}
		if ( ! get_option( 'page_on_front' ) ) {
			return; // no static front page, pagination may be legitimate
		}
		$path = rp_request_path();
		if ( preg_match( '#^/page/\d+$#', $path ) ) {
			wp_safe_redirect( home_url( '/' ), 301, 'front-page-pagination' );
			exit;
		}
	},
	0
);

/* -------------------------------------------------------------------------
 * 2. Keep thin attachment pages out of the index
 *
 * ~870 attachments each rendered an indexable, near-empty HTML page. They are
 * 301-redirected to the parent post, which is the standard consolidation fix.
 * ---------------------------------------------------------------------- */

add_action(
	'template_redirect',
	function () {
		if ( ! is_attachment() || is_admin() ) {
			return;
		}
		$post = get_post();
		if ( ! $post ) {
			return;
		}
		$target = $post->post_parent
			? get_permalink( $post->post_parent )
			: wp_get_attachment_url( $post->ID );

		if ( $target ) {
			wp_safe_redirect( $target, 301, 'att-redirect' );
			exit;
		}
	},
	1
);

/* -------------------------------------------------------------------------
 * 3. Redirect empty date archives to the blog
 *
 * /2026/07/, /2025/01/, /2024/01/ … return 404 today and are reported as
 * "Not found (404)". There is simply no content in those periods, so send the
 * visitor (and the crawler) somewhere useful instead.
 * ---------------------------------------------------------------------- */

add_action(
	'template_redirect',
	function () {
		if ( is_admin() || is_robots() || is_favicon() || is_feed() ) {
			return;
		}

		/*
		 * Empty date archives do not reach is_date(): WordPress resolves
		 * /2026/07/ straight to a 404, so match the request path instead. Those
		 * URLs are reported as "Not found (404)" in Search Console.
		 */
		$path = rp_request_path();
		if ( is_404() && preg_match( '#^/\d{4}(/\d{1,2})?(/\d{1,2})?$#', $path ) ) {
			rp_redirect_to_blog( 'empty-date-archive' );
		}

		if ( ! is_date() ) {
			return;
		}
		global $wp_query;
		if ( $wp_query instanceof WP_Query && 0 === (int) $wp_query->post_count ) {
			rp_redirect_to_blog( 'empty-date-archive' );
		}
	},
	1
);

/**
 * Send a request to the blog index and stop.
 *
 * @param string $reason Internal label used in the redirect header.
 * @return void
 */
function rp_redirect_to_blog( $reason ) {
	$blog = get_option( 'page_for_posts' )
		? get_permalink( get_option( 'page_for_posts' ) )
		: home_url( '/' );
	wp_safe_redirect( $blog, 301, $reason );
	exit;
}

/* -------------------------------------------------------------------------
 * 4. Canonical URLs
 *
 * Core's canonical is unreliable here, so it is replaced. Archive canonicals
 * are derived from the request path, which is self-referencing by definition.
 * ---------------------------------------------------------------------- */

remove_action( 'wp_head', 'rel_canonical' );

/**
 * Correct self-referencing canonical for the current request.
 *
 * @return string Canonical URL, or '' when the request should have none.
 */
function rp_canonical_url() {
	if ( is_search() || is_404() || is_feed() || is_preview() || is_trackback()
		|| is_robots() || is_favicon() ) {
		return '';
	}

	$path = rp_request_path();

	// Paginated archive (/page/N/ and /<base>/page/N/) — always self-referencing.
	// Checked before is_singular() because WordPress mis-resolves /page/2/ to the
	// front-page object, which is what produced the broken "/2/" canonical.
	if ( '' !== $path && preg_match( '#/page/\d+$#', $path ) ) {
		return home_url( user_trailingslashit( $path ) );
	}

	if ( is_attachment() ) {
		$post = get_post();
		if ( $post && $post->post_parent ) {
			return (string) get_permalink( $post->post_parent );
		}
		return $post ? (string) wp_get_attachment_url( $post->ID ) : '';
	}

	if ( is_singular() ) {
		$link  = (string) get_permalink();
		$paged = (int) get_query_var( 'page' );
		if ( $paged > 1 ) {
			$link = trailingslashit( $link ) . user_trailingslashit( $paged, 'single_paged' );
		}
		return $link;
	}

	if ( is_front_page() && ! is_paged() ) {
		return home_url( '/' );
	}

	if ( '' === $path ) {
		return '';
	}
	return home_url( user_trailingslashit( $path ) );
}

add_action(
	'wp_head',
	function () {
		$url = rp_canonical_url();
		if ( '' !== $url ) {
			echo '<link rel="canonical" href="' . esc_url( $url ) . '" />' . "\n";
		}
	},
	10
);

/* -------------------------------------------------------------------------
 * 5. robots meta
 *
 *  - attachments: never index
 *  - author archives: this is a single-author blog, so /author/robertpelloni/
 *    was a straight duplicate of /posts/. No value in indexing it.
 *  - empty archives (category/tag/date with zero posts): indexing them only
 *    creates soft 404s.
 * ---------------------------------------------------------------------- */

add_filter(
	'wp_robots',
	function ( array $robots ) {
		global $wp_query;

		$empty_archive = $wp_query instanceof WP_Query
			&& 0 === (int) $wp_query->post_count
			&& ( is_category() || is_tag() || is_tax() || is_date() || is_author() );

		if ( is_attachment() || is_author() || $empty_archive ) {
			$robots['noindex']   = true;
			$robots['noarchive'] = true;
			unset( $robots['index'] );
		}

		return $robots;
	}
);

/* -------------------------------------------------------------------------
 * 6. Do not advertise per-post feeds
 *
 * feed_links_extra() prints a "<post> Comments Feed" <link> in every post head,
 * which is how Google found all the /<post>/feed/ URLs being reported as
 * "Crawled - currently not indexed".
 * ---------------------------------------------------------------------- */

remove_action( 'wp_head', 'feed_links_extra', 3 );

/**
 * Keep feeds out of the index even if they are reached directly.
 */
add_filter(
	'wp_robots',
	function ( array $robots ) {
		if ( is_feed() ) {
			$robots['noindex']   = true;
			$robots['noarchive'] = true;
			unset( $robots['index'] );
		}
		return $robots;
	}
);

/* -------------------------------------------------------------------------
 * 7. Sanity floor for archive size
 *
 * posts_per_page is corrected in the database (300 -> 12). This filter keeps a
 * sane ceiling so a future misconfiguration cannot dump the whole blog onto a
 * single archive page again.
 * ---------------------------------------------------------------------- */

add_filter(
	'pre_option_posts_per_page',
	function ( $value ) {
		if ( is_admin() ) {
			return $value;
		}
		return ( (int) $value > 50 ) ? 12 : $value;
	}
);

/* -------------------------------------------------------------------------
 * 8. Stop advertising URLs that robots.txt blocks
 *
 * Search Console (2026-10) reported a new indexing reason: "Blocked by
 * robots.txt". The sitemap was not the problem — every sitemap URL is allowed.
 * The URLs were being *discovered* from pointers WordPress prints into every
 * page:
 *
 *   <head>      <link rel="https://api.w.org/" href="/wp-json/">
 *   <head>      <link rel="alternate" type="application/json" href="/wp-json/wp/v2/pages/NN">
 *   <head>      <link rel="alternate" type="application/json+oembed" href="/wp-json/oembed/1.0/embed?...">
 *   <head>      <link rel="alternate" type="text/xml+oembed" href="/wp-json/oembed/1.0/embed?...&format=xml">
 *   <head>      <link rel="alternate" type="application/rss+xml" title="... Comments Feed" href="/comments/feed/">
 *   HTTP Link   <https://robertpelloni.com/wp-json/>; rel="https://api.w.org/"
 *   HTTP Link   <https://robertpelloni.com/wp-json/wp/v2/pages/NN>; rel="alternate"; type="application/json"
 *
 * Every one of those targets is deliberately Disallowed (section 7's rules), so
 * Googlebot followed a pointer, was refused, and logged "Blocked by robots.txt"
 * as a reason pages were not indexed. Removing the pointers stops the discovery
 * entirely, while the REST API stays closed to /wp-json/wp/v2/users enumeration
 * — which is the reason it is Disallowed in the first place.
 *
 * Note: the "Comments Feed" pointer comes from core feed_links(), not from
 * feed_links_extra(). That is why removing feed_links_extra in section 6 never
 * actually removed it.
 * ---------------------------------------------------------------------- */

/**
 * Withdraw the <head> and Link: header pointers to robots-blocked endpoints.
 *
 * Called at plugin load time (before wp_head is built) and again on init, in
 * case a regular plugin registers one of these callbacks afterwards.
 *
 * @return void
 */
function rp_drop_blocked_discovery_links() {
	/*
	 * oEmbed JSON + XML discovery links -> /wp-json/oembed/...
	 * Core registers this callback at two priorities, so both must go.
	 */
	remove_action( 'wp_head', 'wp_oembed_add_discovery_links', 4 );
	remove_action( 'wp_head', 'wp_oembed_add_discovery_links', 10 );

	// rel="https://api.w.org/" and the JSON alternate -> /wp-json/.
	remove_action( 'wp_head', 'rest_output_link_wp_head', 10 );

	// The same URLs sent as HTTP Link: headers, which crawlers also honour.
	remove_action( 'template_redirect', 'rest_output_link_header', 11 );
}
rp_drop_blocked_discovery_links();
add_action( 'init', 'rp_drop_blocked_discovery_links', 1 );

/*
 * Keep the main /feed/ link (robots allows it) but drop the "Comments Feed"
 * pointer, whose target /comments/feed/ is caught by the feed Disallow rule.
 */
add_filter( 'feed_links_show_comments_feed', '__return_false' );
