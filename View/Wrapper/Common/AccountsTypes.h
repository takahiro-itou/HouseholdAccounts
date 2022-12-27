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

#include    "Account/Common/AccountsTypes.h"

namespace  Wrapper  {

typedef     HouseholdAccounts::ErrCode  WrapTargetErrCode;

public  enum class  ErrCode
{
    SUCCESS             = WrapTargetErrCode::SUCCESS,
    FAILURE             = WrapTargetErrCode::FAILURE,
    FILE_OPEN_ERROR     = WrapTargetErrCode::FILE_OPEN_ERROR,
    FILE_IO_ERROR       = WrapTargetErrCode::FILE_IO_ERROR,
    INDEX_OUT_OF_RANGE  = WrapTargetErrCode::INDEX_OUT_OF_RANGE
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

//========================================================================

typedef     HouseholdAccounts::CategoryHandle   CategoryHandle;
typedef     HouseholdAccounts::DateSerial       DateSerial;
typedef     HouseholdAccounts::StringIndex      StringIndex;

//========================================================================
//
//    配列型。
//

}   //  End of namespace  Wrapper

#endif
