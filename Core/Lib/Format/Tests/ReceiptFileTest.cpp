﻿//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
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
**      An Implementation of Test Case 'ReceiptFile'.
**
**      @file       Format/Tests/ReceiptFileTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/Format/ReceiptFile.h"

#include    "Account/DocCls/CategoryManager.h"
#include    "Account/DocCls/ReceiptInfo.h"

#include    <sstream>


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Format  {

//  クラスの前方宣言。  //

//========================================================================
//
//    ReceiptFileTest  class.
//
/**
**    クラス ReceiptFile  の単体テスト。
**/

class  ReceiptFileTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(ReceiptFileTest);
    CPPUNIT_TEST(testReceiptFile);
    CPPUNIT_TEST(testReadFromTextStream1);
    CPPUNIT_TEST(testReadFromTextStream2);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testReceiptFile();
    void  testReadFromTextStream1();
    void  testReadFromTextStream2();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ReceiptFileTest );

//========================================================================
//
//    Tests.
//

void  ReceiptFileTest::testReceiptFile()
{
    ReceiptFile     testee;

    return;
}

void  ReceiptFileTest::testReadFromTextStream1()
{
    typedef     DocCls::ReceiptInfo::ChunkIndex     ChunkIndex;

    DocCls::CategoryManager cateMan;
    cateMan.setupRootCategory(
            CategoryHandle(0), "収入",
            DocCls::CategoryFlags(0),
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.setupRootCategory(
            CategoryHandle(1), "支出",
            DocCls::CategoryFlags(0),
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(0), "ポイント",
            DocCls::CategoryFlags(0),
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(1), "現金",
            DocCls::CategoryFlags(0),
            DateSerial(0),
            Common::DecimalCurrency(0));

    ReceiptFile     testee;

    std::stringstream   ss;

    ss  <<  "NEW;1;2023/03/01;09:00;SHOP A;支出;現金;;"
        <<  "Head1;Cate1;Product1;128;2;0;0;0;;\n";
    ss  <<  ";;;;;;;;"
        <<  "Head2;Cate2;Product2;200;1;10;0;0;;\n";
    ss  <<  ";;;;;収入;ポイント;;"
        <<  "Head3;Cate3;Points;10;1;0;0;0;;\n";

    DocCls::ReceiptList data;
    int retCode;

    retCode = static_cast<int>(testee.setNumSkipColumns(0));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    retCode = static_cast<int>(testee.readFromTextStream(ss, &data));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    CPPUNIT_ASSERT_EQUAL(
            static_cast<ReceiptNumber>(1),
            static_cast<ReceiptNumber>(data.size()) );

    const DocCls::ReceiptInfo &
        ri0 = data.at(static_cast<ReceiptNumber>(0));

    CPPUNIT_ASSERT_EQUAL(
            std::string("SHOP A"),
            ri0.getShopName() );

    const DocCls::ReceiptInfo::ChunkArray &
        chunks  = ri0.getRecordChunks();

    CPPUNIT_ASSERT_EQUAL(
            static_cast<ChunkIndex>(2),
            static_cast<ChunkIndex>(chunks.size()) );

    const DocCls::ReceiptEntriesChunk &
        chunk1  = chunks.at(static_cast<ChunkIndex>(0));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(3),
            chunk1.chlDebitAccount);
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(-1),
            chunk1.chrCreditAccount);
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CurrencyNumerator>(456),
            chunk1.cnlDebitAmount);
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CurrencyNumerator>(0),
            chunk1.cnrCreditAmount);

    const DocCls::ReceiptEntriesChunk &
        chunk2  = chunks.at(static_cast<ChunkIndex>(1));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(2),
            chunk2.chlDebitAccount);
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(-1),
            chunk2.chrCreditAccount);
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CurrencyNumerator>(10),
            chunk2.cnlDebitAmount);
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CurrencyNumerator>(0),
            chunk2.cnrCreditAmount);

    const DocCls::ReceiptEntriesChunk::PurchasingList &
        goods1  = chunk1.goodsList;

    CPPUNIT_ASSERT_EQUAL(
            static_cast<PurchaseNumber>(2),
            static_cast<PurchaseNumber>(goods1.size()) );

    const DocCls::ReceiptEntriesChunk::PurchasingList &
        goods2  = chunk2.goodsList;

    CPPUNIT_ASSERT_EQUAL(
            static_cast<PurchaseNumber>(1),
            static_cast<PurchaseNumber>(goods2.size()) );

    return;
}

void  ReceiptFileTest::testReadFromTextStream2()
{
    ReceiptFile     testee;

    std::stringstream   ss;

    ss  <<  ";NEW;1;2023/03/01;09:00;SHOP A;支出;現金;;"
        <<  "Head1;Cate1;Product1;234;2;0;0;0;;\n";
    ss  <<  ";;;;;;;;;"
        <<  "Head2;Cate2;Product2;300;1;10;0;0;;\n";
    ss  <<  ";;;;;;収入;ポイント;;"
        <<  "Head3;Cate3;Points;20;1;0;0;0;;\n";
    ss  <<  ";NEW;2;2023/03/02;*****;SHOP B;複式;現金;Bank 1;"
        <<  "Head4;Cate4;Deposit;1000;1;0;0;0;;\n";

    DocCls::ReceiptList data;
    int retCode;

    retCode = static_cast<int>(testee.setNumSkipColumns(1));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    retCode = static_cast<int>(testee.readFromTextStream(ss, &data));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    CPPUNIT_ASSERT_EQUAL(
            static_cast<ReceiptNumber>(2),
            static_cast<ReceiptNumber>(data.size()) );

    return;
}

}   //  End of namespace  Format
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
