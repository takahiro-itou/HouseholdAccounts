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
**      An Implementation of Test Case 'BookCategory'.
**
**      @file       DocCls/Tests/BookCategoryTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/DocCls/BookCategory.h"

#include    "Account/DocCls/CategoryManager.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    BookCategoryTest  class.
//
/**
**    クラス BookCategory の単体テスト。
**/

class  BookCategoryTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(BookCategoryTest);
    CPPUNIT_TEST(testBookCategory);
    CPPUNIT_TEST(testIsDescendantOf)
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testBookCategory();
    void  testIsDescendantOf();
};

CPPUNIT_TEST_SUITE_REGISTRATION( BookCategoryTest );

//========================================================================
//
//    Tests.
//

void  BookCategoryTest::testBookCategory()
{
    BookCategory    testee;
    return;
}

void  BookCategoryTest::testIsDescendantOf()
{
    BookCategory    testee;
    CategoryManager cateMan;

    cateMan.reserveRootCategories(CategoryHandle(2));

    cateMan.setupRootCategory(
            CategoryHandle(0), "Root1",
            DocCls::CategoryFlags::CTYPE_INCOME,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.setupRootCategory(
            CategoryHandle(1), "Root2",
            DocCls::CategoryFlags::CTYPE_OUTLAY,
            DateSerial(0),
            Common::DecimalCurrency(0));

    cateMan.insertNewCategory(
            CategoryHandle(0), "Head1",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));
    cateMan.insertNewCategory(
            CategoryHandle(2), "Cate1",
            DocCls::CategoryFlags::CTYPE_INHERIT,
            DateSerial(0),
            Common::DecimalCurrency(0));

    const  BookCategory  &
        bc0 = cateMan.getBookCategory(static_cast<CategoryHandle>(0));

    const  BookCategory  &
        bc1 = cateMan.getBookCategory(static_cast<CategoryHandle>(1));

    const  BookCategory  &
        bc2 = cateMan.getBookCategory(static_cast<CategoryHandle>(2));

    const  BookCategory  &
        bc3 = cateMan.getBookCategory(static_cast<CategoryHandle>(3));


    CPPUNIT_ASSERT_EQUAL(
            1,  static_cast<int>(bc0.isDescendantOf(0))
    );
    CPPUNIT_ASSERT_EQUAL(
            0,  static_cast<int>(bc0.isDescendantOf(1))
    );
    CPPUNIT_ASSERT_EQUAL(
            0,  static_cast<int>(bc0.isDescendantOf(2))
    );
    CPPUNIT_ASSERT_EQUAL(
            0,  static_cast<int>(bc0.isDescendantOf(3))
    );

    CPPUNIT_ASSERT_EQUAL(
            0,  static_cast<int>(bc1.isDescendantOf(0))
    );
    CPPUNIT_ASSERT_EQUAL(
            1,  static_cast<int>(bc1.isDescendantOf(1))
    );
    CPPUNIT_ASSERT_EQUAL(
            0,  static_cast<int>(bc1.isDescendantOf(2))
    );
    CPPUNIT_ASSERT_EQUAL(
            0,  static_cast<int>(bc1.isDescendantOf(3))
    );

    CPPUNIT_ASSERT_EQUAL(
            1,  static_cast<int>(bc2.isDescendantOf(0))
    );
    CPPUNIT_ASSERT_EQUAL(
            0,  static_cast<int>(bc2.isDescendantOf(1))
    );
    CPPUNIT_ASSERT_EQUAL(
            1,  static_cast<int>(bc2.isDescendantOf(2))
    );
    CPPUNIT_ASSERT_EQUAL(
            0,  static_cast<int>(bc2.isDescendantOf(3))
    );

    CPPUNIT_ASSERT_EQUAL(
            1,  static_cast<int>(bc3.isDescendantOf(0))
    );
    CPPUNIT_ASSERT_EQUAL(
            0,  static_cast<int>(bc3.isDescendantOf(1))
    );
    CPPUNIT_ASSERT_EQUAL(
            1,  static_cast<int>(bc3.isDescendantOf(2))
    );
    CPPUNIT_ASSERT_EQUAL(
            1,  static_cast<int>(bc3.isDescendantOf(3))
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
