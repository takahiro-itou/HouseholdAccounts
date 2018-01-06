//  -*-  coding: utf-8; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Household Accounts Core.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2018, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of Test Case 'BookFile'.
**
**      @file       Documents/Tests/BookFileTest.cpp
**/

#include    "TestDriver.h"
#include    "HouseholdAccounts/Documents/BookFile.h"

HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Documents  {

//  クラスの前方宣言。  //

//========================================================================
//
//    BookFileTest  class.
//
/**
**    クラス BookFile の単体テスト。
**/

class  BookFileTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(BookFileTest);
    CPPUNIT_TEST(testBookFile);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testBookFile();
};

CPPUNIT_TEST_SUITE_REGISTRATION( BookFileTest );

//========================================================================
//
//    Tests.
//

void  BookFileTest::testBookFile()
{
    BookFile    bookFile;
    return;
}

}   //  End of namespace  Documents
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
