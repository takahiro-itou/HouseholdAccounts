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
**      An Implementation of Test Case 'CategoryManager'.
**
**      @file       DocCls/Tests/CategoryManagerTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/DocCls/CategoryManager.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    CategoryManagerTest  class.
//
/**
**    クラス CategoryManager  の単体テスト。
**/

class  CategoryManagerTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(CategoryManagerTest);
    CPPUNIT_TEST(testCategoryManager);
    CPPUNIT_TEST(testFindCategory1);
    CPPUNIT_TEST(testFindCategory2);
    CPPUNIT_TEST(testIsDescendantCategory);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testCategoryManager();
    void  testFindCategory1();
    void  testFindCategory2();
    void  testIsDescendantCategory();
};

CPPUNIT_TEST_SUITE_REGISTRATION( CategoryManagerTest );

//========================================================================
//
//    Tests.
//

void  CategoryManagerTest::testCategoryManager()
{
    CategoryManager     testee;
    return;
}

void  CategoryManagerTest::testFindCategory1()
{
    CategoryManager     testee;

    testee.reserveRootCategories(CategoryHandle(4));

    testee.setupRootCategory(
            CategoryHandle(0), "収入",
            CategoryFlags::CTYPE_INCOME,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.setupRootCategory(
            CategoryHandle(1), "支出",
            CategoryFlags::CTYPE_OUTLAY,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.setupRootCategory(
            CategoryHandle(2), "現金",
            CategoryFlags::CTYPE_BALANCE,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.setupRootCategory(
            CategoryHandle(3), "ポイント",
            CategoryFlags::CTYPE_BALANCE,
            DateSerial(0),
            Common::DecimalCurrency(0));

    testee.insertNewCategory(
            CategoryHandle(1), "Head1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.insertNewCategory(
            CategoryHandle(4), "Cate1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.insertNewCategory(
            CategoryHandle(1), "Head2",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.insertNewCategory(
            CategoryHandle(6), "Cate2",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    testee.insertNewCategory(
            CategoryHandle(0), "Head3",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.insertNewCategory(
            CategoryHandle(8), "Cate3",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(10),
            testee.getRegisteredCategoryCount());
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(4),
            testee.getRootCategoryCount());
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(16),
            testee.getBufferCapacity());

    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(0),
            testee.findCategory("収入"));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(1),
            testee.findCategory("支出"));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(2),
            testee.findCategory("現金"));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(3),
            testee.findCategory("ポイント"));

    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(4),
            testee.findCategory("Head1"));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(5),
            testee.findCategory("Cate1"));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(6),
            testee.findCategory("Head2"));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(7),
            testee.findCategory("Cate2"));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(8),
            testee.findCategory("Head3"));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(9),
            testee.findCategory("Cate3"));

    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(-1),
            testee.findCategory("BadCategory"));

    return;
}

