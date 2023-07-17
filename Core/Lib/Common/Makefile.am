
##
##    ライブラリのビルドとインストール。
##

##
##    List of Directories.
##

MODULE_DIR_NAME         =  Common
SUBDIRS                 =  .  Tests

include  $(top_srcdir)/.M4/Makefile.DirList.inc

##
##    List of Source and Header Files.
##

EXTRA_LIBRARY_SOURCE_FILES  =
EXTRA_LIBRARY_HEADER_FILES  =
EXTRA_NOINST_DATA_FILES     =
EXTRA_NOINST_HEADER_FILES   =

LIBRARY_SOURCE_FILES        =  \
        DateTimeFormat.cpp             \
        DecimalCurrency.cpp            \
        TextParser.cpp                 \
        ${EXTRA_LIBRARY_SOURCE_FILES}

LIBRARY_INSTANTIATIONS      =
LIBRARY_INLINE_FILES        =

DIST_NOINST_DATA_FILES      =  \
        CMakeLists.txt              \
        ${EXTRA_NOINST_DATA_FILES}

DIST_NOINST_HEADER_FILES    =  \
        ${EXTRA_NOINST_HEADER_FILES}

INCLIB_HEADER_FILES         =  \
        ${INCLIB_SOURCE_DIR}/AccountsProject.h      \
        ${INCLIB_SOURCE_DIR}/AccountsTypes.h        \
        ${INCLIB_SOURCE_DIR}/BookInterface.h        \
        ${INCLIB_SOURCE_DIR}/DateTimeFormat.h       \
        ${INCLIB_SOURCE_DIR}/DecimalCurrency.h      \
        ${INCLIB_SOURCE_DIR}/EnumBitFlag.h          \
        ${INCLIB_SOURCE_DIR}/StrictTypes.h          \
        ${INCLIB_SOURCE_DIR}/StrictTypes.inl        \
        ${INCLIB_SOURCE_DIR}/StrictVector.h         \
        ${INCLIB_SOURCE_DIR}/StrictVector.inl       \
        ${INCLIB_SOURCE_DIR}/TextParser.h           \
        ${EXTRA_LIBRARY_HEADER_FILES}

INCLIB_NODIST_HEADER_FILES  =

LIBRARY_INSTALL_SRCFILES    =  \
        ${LIBRARY_INLINE_FILES}

LIBRARY_COMPILE_SRCFILES    =  \
        ${LIBRARY_SOURCE_FILES}    \
        ${LIBRARY_INSTANTIATIONS}

##
##    List of Libraries.
##

STATIC_LIBRARIES_LIST   =  libhabCommon.a
SHARED_LIBRARIES_LIST   =

##
##    Internal Libraries.
##

##
##    Compile and Link Options.
##

AM_CPPFLAGS          =  \
        -I${INCTOP_SOURCE_DIR}
AM_CFLAGS               =
AM_CXXFLAGS             =

##
##    Include Common Install Settings.
##

include  $(top_srcdir)/.M4/Makefile.Install.inc

##
##    Build Libraries.
##

libhabCommon_a_SOURCES      =  ${LIBRARY_SOURCE_FILES}

