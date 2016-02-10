--TEST--
Check for mbe_mbstring presence
--SKIPIF--
<?php if (!extension_loaded("mbstring_enhanced")) print "skip"; ?>
--FILE--
<?php 
$is_utf8 = mbe_is_utf8cjk("头痛");
if ($is_utf8) {
        echo "UTF8\n";
} else {
        echo "GBK\n";
}
/*
	you can add regression tests for your extension here

  the output of your test code has to be equal to the
  text in the --EXPECT-- section below for the tests
  to pass, differences between the output and the
  expected text are interpreted as failure

	see php5/README.TESTING for further information on
  writing regression tests
*/
?>
--EXPECT--
UTF8
