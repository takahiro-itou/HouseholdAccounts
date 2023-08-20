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
    CPPUNIT_TEST(testToString2);
    CPPUNIT_TEST(testToString3);
    CPPUNIT_TEST(testToString4);
    CPPUNIT_TEST(testWriteToString1);
    CPPUNIT_TEST(testWriteToString2);
    CPPUNIT_TEST(testWriteToString4);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testPurchasedGoods();
    void  testToString1();
    void  testToString2();
    void  testToString3();
    void  testToString4();
    void  testWriteToString1();
    void  testWriteToString2();
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

void  PurchasedGoodsTest::testToString2()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;
    setupPurchasedGoods2(testee);

    const  std::string  ret = testee.toString();

    CPPUNIT_ASSERT_EQUAL(
            std::string("Head2;Cate2;Product2;200;1;20;3;7"),
            ret
    );

    return;
}

void  PurchasedGoodsTest::testToString3()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;
    setupPurchasedGoods3(testee);

    const  std::string  ret = testee.toString();

    CPPUNIT_ASSERT_EQUAL(
            std::string("Head3;Cate3;Points;10;1;0;0;0"),
            ret
    );

    return;
}

void  PurchasedGoodsTest::testToString4()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;
    setupPurchasedGoods4(testee);

    const  std::string  ret = testee.toString();

    CPPUNIT_ASSERT_EQUAL(
            std::string("Head4;Cate4;Deposit;30000;1;0;0;0"),
            ret
    );

    return;
}

void  PurchasedGoodsTest::testWriteToString1()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;
    setupPurchasedGoods1(testee);

    std::stringstream   ss;
    testee.writeToStream(ss);

    CPPUNIT_ASSERT_EQUAL(
            std::string("Head1;Cate1;Product1;1280;2;10;1;2"),
            ss.str()
    );

    return;
}

void  PurchasedGoodsTest::testWriteToString2()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;
    setupPurchasedGoods2(testee);

    std::stringstream   ss;
    testee.writeToStream(ss);

    CPPUNIT_ASSERT_EQUAL(
            std::string("Head2;Cate2;Product2;200;1;20;3;7"),
            ss.str()
    );

    return;
}

void  PurchasedGoodsTest::testWriteToString4()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;
    setupPurchasedGoods4(testee);

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
