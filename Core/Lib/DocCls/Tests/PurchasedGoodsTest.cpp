﻿//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
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

#include    "SetupTestData.inl"


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
    CPPUNIT_TEST(testToString1);
    CPPUNIT_TEST(testWriteToString4);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testPurchasedGoods();
    void  testToString1();
    void  testWriteToString4();
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

void  PurchasedGoodsTest::testToString1()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;
    setupPurchasedGoods1(testee);

    const  std::string  ret = testee.toString();

    CPPUNIT_ASSERT_EQUAL(
            std::string("Head1;Cate1;Product1;1280;2;10;1;2"),
            ret
    );

    return;
}

void  PurchasedGoodsTest::testWriteToString4()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;

    testee.accountHeadings  = static_cast<CategoryHandle>(11);
    testee.accountCategory  = static_cast<CategoryHandle>(12);
    testee.productName      = "Deposit";
    testee.unitPrice        = static_cast<CurrencyNumerator>(30000);
    testee.nQuantity        = static_cast<int>(1);
    testee.cDiscount        = static_cast<CurrencyNumerator>(0);
    testee.exclusiveTaxVal  = static_cast<CurrencyNumerator>(0);
    testee.inclusiveTaxVal  = static_cast<CurrencyNumerator>(0);
    testee.cSubTotal        = static_cast<CurrencyNumerator>(30000);

    std::stringstream   ss;
    testee.writeToStream(ss);

    CPPUNIT_ASSERT_EQUAL(
            std::string("Head4;Cate4;Deposit;30000;1;0;0;0"),
            ss.str()
    );

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
