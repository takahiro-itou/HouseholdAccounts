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
**      An Implementation of Test Case 'StrictInteger'.
**
**      @file       Common/Tests/StrictIntegerTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/Common/StrictInteger.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //
struct  tagInt;

//========================================================================
//
//    StrictIntegerTest  class.
//
/**
**    クラス StrictInteger  の単体テスト。
**/

class  StrictIntegerTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(StrictIntegerTest);
    CPPUNIT_TEST(testStrictInteger);
    CPPUNIT_TEST(testOpeAssign);
    CPPUNIT_TEST(testOpePreIncrement);
    CPPUNIT_TEST(testOpePostIncrement);
    CPPUNIT_TEST(testOpePreDecrement);
    CPPUNIT_TEST(testOpePostDecrement);
    CPPUNIT_TEST(testOpeCmpEqual);
    CPPUNIT_TEST(testOpeCmpNotEqual);
    CPPUNIT_TEST(testOpeCmpLt);
    CPPUNIT_TEST_SUITE_END();

private:
    typedef     StrictInteger<int, tagInt>  TestTarget;

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testStrictInteger();
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

CPPUNIT_TEST_SUITE_REGISTRATION( StrictIntegerTest );

//========================================================================
//
//    Tests.
//

void  StrictIntegerTest::testStrictInteger()
{
    TestTarget  testee1;
    TestTarget  testee2(100);
    TestTarget  testee3(testee2);

    CPPUNIT_ASSERT_EQUAL(  0, testee1.m_cValue);
    CPPUNIT_ASSERT_EQUAL(100, testee2.m_cValue);
    CPPUNIT_ASSERT_EQUAL(100, testee3.m_cValue);

    return;
}

void  StrictIntegerTest::testOpeAssign()
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

void  StrictIntegerTest::testOpePreIncrement()
{
    TestTarget  testee(110);
    TestTarget  result;

    CPPUNIT_ASSERT_EQUAL(110, testee.m_cValue);

    result = ++ testee;

    CPPUNIT_ASSERT_EQUAL(111, testee.m_cValue);
    CPPUNIT_ASSERT_EQUAL(111, result.m_cValue);

    return;
}

void  StrictIntegerTest::testOpePostIncrement()
{
    TestTarget  testee(120);
    TestTarget  result;

    CPPUNIT_ASSERT_EQUAL(120, testee.m_cValue);

    result = testee ++;

    CPPUNIT_ASSERT_EQUAL(121, testee.m_cValue);
    CPPUNIT_ASSERT_EQUAL(120, result.m_cValue);

    return;
}

void  StrictIntegerTest::testOpePreDecrement()
{
    TestTarget  testee(200);
    TestTarget  result;

    CPPUNIT_ASSERT_EQUAL(200, testee.m_cValue);

    result = -- testee;

    CPPUNIT_ASSERT_EQUAL(199, testee.m_cValue);
    CPPUNIT_ASSERT_EQUAL(199, result.m_cValue);

    return;
}

void  StrictIntegerTest::testOpePostDecrement()
{
    TestTarget  testee(300);
    TestTarget  result;

    CPPUNIT_ASSERT_EQUAL(300, testee.m_cValue);

    result = testee --;

    CPPUNIT_ASSERT_EQUAL(299, testee.m_cValue);
    CPPUNIT_ASSERT_EQUAL(300, result.m_cValue);

    return;
}

void  StrictIntegerTest::testOpeCmpEqual()
{
    TestTarget  testee1(300);
    TestTarget  testee2(300);
    TestTarget  testee3;

    CPPUNIT_ASSERT_EQUAL(true,  testee1 == testee2);
    CPPUNIT_ASSERT_EQUAL(false, testee1 == testee3);

    CPPUNIT_ASSERT_EQUAL(true, testee1 == 300);
    CPPUNIT_ASSERT_EQUAL(true, 300 == testee1);

    CPPUNIT_ASSERT_EQUAL(false, testee1 == 0);
    CPPUNIT_ASSERT_EQUAL(false, 0 == testee1);

    return;
}

void  StrictIntegerTest::testOpeCmpNotEqual()
{
    TestTarget  testee1(300);
    TestTarget  testee2(300);
    TestTarget  testee3;

    CPPUNIT_ASSERT_EQUAL(false, testee1 != testee2);
    CPPUNIT_ASSERT_EQUAL(true,  testee1 != testee3);

    CPPUNIT_ASSERT_EQUAL(false, testee1 != 300);
    CPPUNIT_ASSERT_EQUAL(false, 300 != testee1);

    CPPUNIT_ASSERT_EQUAL(true,  testee1 != 0);
    CPPUNIT_ASSERT_EQUAL(true,  0 != testee1);

    return;
}

void  StrictIntegerTest::testOpeCmpLt()
{
    TestTarget  testee1(100);
    TestTarget  testee2(101);
    TestTarget  testee3(100);

    CPPUNIT_ASSERT_EQUAL(true , testee1 < testee2);
    CPPUNIT_ASSERT_EQUAL(false, testee2 < testee1);

    CPPUNIT_ASSERT_EQUAL(false, testee1 < testee3);
    CPPUNIT_ASSERT_EQUAL(false, testee3 < testee1);

    CPPUNIT_ASSERT_EQUAL(false, testee1 <  99);
    CPPUNIT_ASSERT_EQUAL(false, testee1 < 100);
    CPPUNIT_ASSERT_EQUAL(true , testee1 < 101);

    CPPUNIT_ASSERT_EQUAL(true ,  99 < testee1);
    CPPUNIT_ASSERT_EQUAL(false, 100 < testee1);
    CPPUNIT_ASSERT_EQUAL(false, 101 < testee1);

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
