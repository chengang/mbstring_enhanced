--TEST--
Check for mbe_mbstring presence
--SKIPIF--
<?php if (!extension_loaded("mbstring_enhanced")) print "skip"; ?>
--FILE--
<?php 
$striped_str = mbe_strip_utf8_left_cjk("abcdefg€€€€€higklmn€€€\n€€€zz头dffh");
if ($striped_str == "abcdefg               higklmn         \n         zz   dffh") {
        echo "RIGHT\n";
} else {
        echo "WRONG\n";
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
RIGHT
