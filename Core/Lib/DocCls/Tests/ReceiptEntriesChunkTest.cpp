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

#include    "SetupTestData.inl"


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
    CPPUNIT_TEST(testToString1);
    CPPUNIT_TEST(testToString2);
    CPPUNIT_TEST(testToString3);
    CPPUNIT_TEST(testWriteToString1);
    CPPUNIT_TEST(testWriteToString2);
    CPPUNIT_TEST(testWriteToString3);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    Boolean
    prepareTestData2(
            ReceiptEntriesChunk *   chunk);

private:
    void  testReceiptEntriesChunk();
    void  testToString1();
    void  testToString2();
    void  testToString3();
    void  testWriteToString1();
    void  testWriteToString2();
    void  testWriteToString3();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ReceiptEntriesChunkTest );

//========================================================================
//
//    For Internal Use Only.
//

Boolean
ReceiptEntriesChunkTest::prepareTestData2(
        ReceiptEntriesChunk *   chunk)
{
    chunk->blockFlags       = ReceiptEntriesChunk::ChunkInOutFlags::DOUBLE_ENTRY;
    chunk->chlDebitAccount  = static_cast<CategoryHandle>(2);
    chunk->chrCreditAccount = static_cast<CategoryHandle>(4);
    chunk->cnlDebitAmount   = static_cast<CurrencyNumerator>(0);
    chunk->cnrCreditAmount  = static_cast<CurrencyNumerator>(0);

    chunk->goodsList.clear();
    chunk->goodsList.resize(static_cast<PurchaseNumber>(1));

    ReceiptEntriesChunk::PurchasingList  &
            goods1  = chunk->goodsList;

    {
        PurchasedGoods &pg0 = goods1[static_cast<PurchaseNumber>(0)];
        pg0.accountHeadings = static_cast<CategoryHandle>(11);
        pg0.accountCategory = static_cast<CategoryHandle>(12);
        pg0.productName     = "Deposit";
        pg0.unitPrice       = static_cast<CurrencyNumerator>(1000);
        pg0.nQuantity       = 1;
        pg0.cDiscount       = static_cast<CurrencyNumerator>(0);
        pg0.exclusiveTaxVal = static_cast<CurrencyNumerator>(0);
        pg0.inclusiveTaxVal = static_cast<CurrencyNumerator>(0);
        pg0.cSubTotal       = static_cast<CurrencyNumerator>(1000);
        pg0.pCatMan         = chunk->pCatMan;
    }

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

void  ReceiptEntriesChunkTest::testToString1()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    ReceiptEntriesChunk     testee;
    testee.pCatMan  = &cateMan;
    setupReceiptEntriesChunk1(testee);

    const  std::string  ret = testee.toString();

    CPPUNIT_ASSERT_EQUAL(
            std::string(
                    "支出;現金;;Head1;Cate1;Product1;1280;2;10;1;2\n"
                    ";;;Head2;Cate2;Product2;200;1;20;3;7"
            ),
            ret
    );

    return;
}

void  ReceiptEntriesChunkTest::testToString2()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    ReceiptEntriesChunk     testee;
    testee.pCatMan  = &cateMan;
    setupReceiptEntriesChunk2(testee);

    const  std::string  ret = testee.toString();

    CPPUNIT_ASSERT_EQUAL(
            std::string("収入;ポイント;;Head3;Cate3;Points;10;1;0;0;0"),
            ret
    );

    return;
}

void  ReceiptEntriesChunkTest::testToString3()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    ReceiptEntriesChunk     testee;
    testee.pCatMan  = &cateMan;
    setupReceiptEntriesChunk3(testee);

    const  std::string  ret = testee.toString();

    CPPUNIT_ASSERT_EQUAL(
            std::string("複式;現金;Bank 1;Head4;Cate4;Deposit;30000;1;0;0;0"),
            ret
    );

    return;
}

void  ReceiptEntriesChunkTest::testWriteToString1()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    ReceiptEntriesChunk     testee;
    testee.pCatMan  = &cateMan;
    setupReceiptEntriesChunk1(testee);

    std::stringstream   ss;
    testee.writeToStream(ss);

    CPPUNIT_ASSERT_EQUAL(
            std::string(
                    "支出;現金;;Head1;Cate1;Product1;1280;2;10;1;2\n"
                    ";;;Head2;Cate2;Product2;200;1;20;3;7"
            ),
            ss.str()
    );

    return;
}

void  ReceiptEntriesChunkTest::testWriteToString2()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    ReceiptEntriesChunk     testee;
    testee.pCatMan  = &cateMan;
    setupReceiptEntriesChunk2(testee);

    std::stringstream   ss;
    testee.writeToStream(ss);

    CPPUNIT_ASSERT_EQUAL(
            std::string("収入;ポイント;;Head3;Cate3;Points;10;1;0;0;0"),
            ss.str()
    );

    return;
}

void  ReceiptEntriesChunkTest::testWriteToString3()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    ReceiptEntriesChunk     testee;
    testee.pCatMan  = &cateMan;
    setupReceiptEntriesChunk3(testee);

    std::stringstream   ss;
    testee.writeToStream(ss);

    CPPUNIT_ASSERT_EQUAL(
            std::string("複式;現金;Bank 1;Head4;Cate4;Deposit;30000;1;0;0;0"),
            ss.str()
    );

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
