//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Household Accounts Core.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2022, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING and LICENSE files)                    **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of Test Case 'BookFile'.
**
**      @file       FileFormat/Tests/BookFileTest.cpp
**/

#include    "TestDriver.h"
#include    "HouseholdAccounts/FileFormat/BookFile.h"

HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  FileFormat  {

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

}   //  End of namespace  FileFormat
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
