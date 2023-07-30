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
**      An Implementation of Test Case 'DateTimeFormat'.
**
**      @file       Common/Tests/DateTimeFormatTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/Common/DateTimeFormat.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    DateTimeFormatTest  class.
//
/**
**    クラス DateTimeFormat の単体テスト。
**/

class  DateTimeFormatTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(DateTimeFormatTest);
    CPPUNIT_TEST(testDateTimeFormat);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testDateTimeFormat();
};

CPPUNIT_TEST_SUITE_REGISTRATION( DateTimeFormatTest );

//========================================================================
//
//    Tests.
//

void  DateTimeFormatTest::testDateTimeFormat()
{
    DateTimeFormat  testee;
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
