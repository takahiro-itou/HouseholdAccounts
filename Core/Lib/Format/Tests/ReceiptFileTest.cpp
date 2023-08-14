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
    CPPUNIT_TEST(testSaveToTextStream1);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    typedef     DocCls::CategoryManager     CategoryManager;

    Boolean
    setupCategoryManager1(
            CategoryManager &cateMan);

    Boolean
    setupCategoryManager2(
            CategoryManager &cateMan);

private:
    void  testReceiptFile();
    void  testReadFromTextStream1();
    void  testReadFromTextStream2();
    void  testSaveToTextStream1();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ReceiptFileTest );

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

Boolean
ReceiptFileTest::setupCategoryManager2(
        CategoryManager &cateMan)
{
    cateMan.reserveRootCategories(CategoryHandle(5));
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
    cateMan.setupRootCategory(
            CategoryHandle(4), "Bank 1",
            DocCls::CategoryFlags::CTYPE_BALANCE,
            DateSerial(0),
            Common::DecimalCurrency(0));

    cateMan.insertNewCategory(
            CategoryHandle(1), "Head1",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(5), "Cate1",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(1), "Head2",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(7), "Cate2",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(0), "Head3",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(9), "Cate3",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(1), "Head4",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(11), "Cate4",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    return ( Boolean::BOOL_TRUE );
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

    DocCls::CategoryManager cateMan;
    setupCategoryManager1(cateMan);

    ReceiptFile     testee;
    std::stringstream   ss;

    ss  <<  "NEW;1;2023/03/01;09:00;SHOP A;支出;現金;;"
        <<  "Head1;Cate1;Product1;128;2;0;0;0;;\n";
    ss  <<  ";;;;;;;;"
        <<  "Head2;Cate2;Product2;200;1;10;1;2;;\n";
    ss  <<  ";;;;;収入;ポイント;;"
        <<  "Head3;Cate3;Points;10;1;0;0;0;;\n";

    DocCls::ReceiptList data;
    int retCode;

    retCode = static_cast<int>(testee.setNumSkipColumns(0));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    retCode = static_cast<int>(testee.setCategoryManager(cateMan));
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
            static_cast<CategoryHandle>(2),
            chunk1.chlDebitAccount);
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(-1),
            chunk1.chrCreditAccount);
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CurrencyNumerator>(447),
            chunk1.cnlDebitAmount);
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CurrencyNumerator>(0),
            chunk1.cnrCreditAmount);

    const DocCls::ReceiptEntriesChunk &
        chunk2  = chunks.at(static_cast<ChunkIndex>(1));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(3),
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

    {
        const DocCls::PurchasedGoods &
            pg0 = goods1.at(static_cast<PurchaseNumber>(0));

        CPPUNIT_ASSERT_EQUAL(
                static_cast<CategoryHandle>(4),
                pg0.accountHeadings);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CategoryHandle>(5),
                pg0.accountCategory);
        CPPUNIT_ASSERT_EQUAL(std::string("Product1"), pg0.productName);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(128), pg0.unitPrice);
        CPPUNIT_ASSERT_EQUAL(2, pg0.nQuantity);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(0), pg0.cDiscount);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(256), pg0.cSubTotal);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(0), pg0.inclusiveTaxVal);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(0), pg0.exclusiveTaxVal);
    }

    {
        const DocCls::PurchasedGoods &
            pg1 = goods1.at(static_cast<PurchaseNumber>(1));

        CPPUNIT_ASSERT_EQUAL(
                static_cast<CategoryHandle>(6),
                pg1.accountHeadings);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CategoryHandle>(7),
                pg1.accountCategory);
        CPPUNIT_ASSERT_EQUAL(std::string("Product2"), pg1.productName);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(200), pg1.unitPrice);
        CPPUNIT_ASSERT_EQUAL(1, pg1.nQuantity);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(10), pg1.cDiscount);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(191), pg1.cSubTotal);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(2), pg1.inclusiveTaxVal);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(1), pg1.exclusiveTaxVal);
    }

    const DocCls::ReceiptEntriesChunk::PurchasingList &
        goods2  = chunk2.goodsList;

    CPPUNIT_ASSERT_EQUAL(
            static_cast<PurchaseNumber>(1),
            static_cast<PurchaseNumber>(goods2.size()) );

    {
        const DocCls::PurchasedGoods &
            pg2 = goods2.at(static_cast<PurchaseNumber>(0));

        CPPUNIT_ASSERT_EQUAL(
                static_cast<CategoryHandle>(8),
                pg2.accountHeadings);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CategoryHandle>(9),
                pg2.accountCategory);
        CPPUNIT_ASSERT_EQUAL(std::string("Points"), pg2.productName);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(10), pg2.unitPrice);
        CPPUNIT_ASSERT_EQUAL(1, pg2.nQuantity);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(0), pg2.cDiscount);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(10), pg2.cSubTotal);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(0), pg2.inclusiveTaxVal);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(0), pg2.exclusiveTaxVal);
    }

    return;
}

