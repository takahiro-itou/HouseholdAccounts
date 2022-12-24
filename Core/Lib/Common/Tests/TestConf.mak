
##
##    List of Tests.
##

EXTRATESTS              =
TESTS                   =  \
        DecimalCurrencyTest            \
        HouseholdAccountsSettingsTest  \
        TextParserTest                 \
        ${EXTRATESTS}
##
##    Test Configurations.
##

TARGET_TESTEE_LIBRARY       +=  -lhacCommon

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

DecimalCurrencyTest_SOURCES             =  DecimalCurrencyTest.cpp
HouseholdAccountsSettingsTest_SOURCES   =  HouseholdAccountsSettingsTest.cpp
TextParserTest_SOURCES                  =  TextParserTest.cpp

