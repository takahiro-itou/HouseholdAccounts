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
**      An Interface of Test Driver.
**
**      @file       Tests/TestDriver.h
**/

#if !defined( HACORE_TESTS_INCLUDED_TEST_DRIVER_H )
#    define   HACORE_TESTS_INCLUDED_TEST_DRIVER_H

//----------------------------------------------------------------
/**   単体テストを起動するエントリポイント。
**
**  @param [in] argc
**  @param [in] argv
**  @return
**/

int
executeCppUnitTests(
        int     argc,
        char *  argv[]);

#if ( HAVE_CPPUNIT )

#    include    <cppunit/extensions/HelperMacros.h>

using   namespace   CPPUNIT_NS;

#else   //  if ! ( HAVE_CPPUNIT )

#include    <iostream>
#include    <stdlib.h>

#if !defined( HACORE_COMMON_INCLUDED_ACCOUTNS_TYPES_H )
#    include    "Account/Common/AccountsTypes.h"
#endif

class   TestFixture
{
public:
    TestFixture();
    virtual  ~TestFixture();

    virtual  void   setUp();
    virtual  void   tearDown();
};

#define     CPPUNIT_TEST_SUITE(classname)       \
public:                                         \
    classname() {                               \
        executeTests();                         \
   }                                            \
protected:                                      \
    void  executeTests()  {

#define     CPPUNIT_TEST(funcname)              \
    funcname()

#define     CPPUNIT_TEST_SUITE_END()            \
    }                                           \
    static  void  run()

#define     CPPUNIT_TEST_SUITE_REGISTRATION(classname)  \
    classname   g_ ## classname ## _Instance;


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

template  <typename  T>
void  assertEqual(
        const  T  &     vExp,
        const  T  &     vAct,
        const  char  *  szFile,
        const  int      nLine)
{
    if ( vExp != vAct ) {
        std::cerr   <<  "\nEquality Assertion Failed."
                    <<  "\n  Expected : "   <<  vExp
                    <<  "\n  Actual   : "   <<  vAct
                    <<  std::endl;
        exit ( 1 );
    }
    return;
}

template  <typename  T>
void  assertBool(
        const  T  &     vAct,
        const  char  *  szFile,
        const  int      nLine)
{
    if ( (vAct) == (Boolean::BOOL_FALSE) ) {
        std::cerr   <<  "\nAssertion Failed."
                    <<  "\n  Actual   : "
                    <<  static_cast<bool>(vAct)
                    <<  std::endl;
        exit ( 1 );
    }
    return;
}

HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#define     CPPUNIT_ASSERT_EQUAL(exp, act)      \
    assertEqual(exp,  act,  __FILE__,  __LINE__)

#define     CPPUNIT_ASSERT(act)                 \
    assertBool(TO_STRICT_FROM_BOOL(act), __FILE__, __LINE__)

#endif

#endif
