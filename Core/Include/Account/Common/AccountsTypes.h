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

#if !defined( HACORE_COMMON_INCLUDED_ACCOUTNS_TYPES_H )
#    define   HACORE_COMMON_INCLUDED_ACCOUTNS_TYPES_H


#if !defined( HACORE_COMMON_INCLUDED_HOUSEHOLD_ACCOUNTS_SETTINGS_H )
#    include    "Account/Common/HouseholdAccountsSettings.h"
#endif

#if !defined( HACORE_SYS_INCLUDED_STDDEF_H )
#    include    <stddef.h>
#    define   HACORE_SYS_INCLUDED_STDDEF_H
#endif

#if !defined( HACORE_SYS_INCLUDED_STDINT_H )
#    include    <stdint.h>
#    define   HACORE_SYS_INCLUDED_STDINT_H
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

//========================================================================
//
//    Type Definitions.
//

//----------------------------------------------------------------
/**
**    エラーコード。
**/

enum class  ErrCode
{
    /**   正常終了。    **/
    SUCCESS             = 0,

    /**   異常終了。エラーの理由は不明または報告なし。  **/
    FAILURE             = 1,

    /**   ファイルオープンエラー。  **/
    FILE_OPEN_ERROR     = 2,

    /**   ファイル入出力エラー。    **/
    FILE_IO_ERROR       = 3,

    /**   無効なインデックス指定。  **/
    INDEX_OUT_OF_RANGE  = 4
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

typedef     int                 StringIndex;

//----------------------------------------------------------------
/**
**    勘定科目および分類のインデックス型。
**/

typedef     int                 CategoryHandle;

//----------------------------------------------------------------
/**
**
**/

typedef     int                 DateSerial;

typedef     int                 TimeSerial;

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
