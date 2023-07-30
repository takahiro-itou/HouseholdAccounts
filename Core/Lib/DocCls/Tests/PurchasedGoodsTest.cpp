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
**      An Implementation of Test Case 'PurchasedGoods'.
**
**      @file       DocCls/Tests/PurchasedGoodsTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/DocCls/PurchasedGoods.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    PurchasedGoodsTest  class.
//
/**
**    クラス PurchasedGoods の単体テスト。
**/

class  PurchasedGoodsTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(PurchasedGoodsTest);
    CPPUNIT_TEST(testPurchasedGoods);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testPurchasedGoods();
};

CPPUNIT_TEST_SUITE_REGISTRATION( PurchasedGoodsTest );

//========================================================================
//
//    Tests.
//

void  PurchasedGoodsTest::testPurchasedGoods()
{
    PurchasedGoods  testee;

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
