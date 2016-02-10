dnl $Id$
dnl config.m4 for extension mbstring_enhanced

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(mbstring_enhanced, for mbstring_enhanced support,
Make sure that the comment is aligned:
[  --with-mbstring_enhanced             Include mbstring_enhanced support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(mbstring_enhanced, whether to enable mbstring_enhanced support,
dnl Make sure that the comment is aligned:
dnl [  --enable-mbstring_enhanced           Enable mbstring_enhanced support])

if test "$PHP_MBSTRING_ENHANCED" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-mbstring_enhanced -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/mbstring_enhanced.h"  # you most likely want to change this
  dnl if test -r $PHP_MBSTRING_ENHANCED/$SEARCH_FOR; then # path given as parameter
  dnl   MBSTRING_ENHANCED_DIR=$PHP_MBSTRING_ENHANCED
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for mbstring_enhanced files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MBSTRING_ENHANCED_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MBSTRING_ENHANCED_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the mbstring_enhanced distribution])
  dnl fi

  dnl # --with-mbstring_enhanced -> add include path
  dnl PHP_ADD_INCLUDE($MBSTRING_ENHANCED_DIR/include)

  dnl # --with-mbstring_enhanced -> check for lib and symbol presence
  dnl LIBNAME=mbstring_enhanced # you may want to change this
  dnl LIBSYMBOL=mbstring_enhanced # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MBSTRING_ENHANCED_DIR/$PHP_LIBDIR, MBSTRING_ENHANCED_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MBSTRING_ENHANCEDLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong mbstring_enhanced lib version or lib not found])
  dnl ],[
  dnl   -L$MBSTRING_ENHANCED_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MBSTRING_ENHANCED_SHARED_LIBADD)

  PHP_NEW_EXTENSION(mbstring_enhanced, mbstring_enhanced.c, $ext_shared)
fi
