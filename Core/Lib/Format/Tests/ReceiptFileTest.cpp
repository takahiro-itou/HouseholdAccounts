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
**      An Implementation of Test Case 'ReceiptFile'.
**
**      @file       Format/Tests/ReceiptFileTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/Format/ReceiptFile.h"

#include    "Account/DocCls/CategoryManager.h"
#include    "Account/DocCls/ReceiptInfo.h"

#include    <sstream>

#include    "../../DocCls/Tests/SetupTestData.inl"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Format  {

namespace  {

static  const   std::string
TEST_CASE_1_EXPECTED_STRING(
        "NEW;1;2023/03/01;09:00;SHOP A;支出;現金;;"
        "Head1;Cate1;Product1;234;2;0;0;0;;\n"
        ";;;;;;;;"
        "Head2;Cate2;Product2;300;1;10;3;7;;\n"
        ";;;;;収入;ポイント;;"
        "Head3;Cate3;Points;10;1;0;0;0;;\n"
);

static  const   std::string
TEST_CASE_2_EXPECTED_STRING(
        ";NEW;1;2023/03/01;09:00;SHOP A;支出;現金;;"
        "Head1;Cate1;Product1;1280;2;10;1;2;;\n"
        ";;;;;;;;;"
        "Head2;Cate2;Product2;200;1;20;3;7;;\n"
        ";;;;;;収入;ポイント;;"
        "Head3;Cate3;Points;10;1;0;0;0;;\n"
        ";;;;;;;;;"
        "Head1;Cate1;Discounts;20;1;0;0;0;;\n"
        ";NEW;2;2023/03/02;*****;SHOP B;複式;現金;Bank 1;"
        "Head4;Cate4;Deposit;30000;1;0;0;0;;\n"
);

//----------------------------------------------------------------

inline  void
comparePurchasedGoods(
        const   DocCls::PurchasedGoods  &expect,
        const   DocCls::PurchasedGoods  &actual)
{
    CPPUNIT_ASSERT_EQUAL(expect.accountHeadings,  actual.accountHeadings);
    CPPUNIT_ASSERT_EQUAL(expect.accountCategory,  actual.accountCategory);
    CPPUNIT_ASSERT_EQUAL(expect.productName,      actual.productName);
    CPPUNIT_ASSERT_EQUAL(expect.unitPrice,        actual.unitPrice);
    CPPUNIT_ASSERT_EQUAL(expect.nQuantity,        actual.nQuantity);
    CPPUNIT_ASSERT_EQUAL(expect.cDiscount,        actual.cDiscount);
    CPPUNIT_ASSERT_EQUAL(expect.exclusiveTaxVal,  actual.exclusiveTaxVal);
    CPPUNIT_ASSERT_EQUAL(expect.inclusiveTaxVal,  actual.inclusiveTaxVal);
    CPPUNIT_ASSERT_EQUAL(expect.cSubTotal,        actual.cSubTotal);

    return;
}

//----------------------------------------------------------------

inline  void
compareReceiptEntriesChunk(
        const  DocCls::ReceiptEntriesChunk  &expect,
        const  DocCls::ReceiptEntriesChunk  &actual)
{
    CPPUNIT_ASSERT_EQUAL(expect.chlDebitAccount,  actual.chlDebitAccount);
    CPPUNIT_ASSERT_EQUAL(expect.chrCreditAccount, actual.chrCreditAccount);
    CPPUNIT_ASSERT_EQUAL(expect.cnlDebitAmount,   actual.cnlDebitAmount);
    CPPUNIT_ASSERT_EQUAL(expect.cnrCreditAmount,  actual.cnrCreditAmount);

    return;
}

}   //  End of (Unnamed) namespace.

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
    CPPUNIT_TEST(testSaveToTextStream1);
    CPPUNIT_TEST(testSaveToTextStream2);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    typedef     DocCls::CategoryManager     CategoryManager;

    std::ostream  &
    prepareTextStream1(
            std::ostream  &outStr);

    std::ostream  &
    prepareTextStream2(
            std::ostream  &outStr);

private:
    void  testReceiptFile();
    void  testReadFromTextStream1();
    void  testReadFromTextStream2();
    void  testSaveToTextStream1();
    void  testSaveToTextStream2();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ReceiptFileTest );

//========================================================================
//
//    For Internal Use Only.
//

std::ostream  &
ReceiptFileTest::prepareTextStream1(
        std::ostream  &outStr)
{
    outStr  <<  TEST_CASE_1_EXPECTED_STRING;
    return ( outStr );
}

