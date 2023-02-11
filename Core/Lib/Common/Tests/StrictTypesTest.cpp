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
**      An Implementation of Test Case 'StrictTypes'.
**
**      @file       Common/Tests/StrictTypesTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/Common/StrictTypes.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //
struct  tagInt;

//========================================================================
//
//    StrictTypesTest  class.
//
/**
**    クラス StrictTypes  の単体テスト。
**/

class  StrictTypesTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(StrictTypesTest);
    CPPUNIT_TEST(testStrictTypes);
    CPPUNIT_TEST(testOpeAssign);
    CPPUNIT_TEST(testOpePreIncrement);
    CPPUNIT_TEST(testOpePostIncrement);
    CPPUNIT_TEST(testOpePreDecrement);
    CPPUNIT_TEST(testOpePostDecrement);
    CPPUNIT_TEST(testOpeMul);
    CPPUNIT_TEST(testOpeDiv);
    CPPUNIT_TEST(testOpeMod);
    CPPUNIT_TEST(testOpeAdd);
    CPPUNIT_TEST(testOpeSub);
    CPPUNIT_TEST(testOpeShl);
    CPPUNIT_TEST(testOpeShr);
    CPPUNIT_TEST(testOpeAnd);
    CPPUNIT_TEST(testOpeXor);
    CPPUNIT_TEST(testOpeOr);
    CPPUNIT_TEST(testOpeCmpEqual);
    CPPUNIT_TEST(testOpeCmpNotEqual);
    CPPUNIT_TEST(testOpeCmpLt);
    CPPUNIT_TEST(testOpeCmpLe);
    CPPUNIT_TEST(testOpeCmpGt);
    CPPUNIT_TEST(testOpeCmpGe);
    CPPUNIT_TEST_SUITE_END();

private:
    typedef     StrictTypes<int, tagInt>    TestTarget;

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testStrictTypes();
    void  testOpeAssign();
    void  testOpePreIncrement();
    void  testOpePostIncrement();
    void  testOpePreDecrement();
    void  testOpePostDecrement();
    void  testOpeMul();
    void  testOpeDiv();
    void  testOpeMod();
    void  testOpeAdd();
    void  testOpeSub();
    void  testOpeShl();
    void  testOpeShr();
    void  testOpeAnd();
    void  testOpeXor();
    void  testOpeOr ();
    void  testOpeCmpEqual();
    void  testOpeCmpNotEqual();
    void  testOpeCmpLt();
    void  testOpeCmpLe();
    void  testOpeCmpGt();
    void  testOpeCmpGe();
};

CPPUNIT_TEST_SUITE_REGISTRATION( StrictTypesTest );

//========================================================================
//
//    Tests.
//

void  StrictTypesTest::testStrictTypes()
{
    TestTarget  testee1;
    TestTarget  testee2(100);
    TestTarget  testee3(testee2);

    CPPUNIT_ASSERT_EQUAL(  0, testee1.m_cValue);
    CPPUNIT_ASSERT_EQUAL(100, testee2.m_cValue);
    CPPUNIT_ASSERT_EQUAL(100, testee3.m_cValue);

    return;
}

void  StrictTypesTest::testOpeAssign()
{
    TestTarget  testee1(100);
    TestTarget  testee2;

    CPPUNIT_ASSERT_EQUAL(100, testee1.m_cValue);
    CPPUNIT_ASSERT_EQUAL(  0, testee2.m_cValue);

    testee2 = testee1;

    CPPUNIT_ASSERT_EQUAL(100, testee1.m_cValue);
    CPPUNIT_ASSERT_EQUAL(100, testee2.m_cValue);

    return;
}

