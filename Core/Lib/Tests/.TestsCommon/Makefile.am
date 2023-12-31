
##
##    ライブラリの単体テスト。
##

##
##    List of Directories.
##

include  $(top_srcdir)/.M4/Makefile.DirList.inc

DRIVER_SOURCE_DIR       =  ${LIBTOP_SOURCE_DIR}/Tests
DRIVER_BINARY_DIR       =  ${LIBTOP_BINARY_DIR}/Tests
TESTEE_SOURCE_DIR       =  @srcdir@/..
TESTEE_BINARY_DIR       =  ..

##
##    Initialize Test Configurations.
##

TARGET_TESTEE_LIBRARY       =

DIST_NOINST_DATA_FILES      =
DIST_NOINST_HEADER_FILES    =
EXTRA_TEST_DRIVERS          =
LIBRARY_TEST_DRIVERS        =
SOURCE_TEST_DRIVERS         =

TEST_CPPFLAGS_COMMON        =
TEST_LDFLAGS_COMMON         =

##
##    Test Configurations.
##

include  $(srcdir)/TestConf.mak

##
##    Append Test Configurations.
##

DIST_NOINST_DATA_FILES      +=  CMakeLists.txt  TestConf.cmake
DIST_NOINST_HEADER_FILES    +=
EXTRA_TEST_DRIVERS          +=
LIBRARY_TEST_DRIVERS        +=  ${DRIVER_BINARY_DIR}/libTestDriver.a
SOURCE_TEST_DRIVERS         +=

##
##    Compile and Link Options.
##

TEST_CPPFLAGS_COMMON        +=
TEST_LDFLAGS_COMMON         +=

TEST_CPPFLAGS_XUNIT         =  @CPPUNIT_CPPFLAGS@
TEST_CFLAGS_XUNIT           =  @CPPUNIT_CFLAGS@
TEST_CXXFLAGS_XUNIT         =  @CPPUNIT_CXXFLAGS@
TEST_LDFLAGS_XUNIT          =  @CPPUNIT_LDFLAGS@

if  AMCNF_CPPUNIT_ENABLED
TEST_LINK_LDADD_XUNIT       =  @CPPUNIT_LINK_LDADD@
else
TEST_LINK_LDADD_XUNIT       =
endif

AM_CPPFLAGS         =  \
        -I${TESTEE_SOURCE_DIR}      \
        -I${INCTOP_SOURCE_DIR}      \
        -I${LIBTOP_SOURCE_DIR}      \
        -I${DRIVER_SOURCE_DIR}      \
        -I${DRIVER_BINARY_DIR}      \
        ${TEST_CPPFLAGS_COMMON}     \
        ${TEST_CPPFLAGS_XUNIT}

AM_CFLAGS           =  ${TEST_CFLAGS_XUNIT}
AM_CXXFLAGS         =  ${TEST_CXXFLAGS_XUNIT}
AM_LDFLAGS          =  \
        -L${LIBTOP_BINARY_DIR}  \
        ${TEST_LDFLAGS_COMMON}  \
        ${TEST_LDFLAGS_XUNIT}

LDADD               =  \
        ${TARGET_TESTEE_LIBRARY}  \
        ${LIBRARY_TEST_DRIVERS}   \
        ${TEST_LINK_LDADD_XUNIT}

##
##    List of Installs.
##

check_PROGRAMS      =  ${TESTS}

##
##    Include Common Install Settings.
##

include  $(top_srcdir)/.M4/Makefile.Install.inc

