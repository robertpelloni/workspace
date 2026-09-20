<?php
/**
 * Dump every wp_head / template_redirect callback with the file and line it
 * was registered from, so an unknown closure can be traced back to its plugin.
 */

$filters = array( 'wp_head', 'template_redirect', 'wp_robots' );

foreach ( $filters as $tag ) {
	global $wp_filter;
	if ( ! isset( $wp_filter[ $tag ] ) ) {
		continue;
	}
	echo "\n===== {$tag} =====\n";
	$f = $wp_filter[ $tag ];
	foreach ( $f->callbacks as $prio => $cbs ) {
		foreach ( $cbs as $id => $cb ) {
			$fn    = $cb['function'];
			$where = 'unknown';
			$name  = (string) $id;
			try {
				if ( $fn instanceof Closure ) {
					$r     = new ReflectionFunction( $fn );
					$where = $r->getFileName() . ':' . $r->getStartLine();
					$name  = 'Closure';
				} elseif ( is_array( $fn ) ) {
					$r     = new ReflectionMethod( $fn[0], $fn[1] );
					$where = $r->getFileName() . ':' . $r->getStartLine();
					$name  = ( is_object( $fn[0] ) ? get_class( $fn[0] ) : (string) $fn[0] ) . '::' . $fn[1];
				} elseif ( is_object( $fn ) ) {
					$r     = new ReflectionMethod( $fn, '__invoke' );
					$where = $r->getFileName() . ':' . $r->getStartLine();
					$name  = get_class( $fn ) . '::__invoke';
				} else {
					$r     = new ReflectionFunction( (string) $fn );
					$where = $r->getFileName() . ':' . $r->getStartLine();
					$name  = (string) $fn;
				}
			} catch ( Throwable $e ) {
				$where = 'reflect-failed: ' . $e->getMessage();
			}
			printf( "%-4s %-52s %s\n", $prio, $name, str_replace( ABSPATH, '', $where ) );
		}
	}
}

echo "\n===== feed_links() source (does it emit a Comments Feed link?) =====\n";
$r = new ReflectionFunction( 'feed_links' );
$lines = file( $r->getFileName() );
for ( $i = $r->getStartLine() - 1; $i < min( $r->getEndLine(), $r->getStartLine() + 45 ); $i++ ) {
	echo ( $i + 1 ) . ': ' . $lines[ $i ];
}
