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
**      @file       DocCls/Tests/StringTableTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/DocCls/StringTable.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

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
    CPPUNIT_TEST(testSearchEntry);
    CPPUNIT_TEST(testSortIndex);
    CPPUNIT_TEST(testSortTable1);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testStringTable();
    void  testInsertString();
    void  testSearchEntry();
    void  testSortIndex();
    void  testSortTable1();
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

    CPPUNIT_ASSERT_EQUAL(24, TO_VALUE_FROM_STRICT(testee.getNumEntries()));

    return;
}

void  StringTableTest::testSearchEntry()
{
    StringTable                 testee;
    StringTable::FindResult     result;

    testee.insertString("AA");
    testee.insertString("AB");
    testee.insertString("AC");
    testee.insertString("AD");
    testee.insertString("AW");
    testee.insertString("AX");
    testee.insertString("AY");
    testee.insertString("AZ");

    testee.insertString("CA");
    testee.insertString("CB");
    testee.insertString("CC");
    testee.insertString("CD");
    testee.insertString("CW");
    testee.insertString("CX");
    testee.insertString("CY");
    testee.insertString("CZ");

    testee.insertString("BZ");
    testee.insertString("BY");
    testee.insertString("BX");
    testee.insertString("BW");
    testee.insertString("BD");
    testee.insertString("BC");
    testee.insertString("BB");
    testee.insertString("BA");

    result  = testee.searchEntryTest("AA");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL( 0, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL( 0, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("AB");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL( 1, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL( 1, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("AC");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL( 2, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL( 2, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("AD");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL( 3, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL( 3, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("AE");
    CPPUNIT_ASSERT( ! TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(-1, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL( 4, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("AW");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL( 4, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL( 4, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("AX");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL( 5, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL( 5, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("AY");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL( 6, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL( 6, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("AZ");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL( 7, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL( 7, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("CA");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL( 8, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(16, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("CB");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL( 9, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(17, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("CC");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(10, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(18, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("CD");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(11, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(19, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("CV");
    CPPUNIT_ASSERT( ! TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(-1, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(20, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("CW");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(12, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(20, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("CX");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(13, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(21, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("CY");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(14, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(22, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("CZ");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(15, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(23, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("BZ");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(16, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(15, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("BY");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(17, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(14, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("BX");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(18, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(13, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("BW");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(19, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(12, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("BV");
    CPPUNIT_ASSERT( ! TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(-1, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(12, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("BE");
    CPPUNIT_ASSERT( ! TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(-1, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(12, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("BD");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(20, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(11, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("BC");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(21, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(10, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("BB");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(22, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL( 9, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("BA");
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(23, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL( 8, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("00");
    CPPUNIT_ASSERT( ! TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(-1, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL( 0, TO_VALUE_FROM_STRICT(result.siInsert) );

    result  = testee.searchEntryTest("DD");
    CPPUNIT_ASSERT( ! TO_BOOL_FROM_STRICT(result.flgFound) );
    CPPUNIT_ASSERT_EQUAL(-1, TO_VALUE_FROM_STRICT(result.siResult) );
    CPPUNIT_ASSERT_EQUAL(24, TO_VALUE_FROM_STRICT(result.siInsert) );

    return;
}

void  StringTableTest::testSortIndex()
{
    StringTable     testee;

    testee.insertString("AA");
    testee.insertString("AB");
    testee.insertString("AC");
    testee.insertString("AD");
    testee.insertString("AW");
    testee.insertString("AX");
    testee.insertString("AY");
    testee.insertString("AZ");

    testee.insertString("CA");
    testee.insertString("CB");
    testee.insertString("CC");
    testee.insertString("CD");
    testee.insertString("CW");
    testee.insertString("CX");
    testee.insertString("CY");
    testee.insertString("CZ");

    testee.insertString("BZ");
    testee.insertString("BY");
    testee.insertString("BX");
    testee.insertString("BW");
    testee.insertString("BD");
    testee.insertString("BC");
    testee.insertString("BB");
    testee.insertString("BA");

    const  StringTable::IndexArray  & sorts = testee.m_sortedIndex;

    CPPUNIT_ASSERT_EQUAL( 0, TO_VALUE_FROM_STRICT(sorts[StringIndex( 0)]) );
    CPPUNIT_ASSERT_EQUAL( 1, TO_VALUE_FROM_STRICT(sorts[StringIndex( 1)]) );
    CPPUNIT_ASSERT_EQUAL( 2, TO_VALUE_FROM_STRICT(sorts[StringIndex( 2)]) );
    CPPUNIT_ASSERT_EQUAL( 3, TO_VALUE_FROM_STRICT(sorts[StringIndex( 3)]) );
    CPPUNIT_ASSERT_EQUAL( 4, TO_VALUE_FROM_STRICT(sorts[StringIndex( 4)]) );
    CPPUNIT_ASSERT_EQUAL( 5, TO_VALUE_FROM_STRICT(sorts[StringIndex( 5)]) );
    CPPUNIT_ASSERT_EQUAL( 6, TO_VALUE_FROM_STRICT(sorts[StringIndex( 6)]) );
    CPPUNIT_ASSERT_EQUAL( 7, TO_VALUE_FROM_STRICT(sorts[StringIndex( 7)]) );

    CPPUNIT_ASSERT_EQUAL(23, TO_VALUE_FROM_STRICT(sorts[StringIndex( 8)]) );
    CPPUNIT_ASSERT_EQUAL(22, TO_VALUE_FROM_STRICT(sorts[StringIndex( 9)]) );
    CPPUNIT_ASSERT_EQUAL(21, TO_VALUE_FROM_STRICT(sorts[StringIndex(10)]) );
    CPPUNIT_ASSERT_EQUAL(20, TO_VALUE_FROM_STRICT(sorts[StringIndex(11)]) );
    CPPUNIT_ASSERT_EQUAL(19, TO_VALUE_FROM_STRICT(sorts[StringIndex(12)]) );
    CPPUNIT_ASSERT_EQUAL(18, TO_VALUE_FROM_STRICT(sorts[StringIndex(13)]) );
    CPPUNIT_ASSERT_EQUAL(17, TO_VALUE_FROM_STRICT(sorts[StringIndex(14)]) );
    CPPUNIT_ASSERT_EQUAL(16, TO_VALUE_FROM_STRICT(sorts[StringIndex(15)]) );

    CPPUNIT_ASSERT_EQUAL( 8, TO_VALUE_FROM_STRICT(sorts[StringIndex(16)]) );
    CPPUNIT_ASSERT_EQUAL( 9, TO_VALUE_FROM_STRICT(sorts[StringIndex(17)]) );
    CPPUNIT_ASSERT_EQUAL(10, TO_VALUE_FROM_STRICT(sorts[StringIndex(18)]) );
    CPPUNIT_ASSERT_EQUAL(11, TO_VALUE_FROM_STRICT(sorts[StringIndex(19)]) );
    CPPUNIT_ASSERT_EQUAL(12, TO_VALUE_FROM_STRICT(sorts[StringIndex(20)]) );
    CPPUNIT_ASSERT_EQUAL(13, TO_VALUE_FROM_STRICT(sorts[StringIndex(21)]) );
    CPPUNIT_ASSERT_EQUAL(14, TO_VALUE_FROM_STRICT(sorts[StringIndex(22)]) );
    CPPUNIT_ASSERT_EQUAL(15, TO_VALUE_FROM_STRICT(sorts[StringIndex(23)]) );

    return;
}

void  StringTableTest::testSortTable1()
{
    StringTable     testee;

    const  StringIndex  num = static_cast<StringIndex>(7);
    testee.reserveBuffer(num);
    for ( StringIndex i = static_cast<StringIndex>(0); i < num; ++ i )
    {
        testee.setSortIndex(i, i);
    }

    testee.appendString("AX");
    testee.appendString("AY");
    testee.appendString("AZ");
    testee.appendString("AA");
    testee.appendString("AB");
    testee.appendString("AC");
    testee.appendString("AD");

    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(testee.checkDataIntegrity()) );
    CPPUNIT_ASSERT( ! TO_BOOL_FROM_STRICT(testee.checkSortIntegrity()) );

    const  int  retCode = static_cast<int>(testee.sortTable());

    const  StringTable::IndexArray  & sorts = testee.m_sortedIndex;

    CPPUNIT_ASSERT_EQUAL( 3, TO_VALUE_FROM_STRICT(sorts[StringIndex(0)]) );
    CPPUNIT_ASSERT_EQUAL( 4, TO_VALUE_FROM_STRICT(sorts[StringIndex(1)]) );
    CPPUNIT_ASSERT_EQUAL( 5, TO_VALUE_FROM_STRICT(sorts[StringIndex(2)]) );
    CPPUNIT_ASSERT_EQUAL( 6, TO_VALUE_FROM_STRICT(sorts[StringIndex(3)]) );
    CPPUNIT_ASSERT_EQUAL( 0, TO_VALUE_FROM_STRICT(sorts[StringIndex(4)]) );
    CPPUNIT_ASSERT_EQUAL( 1, TO_VALUE_FROM_STRICT(sorts[StringIndex(5)]) );
    CPPUNIT_ASSERT_EQUAL( 2, TO_VALUE_FROM_STRICT(sorts[StringIndex(6)]) );

    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(testee.checkDataIntegrity()) );
    CPPUNIT_ASSERT( TO_BOOL_FROM_STRICT(testee.checkSortIntegrity()) );

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
