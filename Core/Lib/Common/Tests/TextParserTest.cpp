//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
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
**      An Implementation of Test Case 'TextParser'.
**
**      @file       Common/Tests/TextParserTest.cpp
**/

#include    "TestDriver.h"
#include    "HouseholdAccounts/Common/TextParser.h"

HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    TextParserTest  class.
//
/**
**    クラス TextParser の単体テスト。
**/

class  TextParserTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(TextParserTest);
    CPPUNIT_TEST(testTextParser);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testTextParser();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TextParserTest );

//========================================================================
//
//    Tests.
//

void  TextParserTest::testTextParser()
{
    TextParser  parser;
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
