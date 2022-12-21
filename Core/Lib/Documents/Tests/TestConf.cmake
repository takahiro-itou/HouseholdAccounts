
##----------------------------------------------------------------
##
##    テストの設定。
##

add_test(
    NAME        BookCategoryTest
    COMMAND     $<TARGET_FILE:BookCategoryTest>
)

add_test(
    NAME        BookDocumentTest
    COMMAND     $<TARGET_FILE:BookDocumentTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(BookCategoryTest     BookCategoryTest.cpp)

add_executable(BookDocumentTest     BookDocumentTest.cpp)

