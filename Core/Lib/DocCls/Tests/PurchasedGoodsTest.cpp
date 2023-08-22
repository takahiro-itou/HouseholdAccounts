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

#include    <sstream>

#include    "SetupTestData.inl"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

namespace  {

static  const   std::string
TEST_CASE_1_EXPECTED_STRING("Head1;Cate1;Product1;1280;2;10;1;2");

static  const   std::string
TEST_CASE_2_EXPECTED_STRING("Head2;Cate2;Product2;200;1;20;3;7");

static  const   std::string
TEST_CASE_3_EXPECTED_STRING("Head3;Cate3;Points;10;1;0;0;0");

static  const   std::string
TEST_CASE_4_EXPECTED_STRING("Head1;Cate1;Discounts;20;1;0;0;0");

}   //  End of (Unnamed) namespace.

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
    CPPUNIT_TEST(testToString5);
    CPPUNIT_TEST(testWriteToStream1);
    CPPUNIT_TEST(testWriteToStream2);
    CPPUNIT_TEST(testWriteToStream3);
    CPPUNIT_TEST(testWriteToStream4);
    CPPUNIT_TEST(testWriteToStream5);
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
    void  testToString5();
    void  testWriteToStream1();
    void  testWriteToStream2();
    void  testWriteToStream3();
    void  testWriteToStream4();
    void  testWriteToStream5();
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
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_1_EXPECTED_STRING, ret);

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
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_2_EXPECTED_STRING, ret);

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
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_3_EXPECTED_STRING, ret);

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
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_4_EXPECTED_STRING, ret);

    return;
}

void  PurchasedGoodsTest::testToString5()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;
    setupPurchasedGoods5(testee);

    const  std::string  ret = testee.toString();

    CPPUNIT_ASSERT_EQUAL(
            std::string("Head4;Cate4;Deposit;30000;1;0;0;0"),
            ret
    );

    return;
}

void  PurchasedGoodsTest::testWriteToStream1()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;
    setupPurchasedGoods1(testee);

    std::stringstream   ss;
    testee.writeToStream(ss);
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_1_EXPECTED_STRING, ss.str());

    return;
}

void  PurchasedGoodsTest::testWriteToStream2()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;
    setupPurchasedGoods2(testee);

    std::stringstream   ss;
    testee.writeToStream(ss);
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_2_EXPECTED_STRING, ss.str());

    return;
}

void  PurchasedGoodsTest::testWriteToStream3()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;
    setupPurchasedGoods3(testee);

    std::stringstream   ss;
    testee.writeToStream(ss);
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_3_EXPECTED_STRING, ss.str());

    return;
}

void  PurchasedGoodsTest::testWriteToStream4()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;
    setupPurchasedGoods4(testee);

    std::stringstream   ss;
    testee.writeToStream(ss);
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_4_EXPECTED_STRING, ss.str());

    return;
}

void  PurchasedGoodsTest::testWriteToStream5()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    PurchasedGoods      testee;
    testee.pCatMan  = &cateMan;
    setupPurchasedGoods5(testee);

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
