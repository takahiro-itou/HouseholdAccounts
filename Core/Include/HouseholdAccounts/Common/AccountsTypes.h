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
**      Type Definitions.
**
**      @file       Common/AccountsTypes.h
**/

#if !defined( HACCOUNTS_COMMON_INCLUDED_ACCOUTNS_TYPES_H )
#    define   HACCOUNTS_COMMON_INCLUDED_ACCOUTNS_TYPES_H

#include    "HouseholdAccounts/Common/HouseholdAccountsSettings.h"

#include    <stddef.h>

HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

//========================================================================
//
//    Type Definitions.
//

//----------------------------------------------------------------
/**
**    エラーコード。
**/

enum  ErrCode
{

    /**   正常終了。    **/
    ERR_SUCCESS             = 0,

    /**   異常終了。エラーの理由は不明または報告なし。  **/
    ERR_FAILURE             = 1,

    /**   ファイルオープンエラー。  **/
    ERR_FILE_OPEN_ERROR     = 2,

    /**   ファイル入出力エラー。    **/
    ERR_FILE_IO_ERROR       = 3,

    /**   無効なインデックス指定。  **/
    ERR_INDEX_OUT_OF_RANGE  = 4
};

//----------------------------------------------------------------
/**
**    型安全なブール型。
**/

enum  Boolean
{
    BOOL_FALSE  =  0,       /**<  偽。  **/
    BOOL_TRUE   =  1        /**<  真。  **/
};

//----------------------------------------------------------------
/**
**    文字列インデックス型。
**/

typedef     int64_t             StringIndex;

//----------------------------------------------------------------
/**
**    ファイルの長さを表す型。
**/

typedef     size_t              FileLength;

//----------------------------------------------------------------
/**
**    バッファサイズ（要素数）を表す型。
**/

typedef     size_t              BufferSize;

//----------------------------------------------------------------
/**
**    読み取り専用バッファ。
**/

typedef     const  void  *      LpcReadBuf;

//----------------------------------------------------------------
/**
**    読み書き両用バッファ。
**/

typedef     void  *             LpWriteBuf;

//----------------------------------------------------------------
/**
**    バイト型。
**/

typedef     unsigned char       BtByte;

/**
**    バイト型の読み取り専用バッファ。
**/

typedef     const  BtByte  *    LpcByteReadBuf;

/**
**    バイト型の読み書き両用バッファ。
**/

typedef     BtByte  *           LpByteWriteBuf;

//========================================================================
//
//    安全なポインタ型のキャスト。
//

template  <typename  T>
T  pointer_cast(void  *  p)
{
    return ( static_cast<T>(p) );
}

template  <typename  T>
T  pointer_cast(const  void  *  p)
{
    return ( static_cast<T>(p) );
}

HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
