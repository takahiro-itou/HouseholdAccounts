//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Household Accounts Core.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2023, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING and LICENSE files)                    **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of Test Case 'BookCategory'.
**
**      @file       DocCls/Tests/BookCategoryTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/DocCls/BookCategory.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    BookCategoryTest  class.
//
/**
**    クラス BookCategory の単体テスト。
**/

class  BookCategoryTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(BookCategoryTest);
    CPPUNIT_TEST(testBookCategory);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testBookCategory();
};

CPPUNIT_TEST_SUITE_REGISTRATION( BookCategoryTest );

//========================================================================
//
//    Tests.
//

void  BookCategoryTest::testBookCategory()
{
    BookCategory    testee;
    return;
}

}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
