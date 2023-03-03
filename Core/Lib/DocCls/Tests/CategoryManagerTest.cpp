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
**      An Implementation of Test Case 'CategoryManager'.
**
**      @file       DocCls/Tests/CategoryManagerTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/DocCls/CategoryManager.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    CategoryManagerTest  class.
//
/**
**    クラス CategoryManager  の単体テスト。
**/

class  CategoryManagerTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(CategoryManagerTest);
    CPPUNIT_TEST(testCategoryManager);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testCategoryManager();
};

CPPUNIT_TEST_SUITE_REGISTRATION( CategoryManagerTest );

//========================================================================
//
//    Tests.
//

void  CategoryManagerTest::testCategoryManager()
{
    CategoryManager     testee;
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
