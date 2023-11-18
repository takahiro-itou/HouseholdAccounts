dnl----------------------------------------------------------------
dnl
dnl   関数：MYAC_WITH_EXT_LIB
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
AC_DEFUN([MYAC_WITH_EXT_LIB],[
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
[if  test "x${myac_with_]m4_bpatsubst([$2],-,_)[_path}y" != "xy" ; then]
  m4_bpatsubst([$1],-,_)[_INCLUDE_DIR="${myac_with_]m4_bpatsubst([$2],-,_)[_path}/include"]
  m4_bpatsubst([$1],-,_)[_LIBRARY_DIR="${myac_with_]m4_bpatsubst([$2],-,_)[_path}/lib"]
[fi]
AC_MSG_RESULT(m4_bpatsubst([$1],-,_)[_INCLUDE_DIR=${]m4_bpatsubst([$1],-,_)[_INCLUDE_DIR}])
AC_MSG_RESULT(m4_bpatsubst([$1],-,_)[_LIBRARY_DIR=${]m4_bpatsubst([$1],-,_)[_LIBRARY_DIR}])
])dnl   End of AC_DEFUN(MYAC_WITH_EXT_LIB)
dnl

