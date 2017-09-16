dnl----------------------------------------------------------------
dnl
dnl   関数：MYAC_CUSTOMIZE_LIBRARY_DIR
dnl
dnl   概要：ライブラリを配置するディレクトリを設定する。
dnl   引数：
dnl     -  $1   ライブラリ・トップ・ディレクトリ名。
dnl   機能：ライブラリのインストール先を設定する。
dnl         ライブラリ・トップ・ディレクトリの下に、
dnl         各モジュール毎のディレクトリが配置される。
dnl         また、変数 LIBTOP_DIR_NAMME が設定される。
dnl   効果：以下の変数が設定される：
dnl     -   LIBTOP_DIR_NAME
dnl
AC_DEFUN([MYAC_CUSTOMIZE_LIBRARY_DIR],[
dnl    インストール先を変更。
[libdir='${exec_prefix}/][$1][']
dnl    変数定義。
LIBTOP_DIR_NAME=[$1]
AC_SUBST(LIBTOP_DIR_NAME)
])dnl   End of AC_DEFUN(MYAC_CUSTOMIZE_LIBRARY_DIR)
dnl
dnl----------------------------------------------------------------
dnl
dnl   関数：MYAC_CUSTOMIZE_BINARY_DIR
dnl
dnl   概要：バイナリを配置するディレクトリを設定する。
dnl   引数：
dnl     -  $1   バイナリ・トップ・ディレクトリ名。
dnl   機能：バイナリのインストール先を設定する。
dnl         また、変数 BINTOP_DIR_NAMME が設定される。
dnl   効果：以下の変数が設定される：
dnl     -   BINTOP_DIR_NAME
dnl
AC_DEFUN([MYAC_CUSTOMIZE_BINARY_DIR],[
dnl    インストール先を変更。
[bindir='${exec_prefix}/][$1][']
dnl    変数定義。
BINTOP_DIR_NAME=[$1]
AC_SUBST(BINTOP_DIR_NAME)
])dnl   End of AC_DEFUN(MYAC_CUSTOMIZE_LIBRARY_DIR)
dnl
dnl----------------------------------------------------------------
dnl
dnl   関数：MYAC_CUSTOMIZE_INCLUDE_DIR
dnl
dnl   概要：ヘッダファイルを配置するディレクトリを設定する。
dnl   引数：
dnl     -  $1   インクルード・トップ・ディレクトリ名。
dnl     -  $2   パッケージ・ディレクトリ名。
dnl     -  $3   コンフィグ・モジュール・ディレクトリ名。
dnl     -  $4   コンフィグ・ヘッダ・ファイル名。
dnl   機能：ヘッダファイルのインストール先を設定する。
dnl         インクルード・トップ・ディレクトリの下に、
dnl         パッケージ専用のディレクトリを配置する。
dnl         そのパッケージ・ディレクトリの下に、
dnl         各モジュール毎のディレクトリが配置される。
dnl   機能：さらに、コンフィグ・ヘッダ・ファイルを出力する。
dnl         入力はパッケージ・ディレクトリに存在する
dnl         モジュール [$3] 以下の [$4][.in]  を使う。
dnl         出力はインクルード・トップ・ディレクトリに、
dnl         ファイル名 [.][$2][.][$4] で出力する。
dnl   効果：以下の変数が設定される：
dnl     -   INCTOP_DIR_NAME
dnl     -   INCPKG_DIR_NAME
dnl
AC_DEFUN([MYAC_CUSTOMIZE_INCLUDE_DIR],[
dnl    インストール先を変更。
[includedir='${prefix}/][$1][']
dnl    変数定義。
INCTOP_DIR_NAME=[$1]
INCPKG_DIR_NAME=[$2]
AC_SUBST(INCTOP_DIR_NAME)
AC_SUBST(INCPKG_DIR_NAME)
dnl    コンフィグヘッダを出力。
AC_CONFIG_HEADER([$1/.$2.$4:$1/$2/$3/$4.in])
])dnl   End of AC_DEFUN(MYAC_CUSTOMIZE_INCLUDE_DIR)
dnl