void  CategoryManagerTest::testFindCategory2()
{
    CategoryManager     testee;

    testee.reserveRootCategories(CategoryHandle(4));

    testee.setupRootCategory(
            CategoryHandle(0), "Root1",
            CategoryFlags::CTYPE_INCOME,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.setupRootCategory(
            CategoryHandle(1), "Root2",
            CategoryFlags::CTYPE_OUTLAY,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.setupRootCategory(
            CategoryHandle(2), "Balance1",
            CategoryFlags::CTYPE_BALANCE,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.setupRootCategory(
            CategoryHandle(3), "Balance2",
            CategoryFlags::CTYPE_BALANCE,
            DateSerial(0),
            Common::DecimalCurrency(0));

    testee.insertNewCategory(
            CategoryHandle(0), "Head1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.insertNewCategory(
            CategoryHandle(4), "Cate1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    testee.insertNewCategory(
            CategoryHandle(1), "Head1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.insertNewCategory(
            CategoryHandle(6), "Cate1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    testee.insertNewCategory(
            CategoryHandle(2), "Head1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.insertNewCategory(
            CategoryHandle(8), "Cate1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    testee.insertNewCategory(
            CategoryHandle(3), "Head1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.insertNewCategory(
            CategoryHandle(10), "Cate1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(12),
            testee.getRegisteredCategoryCount());
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(4),
            testee.getRootCategoryCount());
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(16),
            testee.getBufferCapacity());

    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(0),
            testee.findCategory("Root1"));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(1),
            testee.findCategory("Root2"));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(2),
            testee.findCategory("Balance1"));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(3),
            testee.findCategory("Balance2"));

    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(4),
            testee.findCategory("Head1"));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(5),
            testee.findCategory("Cate1"));

    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(4),
            testee.findCategory("Head1", static_cast<CategoryHandle>(0)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(5),
            testee.findCategory("Cate1", static_cast<CategoryHandle>(0)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(4),
            testee.findCategory("Head1", static_cast<CategoryHandle>(4)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(5),
            testee.findCategory("Cate1", static_cast<CategoryHandle>(4)));

    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(6),
            testee.findCategory("Head1", static_cast<CategoryHandle>(1)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(7),
            testee.findCategory("Cate1", static_cast<CategoryHandle>(1)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(6),
            testee.findCategory("Head1", static_cast<CategoryHandle>(6)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(7),
            testee.findCategory("Cate1", static_cast<CategoryHandle>(6)));

    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(8),
            testee.findCategory("Head1", static_cast<CategoryHandle>(2)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(9),
            testee.findCategory("Cate1", static_cast<CategoryHandle>(2)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(8),
            testee.findCategory("Head1", static_cast<CategoryHandle>(8)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(9),
            testee.findCategory("Cate1", static_cast<CategoryHandle>(8)));

    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(10),
            testee.findCategory("Head1", static_cast<CategoryHandle>(3)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(11),
            testee.findCategory("Cate1", static_cast<CategoryHandle>(3)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(10),
            testee.findCategory("Head1", static_cast<CategoryHandle>(10)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(11),
            testee.findCategory("Cate1", static_cast<CategoryHandle>(10)));

    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(-1),
            testee.findCategory("BadCategory"));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(-1),
            testee.findCategory("Head1", static_cast<CategoryHandle>(5)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(-1),
            testee.findCategory("Head1", static_cast<CategoryHandle>(7)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(-1),
            testee.findCategory("Head1", static_cast<CategoryHandle>(9)));
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(-1),
            testee.findCategory("Head1", static_cast<CategoryHandle>(11)));

    return;
}

void  CategoryManagerTest::testIsDescendantCategory()
{
    CategoryManager     testee;

    testee.reserveRootCategories(CategoryHandle(4));

    testee.setupRootCategory(
            CategoryHandle(0), "Root1",
            CategoryFlags::CTYPE_INCOME,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.setupRootCategory(
            CategoryHandle(1), "Root2",
            CategoryFlags::CTYPE_OUTLAY,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.setupRootCategory(
            CategoryHandle(2), "Balance1",
            CategoryFlags::CTYPE_BALANCE,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.setupRootCategory(
            CategoryHandle(3), "Balance2",
            CategoryFlags::CTYPE_BALANCE,
            DateSerial(0),
            Common::DecimalCurrency(0));

    testee.insertNewCategory(
            CategoryHandle(0), "Head1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.insertNewCategory(
            CategoryHandle(4), "Cate1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    testee.insertNewCategory(
            CategoryHandle(1), "Head1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.insertNewCategory(
            CategoryHandle(6), "Cate1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    testee.insertNewCategory(
            CategoryHandle(2), "Head1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.insertNewCategory(
            CategoryHandle(8), "Cate1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    testee.insertNewCategory(
            CategoryHandle(3), "Head1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    testee.insertNewCategory(
            CategoryHandle(10), "Cate1",
            CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(12),
            testee.getRegisteredCategoryCount());
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(4),
            testee.getRootCategoryCount());
    CPPUNIT_ASSERT_EQUAL(
            static_cast<CategoryHandle>(16),
            testee.getBufferCapacity());

    const  int  pattern[12][12] = {
        { 1, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 1, 0,   0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 1,   0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 0, 0, 0,   1, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 0, 0, 0,   1, 1, 0, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0,   0, 0, 1, 0, 0, 0, 0, 0 },
        { 0, 1, 0, 0,   0, 0, 1, 1, 0, 0, 0, 0 },
        { 0, 0, 1, 0,   0, 0, 0, 0, 1, 0, 0, 0 },
        { 0, 0, 1, 0,   0, 0, 0, 0, 1, 1, 0, 0 },
        { 0, 0, 0, 1,   0, 0, 0, 0, 0, 0, 1, 0 },
        { 0, 0, 0, 1,   0, 0, 0, 0, 0, 0, 1, 1 }
    };

    for ( int i = 0; i < 12; ++ i ) {
        for ( int j = 0; j < 12; ++ j ) {
            Boolean retCode = testee.isDescendantCategory(
                    static_cast<CategoryHandle>(i),
                    static_cast<CategoryHandle>(j));
            CPPUNIT_ASSERT_EQUAL(
                    pattern[i][j], static_cast<int>(retCode));
        }
    }

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
