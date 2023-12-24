dnl
dnl   コンパイラオプション -std=c++11 を検査。
dnl
##
##  Check -std=c++11 Compiler Option.
##
MYAC_CHECK_EXTRA_COMPILER_OPTION(
    [COMPILER_ACCEPTS_GNUXX14],
    [gnuplusplus14],  [-std=gnu++14])
MYAC_CHECK_EXTRA_COMPILER_OPTION(
    [COMPILER_ACCEPTS_GNUXX11],
    [gnuplusplus11],  [-std=gnu++11])
MYAC_CHECK_EXTRA_COMPILER_OPTION(
    [COMPILER_ACCEPTS_CXX11],
    [cplusplus11],  [-std=c++11])
MYAC_CHECK_EXTRA_COMPILER_OPTION(
    [COMPILER_ACCEPTS_CXX0X],
    [cplusplus0x],  [-std=c++0x])
AC_MSG_CHECKING([Compiler Accepts c++11])
[if test "x${myac_cf_gnuplusplus14_enabled}y" = "xTRUEy" ; then]
    [myac_cf_stdcxx_enabled=TRUE]
    [CXXFLAGS_ENABLE_STDCXX="${COMPILER_ACCEPTS_GNUXX14}"]
[elif test "x${myac_cf_gnuplusplus11_enabled}y" = "xTRUEy" ; then]
    [myac_cf_stdcxx_enabled=TRUE]
    [CXXFLAGS_ENABLE_STDCXX="${COMPILER_ACCEPTS_GNUXX11}"]
[elif test "x${myac_cf_cplusplus11_enabled}y" = "xTRUEy" ; then]
    [myac_cf_stdcxx_enabled=TRUE]
    [CXXFLAGS_ENABLE_STDCXX="${COMPILER_ACCEPTS_CXX11}"]
[elif test "x${myac_cf_cplusplus0x_enabled}y" = "xTRUEy" ; then]
    [myac_cf_stdcxx_enabled=TRUE]
    [CXXFLAGS_ENABLE_STDCXX="${COMPILER_ACCEPTS_CXX0X}"]
[else]
    [myac_cf_stdcxx_enabled=FALSE]
[fi]
[if test "x${myac_cf_stdcxx_enabled}y" = "xTRUEy" ; then]
    [CXXFLAGS="${CXXFLAGS}  ${CXXFLAGS_ENABLE_STDCXX}"]
    AC_MSG_RESULT([YES : ${CXXFLAGS_ENABLE_STDCXX}])
[else]
    AC_MSG_RESULT([NO])
[fi]

