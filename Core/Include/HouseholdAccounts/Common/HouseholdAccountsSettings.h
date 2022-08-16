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
**      @file       Common/HouseholdAccountsSettings.h
**/

#if !defined( HACCOUNTS_COMMON_INCLUDED_HOUSEHOLD_ACCOUNTS_SETTINGS_H )
#    define   HACCOUNTS_COMMON_INCLUDED_HOUSEHOLD_ACCOUNTS_SETTINGS_H

//  スクリプトによる設定値が書き込まれたヘッダを読み込む。  //
#if defined( HOUSEHOLDACCOUNTS_USE_PRE_CONFIGURED_MSVC )
#    include    "HouseholdAccounts/.Config/PreConfigHouseholdAccounts.msvc.h"
#else
#    include    "HouseholdAccounts/.Config/ConfiguredHouseholdAccounts.h"
#endif

HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
