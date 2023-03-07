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


#if !defined( HACORE_COMMON_INCLUDED_ACCOUNTS_PROJECT_H )
#    include    "Account/Common/AccountsProject.h"
#endif

#if !defined( HACORE_COMMON_INCLUDED_STRICT_TYPES_H )
#    include    "Account/Common/StrictTypes.h"
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

#if defined( _DEBUG ) && !defined( HACORE_DISABLE_STRICT_TYPES )

enum  class Boolean : int
{
    BOOL_FALSE  =  0,       /**<  偽。  **/
    BOOL_TRUE   =  1        /**<  真。  **/
};

#define     TO_STRICT_FROM_BOOL(b)      static_cast<Boolean>(b)
#define     TO_SBOOLEAN_FROM_INT(b)     \
    static_cast<Boolean>(static_cast<int>(b) != 0)
#define     TO_BOOL_FROM_STRICT(sb)     ((sb) != Boolean::BOOL_FALSE)

#else

enum  Boolean : int
{
    BOOL_FALSE  = 0,
    BOOL_TRUE   = 1,
};

#define     TO_STRICT_FROM_BOOL(b)      static_cast<Boolean>(b)
#define     TO_SBOOLEAN_FROM_INT(b)     \
    static_cast<Boolean>(static_cast<int>(b) != 0)
#define     TO_BOOL_FROM_STRICT(sb)     (sb)

#endif

//----------------------------------------------------------------
//
//    厳格な型の宣言を行うマクロ。
//  デバッグ版では、厳格な型を利用する。
//

#if defined( _DEBUG ) && !defined( HACORE_DISABLE_STRICT_TYPES )

#    define     DECLARE_STRICT_TYPE(BaseType, DeclType)         \
    struct tag_Type_ ## DeclType;                               \
    typedef                                                     \
    Common::StrictTypes<BaseType, tag_Type_ ## DeclType>        \
    DeclType

#    define     DECLARE_STRICT_VECTOR(ValT, IdxT, DeclType)     \
    typedef     Common::StrictVector<ValT, IdxT>    DeclType

#    define     TO_VALUE_FROM_STRICT(sv)    sv.getValue()

#else

#    define     DECLARE_STRICT_TYPE(BaseType, DeclType)         \
    typedef     BaseType    DeclType

#    define     DECLARE_STRICT_VECTOR(ValT, IdxT, DeclType)     \
    typedef     std::vector<ValT>   DeclType

#    define     TO_VALUE_FROM_STRICT(sv)    (sv)

#endif

//----------------------------------------------------------------
/**
**    文字列インデックス型。
**/

DECLARE_STRICT_TYPE(int,        StringIndex);

//----------------------------------------------------------------
/**
**    勘定科目および分類のインデックス型。
**/

DECLARE_STRICT_TYPE(int,        CategoryHandle);

//----------------------------------------------------------------
/**
**    項目内のサブ項目のインデックス型。
**/

DECLARE_STRICT_TYPE(int,        SubCategoryIdx);

//----------------------------------------------------------------
/**
**    商品インデックス型。
**/

DECLARE_STRICT_TYPE(int,        MerchandiseIdx);

//----------------------------------------------------------------
/**
**    レシートインデックス型。
**/

DECLARE_STRICT_TYPE(int,        ReceiptIndex);

//----------------------------------------------------------------
/**
**
**/

DECLARE_STRICT_TYPE(int,        DateSerial);

DECLARE_STRICT_TYPE(int,        TimeSerial);

//----------------------------------------------------------------
/**
**    ファイルの長さを表す型。
**/

DECLARE_STRICT_TYPE(size_t,     FileLength);

//----------------------------------------------------------------
/**
**    バッファサイズ（要素数）を表す型。
**/

DECLARE_STRICT_TYPE(size_t,     BufferSize);

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
