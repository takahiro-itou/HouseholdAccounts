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

#include    <sstream>

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
    CPPUNIT_TEST(testWriteToStream1);
    CPPUNIT_TEST(testWriteToStream2);
    CPPUNIT_TEST(testWriteToStream3);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testReceiptEntriesChunk();
    void  testToString1();
    void  testToString2();
    void  testToString3();
    void  testWriteToStream1();
    void  testWriteToStream2();
    void  testWriteToStream3();
};

CPPUNIT_TEST_SUITE_REGISTRATION( ReceiptEntriesChunkTest );

//========================================================================
//
//    For Internal Use Only.
//

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
            std::string(
                    "収入;ポイント;;Head3;Cate3;Points;10;1;0;0;0\n"
                    ";;;Head1;Cate1;Discounts;20;1;0;0;0"
            ),
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

void  ReceiptEntriesChunkTest::testWriteToStream1()
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

void  ReceiptEntriesChunkTest::testWriteToStream2()
{
    CategoryManager     cateMan;
    setupCategoryManager1(cateMan);

    ReceiptEntriesChunk     testee;
    testee.pCatMan  = &cateMan;
    setupReceiptEntriesChunk2(testee);

    std::stringstream   ss;
    testee.writeToStream(ss);

    CPPUNIT_ASSERT_EQUAL(
            std::string(
                    "収入;ポイント;;Head3;Cate3;Points;10;1;0;0;0\n"
                    ";;;Head1;Cate1;Discounts;20;1;0;0;0"
            ),
            ss.str()
    );

    return;
}

void  ReceiptEntriesChunkTest::testWriteToStream3()
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
