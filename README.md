mbstring_enhanced
=================

mbstring_enhanced is a PHP mbstring extension enhanced for CJK characters.

Functions
---------

#### mbe_is_utf8cjk   
(tested for PHP 5)   
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
    $encoding = $is_utf8 ? "UTF8" : "GBK";
    echo $encoding; // prints UTF8
```

*Example #2 mbe_is_utf8cjk() example with glyph*   

```php
    <?php
    $is_utf8 = mbe_is_utf8cjk("i had a badly 头痛 yestoday night.€");
    $encoding = $is_utf8 ? "UTF8" : "GBK";
    echo $encoding; // prints GBK, maybe not accurately described but helps for asian
```

#### mbe_strip_utf8_left_cjk   
(tested for PHP 5)   
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
7. Add the following lines to your php.ini:
```php
    extension=mbstring_enhanced.so
```

mbstring_enhanced.so is installed to the default extension directory and you can call function `mbe_is_utf8cjk` and `mbe_strip_utf8_left_cjk` in your php code.

Bug Reports
-----------
Fill bug reports at 
https://github.com/chengang/mbstring_enhanced/issues
