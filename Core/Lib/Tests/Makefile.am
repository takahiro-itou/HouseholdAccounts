
##
##    ライブラリの単体テストドライバ。
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
##    List of Source and Header Files.
##

DIST_NOINST_DATA_FILES      +=  CMakeLists.txt
DIST_NOINST_HEADER_FILES    +=  TestDriver.h
EXTRA_TEST_DRIVERS          +=
LIBRARY_TEST_DRIVERS        +=  libTestDriver.a
SOURCE_TEST_DRIVERS         +=  TestDriver.cpp

##
##    Compile and Link Options.
##

TEST_CPPFLAGS_COMMON        +=
TEST_LDFLAGS_COMMON         +=

if  AMCNF_CPPUNIT_ENABLED
TEST_CPPFLAGS_XUNIT         =  @CPPUNIT_CPPFLAGS@
TEST_CFLAGS_XUNIT           =  @CPPUNIT_CFLAGS@
TEST_CXXFLAGS_XUNIT         =  @CPPUNIT_CXXFLAGS@
TEST_LDFLAGS_XUNIT          =  @CPPUNIT_LDFLAGS@
TEST_LINK_LDADD_XUNIT       =  @CPPUNIT_LINK_LDADD@
else
TEST_CPPFLAGS_XUNIT         =  @CPPUNIT_CPPFLAGS@
TEST_CFLAGS_XUNIT           =  @CPPUNIT_CFLAGS@
TEST_CXXFLAGS_XUNIT         =  @CPPUNIT_CXXFLAGS@
TEST_LDFLAGS_XUNIT          =  @CPPUNIT_LDFLAGS@
TEST_LINK_LDADD_XUNIT       =
endif

AM_CPPFLAGS         =  \
        -I${TESTEE_SOURCE_DIR}      \
        -I${INCTOP_SOURCE_DIR}      \
        -I${DRIVER_SOURCE_DIR}      \
        -I${DRIVER_BINARY_DIR}      \
        ${TEST_CPPFLAGS_COMMON}     \
        ${TEST_CPPFLAGS_XUNIT}

AM_CFLAGS           =  ${TEST_CFLAGS_XUNIT}
AM_CXXFLAGS         =  ${TEST_CXXFLAGS_XUNIT}
AM_LDFLAGS          =  \
        ${TEST_LDFLAGS_COMMON}   \
        ${TEST_LDFLAGS_XUNIT}

LDADD               =  \
        ${TEST_LINK_LDADD_XUNIT}

##
##    List of Installs.
##

check_PROGRAMS      =  ${TESTS}
noinst_LIBRARIES    =  ${LIBRARY_TEST_DRIVERS}

##
##    Include Common Install Settings.
##

include  $(top_srcdir)/.M4/Makefile.Install.inc

##
##    Build of Test Drivers.
##

libTestDriver_a_SOURCES     =  ${SOURCE_TEST_DRIVERS}

