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
**      An Implementation of Test Case 'ReceiptEntriesChunk'.
**
**      @file       DocCls/Tests/ReceiptEntriesChunkTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/DocCls/ReceiptEntriesChunk.h"

#include    "Account/DocCls/CategoryManager.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    ReceiptEntriesChunkTest  class.
//
/**
**    クラス ReceiptEntriesChunk  の単体テスト。
**/

class  ReceiptEntriesChunkTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(ReceiptEntriesChunkTest);
    CPPUNIT_TEST(testReceiptEntriesChunk);
    CPPUNIT_TEST(testToString);
    CPPUNIT_TEST(testWriteToString);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    typedef     CategoryManager     CategoryManager;

    Boolean
    setupCategoryManager1(
            CategoryManager &cateMan);

private:
    void  testReceiptEntriesChunk();
    void  testToString();
    void  testWriteToString();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ReceiptEntriesChunkTest );

//========================================================================
//
//    For Internal Use Only.
//

Boolean
ReceiptFileTest::setupCategoryManager1(
        CategoryManager &cateMan)
{
    cateMan.reserveRootCategories(CategoryHandle(4));
    cateMan.setupRootCategory(
            CategoryHandle(0), "収入",
            DocCls::CategoryFlags::CTYPE_INCOME,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.setupRootCategory(
            CategoryHandle(1), "支出",
            DocCls::CategoryFlags::CTYPE_OUTLAY,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.setupRootCategory(
            CategoryHandle(2), "現金",
            DocCls::CategoryFlags::CTYPE_BALANCE,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.setupRootCategory(
            CategoryHandle(3), "ポイント",
            DocCls::CategoryFlags::CTYPE_BALANCE,
            DateSerial(0),
            Common::DecimalCurrency(0));

    cateMan.insertNewCategory(
            CategoryHandle(1), "Head1",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(4), "Cate1",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(1), "Head2",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(6), "Cate2",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(0), "Head3",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(8), "Cate3",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    return ( Boolean::BOOL_TRUE );
}

//========================================================================
//
//    Tests.
//

void  ReceiptEntriesChunkTest::testReceiptEntriesChunk()
{
    ReceiptEntriesChunk     testee;

    return;
}

void  ReceiptEntriesChunkTest::testToString()
{
    ReceiptEntriesChunk     testee;

    return;
}

void  ReceiptEntriesChunkTest::testWriteToString()
{
    ReceiptEntriesChunk     testee;

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
