//  -*-  coding: utf-8; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Household Accounts Core.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2017, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of Test Case 'HouseholdAccountsSettings'.
**
**      @file       Common/Tests/HouseholdAccountsSettingsTest.cpp
**/

#include    "TestDriver.h"
#include    "HouseholdAccounts/Common/HouseholdAccountsSettings.h"

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
