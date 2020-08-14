
##----------------------------------------------------------------
##
##    テストの設定。
##

Add_Test (NAME  BookFileTest
    COMMAND  $<TARGET_FILE:BookFileTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

Add_Executable (BookFileTest  BookFileTest.cpp)

