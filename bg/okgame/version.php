<?php 

header('Content-Type: text/plain');
// Read version from VERSION.md
$version = trim(file_get_contents("VERSION.md"));
echo $version;

// Stats tracking (legacy)
$hit_count=0;
$statfile = @fopen("stats/count".date("Ymd").".txt","a+");
@rewind($statfile);
$hit_count = @fread($statfile, 25000);
$hit_count++;
@fclose($statfile);

$statfile = @fopen("stats/count".date("Ymd").".txt","w+");
@fwrite($statfile, $hit_count);
@fclose($statfile);
?>
