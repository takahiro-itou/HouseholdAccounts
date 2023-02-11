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
**      An Implementation of Test Case 'StringTable'.
**
**      @file       Documents/Tests/StringTableTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/Documents/StringTable.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Documents  {

//  クラスの前方宣言。  //

//========================================================================
//
//    StringTableTest  class.
//
/**
**    クラス StringTable  の単体テスト。
**/

class  StringTableTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(StringTableTest);
    CPPUNIT_TEST(testStringTable);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testStringTable();
};

CPPUNIT_TEST_SUITE_REGISTRATION( StringTableTest );

//========================================================================
//
//    Tests.
//

void  StringTableTest::testStringTable()
{
    StringTable     testee;
    return;
}

}   //  End of namespace  Documents
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
