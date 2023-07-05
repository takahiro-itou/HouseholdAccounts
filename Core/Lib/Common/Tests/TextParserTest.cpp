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
**      An Implementation of Test Case 'TextParser'.
**
**      @file       Common/Tests/TextParserTest.cpp
**/

#include    "TestDriver.h"
#include    "Account/Common/TextParser.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    TextParserTest  class.
//
/**
**    クラス TextParser の単体テスト。
**/

class  TextParserTest : public  TestFixture
{
    CPPUNIT_TEST_SUITE(TextParserTest);
    CPPUNIT_TEST(testTextParser);
    CPPUNIT_TEST(testSplitText1);
    CPPUNIT_TEST(testSplitText2);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testTextParser();
    void  testSplitText1();
    void  testSplitText2();
};

CPPUNIT_TEST_SUITE_REGISTRATION( TextParserTest );

//========================================================================
//
//    Tests.
//

void  TextParserTest::testTextParser()
{
    TextParser  parser;
    return;
}

void  TextParserTest::testSplitText1()
{
    TextParser::TextBuffer  bufText;
    TextParser::TokenArray  vTokens;

    ErrCode retCode;
    retCode = TextParser::splitText(
                    "abc;def;;g;h;i;", ";", bufText, vTokens);

    CPPUNIT_ASSERT_EQUAL(
            static_cast<int>(ErrCode::SUCCESS),
            static_cast<int>(retCode) );

    CPPUNIT_ASSERT_EQUAL(
            static_cast<size_t>(7),
            static_cast<size_t>(vTokens.size()) );

    CPPUNIT_ASSERT_EQUAL( std::string("abc"), std::string(vTokens[0]) );
    CPPUNIT_ASSERT_EQUAL( std::string("def"), std::string(vTokens[1]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[2]) );
    CPPUNIT_ASSERT_EQUAL( std::string("g"),   std::string(vTokens[3]) );
    CPPUNIT_ASSERT_EQUAL( std::string("h"),   std::string(vTokens[4]) );
    CPPUNIT_ASSERT_EQUAL( std::string("i"),   std::string(vTokens[5]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[6]) );

    return;
}

void  TextParserTest::testSplitText2()
{
    TextParser::TextBuffer  bufText;
    TextParser::TokenArray  vTokens;

    ErrCode retCode;
    retCode = TextParser::splitText(
                    "abc,\"123,456\",,def,,h", ",", bufText, vTokens);

    CPPUNIT_ASSERT_EQUAL(
            static_cast<int>(ErrCode::SUCCESS),
            static_cast<int>(retCode) );

    CPPUNIT_ASSERT_EQUAL(
            static_cast<size_t>(6),
            static_cast<size_t>(vTokens.size()) );

    CPPUNIT_ASSERT_EQUAL( std::string("abc"), std::string(vTokens[0]) );
    CPPUNIT_ASSERT_EQUAL( std::string("123,456"), std::string(vTokens[1]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[2]) );
    CPPUNIT_ASSERT_EQUAL( std::string("def"), std::string(vTokens[3]) );
    CPPUNIT_ASSERT_EQUAL( std::string(""),    std::string(vTokens[4]) );
    CPPUNIT_ASSERT_EQUAL( std::string("h"),   std::string(vTokens[5]) );

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
