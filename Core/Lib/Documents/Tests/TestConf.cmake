
##----------------------------------------------------------------
##
##    テストの設定。
##

Add_Test (NAME  BookDocumentTest
    COMMAND  $<TARGET_FILE:BookDocumentTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

Add_Executable (BookDocumentTest  BookDocumentTest.cpp)

