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
**      An Implementation of Test Case 'HouseholdAccountsSettings'.
**
**      @file       Common/Tests/HouseholdAccountsSettingsTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/Common/HouseholdAccountsSettings.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

//========================================================================
//
//    HouseholdAccountsSettingsTest  class.
//
/**
**    クラス HouseholdAccountsSettings  の単体テスト。
**/

class  HouseholdAccountsSettingsTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(HouseholdAccountsSettingsTest);
    CPPUNIT_TEST(testNameSpace);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testNameSpace();
};

CPPUNIT_TEST_SUITE_REGISTRATION( HouseholdAccountsSettingsTest );

//========================================================================
//
//    Tests.
//

void  HouseholdAccountsSettingsTest::testNameSpace()
{
    return;
}

HOUSEHOLD_ACCOUNTS_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
