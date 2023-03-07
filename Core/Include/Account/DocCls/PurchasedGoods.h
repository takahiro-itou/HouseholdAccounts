﻿//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Household Accounts Core.  ---                  **
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
**      An Interface of PurchasedGoods struct.
**
**      @file       DocCls/PurchasedGoods.h
**/

#if !defined( HACORE_DOCCLS_INCLUDED_PURCHASED_GOODS_H )
#    define   HACORE_DOCCLS_INCLUDED_PURCHASED_GOODS_H


#if !defined( HACORE_COMMON_INCLUDED_ACCOUTNS_TYPES_H )
#    include    "Account/Common/AccountsTypes.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    PurchasedGoods  struct.
//
/**
**    商品の一個分のデータ。
**
**    購入した商品やサービス、または
**  収入や資金振替の場合は財源等を管理する。
**/

struct  PurchasedGoods
{
//========================================================================
//
//    Internal Type Definitions.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    PurchasedGoods();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~PurchasedGoods();

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

//========================================================================
//
//    Public Member Functions (Operators).
//

//========================================================================
//
//    Accessors.
//

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
public:

    /**   勘定科目。    **/
    CategoryHandle  accountHeadings;

    /**   分類 (内訳) 。    **/
    CategoryHandle  accountCategory;

    /**   商品名の ID  (文字列テーブル内のインデックス) 。  **/
    StringIndex     siGoodsId;

    /**   商品名。  **/
    std::string     productName;

    /**   単価。    **/
    int             unitPrice;

    /**   数量。    **/
    int             nQuantity;

    /**   値引額。  **/
    int             cDiscount;

    /**   小計。    **/
    int             cSubTotal;

    /**
    **    内税額。
    **
    **  税込み価格ではなく税金額そのもの。
    **/
    int             inclusiveTaxVal;

    /**
    **    外税額。
    **
    **  税抜き価格ではなく税金額そのもの。
    **/
    int             exclusiveTaxVal;

private:

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   PurchasedGoodsTest;
};

}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
