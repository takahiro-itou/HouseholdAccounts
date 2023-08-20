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
**      Setup Unit Test Data.
**
**      @file       DocCls/Tests/SetupTestData.inl
**/

#if !defined( HACORE_DOCCLS_TESTS_INCLUDED_SETUP_TEST_DATA_INL )
#    define   HACORE_DOCCLS_TESTS_INCLUDED_SETUP_TEST_DATA_INL


#if !defined( HACORE_DOCCLS_INCLUDED_CATEGORY_MANAGER_H )
#    include    "Account/DocCls/CategoryManager.h"
#endif

#if !defined( HACORE_DOCCLS_INCLUDED_RECEIPT_ENTRIES_CHUNK_H )
#    include    "Account/DocCls/ReceiptEntriesChunk.h"
#endif

#if !defined( HACORE_DOCCLS_INCLUDED_RECEIPT_INFO_H )
#    include    "Account/DocCls/ReceiptInfo.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//----------------------------------------------------------------

inline  Boolean
setupCategoryManager1(
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

//----------------------------------------------------------------

inline  Boolean
setupPurchasedGoods1(
        PurchasedGoods  &pg)
{
    pg.accountHeadings  = static_cast<CategoryHandle>(5);
    pg.accountCategory  = static_cast<CategoryHandle>(6);
    pg.productName      = "Product1";
    pg.unitPrice        = static_cast<CurrencyNumerator>(1280);
    pg.nQuantity        = static_cast<int>(2);
    pg.cDiscount        = static_cast<CurrencyNumerator>(10);
    pg.exclusiveTaxVal  = static_cast<CurrencyNumerator>(1);
    pg.inclusiveTaxVal  = static_cast<CurrencyNumerator>(2);
    pg.cSubTotal        = static_cast<CurrencyNumerator>(2560 - 10 + 1);

    return ( Boolean::BOOL_TRUE );
}

//----------------------------------------------------------------

inline  Boolean
setupPurchasedGoods2(
        PurchasedGoods  &pg)
{
    pg.accountHeadings  = static_cast<CategoryHandle>(7);
    pg.accountCategory  = static_cast<CategoryHandle>(8);
    pg.productName      = "Product2";
    pg.unitPrice        = static_cast<CurrencyNumerator>(200);
    pg.nQuantity        = static_cast<int>(1);
    pg.cDiscount        = static_cast<CurrencyNumerator>(20);
    pg.exclusiveTaxVal  = static_cast<CurrencyNumerator>(3);
    pg.inclusiveTaxVal  = static_cast<CurrencyNumerator>(7);
    pg.cSubTotal        = static_cast<CurrencyNumerator>(183);

    return ( Boolean::BOOL_TRUE );

}

//----------------------------------------------------------------

inline  Boolean
setupPurchasedGoods3(
        PurchasedGoods  &pg)
{
    pg.accountHeadings  = static_cast<CategoryHandle>(9);
    pg.accountCategory  = static_cast<CategoryHandle>(10);
    pg.productName      = "Points";
    pg.unitPrice        = static_cast<CurrencyNumerator>(10);
    pg.nQuantity        = static_cast<int>(1);
    pg.cDiscount        = static_cast<CurrencyNumerator>(0);
    pg.exclusiveTaxVal  = static_cast<CurrencyNumerator>(0);
    pg.inclusiveTaxVal  = static_cast<CurrencyNumerator>(0);
    pg.cSubTotal        = static_cast<CurrencyNumerator>(10);

    return ( Boolean::BOOL_TRUE );

}

//----------------------------------------------------------------

inline  Boolean
setupPurchasedGoods4(
        PurchasedGoods  &pg)
{
    pg.accountHeadings  = static_cast<CategoryHandle>(11);
    pg.accountCategory  = static_cast<CategoryHandle>(12);
    pg.productName      = "Deposit";
    pg.unitPrice        = static_cast<CurrencyNumerator>(30000);
    pg.nQuantity        = static_cast<int>(1);
    pg.cDiscount        = static_cast<CurrencyNumerator>(0);
    pg.exclusiveTaxVal  = static_cast<CurrencyNumerator>(0);
    pg.inclusiveTaxVal  = static_cast<CurrencyNumerator>(0);
    pg.cSubTotal        = static_cast<CurrencyNumerator>(30000);

    return ( Boolean::BOOL_TRUE );
}

//----------------------------------------------------------------

inline  Boolean
setupReceiptEntriesChunk1(
        ReceiptEntriesChunk &chunk)
{
    chunk.blockFlags        = ReceiptEntriesChunk::ChunkInOutFlags::OUTLAY;
    chunk.chlDebitAccount   = static_cast<CategoryHandle>(2);
    chunk.chrCreditAccount  = static_cast<CategoryHandle>(-1);
    chunk.cnlDebitAmount    = static_cast<CurrencyNumerator>(0);
    chunk.cnrCreditAmount   = static_cast<CurrencyNumerator>(0);

    chunk.goodsList.clear();
    chunk.goodsList.resize(static_cast<PurchaseNumber>(2));

    ReceiptEntriesChunk::PurchasingList  &
            goods1  = chunk.goodsList;

    PurchasedGoods &pg0 = goods1[static_cast<PurchaseNumber>(0)];
    pg0.pCatMan = chunk.pCatMan;
    setupPurchasedGoods1(pg0);

    PurchasedGoods &pg1 = goods1[static_cast<PurchaseNumber>(1)];
    pg1.pCatMan         = chunk.pCatMan;
    setupPurchasedGoods2(pg1);

    return ( Boolean::BOOL_TRUE );
}

//----------------------------------------------------------------

inline  Boolean
setupReceiptEntriesChunk2(
        ReceiptEntriesChunk &chunk)
{
    chunk.blockFlags        = ReceiptEntriesChunk::ChunkInOutFlags::INCOME;
    chunk.chlDebitAccount   = static_cast<CategoryHandle>(3);
    chunk.chrCreditAccount  = static_cast<CategoryHandle>(-1);
    chunk.cnlDebitAmount    = static_cast<CurrencyNumerator>(0);
    chunk.cnrCreditAmount   = static_cast<CurrencyNumerator>(0);

    chunk.goodsList.clear();
    chunk.goodsList.resize(static_cast<PurchaseNumber>(1));

    ReceiptEntriesChunk::PurchasingList  &
            goods1  = chunk.goodsList;

    PurchasedGoods &pg0 = goods1[static_cast<PurchaseNumber>(0)];
    pg0.pCatMan = chunk.pCatMan;
    setupPurchasedGoods3(pg0);

    return ( Boolean::BOOL_TRUE );
}

//----------------------------------------------------------------

inline  Boolean
setupReceiptEntriesChunk3(
        ReceiptEntriesChunk &chunk)
{
    chunk.blockFlags
            = ReceiptEntriesChunk::ChunkInOutFlags::DOUBLE_ENTRY;
    chunk.chlDebitAccount   = static_cast<CategoryHandle>(2);
    chunk.chrCreditAccount  = static_cast<CategoryHandle>(4);
    chunk.cnlDebitAmount    = static_cast<CurrencyNumerator>(0);
    chunk.cnrCreditAmount   = static_cast<CurrencyNumerator>(0);

    chunk.goodsList.clear();
    chunk.goodsList.resize(static_cast<PurchaseNumber>(1));

    ReceiptEntriesChunk::PurchasingList  &
            goods1  = chunk.goodsList;

    PurchasedGoods &pg0 = goods1[static_cast<PurchaseNumber>(0)];
    pg0.pCatMan = chunk.pCatMan;
    setupPurchasedGoods4(pg0);

    return ( Boolean::BOOL_TRUE );
}

//----------------------------------------------------------------

inline  Boolean
setupReceiptInfo1(
        ReceiptInfo &ri)
{
    typedef     ReceiptInfo::ChunkIndex     ChunkIndex;

    ri.m_receiptDate    = "2023/03/01";
    ri.m_receiptTime    = "09:00";
    ri.m_shopName       = "SHOP A";

    ReceiptInfo::ChunkArray &chunks = ri.m_recordChunk;
    chunks.clear();
    chunks.resize(static_cast<ChunkIndex>(2));

    ReceiptEntriesChunk &chunk0 = chunks[static_cast<ChunkIndex>(0)];
    chunk0.pCatMan  = ri.pCatMan;
    setupReceiptEntriesChunk1(chunk0);

    ReceiptEntriesChunk &chunk1 = chunks[static_cast<ChunkIndex>(1)];
    chunk1.pCatMan  = ri.pCatMan;
    setupReceiptEntriesChunk2(chunk1);

    return ( Boolean::BOOL_TRUE );
}

}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
