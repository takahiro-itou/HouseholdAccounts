
##----------------------------------------------------------------
##
##    テストの設定。
##

Add_Test (NAME  HouseholdAccountsSettingsTest
    COMMAND  $<TARGET_FILE:HouseholdAccountsSettingsTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

Add_Executable (HouseholdAccountsSettingsTest  HouseholdAccountsSettingsTest.cpp)

