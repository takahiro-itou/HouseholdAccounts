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
