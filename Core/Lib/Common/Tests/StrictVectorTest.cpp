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


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

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
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testStrictVector();
};

CPPUNIT_TEST_SUITE_REGISTRATION( StrictVectorTest );

//========================================================================
//
//    Tests.
//

void  StrictVectorTest::testStrictVector()
{
    StrictVector<int, int>  testee;
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
