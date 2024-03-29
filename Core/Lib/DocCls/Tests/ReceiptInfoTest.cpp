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
**      An Implementation of Test Case 'ReceiptInfo'.
**
**      @file       DocCls/Tests/ReceiptInfoTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/DocCls/ReceiptInfo.h"

#include    <sstream>

#include    "SetupTestData.inl"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

namespace  {

static  const   std::string
TEST_CASE_1_EXPECTED_STRING(
        "2023/03/01;09:00;SHOP A;"
        "支出;現金;;Head1;Cate1;Product1;234;2;0;0;0\n"
        ";;;;;;Head2;Cate2;Product2;300;1;10;3;7\n"
        ";;;収入;ポイント;;Head3;Cate3;Points;10;1;0;0;0"
);

static  const   std::string
TEST_CASE_2_EXPECTED_STRING(
        "2023/03/01;09:00;SHOP A;"
        "支出;現金;;Head1;Cate1;Product1;1280;2;10;1;2\n"
        ";;;;;;Head2;Cate2;Product2;200;1;20;3;7\n"
        ";;;収入;ポイント;;Head3;Cate3;Points;10;1;0;0;0\n"
        ";;;;;;Head1;Cate1;Discounts;20;1;0;0;0"
);

static  const   std::string
TEST_CASE_3_EXPECTED_STRING(
        "2023/03/02;*****;SHOP B;"
        "複式;現金;Bank 1;Head4;Cate4;Deposit;30000;1;0;0;0"
);

}   //  End of (Unnamed) namespace.

//  クラスの前方宣言。  //

//========================================================================
//
//    ReceiptInfoTest  class.
//
/**
**    クラス ReceiptInfo  の単体テスト。
**/

class  ReceiptInfoTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(ReceiptInfoTest);
    CPPUNIT_TEST(testReceiptInfo);
    CPPUNIT_TEST(testToString1);
    CPPUNIT_TEST(testToString2);
    CPPUNIT_TEST(testToString3);
    CPPUNIT_TEST(testWriteToStream1);
    CPPUNIT_TEST(testWriteToStream2);
    CPPUNIT_TEST(testWriteToStream3);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testReceiptInfo();
    void  testToString1();
    void  testToString2();
    void  testToString3();
    void  testWriteToStream1();
    void  testWriteToStream2();
    void  testWriteToStream3();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ReceiptInfoTest );

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Tests.
//

void  ReceiptInfoTest::testReceiptInfo()
{
    ReceiptInfo     testee;

    return;
}

void  ReceiptInfoTest::testToString1()
{
    CategoryManager     catMan;
    setupCategoryManager1(catMan);

    ReceiptInfo     testee;
    setupReceiptInfo1(catMan, testee);

    const  std::string  ret = testee.toString();
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_1_EXPECTED_STRING, ret);

    return;
}

void  ReceiptInfoTest::testToString2()
{
    CategoryManager     catMan;
    setupCategoryManager1(catMan);

    ReceiptInfo     testee;
    setupReceiptInfo2(catMan, testee);

    const  std::string  ret = testee.toString();
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_2_EXPECTED_STRING, ret);

    return;
}

void  ReceiptInfoTest::testToString3()
{
    CategoryManager     catMan;
    setupCategoryManager1(catMan);

    ReceiptInfo     testee;
    setupReceiptInfo3(catMan, testee);

    const  std::string  ret = testee.toString();
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_3_EXPECTED_STRING, ret);

    return;
}

void  ReceiptInfoTest::testWriteToStream1()
{
    CategoryManager     catMan;
    setupCategoryManager1(catMan);

    ReceiptInfo     testee;
    setupReceiptInfo1(catMan, testee);

    std::stringstream   ss;
    testee.writeToStream(ss);
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_1_EXPECTED_STRING, ss.str());

    return;
}

void  ReceiptInfoTest::testWriteToStream2()
{
    CategoryManager     catMan;
    setupCategoryManager1(catMan);

    ReceiptInfo     testee;
    setupReceiptInfo2(catMan, testee);

    std::stringstream   ss;
    testee.writeToStream(ss);
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_2_EXPECTED_STRING, ss.str());

    return;
}

void  ReceiptInfoTest::testWriteToStream3()
{
    CategoryManager     catMan;
    setupCategoryManager1(catMan);

    ReceiptInfo     testee;
    setupReceiptInfo3(catMan, testee);

    std::stringstream   ss;
    testee.writeToStream(ss);
    CPPUNIT_ASSERT_EQUAL(TEST_CASE_3_EXPECTED_STRING, ss.str());

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
