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
**      An Interface of BookItem class(es).
**
**      @file       Interface/BookItem.h
**/

#if !defined( HAWRAPPER_INTERFACE_INCLUDED_BOOK_ITEM_H )
#    define   HAWRAPPER_INTERFACE_INCLUDED_BOOK_ITEM_H

#pragma     once

#include    "HouseholdAccounts/Common/AccountsTypes.h"

namespace  Wrapper  {

//========================================================================
//
//    Type Definitions.
//
//    家計簿内の各項目、口座 (現金を含む) 残高。
//

/**
**    項目用フラグ。
**/

public  enum class  ItemFlag
{
    ITEM_FLAG_TYPEMASK          = 0x000000ff,

    ITEM_FLAG_NOTUSED           = 0,    /**<  未使用。          **/
    ITEM_FLAG_INHERIT           = 1,    /**<  親の設定を継承。  **/
    ITEM_FLAG_BALANCE           = 9,    /**<  残高表示。        **/
    ITEM_FLAG_INCOME            = 17,   /**<  収入。            **/
    ITEM_FLAG_OUTLAY            = 18,   /**<  支出。            **/
    ITEM_FLAG_BANK              = 25,   /**<  銀行口座。        **/
    ITEM_FLAG_BANK_WITHDRAW     = 26,   /**<  口座引出。        **/
    ITEM_FLAG_BANK_DEPOSIT      = 27,   /**<  口座入金。        **/
    ITEM_FLAG_BANK_TRANSFER     = 28,   /**<  口座振替。        **/

    ITEM_FLAG_EXPANDED          = 0x00000100,

    ITEM_FLAG_NOCOUNT_PARENT    = 0x00010000,
    ITEM_FLAG_NOCOUNT_ROOT      = 0x00020000,
    ITEM_FLAG_HIDEN             = 0x10000000,
    ITEM_FLAG_UNERASABLE        = 0x20000000,
    ITEM_FLAG_READONLY          = 0x40000000
};

//========================================================================
/**
**    データ項目。
**/

public value struct BookItemEntry
{
public:

    /**   親項目のハンドル。    **/
    property    int     nParentHandle;

    /**   項目名の ID  (文字列テーブル内のインデックス) 。  **/
    property    int     nItemNameID;

    /**   項目名。  **/
    property    System::String^     sItemName;

    /**   サブ項目数。  **/
    property    int     nSubItemCount;

    /**   サブ項目のハンドル (インデックス) 。  **/
    property    cli::array<int, 1>^     nSubItems;

    /**   開始年月日 (残高の項目のみ) 。    **/
    property    int     nStartDate;

    /**   開始時の残高 (残高の項目のみ) 。  **/
    property    int     nStartBalance;
};

//========================================================================
/**
**    項目一覧。
**/

public value struct BookItems
{
//========================================================================
//
//    Internal Type Definitions.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//========================================================================
//
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   指定した項目を展開したり閉じたりする。
    **
    **  @param [in] lngItemIndex    項目番号。
    **  @param [in] blnExpanded     展開または折畳。
    **  @return     void.
    **/
    void
    expandItem(
            const  int              lngItemIndex,
            const  System::Boolean  blnExpanded);

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   項目用のバッファのサイズを得る。
    **
    **  @return     項目用バッファのサイズ。
    **/
    int
    getItemBufferSize();

    //----------------------------------------------------------------
    /**   項目の名前を取得する。
    **
    **  @param [in] lngItemIndex    項目番号。
    **/
    System::String^
    getItemName(
            const  int  lngItemIndex);

    //----------------------------------------------------------------
    /**   項目の種類を取得する。
    **
    **  @param [in] lngItemIndex    項目番号。
    **/
    int
    getItemType(
            const  int  lngItemIndex);

    //----------------------------------------------------------------
    /**   使用済みの項目数を取得する。
    **
    **  @return     使用済みの項目数を返す。
    **/
    int
    getRegisteredItemCount();

    //----------------------------------------------------------------
    /**   ルートにある項目数を取得する。
    **
    **  @return     ルートの項目数を返す。
    **/
    int
    getRootItemCount();

    //----------------------------------------------------------------
    /**   項目のルート項目のハンドルを取得する。
    **
    **  @param [in] lngItemIndex    項目番号。
    **  @return     項目がルート項目を示している場合は、
    **      それ自身を返す。
    **/
    int
    getRootItemHandle(
            const  int  lngItemIndex);

    //----------------------------------------------------------------
    /**   項目が持つサブ項目の個数を取得する。
    **
    **  @param [in] lngItemIndex    項目番号。
    **  @return     サブ項目の個数を返す。
    **/
    int
    getSubItemCount(
            const  int  lngItemIndex);

    //----------------------------------------------------------------
    /**   指定した項目が展開されているか調べる。
    **
    **  @param [in] lngItemIndex   項目番号。
    **  @retval
    **/
    System::Boolean
    isItemExpanded(
            const  int  lngItemIndex);

//========================================================================
//
//    Properties.
//
public:

    /**   項目用バッファサイズ。    **/
    property    int     nItemBufferSize;

    /**   登録済み項目数。          **/
    property    int     nRegisteredItemCount;

    /**   ルートになる項目の数。    **/
    property    int     nRootItemCount;

    /**   項目のフラグ。            **/
    property    cli::array<int, 1>^         nFlags;

    /**   項目データ。              **/
    property    cli::array<BookItemEntry>^  utItemEntries;

    /**   「内税」項目のハンドル。  **/
    property    int     nInnerTaxItemHandle;

    /**   「外税」項目のハンドル。  **/
    property    int     nOuterTaxItemHandle;

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//

};

}   //  End of namespace  Wrapper

#endif
