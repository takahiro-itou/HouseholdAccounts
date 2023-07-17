
##----------------------------------------------------------------
##
##    テストの設定。
##

Add_Test (NAME  BookFileTest
    COMMAND  $<TARGET_FILE:BookFileTest>
)

Add_Test (NAME  ReceiptFileTest
    COMMAND  $<TARGET_FILE:ReceiptFileTest>
)

##----------------------------------------------------------------
##
##    テストプログラムのビルド。
##

Add_Executable (BookFileTest     BookFileTest.cpp)
Add_Executable (ReceiptFileTest  ReceiptFileTest.cpp)

