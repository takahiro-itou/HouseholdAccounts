
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

add_test(
    NAME        CategoryManagerTest
    COMMAND     $<TARGET_FILE:CategoryManagerTest>
)

add_test(
    NAME        StringTableTest
    COMMAND     $<TARGET_FILE:StringTableTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

add_executable(BookCategoryTest     BookCategoryTest.cpp)
add_executable(BookDocumentTest     BookDocumentTest.cpp)
add_executable(CategoryManagerTest  CategoryManagerTest.cpp)
add_executable(StringTableTest      StringTableTest.cpp)

