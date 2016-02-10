<?php
$br = (php_sapi_name() == "cli")? "":"<br>";

if(!extension_loaded('mbstring_enhanced')) {
	dl('mbstring_enhanced.' . PHP_SHLIB_SUFFIX);
}
$module = 'mbstring_enhanced';
$functions = get_extension_funcs($module);
echo "Functions available in the test extension:$br\n";
foreach($functions as $func) {
    echo $func."$br\n";
}
echo "$br\n";
?>
