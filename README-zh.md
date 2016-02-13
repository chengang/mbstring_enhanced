PHP 扩展: mbstring_enhanced
===========================

[![Build Status](https://travis-ci.org/chengang/mbstring_enhanced.svg?branch=master)](https://travis-ci.org/chengang/mbstring_enhanced)

Click [README](https://github.com/chengang/mbstring_enhanced/blob/master/README.md) for English.

这个是一个为中日韩语言增强的多字节字符处理PHP扩展库。

解决的两个问题
--------------
###### 一、`mb_detect_encoding` 检测失败问题    
有时候PHP不能正确检测字符集，像这样——

```php
    <?php
    $str = "头痛";
    echo mb_detect_encoding($str, "UTF-8, CP936", true); // 打印 UTF-8
    echo "\n";
    echo mb_detect_encoding($str, "CP936, UTF-8", true); // 打印 CP936
    echo "\n";
```

这并不是一个错误，这是因为 *头痛* 的二进制码在 UTF-8 和 CP936 (又名GBK) 中都有对应的字符。   
PHP尽力了，它不能跨越标准去做事。但是在实际的应用开发时，我们又确实需要分清 *头痛* 到底是什么字符集编码的。   
于是我们为中日韩的字符做了特殊检测，增加了`mbe_is_utf8cjk`来处理这个问题。   

###### 二、GBK 编码的数据库处理 UTF-8 字符时出错
没错，GBK (又名CP936) 更小更快也更容易处理和理解。   
如果只存储中文的话，它是个不错的选择。   
但，GBK编码的数据库接收到GBK码表中不存在的UTF-8字符输入时，麻烦就来了。   
这个场景里，我们希望`mbe_strip_utf8_left_cjk` 这个函数能帮上忙。   

函数参考
--------

#### mbe_is_utf8cjk   
*(PHP5.3, PHP 5.4, PHP 5.5, PHP 5.6测试通过)*   
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
*(PHP5.3, PHP 5.4, PHP 5.5, PHP 5.6测试通过)*   
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
