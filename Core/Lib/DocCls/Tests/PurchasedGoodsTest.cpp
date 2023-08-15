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

#include    "Account/DocCls/CategoryManager.h"


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
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST(testWriteToString);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    typedef     DocCls::CategoryManager     CategoryManager;

    Boolean
    setupCategoryManager1(
            CategoryManager &cateMan);

private:
    void  testPurchasedGoods();
    void  testToString();
    void  testWriteToString();
};

CPPUNIT_TEST_SUITE_REGISTRATION( PurchasedGoodsTest );

//========================================================================
//
//    For Internal Use Only.
//

Boolean
PurchasedGoodsTest::setupCategoryManager1(
        CategoryManager &cateMan)
{
    cateMan.reserveRootCategories(CategoryHandle(1));
    cateMan.setupRootCategory(
            CategoryHandle(0), "支出",
            DocCls::CategoryFlags::CTYPE_OUTLAY,
            DateSerial(0),
            Common::DecimalCurrency(0));

    cateMan.insertNewCategory(
            CategoryHandle(0), "Head1",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(1), "Cate1",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    return ( Boolean::BOOL_TRUE );
}

//========================================================================
//
//    Tests.
//

void  PurchasedGoodsTest::testPurchasedGoods()
{
    PurchasedGoods  testee;

    return;
}

void  PurchasedGoodsTest::testToString()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods  testee;

    testee.accountHeadings  = static_cast<CategoryHandle>(1);
    testee.accountCategory  = static_cast<CategoryHandle>(2);
    testee.productName      = "Product1";
    testee.unitPrice        = static_cast<CurrencyNumerator>(128);
    testee.nQuantity        = static_cast<int>(2);
    testee.cDiscount        = static_cast<CurrencyNumerator>(10);
    testee.exclusiveTaxVal  = static_cast<CurrencyNumerator>(1);
    testee.inclusiveTaxVal  = static_cast<CurrencyNumerator>(2);
    testee.cSubTotal        = static_cast<CurrencyNumerator>(256 - 10 + 1);
    testee.pCatMan          = &cateMan;

    const  std::string  ret = testee.toString();

    CPPUNIT_ASSERT_EQUAL(
            std::string("Head1;Cate1;Product1;128;2;10;1;2"),
            ret
    );

    return;
}

void  PurchasedGoodsTest::testWriteToString()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods  testee;

    testee.accountHeadings  = static_cast<CategoryHandle>(1);
    testee.accountCategory  = static_cast<CategoryHandle>(2);
    testee.productName      = "Product1";
    testee.unitPrice        = static_cast<CurrencyNumerator>(3000);
    testee.nQuantity        = static_cast<int>(1);
    testee.cDiscount        = static_cast<CurrencyNumerator>(10);
    testee.exclusiveTaxVal  = static_cast<CurrencyNumerator>(3);
    testee.inclusiveTaxVal  = static_cast<CurrencyNumerator>(7);
    testee.cSubTotal        = static_cast<CurrencyNumerator>(3000 - 10 + 3);
    testee.pCatMan          = &cateMan;

    std::stringstream   ss;
    testee.writeToStream(ss);

    CPPUNIT_ASSERT_EQUAL(
            std::string("Head1;Cate1;Product1;3000;1;10;3;7"),
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
