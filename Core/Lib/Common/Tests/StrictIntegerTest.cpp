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
    CPPUNIT_TEST_SUITE_END();

private:
    typedef     StrictInteger<int, tagInt>  TestTarget;

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testStrictInteger();
};

CPPUNIT_TEST_SUITE_REGISTRATION( StrictIntegerTest );

//========================================================================
//
//    Tests.
//

void  StrictIntegerTest::testStrictInteger()
{
    TestTarget  testee;

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
