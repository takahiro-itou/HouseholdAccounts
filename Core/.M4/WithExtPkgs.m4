dnl----------------------------------------------------------------
dnl
dnl   関数：MYAC_WITH_EXT_PKG
dnl
dnl   概要：オプション --with-XXX を作成する。
dnl   引数：
dnl     -  $1   外部ライブラリの名前（未使用／予約）
dnl     -  $2   オプション名
dnl     -  $3   ヘルプメッセージ
dnl     -  $4   デフォルトの値
dnl     -  $5   結果を格納する変数
dnl   機能：スクリプトに --with-$2  オプションを作成する。
dnl         主に、外部ライブラリの利用可否をユーザーに問う。
dnl         またライブラリのインストールパスの指定にも使う。
dnl   効果：以下の変数が設定される：
dnl     -   $5
dnl             条件分岐用の変数名（Makefile.am 用）。
dnl     -   myac_with_$2_path
dnl             オプションに値が付与されていた場合はその値。
dnl             通常は外部ライブラリのインストールパス。
dnl     -   myac_with_$2_enable
dnl             ユーザーが指定した内容に従って、
dnl             その結果が TRUE/FALSE で記録される。
dnl
AC_DEFUN([MYAC_WITH_EXT_PKG],[
AC_ARG_WITH([$2],
    AC_HELP_STRING([--with-]$2[=PATH], $3),
    [[myac_with_]m4_bpatsubst([$2],-,_)[_val=${withval}] ],
    [[myac_with_]m4_bpatsubst([$2],-,_)[_val=']$4[']]dnl
)dnl
[case  "${myac_with_]m4_bpatsubst([$2],-,_)[_val}"  in]
[  yes)  myac_with_]m4_bpatsubst([$2],-,_)[_path='']
[        myac_with_]m4_bpatsubst([$2],-,_)[_enable=TRUE  ;;]
[  no )  myac_with_]m4_bpatsubst([$2],-,_)[_path='']
[        myac_with_]m4_bpatsubst([$2],-,_)[_enable=FALSE ;;]
[  *  )  myac_with_]m4_bpatsubst([$2],-,_)[_path=${myac_with_]m4_bpatsubst([$2],-,_)[_val}]
[        myac_with_]m4_bpatsubst([$2],-,_)[_enable=TRUE  ;;]
[esac]
dnl
AM_CONDITIONAL(
    [$5],
    [[test  "x${myac_with_]m4_bpatsubst([$2],-,_)[_enable}y" = "xTRUEy"]]dnl
)dnl
])dnl   End of AC_DEFUN(MYAC_WITH_EXT_PKG)
dnl
dnl----------------------------------------------------------------
dnl
dnl   関数：MYAC_SET_EXT_PKG_OPTIONS
dnl
dnl   概要：オプション --with-XXX を作成する。
dnl   引数：
dnl     -  $1   外部ライブラリの名前
dnl     -  $2   オプション名
dnl     -  $3   ライブラリのディレクトリ名
dnl     -  $4   ヘッダファイルのディレクトリ名
dnl     -  $5   バイナリのディレクトリ名
dnl
AC_DEFUN([MYAC_SET_EXT_PKG_OPTIONS],[
AC_MSG_CHECKING([[for ]$1[ Options]])
dnl
[if test "x${myac_with_]m4_bpatsubst([$2],-,_)[_enable}y" = "xTRUEy" ; then]
  [if test "x${myac_with_]m4_bpatsubst([$2],-,_)[_path}y" != "xy" ; then]
    $1[_LIBDIR="${myac_with_]m4_bpatsubst([$2],-,_)[_path}/]$3["]
    $1[_INCDIR="${myac_with_]m4_bpatsubst([$2],-,_)[_path}/]$4["]
    $1[_BINDIR="${myac_with_]m4_bpatsubst([$2],-,_)[_path}/]$5["]
    $1[_CPPFLAGS=-I"${]$1[_INCDIR}"]
    $1[_CPPFLAGS+=' -DHAVE_]$1[=1']
    $1[_CFLAGS='']
    $1[_CXXFLAGS='']
    $1[_LDFLAGS=-L"${]$1[_LIBDIR}"]
  [else]
    $1[_LIBDIR='']
    $1[_INCDIR='']
    $1[_BINDIR='']
    $1[_CPPFLAGS='']
    $1[_CPPFLAGS+=' -DHAVE_]$1[=1']
    $1[_CFLAGS='']
    $1[_CXXFLAGS='']
    $1[_LDFLAGS='']
  [fi]
[else]
  $1[_LIBDIR='']
  $1[_INCDIR='']
  $1[_BINDIR='']
  $1[_CPPFLAGS='']
  $1[_CPPFLAGS+=' -DHAVE_]$1[=0']
  $1[_CFLAGS='']
  $1[_CXXFLAGS='']
  $1[_LDFLAGS='']
[fi]
dnl
AC_MSG_RESULT([${myac_with_]m4_bpatsubst([$2],-,_)[_val}])
AC_MSG_CHECKING([[for ]$1[ path]])
AC_MSG_RESULT([${myac_with_]m4_bpatsubst([$2],-,_)[_path}])
dnl
AC_MSG_CHECKING([[for ]$1[ PreProcessor Options]])
AC_MSG_RESULT([$1[_CPPFLAGS = ${]$1[_CPPFLAGS}]])
AC_MSG_CHECKING([[for ]$1[ Compiler Options]])
AC_MSG_RESULT([$1[_CFLAGS   = ${]$1[_CFLAGS}]])
AC_MSG_CHECKING([[for ]$1[ Compiler Options]])
AC_MSG_RESULT([$1[_CXXFLAGS = ${]$1[_CXXFLAGS}]])
dnl
AC_MSG_CHECKING([[for ]$1[ Linker Options  ]])
AC_MSG_RESULT([$1[_LDFLAGS  = ${]$1[_LDFLAGS}]])
dnl
AC_SUBST($1[_LIBDIR])
AC_SUBST($1[_INCDIR])
AC_SUBST($1[_BINDIR])
AC_SUBST($1[_CPPFLAGS])
AC_SUBST($1[_CFLAGS])
AC_SUBST($1[_CXXFLAGS])
AC_SUBST($1[_LDFLAGS])
])dnl   End of AC_DEFUN(MYAC_SET_EXT_PKG_OPTIONS)
dnl
