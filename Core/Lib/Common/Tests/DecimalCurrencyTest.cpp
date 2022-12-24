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
**      An Implementation of Test Case 'DecimalCurrency'.
**
**      @file       Common/Tests/DecimalCurrencyTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/Common/DecimalCurrency.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //

//========================================================================
//
//    DecimalCurrencyTest  class.
//
/**
**    クラス DecimalCurrency  の単体テスト。
**/

class  DecimalCurrencyTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(DecimalCurrencyTest);
    CPPUNIT_TEST(testDecimalCurrency);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testDecimalCurrency();
};

CPPUNIT_TEST_SUITE_REGISTRATION( DecimalCurrencyTest );

//========================================================================
//
//    Tests.
//

void  DecimalCurrencyTest::testDecimalCurrency()
{
    DecimalCurrency     testee;
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
