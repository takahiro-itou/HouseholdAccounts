
##
##    List of Tests.
##

EXTRATESTS              =
TESTS                   =  \
        HouseholdAccountsSettingsTest  \
        TextParserTest                 \
        ${EXTRATESTS}
##
##    Test Configurations.
##

TARGET_TESTEE_LIBRARY       +=  ../libhacCommon.a

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

HouseholdAccountsSettingsTest_SOURCES   =  HouseholdAccountsSettingsTest.cpp
TextParserTest_SOURCES                  =  TextParserTest.cpp