std::ostream  &
ReceiptFileTest::prepareTextStream2(
        std::ostream  &outStr)
{
    outStr  <<  TEST_CASE_2_EXPECTED_STRING;
    return ( outStr );
}

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

    DocCls::CategoryManager catMan;
    setupCategoryManager1(catMan);

    ReceiptFile     testee;
    std::stringstream   ss;
    prepareTextStream1(ss);

    DocCls::ReceiptList data;
    int retCode;

    retCode = static_cast<int>(testee.setNumSkipColumns(0));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    retCode = static_cast<int>(testee.setCategoryManager(catMan));
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
    {
        DocCls::ReceiptEntriesChunk expect1(catMan);
        setupReceiptEntriesChunk1(expect1);
        compareReceiptEntriesChunk(expect1, chunk1);
    }

    const DocCls::ReceiptEntriesChunk &
        chunk2  = chunks.at(static_cast<ChunkIndex>(1));
    {
        DocCls::ReceiptEntriesChunk expect2(catMan);
        setupReceiptEntriesChunk2(expect2);
        compareReceiptEntriesChunk(expect2, chunk2);
    }

    const DocCls::ReceiptEntriesChunk::PurchasingList &
        goods1  = chunk1.goodsList;

    CPPUNIT_ASSERT_EQUAL(
            static_cast<PurchaseNumber>(2),
            static_cast<PurchaseNumber>(goods1.size()) );

    {
        const DocCls::PurchasedGoods &
            pg0 = goods1.at(static_cast<PurchaseNumber>(0));
        DocCls::PurchasedGoods  expect0(catMan);
        setupPurchasedGoods1(expect0);
        comparePurchasedGoods(expect0, pg0);
    }

    {
        const DocCls::PurchasedGoods &
            pg1 = goods1.at(static_cast<PurchaseNumber>(1));
        DocCls::PurchasedGoods  expect1(catMan);
        setupPurchasedGoods2(expect1);
        comparePurchasedGoods(expect1, pg1);
    }

    const DocCls::ReceiptEntriesChunk::PurchasingList &
        goods2  = chunk2.goodsList;

    CPPUNIT_ASSERT_EQUAL(
            static_cast<PurchaseNumber>(1),
            static_cast<PurchaseNumber>(goods2.size()) );

    {
        const DocCls::PurchasedGoods &
            pg2 = goods2.at(static_cast<PurchaseNumber>(0));
        DocCls::PurchasedGoods  expect2(catMan);
        setupPurchasedGoods5(expect2);
        comparePurchasedGoods(expect2, pg2);
    }

    return;
}

