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
    CPPUNIT_TEST(testInsertString);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testStringTable();
    void  testInsertString();
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

void  StringTableTest::testInsertString()
{
    StringTable     testee;

    CPPUNIT_ASSERT_EQUAL( 0, TO_VALUE_FROM_STRICT(testee.insertString("AA")));
    CPPUNIT_ASSERT_EQUAL( 1, TO_VALUE_FROM_STRICT(testee.insertString("AB")));
    CPPUNIT_ASSERT_EQUAL( 2, TO_VALUE_FROM_STRICT(testee.insertString("AC")));
    CPPUNIT_ASSERT_EQUAL( 3, TO_VALUE_FROM_STRICT(testee.insertString("AD")));
    CPPUNIT_ASSERT_EQUAL( 4, TO_VALUE_FROM_STRICT(testee.insertString("AE")));
    CPPUNIT_ASSERT_EQUAL( 5, TO_VALUE_FROM_STRICT(testee.insertString("AF")));
    CPPUNIT_ASSERT_EQUAL( 6, TO_VALUE_FROM_STRICT(testee.insertString("AG")));
    CPPUNIT_ASSERT_EQUAL( 7, TO_VALUE_FROM_STRICT(testee.insertString("AH")));

    CPPUNIT_ASSERT_EQUAL( 8, TO_VALUE_FROM_STRICT(testee.insertString("CA")));
    CPPUNIT_ASSERT_EQUAL( 9, TO_VALUE_FROM_STRICT(testee.insertString("CB")));
    CPPUNIT_ASSERT_EQUAL(10, TO_VALUE_FROM_STRICT(testee.insertString("CC")));
    CPPUNIT_ASSERT_EQUAL(11, TO_VALUE_FROM_STRICT(testee.insertString("CD")));
    CPPUNIT_ASSERT_EQUAL(12, TO_VALUE_FROM_STRICT(testee.insertString("CE")));
    CPPUNIT_ASSERT_EQUAL(13, TO_VALUE_FROM_STRICT(testee.insertString("CF")));
    CPPUNIT_ASSERT_EQUAL(14, TO_VALUE_FROM_STRICT(testee.insertString("CG")));
    CPPUNIT_ASSERT_EQUAL(15, TO_VALUE_FROM_STRICT(testee.insertString("CH")));

    CPPUNIT_ASSERT_EQUAL(16, TO_VALUE_FROM_STRICT(testee.insertString("BH")));
    CPPUNIT_ASSERT_EQUAL(17, TO_VALUE_FROM_STRICT(testee.insertString("BG")));
    CPPUNIT_ASSERT_EQUAL(18, TO_VALUE_FROM_STRICT(testee.insertString("BF")));
    CPPUNIT_ASSERT_EQUAL(19, TO_VALUE_FROM_STRICT(testee.insertString("BE")));
    CPPUNIT_ASSERT_EQUAL(20, TO_VALUE_FROM_STRICT(testee.insertString("BD")));
    CPPUNIT_ASSERT_EQUAL(21, TO_VALUE_FROM_STRICT(testee.insertString("BC")));
    CPPUNIT_ASSERT_EQUAL(22, TO_VALUE_FROM_STRICT(testee.insertString("BB")));
    CPPUNIT_ASSERT_EQUAL(23, TO_VALUE_FROM_STRICT(testee.insertString("BA")));

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
