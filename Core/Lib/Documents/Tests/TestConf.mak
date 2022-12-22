
##
##    List of Tests.
##

EXTRATESTS              =
TESTS                   =      \
        BookCategoryTest       \
        BookDocumentTest       \
        CategoryManagerTest    \
        ${EXTRATESTS}
##
##    Test Configurations.
##

TARGET_TESTEE_LIBRARY       +=  ../libhacDocuments.a

DIST_NOINST_DATA_FILES      +=
DIST_NOINST_HEADER_FILES    +=
EXTRA_TEST_DRIVERS          +=
LIBRARY_TEST_DRIVERS        +=
SOURCE_TEST_DRIVERS         +=

##
##    Compile and Link Options.
##

TEST_CPPFLAGS_COMMON        +=
TEST_LDFLAGS_COMMON         +=

##
##    Test Programs.
##

BookCategoryTest_SOURCES     =  BookCategoryTest.cpp
BookDocumentTest_SOURCES     =  BookDocumentTest.cpp
CategoryManagerTest_SOURCES  =  CategoryManagerTest.cpp

