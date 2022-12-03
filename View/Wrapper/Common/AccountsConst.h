//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**              ---  Household Accounts  Wrapper Lib.  ---              **
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
**      Constant Definitions.
**
**      @file       Common/AccountsConst.h
**/

#if !defined( HAWRAPPER_COMMON_INCLUDED_ACCOUNTS_CONST_H )
#    define   HAWRAPPER_COMMON_INCLUDED_ACCOUNTS_CONST_H

#pragma     once

#include    "HouseholdAccounts/Common/AccountsTypes.h"

namespace  Wrapper  {

const   int     DAY_START   = 6;
const   int     MAXITEMS    = 65536;
const   int     MAXBALANCES = 256;

constexpr   int     MAX_DAYS    = 378;
constexpr   int     MAX_WEEKS   = 54;
constexpr   int     MAX_MONTH   = 12;

}   //  End of namespace  Wrapper

#endif
