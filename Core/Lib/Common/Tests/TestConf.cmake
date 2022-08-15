
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(
    NAME        HouseholdAccountsSettingsTest
    COMMAND     $<TARGET_FILE:HouseholdAccountsSettingsTest>
)

add_test(
    NAME        TextParserTest
    COMMAND     $<TARGET_FILE:TextParserTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(
    HouseholdAccountsSettingsTest
    HouseholdAccountsSettingsTest.cpp
)

add_executable(TextParserTest      TextParserTest.cpp)

