PHP extension: mbstring_enhanced
================================

[![Build Status](https://travis-ci.org/chengang/mbstring_enhanced.svg?branch=master)](https://travis-ci.org/chengang/mbstring_enhanced)

点击 [中文文档](https://github.com/chengang/mbstring_enhanced/blob/master/README-zh.md) 查看中文文档   

mbstring_enhanced is a PHP mbstring extension enhanced for CJK (Chinese, Japanese, Korean) characters.

Two problems sloved
-------------------
###### 1. Better `mb_detect_encoding` for CJK    
Somtimes PHP does not detect character encoding, like below:

```php
    <?php
    $str = "头痛";
    echo mb_detect_encoding($str, "UTF-8, CP936", true); // prints UTF-8
    echo "\n";
    echo mb_detect_encoding($str, "CP936, UTF-8", true); // prints CP936
    echo "\n";
```

That is not an error. That is because the binary form of the string we want to detect can be found both in UTF-8 and CP936 (aka GBK).   
PHP code do its best, but that really confuse.   
There are some clues for CJK (Chinese, Japanese, Korean), we sloved the problem with the function `mbe_is_utf8cjk`.   

###### 2. Process UTF-8 with GBK database
Yes, GBK (aka CP936) is smaller, fatser and much more simple than UTF-8 for Chinese.   
But people have problems when they have storages or databases encoding with GBK and then receive some characters encoding with UTF-8.   
We hope the function `mbe_strip_utf8_left_cjk` can help.   

Functions
---------

#### mbe_is_utf8cjk   
*(tested for PHP 5.3, PHP 5.4, PHP 5.5, PHP 5.6)*   
`mbe_is_utf8cjk` - Check if the string is valid CJK in UTF-8 character encoding

###### Description

```php
   bool mbe_is_utf8cjk ( string $str )
```

###### Parameters
**str**   
The string being detected.

###### Return Values
Returns **TRUE** when the string being detected is in UTF-8 character encoding and contains ascii characters and CJK characters only.   
Returns **FALSE** otherwise.

###### Examples
*Example #1 mbe_is_utf8cjk() example*   

```php
    <?php
    $is_utf8 = mbe_is_utf8cjk("i had a badly 头痛 yestoday night.");
    $encoding = $is_utf8 ? "UTF-8" : "GBK";
    echo $encoding; // prints UTF-8
```

*Example #2 mbe_is_utf8cjk() a practical example for chinese encoding detect*   

```php
    <?php
    function mbe_detect_utf8_or_gbk ($str) {
        $encoding1 = mb_detect_encoding($str, "UTF-8, CP936", true);
        $encoding2 = mb_detect_encoding($str, "CP936, UTF-8", true);
        if ($encoding1 == $encoding2) {
            return $encoding1;
        }
        return mbe_is_utf8cjk ($str) ? "UTF-8" : "GBK";
    }
    $encoding = mbe_detect_utf8_or_gbk("i had a badly 头痛 yestoday night.");
    echo $encoding;
```

#### mbe_strip_utf8_left_cjk   
*(tested for PHP 5.3, PHP 5.4, PHP 5.5, PHP 5.6)*   
`mbe_strip_utf8_left_cjk` - Strip UTF-8 encoding characters that is not ascii character or CJK character from a string 

###### Description

```php
   string mbe_strip_utf8_left_cjk ( string $str )
```
Replace characters that is not ascii character or CJK character in the string with blank.

###### Parameters
**str**   
The UTF-8 string being striped.
>    **Note:**
>    Input a string that is not encoding in UTF-8 may cause errors.


###### Return Values
Returns the stripped string that left ascii characters and CJK characters only.   
>    **Note:**
>    The return string keeps the same `strlen` of the input string.

###### Examples
*Example #1 mbe_strip_utf8_left_cjk() example*   

```php
    <?php
    $striped_str = mbe_strip_utf8_left_cjk("abcdefg€\n€zz中文dffh");
    echo $striped_str; // prints "abcdefg   \n   zz中文dffh"
```

How to use
----------
1. Install autoconf and php-devel.
2. `cd mbstring_enhanced && phpize`
3. `./configure`
4. `make`
5. `make test`
6. `make install`
7. Add the following line to your php.ini:
```
    extension=mbstring_enhanced.so
```

mbstring_enhanced.so is installed to the default extension directory and you can call function `mbe_is_utf8cjk` and `mbe_strip_utf8_left_cjk` in your php code.

Bug Reports
-----------
Please fill bug reports at 
https://github.com/chengang/mbstring_enhanced/issues
