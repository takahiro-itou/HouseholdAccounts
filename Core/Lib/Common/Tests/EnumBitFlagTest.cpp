//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Household Accounts Core.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2022, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING and LICENSE files)                    **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of Test Case 'EnumBitFlag'.
**
**      @file       Common/Tests/EnumBitFlagTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/Common/EnumBitFlag.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //

//========================================================================
//
//    EnumBitFlagTest  class.
//
/**
**    クラス EnumBitFlag  の単体テスト。
**/

class  EnumBitFlagTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(EnumBitFlagTest);
    CPPUNIT_TEST(testEnumBitFlag);
    CPPUNIT_TEST(testEnumBitFlagNot);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testEnumBitFlag();
    void  testEnumBitFlagNot();
};

CPPUNIT_TEST_SUITE_REGISTRATION( EnumBitFlagTest );

//========================================================================
//
//    Tests.
//

enum class  TestEnumType : uint32_t
{
    THE_BIT_0 = 1 << 0,
    THE_BIT_1 = 1 << 1,
    THE_BIT_2 = 1 << 2,
    THE_BIT_3 = 1 << 3,

    MASK = THE_BIT_1 | THE_BIT_2,
};

void  EnumBitFlagTest::testEnumBitFlag()
{
    TestEnumType  a = TestEnumType::THE_BIT_3 | TestEnumType::THE_BIT_2;

    return;
}

void  EnumBitFlagTest::testEnumBitFlagNot()
{
    TestEnumType  a = TestEnumType::THE_BIT_1;
    TestEnumType  b = ~ a;

    CPPUNIT_ASSERT_EQUAL(
            0xfffffffd,
            static_cast<uint32_t>(b));

    return;
}

}   //  End of namespace  Common
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
