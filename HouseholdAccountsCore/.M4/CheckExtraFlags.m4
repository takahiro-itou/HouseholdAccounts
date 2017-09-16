dnl----------------------------------------------------------------
dnl
dnl   関数：MYAC_CHECK_EXTRA_COMPILER_OPTION
dnl
dnl   概要：コンパイラオプションが利用可能か検査する。
dnl   引数：
dnl     -  $1   オプションを格納する変数
dnl     -  $2   検査結果を記録する変数
dnl     -  $3   検査するコンパイラオプション
dnl   機能：コンパイラがオプションを受け付けるか検査する。
dnl   効果：以下の変数が設定される：
dnl     -   $1
dnl             オプションが受け付けられる場合は、
dnl             そのオプションが末尾に追加される。
dnl     -   myac_cf_$2_enabled
dnl             検査結果が TRUE/FALSE で記録される。
dnl
AC_DEFUN([MYAC_CHECK_EXTRA_COMPILER_OPTION],
[AC_MSG_CHECKING([for Compiler Option ]$3)
saved_CFLAGS=${CFLAGS}
saved_CXXFLAGS=${CXXFLAGS}
[CFLAGS=']$3[']
[CXXFLAGS=']$3[']
AC_TRY_COMPILE(
    [;],
    [;],
    [[myac_cf_]m4_bpatsubst([$2],-,_)[_enabled='TRUE']],
    [[myac_cf_]m4_bpatsubst([$2],-,_)[_enabled='FALSE']])
[if test "x${myac_cf_]m4_bpatsubst([$2],-,_)[_enabled}y" = "xTRUEy" ; then]
    $1[="${]$1[}  ]$3["]
    AC_MSG_RESULT([Accept])
[else]
    AC_MSG_RESULT([Reject])
[fi]
[CFLAGS="${saved_CFLAGS}"]
[CXXFLAGS="${saved_CXXFLAGS}"]
])dnl   End of AC_DEFUN(MYAC_CHECK_EXTRA_COMPILER_OPTION)
dnl
dnl----------------------------------------------------------------
dnl
dnl   関数：MYAC_CHECK_EXTRA_LINKER_OPTION
dnl
dnl   概要：リンカオプションが利用可能か検査する。
dnl   引数：
dnl     -  $1   オプションを格納する変数
dnl     -  $2   検査結果を記録する変数
dnl     -  $3   検査するコンパイラオプション
dnl   機能：リンカがオプションを受け付けるか検査する。
dnl   効果：以下の変数が設定される：
dnl     -   $1
dnl             オプションが受け付けられる場合は、
dnl             そのオプションが末尾に追加される。
dnl     -   myac_lf_$2_enabled
dnl             検査結果が TRUE/FALSE で記録される。
dnl
dnl
dnl   Check Extra Link Options.
dnl
AC_DEFUN([MYAC_CHECK_EXTRA_LINKER_OPTION],
[AC_MSG_CHECKING([for Linker Option ]$3)
saved_LDFLAGS=${LDFLAGS}
[LDFLAGS=']$3[']
AC_TRY_LINK(
    [;],
    [;],
    [[myac_lf_]m4_bpatsubst([$2],-,_)[_enabled='TRUE']],
    [[myac_lf_]m4_bpatsubst([$2],-,_)[_enabled='FALSE']])
[if test "x${myac_lf_]m4_bpatsubst([$2],-,_)[_enabled}y" = "xTRUEy" ; then]
    $1[="${]$1[} ]$3["]
    AC_MSG_RESULT([Accept])
[else]
    AC_MSG_RESULT([Reject])
[fi]
[LDFLAGS="${saved_LDFLAGS}"]
])dnl   End of AC_DEFUN(MYAC_CHECK_EXTRA_LINKER_OPTION)
dnl

