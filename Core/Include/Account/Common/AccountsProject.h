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
**      プロジェクトの設定。
**
**      @file       Common/AccountsProject.h
**/

#if !defined( HACORE_COMMON_INCLUDED_ACCOUNTS_PROJECT_H )
#    define   HACORE_COMMON_INCLUDED_ACCOUNTS_PROJECT_H

//  スクリプトによる設定値が書き込まれたヘッダを読み込む。  //
#if defined( HOUSEHOLDACCOUNTS_USE_PRE_CONFIGURED_MSVC )
#    include    "Account/.Config/PreConfigHouseholdAccounts.msvc.h"
#else
#    include    "Account/.Config/ConfiguredHouseholdAccounts.h"
#endif

//  ビルドタイプが指定されていない場合はエラーにする。  //
#if defined( _DEBUG )
#
#elif defined( NDEBUG )
#
#else
#    error  "Neither _DEBUG nor NDEBUG defined"
#endif

HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
