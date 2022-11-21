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
    property    int     nRootItemType;

    /**   項目インデックス。            **/
    property    int     nItemType;

    /**   商品名の ID  (文字列テーブル内のインデックス) 。  **/
    property    int     nGoodsNameID;

    /**   商品名。  **/
    property    System::String^     sGoodsName;

    /**   単価。    **/
    property    int     nUnitPrice;

    /**   数量。    **/
    property    int     nQuantity;

    /**   小計。    **/
    property    int     nSubTotal;

    /**   予約。    **/
    property    int     nReserved0;
};

//========================================================================
/**
**    １回の買い物 (レシート１枚) のデータ。
**/

public value struct Receipt
{
public:

    /**   フラグ。  **/
    property    int     nFlags;

    /**   購入した商品の数。        **/
    property    int     nNumGoods

    /**   購入した商品のデータ。    **/
    property    cli::array<Goods, 1>^   utGoods;

    /**   小計。    **/
    property    int     nSubTotal;

    /**   内税。    **/
    property    int     nInsideTax;

    /**   外税。    **/
    property    int     nOutsideTax;

    /**   合計。    **/
    property    int     nTotal;

    /**   内税を加える項目インデックス。    **/
    property    int     nInsideTaxItemType;

    /**   外税を加える項目インデックス。    **/
    property    int     nOutsideTaxItemType;

    /**   予約。    **/
    property    int     nReserved0;

    /**   予約。    **/
    property    int     nReserved1;
};

}   //  End of namespace  Wrapper
