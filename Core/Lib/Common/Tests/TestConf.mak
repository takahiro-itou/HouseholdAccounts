
##
##    List of Tests.
##

EXTRATESTS              =
TESTS                   =  \
        AccountsProjectTest     \
        DateTimeFormatTest      \
        DecimalCurrencyTest     \
        EnumBitFlagTest         \
        StrictTypesTest         \
        StrictVectorTest        \
        TextParserTest          \
        ${EXTRATESTS}
##
##    Test Configurations.
##

TARGET_TESTEE_LIBRARY       +=  -lhabCommon

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

AccountsProjectTest_SOURCES     =  AccountsProjectTest.cpp
DateTimeFormatTest_SOURCES      =  DateTimeFormatTest.cpp
DecimalCurrencyTest_SOURCES     =  DecimalCurrencyTest.cpp
EnumBitFlagTest_SOURCES         =  EnumBitFlagTest.cpp
StrictTypesTest_SOURCES         =  StrictTypesTest.cpp
StrictVectorTest_SOURCES        =  StrictVectorTest.cpp
TextParserTest_SOURCES          =  TextParserTest.cpp

