dnl
dnl   コンパイラオプション -std=c++11 を検査。
dnl
##
##  Check -std=c++11 Compiler Option.
##
MYAC_CHECK_EXTRA_COMPILER_OPTION(
    [CXXFLAGS_ENABLE_CPLUSPLUS11],
    [cplusplus11],  [-std=c++11])
MYAC_CHECK_EXTRA_COMPILER_OPTION(
    [CXXFLAGS_ENABLE_CPLUSPLUS0X],
    [cplusplus0x],  [-std=c++0x])
AC_MSG_CHECKING([Compiler Accepts c++11])
[if test "x${myac_cf_cplusplus11_enabled}y" = "xTRUEy" ; then]
    [CXXFLAGS="${CXXFLAGS}  ${CXXFLAGS_ENABLE_CPLUSPLUS11}"]
[elif test "x${myac_cf_cplusplus0x_enabled}y" = "xTRUEy" ; then]
    [myac_cf_cplusplus11_enabled=TRUE]
    [CXXFLAGS_ENABLE_CPLUSPLUS11="${CXXFLAGS_ENABLE_CPLUSPLUS0X}"]
    [CXXFLAGS="${CXXFLAGS}  ${CXXFLAGS_ENABLE_CPLUSPLUS11}"]
[fi]
[if test "x${myac_cf_cplusplus11_enabled}y" = "xTRUEy" ; then]
    AC_MSG_RESULT([YES : ${CXXFLAGS_ENABLE_CPLUSPLUS11}])
[else]
    AC_MSG_RESULT([NO])
[fi]

