//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**              ---  Household Accounts  Wrapper Lib.  ---              **
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
**      Type Definitions.
**
**      @file       Common/AccountsTypes.h
**/

#if !defined( HAWRAPPER_COMMON_INCLUDED_ACCOUNTS_TYPES_H )
#    define   HAWRAPPER_COMMON_INCLUDED_ACCOUNTS_TYPES_H

#pragma     once

#include    "Account/Common/AccountsTypes.h"

namespace  Wrapper  {

typedef     HABook::ErrCode     WrapTargetErrCode;

public  enum class  ErrCode
{
    SUCCESS             = WrapTargetErrCode::SUCCESS,
    FAILURE             = WrapTargetErrCode::FAILURE,
    FILE_OPEN_ERROR     = WrapTargetErrCode::FILE_OPEN_ERROR,
    FILE_IO_ERROR       = WrapTargetErrCode::FILE_IO_ERROR,
    INDEX_OUT_OF_RANGE  = WrapTargetErrCode::INDEX_OUT_OF_RANGE
};

//================================================================
//
//    ブール型。
//

typedef     HABook::Boolean             Boolean;

inline  Boolean
toNativeBoolean(
        System::Boolean b)
{
    return ( static_cast<Boolean>(b) );
}

inline  System::Boolean
fromNativeBoolean(
        Boolean b)
{
    return ( TO_BOOL_FROM_STRICT(b) );
}

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

typedef     HABook::CategoryHandle      CategoryHandle;
typedef     HABook::DateSerial          DateSerial;
typedef     HABook::StringIndex         StringIndex;

//========================================================================
//
//    配列型。
//

//========================================================================
//
//    コアライブラリ内のネイティブ型との相互変換。
//

}   //  End of namespace  Wrapper

#endif
