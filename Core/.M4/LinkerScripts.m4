dnl----------------------------------------------------------------
dnl
dnl   Linker Scripts.
dnl   リンカスクリプトを生成する。
dnl

AC_CONFIG_FILES([Lib/libhacCommon.a:Lib/.LinkerScript/Common.in])
AC_CONFIG_FILES([Lib/libhacDocCls.a:Lib/.LinkerScript/DocCls.in])
AC_CONFIG_FILES([Lib/libhacFormat.a:Lib/.LinkerScript/Format.in])