void  ReceiptFileTest::testReadFromTextStream2()
{
    typedef     DocCls::ReceiptInfo::ChunkIndex     ChunkIndex;

    DocCls::CategoryManager catMan;
    setupCategoryManager1(catMan);

    ReceiptFile     testee;
    std::stringstream   ss;
    prepareTextStream2(ss);

    DocCls::ReceiptList data;
    int retCode;

    retCode = static_cast<int>(testee.setNumSkipColumns(1));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    retCode = static_cast<int>(testee.setCategoryManager(catMan));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    retCode = static_cast<int>(testee.readFromTextStream(ss, &data));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    CPPUNIT_ASSERT_EQUAL(
            static_cast<ReceiptNumber>(2),
            static_cast<ReceiptNumber>(data.size()) );

    {
        const DocCls::ReceiptInfo &
            ri0 = data.at(static_cast<ReceiptNumber>(0));

        CPPUNIT_ASSERT_EQUAL(
                std::string("SHOP A"),
                ri0.getShopName() );

        const DocCls::ReceiptInfo::ChunkArray &
            chunks0 = ri0.getRecordChunks();

        CPPUNIT_ASSERT_EQUAL(
                static_cast<ChunkIndex>(2),
                static_cast<ChunkIndex>(chunks0.size()) );

        const DocCls::ReceiptEntriesChunk &
            chunk1  = chunks0.at(static_cast<ChunkIndex>(0));
        {
            DocCls::ReceiptEntriesChunk expect1(catMan);
            setupReceiptEntriesChunk3(expect1);
            compareReceiptEntriesChunk(expect1, chunk1);
        }

        const DocCls::ReceiptEntriesChunk &
            chunk2  = chunks0.at(static_cast<ChunkIndex>(1));
        {
            DocCls::ReceiptEntriesChunk expect2(catMan);
            setupReceiptEntriesChunk4(expect2);
            compareReceiptEntriesChunk(expect2, chunk2);
        }

        const DocCls::ReceiptEntriesChunk::PurchasingList &
            goods1  = chunk1.goodsList;

        CPPUNIT_ASSERT_EQUAL(
                static_cast<PurchaseNumber>(2),
                static_cast<PurchaseNumber>(goods1.size()) );

        {
            const DocCls::PurchasedGoods &
                pg0 = goods1.at(static_cast<PurchaseNumber>(0));
            DocCls::PurchasedGoods  expect0(catMan);
            setupPurchasedGoods3(expect0);
            comparePurchasedGoods(expect0, pg0);
        }

        {
            const DocCls::PurchasedGoods &
                pg1 = goods1.at(static_cast<PurchaseNumber>(1));
            DocCls::PurchasedGoods  expect1(catMan);
            setupPurchasedGoods4(expect1);
            comparePurchasedGoods(expect1, pg1);
        }

        const DocCls::ReceiptEntriesChunk::PurchasingList &
            goods2  = chunk2.goodsList;

        CPPUNIT_ASSERT_EQUAL(
                static_cast<PurchaseNumber>(2),
                static_cast<PurchaseNumber>(goods2.size()) );

        {
            const DocCls::PurchasedGoods &
                pg2 = goods2.at(static_cast<PurchaseNumber>(0));
            DocCls::PurchasedGoods  expect2(catMan);
            setupPurchasedGoods5(expect2);
            comparePurchasedGoods(expect2, pg2);
        }

        {
            const DocCls::PurchasedGoods &
                pg3 = goods2.at(static_cast<PurchaseNumber>(1));
            DocCls::PurchasedGoods  expect3(catMan);
            setupPurchasedGoods6(expect3);
            comparePurchasedGoods(expect3, pg3);
        }
    }

    {
        const DocCls::ReceiptInfo &
            ri1 = data.at(static_cast<ReceiptNumber>(1));

        CPPUNIT_ASSERT_EQUAL(
                std::string("SHOP B"),
                ri1.getShopName() );

        const DocCls::ReceiptInfo::ChunkArray &
            chunks1 = ri1.getRecordChunks();

        CPPUNIT_ASSERT_EQUAL(
                static_cast<ChunkIndex>(1),
                static_cast<ChunkIndex>(chunks1.size()) );

        const DocCls::ReceiptEntriesChunk &
            chunk3  = chunks1.at(static_cast<ChunkIndex>(0));
        {
            DocCls::ReceiptEntriesChunk expect3(catMan);
            setupReceiptEntriesChunk5(expect3);
            compareReceiptEntriesChunk(expect3, chunk3);
        }

        const DocCls::ReceiptEntriesChunk::PurchasingList &
            goods3  = chunk3.goodsList;

        CPPUNIT_ASSERT_EQUAL(
                static_cast<PurchaseNumber>(1),
                static_cast<PurchaseNumber>(goods3.size()) );
        {
            const DocCls::PurchasedGoods &
                pg4 = goods3.at(static_cast<PurchaseNumber>(0));
            DocCls::PurchasedGoods  expect4(catMan);
            setupPurchasedGoods3(expect4);
            comparePurchasedGoods(expect4, pg4);
        }
    }

    return;
}

void  ReceiptFileTest::testSaveToTextStream1()
{
    typedef     DocCls::ReceiptInfo::ChunkIndex     ChunkIndex;

    DocCls::CategoryManager catMan;
    setupCategoryManager1(catMan);

    ReceiptFile     testee;
    std::stringstream   ss;
    prepareTextStream1(ss);

    DocCls::ReceiptList data;
    int retCode;

    retCode = static_cast<int>(testee.setNumSkipColumns(0));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    retCode = static_cast<int>(testee.setCategoryManager(catMan));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    retCode = static_cast<int>(testee.readFromTextStream(ss, &data));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    std::stringstream   ssOut;
    retCode = static_cast<int>(testee.saveToTextStream(data, ssOut));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    CPPUNIT_ASSERT_EQUAL( ss.str(), ssOut.str() );

    return;
}

void  ReceiptFileTest::testSaveToTextStream2()
{
    typedef     DocCls::ReceiptInfo::ChunkIndex     ChunkIndex;

    DocCls::CategoryManager catMan;
    setupCategoryManager1(catMan);

    ReceiptFile     testee;
    std::stringstream   ss;
    prepareTextStream2(ss);

    DocCls::ReceiptList data;
    int retCode;

    retCode = static_cast<int>(testee.setNumSkipColumns(1));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    retCode = static_cast<int>(testee.setCategoryManager(catMan));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    retCode = static_cast<int>(testee.readFromTextStream(ss, &data));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    std::stringstream   ssOut;
    retCode = static_cast<int>(testee.saveToTextStream(data, ssOut));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    CPPUNIT_ASSERT_EQUAL( ss.str(), ssOut.str() );

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
