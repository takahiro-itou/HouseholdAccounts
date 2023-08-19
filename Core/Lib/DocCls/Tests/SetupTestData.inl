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


#include    "Account/DocCls/CategoryManager.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

inline  Boolean
Boolean
setupCategoryManager1(
        CategoryManager &cateMan)
{
    return ( Boolean::BOOL_TRUE );
}

}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END
