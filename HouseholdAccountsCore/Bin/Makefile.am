
##
##    バイナリのビルドとインストール。
##

##
##    List of Directories.
##

MODULE_DIR_NAME         =  Binary
SUBDIRS                 =  .

include  $(top_srcdir)/.M4/Makefile.DirList.inc

##
##    List of Source and Header Files.
##

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
AM_LDFLAGS              =  -L${LIBTOP_BINARY_DIR}

##
##    List of Installs.
##

bin_PROGRAMS            =  \
        BookViewer

##
##    Build Executables.
##

BookViewer_SOURCES      =  BookViewer.cpp
BookViewer_LDADD        =

