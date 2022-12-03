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
**      An Interface of Receipt class(es).
**
**      @file       Interface/Receipt.h
**/

#pragma     once

#include    "HouseholdAccounts/Common/AccountsTypes.h"

namespace  Wrapper  {

//========================================================================
//
//    １回の買い物 (レシート１枚) の情報。
//

//========================================================================
/**
**    １個の商品。
**/

public value struct Goods
{
public:

    /**   ルートの項目インデックス。    **/
    int     nRootItemType;

    /**   項目インデックス。            **/
    int     nItemType;

    /**   商品名の ID  (文字列テーブル内のインデックス) 。  **/
    int     nGoodsNameID;

    /**   商品名。  **/
    System::String^     sGoodsName;

    /**   単価。    **/
    int     nUnitPrice;

    /**   数量。    **/
    int     nQuantity;

    /**   小計。    **/
    int     nSubTotal;

    /**   予約。    **/
    int     nReserved0;

};

//========================================================================
/**
**    １回の買い物 (レシート１枚) のデータ。
**/

public value struct Receipt
{
public:

    /**   フラグ。  **/
    int     nFlags;

    /**   購入した商品の数。        **/
    int     nNumGoods;

    /**   購入した商品のデータ。    **/
    cli::array<Goods, 1>^   utGoods;

    /**   小計。    **/
    int     nSubTotal;

    /**   内税。    **/
    int     nInsideTax;

    /**   外税。    **/
    int     nOutsideTax;

    /**   合計。    **/
    int     nTotal;

    /**   内税を加える項目インデックス。    **/
    int     nInsideTaxItemType;

    /**   外税を加える項目インデックス。    **/
    int     nOutsideTaxItemType;

    /**   予約。    **/
    int     nReserved0;

    /**   予約。    **/
    int     nReserved1;

};

//========================================================================
/**
**    １日の買い物。
**/

public value struct OneDayReceipts
{
public:

    /**   日付。            **/
    int     nDate;

    /**   レシートの枚数。  **/
    int     nNumReceipt;

    /**   各レシート。      **/
    cli::array<Receipt, 1>^     utReceipts;

};

}   //  End of namespace  Wrapper
