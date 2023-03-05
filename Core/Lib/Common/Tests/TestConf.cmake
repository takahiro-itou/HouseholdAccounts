
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(
    NAME        AccountsProjectTest
    COMMAND     $<TARGET_FILE:AccountsProjectTest>
)

add_test(
    NAME        DateTimeFormatTest
    COMMAND     $<TARGET_FILE:DateTimeFormatTest>
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
    NAME        StrictTypesTest
    COMMAND     $<TARGET_FILE:StrictTypesTest>
)

add_test(
    NAME        StrictVectorTest
    COMMAND     $<TARGET_FILE:StrictVectorTest>
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
add_executable(DateTimeFormatTest   DateTimeFormatTest.cpp)
add_executable(DecimalCurrencyTest  DecimalCurrencyTest.cpp)
add_executable(EnumBitFlagTest      EnumBitFlagTest.cpp)
add_executable(StrictTypesTest      StrictTypesTest.cpp)
add_executable(StrictVectorTest     StrictVectorTest.cpp)
add_executable(TextParserTest       TextParserTest.cpp)

