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
**      Type Definitions.
**
**      @file       Common/AccountsTypes.h
**/

#if !defined( HAWRAPPER_COMMON_INCLUDED_ACCOUNTS_TYPES_H )
#    define   HAWRAPPER_COMMON_INCLUDED_ACCOUNTS_TYPES_H

#pragma     once

#include    "HouseholdAccounts/Common/AccountsTypes.h"

namespace  Wrapper  {

public  enum class  ErrCode
{
    ERR_SUCCESS             = HouseholdAccounts::ERR_SUCCESS,
    ERR_FAILURE             = HouseholdAccounts::ERR_FAILURE,
    ERR_FILE_OPEN_ERROR     = HouseholdAccounts::ERR_FILE_OPEN_ERROR,
    ERR_FILE_IO_ERROR       = HouseholdAccounts::ERR_FILE_IO_ERROR,
    ERR_INDEX_OUT_OF_RANGE  = HouseholdAccounts::ERR_INDEX_OUT_OF_RANGE
};

//----------------------------------------------------------------
/**
**
**/

typedef     int                 IOffsetType;

//----------------------------------------------------------------
/**
**    文字列の配列型。
**/

typedef     cli::array<System::String^, 1>      StringArray;

}   //  End of namespace  Wrapper

#endif
