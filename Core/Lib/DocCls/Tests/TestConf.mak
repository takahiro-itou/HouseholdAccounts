
##
##    List of Tests.
##

EXTRATESTS              =
TESTS                   =  \
        BookCategoryTest           \
        BookDocumentTest           \
        CategoryManagerTest        \
        PurchasedGoodsTest         \
        ReceiptEntriesChunkTest    \
        ReceiptInfoTest            \
        StringTableTest            \
        ${EXTRATESTS}
##
##    Test Configurations.
##

TARGET_TESTEE_LIBRARY       +=  -lhacDocCls

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

BookCategoryTest_SOURCES         =  BookCategoryTest.cpp
BookDocumentTest_SOURCES         =  BookDocumentTest.cpp
CategoryManagerTest_SOURCES      =  CategoryManagerTest.cpp
PurchasedGoodsTest_SOURCES       =  PurchasedGoodsTest.cpp
ReceiptEntriesChunkTest_SOURCES  =  ReceiptEntriesChunkTest.cpp
ReceiptInfoTest_SOURCES          =  ReceiptInfoTest.cpp
StringTableTest_SOURCES          =  StringTableTest.cpp

