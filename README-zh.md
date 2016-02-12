PHP 扩展: mbstring_enhanced
===========================

[![Build Status](https://travis-ci.org/chengang/mbstring_enhanced.svg?branch=master)](https://travis-ci.org/chengang/mbstring_enhanced)

Click [README](https://github.com/chengang/mbstring_enhanced/README.md) for English.

mbstring_enhanced 是为CJK (中日韩语言)增强的多字节字符处理的一个PHP扩展库。

这个库想解决的两个问题
----------------------
###### 1. `mb_detect_encoding` 监测失败    
有时候PHP不能正确监测字符集，就像这样——

```php
    <?php
    $str = "头痛";
    echo mb_detect_encoding($str, "UTF-8, CP936", true); // 打印 UTF-8
    echo "\n";
    echo mb_detect_encoding($str, "CP936, UTF-8", true); // 打印 CP936
    echo "\n";
```

PHP并不知道*头痛*是UTF-8还是CP936 (又名GBK)。   
但这不是一个错误，因为*头痛*的二进制码确实在UTF-8和CP936 (又名GBK) 中都有对应的字符。
PHP按照规范检测了字符集，他做了正确的处理。但是在实际的应用开发时，我们又确实需要分清*头痛*到底是什么字符集。   
于是我们为中日韩的字符做了特殊处理，增加了`mbe_is_utf8cjk`来处理这个状况。   

###### 2. GBK 编码的数据库面对 UTF-8 输入时出错
没错，对于中文而言 GBK (又名CP936) 更小更快也更容易处理和理解。如果只存储中文的话，它确实是个不错的选择。   
但是如果我们选择了GBK编码的数据库或者后端存储，输入又不可控的传来GBK码表中没有的UTF-8字符时，麻烦就来了。
我们希望`mbe_strip_utf8_left_cjk` 这个函数能帮上忙。   

函数参考
--------

#### mbe_is_utf8cjk   
(PHP 5.4以上测试通过)   
`mbe_is_utf8cjk` - 检查字符是不是UTF-8编码的ASCII或者中日韩字符

###### 说明

```php
   bool mbe_is_utf8cjk ( string $str )
```

###### 参数
**str**   
需要被检查的字符串

###### 返回值
如果输入字符串中只包含ASCII和中日韩字符则返回 **TRUE** 。   
反之返回 **FALSE** 。

###### 范例
*Example #1 mbe_is_utf8cjk() 范例*   

```php
    <?php
    $is_utf8 = mbe_is_utf8cjk("i had a badly 头痛 yestoday night.");
    $encoding = $is_utf8 ? "UTF-8" : "GBK";
    echo $encoding; // 打印 UTF-8
```

*Example #2 mbe_is_utf8cjk() 带欧元符号的范例*   

```php
    <?php
    $is_utf8 = mbe_is_utf8cjk("i had a badly 头痛 yestoday night.€");
    $encoding = $is_utf8 ? "UTF-8" : "GBK";
    echo $encoding; // 打印 GBK。这描述也许不准确，但有用。 
```

#### mbe_strip_utf8_left_cjk   
(PHP 5.4以上测试通过)   
`mbe_strip_utf8_left_cjk` - 从字符串中去掉非ASCII或中日韩的字符   

###### 说明   

```php
   string mbe_strip_utf8_left_cjk ( string $str )
```
把非ASCII或中日韩的字符替换成空格   

###### 参数
**str**   
要被处理的UTF-8字符串。   
>    **Note:**
>    如果输入的字符串不是UTF-8编码的会引发错误   


###### 返回值
返回处理后的字符串   
>    **Note:**
>    返回的字符串保持和输入字符串相同的`strlen`长度   

###### 范例
*Example #1 mbe_strip_utf8_left_cjk() 范例*   

```php
    <?php
    $striped_str = mbe_strip_utf8_left_cjk("abcdefg€\n€zz中文dffh");
    echo $striped_str; // 打印 "abcdefg   \n   zz中文dffh"
```

如何安装使用
------------
1. 安装 autoconf 和 php-devel.
2. `cd mbstring_enhanced && phpize`
3. `./configure`
4. `make`
5. `make test`
6. `make install`
7. 在你的 php.ini 文件中加入如下一行:
```
    extension=mbstring_enhanced.so
```

现在mbstring_enhanced.so已经拷贝到了默认的扩展目录下，你可以在你的PHP代码中使用 `mbe_is_utf8cjk` 和 `mbe_strip_utf8_left_cjk` 方法了。    

如何报Bug
---------
请把BUG报到这个地址
https://github.com/chengang/mbstring_enhanced/issues
