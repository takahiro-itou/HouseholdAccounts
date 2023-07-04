dnl
dnl   コンパイラオプション -std=c++11 を検査。
dnl
##
##  Check -std=c++11 Compiler Option.
##
MYAC_CHECK_EXTRA_COMPILER_OPTION(
    [COMPILER_ACCEPTS_CXX11],
    [cplusplus11],  [-std=c++11])
MYAC_CHECK_EXTRA_COMPILER_OPTION(
    [COMPILER_ACCEPTS_CXX0X],
    [cplusplus0x],  [-std=c++0x])
AC_MSG_CHECKING([Compiler Accepts c++11])
[if test "x${myac_cf_cplusplus11_enabled}y" = "xTRUEy" ; then]
    [myac_cf_stdcxx_enabled=TRUE]
    [CXXFLAGS_ENABLE_STD_CXX="${COMPILER_ACCEPTS_CXX11}"]
[elif test "x${myac_cf_cplusplus0x_enabled}y" = "xTRUEy" ; then]
    [myac_cf_stdcxx_enabled=TRUE]
    [CXXFLAGS_ENABLE_STD_CXX="${COMPILER_ACCEPTS_CXX0X}"]
[else]
    [myac_cf_stdcxx_enabled=FALSE]
[fi]
[if test "x${myac_cf_stdcxx_enabled}y" = "xTRUEy" ; then]
    [CXXFLAGS="${CXXFLAGS}  ${CXXFLAGS_ENABLE_STD_CXX}"]
    AC_MSG_RESULT([YES : ${CXXFLAGS_ENABLE_STD_CXX}])
[else]
    AC_MSG_RESULT([NO])
[fi]

