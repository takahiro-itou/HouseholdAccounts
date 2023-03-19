dnl----------------------------------------------------------------
dnl
dnl   Linker Scripts.
dnl   リンカスクリプトを生成する。
dnl

AC_CONFIG_FILES([Lib/libhabCommon.a:Lib/.LinkerScript/Common.in])
AC_CONFIG_FILES([Lib/libhabDocCls.a:Lib/.LinkerScript/DocCls.in])
AC_CONFIG_FILES([Lib/libhabFormat.a:Lib/.LinkerScript/Format.in])

