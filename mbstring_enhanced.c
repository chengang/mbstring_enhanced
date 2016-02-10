/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Chen Gang <yikuyiku.com@gmail.com>                           |
  +----------------------------------------------------------------------+
*/

//#define _MBE_DEBUG

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_mbstring_enhanced.h"

int bytefilter_utf8_indentify(unsigned char *str, int *status, int *flag_cjk_in_3byte, int need_strip) {
  int c1;

  int c = (int)(*str);

  c1 = ((*status) >> 8) & 0xff;
  (*status) &= 0xff;

  if (c < 0x80) {
    if (c < 0) {
      if (!need_strip) {
        return 1; /* bad */
      } else {
        (*str) = 0x20;
      }
    } else if ((*status)) {
      if (!need_strip) {
        return 1; /* bad */
      } else {
        (*str) = 0x20;
      }
    }
    (*status) = 0;
  } else if (c < 0xc0) {
    switch ((*status)) {
    case 0x20: /* 3 byte code 2nd char */
      if ( (*flag_cjk_in_3byte) == 1 ) {
        (*str) = 0x20;
      }
      if ((c1 == 0x0 && c >= 0xa0) || (c1 == 0xd && c < 0xa0) ||
          (c1 > 0x0 && c1 != 0xd)) {
        (*status)++;
      } else {
        if (!need_strip) {
          return 1; /* bad */
        } else {
          (*str) = 0x20;
        }
        (*status) = 0;
      }
      break;
    case 0x30: /* 4 byte code 2nd char */
      if ((c1 == 0x0 && c >= 0x90) || (c1 > 0x0 && c1 < 0x4) ||
          (c1 == 0x4 && c < 0x90)) {
        (*status)++;
      } else {
        if (!need_strip) {
          return 1; /* bad */
        } else {
          (*str) = 0x20;
        }
        (*status) = 0;
      }
      break;
    case 0x31: /* 4 byte code 3rd char */
      (*status)++;
      break;
    case 0x10: /* 2 byte code 2nd char */
      if (!need_strip) {
        return 1; /* bad */
      } else {
        (*str) = 0x20;
      }
      (*status) = 0;
      break;
    case 0x21: /* 3 byte code 3rd char */
      (*status) = 0;
      if ( (*flag_cjk_in_3byte) == 1 ) {
        (*str) = 0x20;
      }
      (*flag_cjk_in_3byte) = 0;
      break;
    case 0x32: /* 4 byte code 4th char */
      if (!need_strip) {
        return 1; /* bad */
      } else {
        (*str) = 0x20;
      }
      (*status) = 0;
      break;
    default:
      if (!need_strip) {
        return 1; /* bad */
      } else {
        (*str) = 0x20;
      }
      (*status) = 0;
      break;
    }
  } else if (c < 0xc2) { /* 0xc0,0xc1 */
    if (!need_strip) {
      return 1; /* bad */
    } else {
      (*str) = 0x20;
    }
    (*status) = 0;
  } else {
    if ((*status)) {
      if (!need_strip) {
        return 1; /* bad */
      } else {
        (*str) = 0x20;
      }
      (*status) = 0;
    }
    (*status) = 0;
    if (c < 0xe0) { /* 2 byte code first char */
      (*status) = 0x10;
    } else if (c < 0xf0) { /* 3 byte code 1st char */
      (*status) = 0x20;
      (*status) |= (c & 0xf) << 8;
      if (c < 0xe3 ) {  // CJK start at 0xe3 0x80 0x80 , unicode u+3000
          if (!need_strip) {
              return 1; /* bad */
          } else {
              (*flag_cjk_in_3byte) = 1;
              (*str) = 0x20;
          }
      }
    } else if (c < 0xf5) { /* 4 byte code 1st char */
      (*status) = 0x30;
      (*status) |= (c & 0x7) << 8;
    } else {
      if (!need_strip) {
        return 1; /* bad */
      } else {
        (*str) = 0x20;
      }
    }
  }

  return 0;
}

int identify_encoding(unsigned char *str, int len, int need_strip) {
  int flag = 0; // 0:yes, 1:no
  int status = 0;
  int flag_cjk_in_3byte = 0;

  if (str != NULL) {
    while (len > 0) {
      flag = bytefilter_utf8_indentify(str, &status, &flag_cjk_in_3byte, need_strip);
#ifdef _MBE_DEBUG
      printf("byte[%02x] flag[%d]\n", *str, flag);
#endif
      if (flag) {
        break;
      }
      str++;
      len--;
    }
  }

  return flag;
}

/* True global resources - no need for thread safety here */
static int le_mbstring_enhanced;

const zend_function_entry mbstring_enhanced_functions[] = {
    PHP_FE(mbe_is_utf8cjk, NULL) PHP_FE(mbe_strip_utf8_left_cjk, NULL)
        PHP_FE_END /* Must be the last line in mbstring_enhanced_functions[] */
};

zend_module_entry mbstring_enhanced_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    "mbstring_enhanced",
    mbstring_enhanced_functions,
    PHP_MINIT(mbstring_enhanced),
    PHP_MSHUTDOWN(mbstring_enhanced),
    NULL,
    NULL,
    PHP_MINFO(mbstring_enhanced),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_MBSTRING_ENHANCED_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES};

#ifdef COMPILE_DL_MBSTRING_ENHANCED
ZEND_GET_MODULE(mbstring_enhanced)
#endif

PHP_MINIT_FUNCTION(mbstring_enhanced) { return SUCCESS; }

PHP_MSHUTDOWN_FUNCTION(mbstring_enhanced) { return SUCCESS; }

PHP_RINIT_FUNCTION(mbstring_enhanced) { return SUCCESS; }

PHP_RSHUTDOWN_FUNCTION(mbstring_enhanced) { return SUCCESS; }

PHP_MINFO_FUNCTION(mbstring_enhanced) {
  php_info_print_table_start();
  php_info_print_table_header(2, "mbstring_enhanced support", "enabled");
  php_info_print_table_end();
}

PHP_FUNCTION(mbe_is_utf8cjk) {
  unsigned char *arg = NULL;
  int arg_len;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) ==
      FAILURE) {
    return;
  }

  int is_utf8cjk = identify_encoding(arg, arg_len, 0);
#ifdef _MBE_DEBUG
  printf("[%s]\n", arg);
#endif

  if (is_utf8cjk == 0) {
    RETURN_TRUE;
  }
  RETURN_FALSE;
}

PHP_FUNCTION(mbe_strip_utf8_left_cjk) {
  unsigned char *arg = NULL;
  int arg_len, len;
  char *strg;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) ==
      FAILURE) {
    return;
  }

  int is_utf8cjk = identify_encoding(arg, arg_len, 1);
  // len = spprintf(&strg, 0, "UNKNOWN");
  RETURN_STRINGL((char *)arg, arg_len, 0);
}