void  StrictTypesTest::testOpePreIncrement()
{
    TestTarget  testee(110);
    TestTarget  result;

    CPPUNIT_ASSERT_EQUAL(110, testee.m_cValue);

    result = ++ testee;

    CPPUNIT_ASSERT_EQUAL(111, testee.m_cValue);
    CPPUNIT_ASSERT_EQUAL(111, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpePostIncrement()
{
    TestTarget  testee(120);
    TestTarget  result;

    CPPUNIT_ASSERT_EQUAL(120, testee.m_cValue);

    result = testee ++;

    CPPUNIT_ASSERT_EQUAL(121, testee.m_cValue);
    CPPUNIT_ASSERT_EQUAL(120, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpePreDecrement()
{
    TestTarget  testee(200);
    TestTarget  result;

    CPPUNIT_ASSERT_EQUAL(200, testee.m_cValue);

    result = -- testee;

    CPPUNIT_ASSERT_EQUAL(199, testee.m_cValue);
    CPPUNIT_ASSERT_EQUAL(199, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpePostDecrement()
{
    TestTarget  testee(300);
    TestTarget  result;

    CPPUNIT_ASSERT_EQUAL(300, testee.m_cValue);

    result = testee --;

    CPPUNIT_ASSERT_EQUAL(299, testee.m_cValue);
    CPPUNIT_ASSERT_EQUAL(300, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpeMul()
{
    TestTarget  testee1(100);
    TestTarget  testee2( 30);
    TestTarget  result;

    result  = testee1 * testee2;
    CPPUNIT_ASSERT_EQUAL(  3000, result.m_cValue);

    result  *= testee1;
    CPPUNIT_ASSERT_EQUAL(300000, result.m_cValue);

    result  = testee1 * 50;
    CPPUNIT_ASSERT_EQUAL(  5000, result.m_cValue);

    result  *= 70;
    CPPUNIT_ASSERT_EQUAL(350000, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpeDiv()
{
    TestTarget  testee1(10000);
    TestTarget  testee2(   30);
    TestTarget  testee3(   20);
    TestTarget  result;

    result  = testee1 / testee2;
    CPPUNIT_ASSERT_EQUAL(333, result.m_cValue);

    result  /= testee3;
    CPPUNIT_ASSERT_EQUAL( 16, result.m_cValue);

    result  = testee1 / 50;
    CPPUNIT_ASSERT_EQUAL(200, result.m_cValue);

    result  /= 70;
    CPPUNIT_ASSERT_EQUAL(  2, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpeMod()
{
    TestTarget  testee1(10000);
    TestTarget  testee2(  159);
    TestTarget  testee3(   35);
    TestTarget  result;

    result  = testee1 % testee2;
    CPPUNIT_ASSERT_EQUAL(142, result.m_cValue);

    result  %= testee3;
    CPPUNIT_ASSERT_EQUAL(  2, result.m_cValue);

    result  = testee1 % 70;
    CPPUNIT_ASSERT_EQUAL( 60, result.m_cValue);

    result  %= 50;
    CPPUNIT_ASSERT_EQUAL( 10, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpeAdd()
{
    TestTarget  testee1(100);
    TestTarget  testee2( 30);
    TestTarget  result;

    result  = testee1 + testee2;
    CPPUNIT_ASSERT_EQUAL(130, result.m_cValue);

    result  += testee1;
    CPPUNIT_ASSERT_EQUAL(230, result.m_cValue);

    result  = testee1 + 50;
    CPPUNIT_ASSERT_EQUAL(150, result.m_cValue);

    result  += 70;
    CPPUNIT_ASSERT_EQUAL(220, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpeSub()
{
    TestTarget  testee1(200);
    TestTarget  testee2( 30);
    TestTarget  result;

    result  = testee1 - testee2;
    CPPUNIT_ASSERT_EQUAL(170, result.m_cValue);

    result  -= testee1;
    CPPUNIT_ASSERT_EQUAL(-30, result.m_cValue);

    result  = testee1 - 50;
    CPPUNIT_ASSERT_EQUAL(150, result.m_cValue);

    result  -= 70;
    CPPUNIT_ASSERT_EQUAL( 80, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpeShl()
{
    TestTarget  testee1(15);
    TestTarget  testee2( 2);
    TestTarget  testee3( 3);
    TestTarget  result;

    result  = testee1 << testee2;
    CPPUNIT_ASSERT_EQUAL( 60, result.m_cValue);

    result  <<= testee3;
    CPPUNIT_ASSERT_EQUAL(480, result.m_cValue);

    result  = testee1 << 4;
    CPPUNIT_ASSERT_EQUAL(240, result.m_cValue);

    result  <<= 2;
    CPPUNIT_ASSERT_EQUAL(960, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpeShr()
{
    TestTarget  testee1(1000);
    TestTarget  testee2(   2);
    TestTarget  testee3(   3);
    TestTarget  result;

    result  = testee1 >> testee2;
    CPPUNIT_ASSERT_EQUAL(250, result.m_cValue);

    result  >>= testee3;
    CPPUNIT_ASSERT_EQUAL( 31, result.m_cValue);

    result  = testee1 >> 4;
    CPPUNIT_ASSERT_EQUAL( 62, result.m_cValue);

    result  >>= 2;
    CPPUNIT_ASSERT_EQUAL( 15, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpeAnd()
{
    TestTarget  testee1(1020);
    TestTarget  testee2( 510);
    TestTarget  testee3( 121);
    TestTarget  result;

    result  = testee1 & testee2;
    CPPUNIT_ASSERT_EQUAL(508, result.m_cValue);

    result  &=  testee3;
    CPPUNIT_ASSERT_EQUAL(120, result.m_cValue);

    result  = testee1 & 499;
    CPPUNIT_ASSERT_EQUAL(496, result.m_cValue);

    result  &=  123;
    CPPUNIT_ASSERT_EQUAL(112, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpeXor()
{
    TestTarget  testee1(  20);
    TestTarget  testee2( 312);
    TestTarget  testee3( 121);
    TestTarget  result;

    result  = testee1 ^ testee2;
    CPPUNIT_ASSERT_EQUAL(300, result.m_cValue);

    result  ^=  testee3;
    CPPUNIT_ASSERT_EQUAL(341, result.m_cValue);

    result  = testee1 ^ 499;
    CPPUNIT_ASSERT_EQUAL(487, result.m_cValue);

    result  ^=  123;
    CPPUNIT_ASSERT_EQUAL(412, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpeOr()
{
    TestTarget  testee1(  20);
    TestTarget  testee2( 312);
    TestTarget  testee3( 121);
    TestTarget  result;

    result  = testee1 | testee2;
    CPPUNIT_ASSERT_EQUAL(316, result.m_cValue);

    result  |=  testee3;
    CPPUNIT_ASSERT_EQUAL(381, result.m_cValue);

    result  = testee1 | 499;
    CPPUNIT_ASSERT_EQUAL(503, result.m_cValue);

    result  |=  123;
    CPPUNIT_ASSERT_EQUAL(511, result.m_cValue);

    return;
}

void  StrictTypesTest::testOpeCmpEqual()
{
    TestTarget  testee1(300);
    TestTarget  testee2(300);
    TestTarget  testee3;

    CPPUNIT_ASSERT_EQUAL(true , testee1 == testee2);
    CPPUNIT_ASSERT_EQUAL(false, testee1 == testee3);

    CPPUNIT_ASSERT_EQUAL(true , testee1 == 300);
    CPPUNIT_ASSERT_EQUAL(true , 300 == testee1);

    CPPUNIT_ASSERT_EQUAL(false, testee1 == 0);
    CPPUNIT_ASSERT_EQUAL(false, 0 == testee1);

    return;
}

void  StrictTypesTest::testOpeCmpNotEqual()
{
    TestTarget  testee1(300);
    TestTarget  testee2(300);
    TestTarget  testee3;

    CPPUNIT_ASSERT_EQUAL(false, testee1 != testee2);
    CPPUNIT_ASSERT_EQUAL(true , testee1 != testee3);

    CPPUNIT_ASSERT_EQUAL(false, testee1 != 300);
    CPPUNIT_ASSERT_EQUAL(false, 300 != testee1);

    CPPUNIT_ASSERT_EQUAL(true , testee1 != 0);
    CPPUNIT_ASSERT_EQUAL(true , 0 != testee1);

    return;
}

void  StrictTypesTest::testOpeCmpLt()
{
    TestTarget  testee1(100);
    TestTarget  testee2( 99);
    TestTarget  testee3(100);
    TestTarget  testee4(101);

    CPPUNIT_ASSERT_EQUAL(false, testee1 < testee2);
    CPPUNIT_ASSERT_EQUAL(false, testee1 < testee3);
    CPPUNIT_ASSERT_EQUAL(true , testee1 < testee4);

    CPPUNIT_ASSERT_EQUAL(true , testee2 < testee1);
    CPPUNIT_ASSERT_EQUAL(false, testee3 < testee1);
    CPPUNIT_ASSERT_EQUAL(false, testee4 < testee1);

    CPPUNIT_ASSERT_EQUAL(false, testee1 <  99);
    CPPUNIT_ASSERT_EQUAL(false, testee1 < 100);
    CPPUNIT_ASSERT_EQUAL(true , testee1 < 101);

    CPPUNIT_ASSERT_EQUAL(true ,  99 < testee1);
    CPPUNIT_ASSERT_EQUAL(false, 100 < testee1);
    CPPUNIT_ASSERT_EQUAL(false, 101 < testee1);

    return;
}

void  StrictTypesTest::testOpeCmpLe()
{
    TestTarget  testee1(200);
    TestTarget  testee2(199);
    TestTarget  testee3(200);
    TestTarget  testee4(201);

    CPPUNIT_ASSERT_EQUAL(false, testee1 <= testee2);
    CPPUNIT_ASSERT_EQUAL(true , testee1 <= testee3);
    CPPUNIT_ASSERT_EQUAL(true , testee1 <= testee4);

    CPPUNIT_ASSERT_EQUAL(true , testee2 <= testee1);
    CPPUNIT_ASSERT_EQUAL(true , testee3 <= testee1);
    CPPUNIT_ASSERT_EQUAL(false, testee4 <= testee1);

    CPPUNIT_ASSERT_EQUAL(false, testee1 <= 199);
    CPPUNIT_ASSERT_EQUAL(true , testee1 <= 200);
    CPPUNIT_ASSERT_EQUAL(true , testee1 <= 201);

    CPPUNIT_ASSERT_EQUAL(true , 199 <= testee1);
    CPPUNIT_ASSERT_EQUAL(true , 200 <= testee1);
    CPPUNIT_ASSERT_EQUAL(false, 201 <= testee1);

    return;
}

void  StrictTypesTest::testOpeCmpGt()
{
    TestTarget  testee1(300);
    TestTarget  testee2(299);
    TestTarget  testee3(300);
    TestTarget  testee4(301);

    CPPUNIT_ASSERT_EQUAL(true , testee1 > testee2);
    CPPUNIT_ASSERT_EQUAL(false, testee1 > testee3);
    CPPUNIT_ASSERT_EQUAL(false, testee1 > testee4);

    CPPUNIT_ASSERT_EQUAL(false, testee2 > testee1);
    CPPUNIT_ASSERT_EQUAL(false, testee3 > testee1);
    CPPUNIT_ASSERT_EQUAL(true , testee4 > testee1);

    CPPUNIT_ASSERT_EQUAL(true , testee1 > 299);
    CPPUNIT_ASSERT_EQUAL(false, testee1 > 300);
    CPPUNIT_ASSERT_EQUAL(false, testee1 > 301);

    CPPUNIT_ASSERT_EQUAL(false, 299 > testee1);
    CPPUNIT_ASSERT_EQUAL(false, 300 > testee1);
    CPPUNIT_ASSERT_EQUAL(true , 301 > testee1);

    return;
}

void  StrictTypesTest::testOpeCmpGe()
{
    TestTarget  testee1(300);
    TestTarget  testee2(299);
    TestTarget  testee3(300);
    TestTarget  testee4(301);

    CPPUNIT_ASSERT_EQUAL(true , testee1 >= testee2);
    CPPUNIT_ASSERT_EQUAL(true , testee1 >= testee3);
    CPPUNIT_ASSERT_EQUAL(false, testee1 >= testee4);

    CPPUNIT_ASSERT_EQUAL(false, testee2 >= testee1);
    CPPUNIT_ASSERT_EQUAL(true , testee3 >= testee1);
    CPPUNIT_ASSERT_EQUAL(true , testee4 >= testee1);

    CPPUNIT_ASSERT_EQUAL(true , testee1 >= 299);
    CPPUNIT_ASSERT_EQUAL(true , testee1 >= 300);
    CPPUNIT_ASSERT_EQUAL(false, testee1 >= 301);

    CPPUNIT_ASSERT_EQUAL(false, 299 >= testee1);
    CPPUNIT_ASSERT_EQUAL(true , 300 >= testee1);
    CPPUNIT_ASSERT_EQUAL(true , 301 >= testee1);

    return;
}

}   //  End of namespace  Common
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
