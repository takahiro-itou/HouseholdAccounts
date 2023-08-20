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
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testReceiptInfo();
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
