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
**      An Implementation of Test Case 'BookDocument'.
**
**      @file       Documents/Tests/BookDocumentTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/Documents/BookDocument.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Documents  {

//  クラスの前方宣言。  //

//========================================================================
//
//    BookDocumentTest  class.
//
/**
**    クラス BookDocument の単体テスト。
**/

class  BookDocumentTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(BookDocumentTest);
    CPPUNIT_TEST(testBookDocument);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testBookDocument();
};

CPPUNIT_TEST_SUITE_REGISTRATION( BookDocumentTest );

//========================================================================
//
//    Tests.
//

void  BookDocumentTest::testBookDocument()
{
    BookDocument    docFile;
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
