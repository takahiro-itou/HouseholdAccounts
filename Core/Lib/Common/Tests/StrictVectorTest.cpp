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
**      An Implementation of Test Case 'StrictVector'.
**
**      @file       Common/Tests/StrictVectorTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/Common/StrictVector.h"

#include    "Account/Common/StrictTypes.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //
struct  tagInt;

//========================================================================
//
//    StrictVectorTest  class.
//
/**
**    クラス StrictVector の単体テスト。
**/

class  StrictVectorTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(StrictVectorTest);
    CPPUNIT_TEST(testStrictVector);
    CPPUNIT_TEST(testPushBack);
    CPPUNIT_TEST(testAt);
    CPPUNIT_TEST_SUITE_END();

private:

    typedef     StrictTypes<int, tagInt>        IndexType;
    typedef     StrictVector<int, IndexType>    TestTarget;

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testStrictVector();
    void  testPushBack();
    void  testAt();
};

CPPUNIT_TEST_SUITE_REGISTRATION( StrictVectorTest );

//========================================================================
//
//    Tests.
//

void  StrictVectorTest::testStrictVector()
{
    TestTarget  testee;

    return;
}

void  StrictVectorTest::testPushBack()
{
    TestTarget  testee;

    testee.push_back(1);
    testee.push_back(2);
    testee.push_back(3);

    return;
}

void  StrictVectorTest::testAt()
{
    TestTarget  testee;
    IndexType   i1(0);
    IndexType   i2(1);
    IndexType   i3(2);

    testee.push_back(1);
    testee.push_back(2);
    testee.push_back(3);

    CPPUNIT_ASSERT_EQUAL(1, testee[i1]);
    CPPUNIT_ASSERT_EQUAL(2, testee[i2]);
    CPPUNIT_ASSERT_EQUAL(3, testee[i3]);

    CPPUNIT_ASSERT_EQUAL(1, testee.at(i1));
    CPPUNIT_ASSERT_EQUAL(2, testee.at(i2));
    CPPUNIT_ASSERT_EQUAL(3, testee.at(i3));

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
