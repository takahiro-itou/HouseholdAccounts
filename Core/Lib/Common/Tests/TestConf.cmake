
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(
    NAME        AccountsProjectTest
    COMMAND     $<TARGET_FILE:AccountsProjectTest>
)

add_test(
    NAME        DecimalCurrencyTest
    COMMAND     $<TARGET_FILE:DecimalCurrencyTest>
)

add_test(
    NAME        EnumBitFlagTest
    COMMAND     $<TARGET_FILE:EnumBitFlagTest>
)

add_test(
    NAME        StrictIntegerTest
    COMMAND     $<TARGET_FILE:StrictIntegerTest>
)

add_test(
    NAME        TextParserTest
    COMMAND     $<TARGET_FILE:TextParserTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(AccountsProjectTest  AccountsProjectTest.cpp)
add_executable(DecimalCurrencyTest  DecimalCurrencyTest.cpp)
add_executable(EnumBitFlagTest      EnumBitFlagTest.cpp)
add_executable(StrictIntegerTest    StrictIntegerTest.cpp)
add_executable(TextParserTest       TextParserTest.cpp)