void  ReceiptFileTest::testReadFromTextStream2()
{
    typedef     DocCls::ReceiptInfo::ChunkIndex     ChunkIndex;

    DocCls::CategoryManager cateMan;
    setupCategoryManager2(cateMan);

    ReceiptFile     testee;

    std::stringstream   ss;

    ss  <<  ";NEW;1;2023/03/01;09:00;SHOP A;支出;現金;;"
        <<  "Head1;Cate1;Product1;234;2;0;0;0;;\n";
    ss  <<  ";;;;;;;;;"
        <<  "Head2;Cate2;Product2;300;1;10;3;7;;\n";
    ss  <<  ";;;;;;収入;ポイント;;"
        <<  "Head3;Cate3;Points;20;1;0;0;0;;\n";
    ss  <<  ";NEW;2;2023/03/02;*****;SHOP B;複式;現金;Bank 1;"
        <<  "Head4;Cate4;Deposit;1000;1;0;0;0;;\n";

    DocCls::ReceiptList data;
    int retCode;

    retCode = static_cast<int>(testee.setNumSkipColumns(1));
    CPPUNIT_ASSERT_EQUAL( static_cast<int>(ErrCode::SUCCESS), retCode );

    retCode = static_cast<int>(testee.setCategoryManager(cateMan));
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
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CategoryHandle>(2),
                chunk1.chlDebitAccount);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CategoryHandle>(-1),
                chunk1.chrCreditAccount);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(761),
                chunk1.cnlDebitAmount);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(0),
                chunk1.cnrCreditAmount);

        const DocCls::ReceiptEntriesChunk &
            chunk2  = chunks0.at(static_cast<ChunkIndex>(1));
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CategoryHandle>(3),
                chunk2.chlDebitAccount);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CategoryHandle>(-1),
                chunk2.chrCreditAccount);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(20),
                chunk2.cnlDebitAmount);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(0),
                chunk2.cnrCreditAmount);

        const DocCls::ReceiptEntriesChunk::PurchasingList &
            goods1  = chunk1.goodsList;

        CPPUNIT_ASSERT_EQUAL(
                static_cast<PurchaseNumber>(2),
                static_cast<PurchaseNumber>(goods1.size()) );

        {
            const DocCls::PurchasedGoods &
                pg0 = goods1.at(static_cast<PurchaseNumber>(0));

            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CategoryHandle>(5),
                    pg0.accountHeadings);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CategoryHandle>(6),
                    pg0.accountCategory);
            CPPUNIT_ASSERT_EQUAL(std::string("Product1"), pg0.productName);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(234), pg0.unitPrice);
            CPPUNIT_ASSERT_EQUAL(2, pg0.nQuantity);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(0), pg0.cDiscount);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(468), pg0.cSubTotal);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(0), pg0.inclusiveTaxVal);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(0), pg0.exclusiveTaxVal);
        }

        {
            const DocCls::PurchasedGoods &
                pg1 = goods1.at(static_cast<PurchaseNumber>(1));

            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CategoryHandle>(7),
                    pg1.accountHeadings);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CategoryHandle>(8),
                    pg1.accountCategory);
            CPPUNIT_ASSERT_EQUAL(std::string("Product2"), pg1.productName);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(300), pg1.unitPrice);
            CPPUNIT_ASSERT_EQUAL(1, pg1.nQuantity);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(10), pg1.cDiscount);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(293), pg1.cSubTotal);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(7), pg1.inclusiveTaxVal);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(3), pg1.exclusiveTaxVal);
        }

        const DocCls::ReceiptEntriesChunk::PurchasingList &
            goods2  = chunk2.goodsList;

        CPPUNIT_ASSERT_EQUAL(
                static_cast<PurchaseNumber>(1),
                static_cast<PurchaseNumber>(goods2.size()) );

        {
            const DocCls::PurchasedGoods &
                pg2 = goods2.at(static_cast<PurchaseNumber>(0));

            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CategoryHandle>(9),
                    pg2.accountHeadings);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CategoryHandle>(10),
                    pg2.accountCategory);
            CPPUNIT_ASSERT_EQUAL(std::string("Points"), pg2.productName);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(20), pg2.unitPrice);
            CPPUNIT_ASSERT_EQUAL(1, pg2.nQuantity);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(0), pg2.cDiscount);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(20), pg2.cSubTotal);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(0), pg2.inclusiveTaxVal);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(0), pg2.exclusiveTaxVal);
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
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CategoryHandle>(2),
                chunk3.chlDebitAccount);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CategoryHandle>(4),
                chunk3.chrCreditAccount);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(1000),
                chunk3.cnlDebitAmount);
        CPPUNIT_ASSERT_EQUAL(
                static_cast<CurrencyNumerator>(1000),
                chunk3.cnrCreditAmount);

        const DocCls::ReceiptEntriesChunk::PurchasingList &
            goods3  = chunk3.goodsList;

        CPPUNIT_ASSERT_EQUAL(
                static_cast<PurchaseNumber>(1),
                static_cast<PurchaseNumber>(goods3.size()) );
        {
            const DocCls::PurchasedGoods &
                pg3 = goods3.at(static_cast<PurchaseNumber>(0));

            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CategoryHandle>(11),
                    pg3.accountHeadings);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CategoryHandle>(12),
                    pg3.accountCategory);
            CPPUNIT_ASSERT_EQUAL(std::string("Deposit"), pg3.productName);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(1000), pg3.unitPrice);
            CPPUNIT_ASSERT_EQUAL(1, pg3.nQuantity);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(0), pg3.cDiscount);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(1000), pg3.cSubTotal);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(0), pg3.inclusiveTaxVal);
            CPPUNIT_ASSERT_EQUAL(
                    static_cast<CurrencyNumerator>(0), pg3.exclusiveTaxVal);
        }
    }

    return;
}

void  ReceiptFileTest::testSaveToTextStream1()
{
    typedef     DocCls::ReceiptInfo::ChunkIndex     ChunkIndex;

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
