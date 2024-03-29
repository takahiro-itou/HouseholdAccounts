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
**      An Implementation of PurchasedGoods class.
**
**      @file       DocCls/PurchasedGoods.cpp
**/

#include    "Account/pch/PreCompile.h"
#include    "Account/DocCls/PurchasedGoods.h"

#include    "Account/DocCls/CategoryManager.h"

#include    <sstream>


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

namespace  {

//----------------------------------------------------------------
/** 　　項目ハンドルから項目名を取得する
**
**/

const  std::string  &
getCategoryName(
        const   CategoryManager  *  pCatMan,
        const   CategoryHandle      hCate)
{
    return  pCatMan->getBookCategory(hCate).getCategoryName();
}

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    PurchasedGoods  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

PurchasedGoods::PurchasedGoods()
    : accountHeadings(-1),
      accountCategory(-1),
      siGoodsId(-1),
      productName(),
      unitPrice(0),
      nQuantity(0),
      cDiscount(0),
      exclusiveTaxVal(0),
      inclusiveTaxVal(0),
      cSubTotal(0),
      pCatMan(nullptr)
{
}

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

PurchasedGoods::PurchasedGoods(
        const  CategoryManager  &cateManager)
    : accountHeadings(-1),
      accountCategory(-1),
      siGoodsId(-1),
      productName(),
      unitPrice(0),
      nQuantity(0),
      cDiscount(0),
      exclusiveTaxVal(0),
      inclusiveTaxVal(0),
      cSubTotal(0),
      pCatMan(&cateManager)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

PurchasedGoods::~PurchasedGoods()
{
}

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

//----------------------------------------------------------------
//    インスタンスを文字列表現に変換する。
//

const   std::string
PurchasedGoods::toString()  const
{
    std::stringstream   ss;
    this->writeToStream(ss);
    return  ss.str();
}

//----------------------------------------------------------------
//    インスタンスの文字列表現をストリームに書き込む。
//

std::ostream  &
PurchasedGoods::writeToStream(
        std::ostream  & os)  const
{
    if ( pCatMan != nullptr ) {
        os  <<  getCategoryName(pCatMan, this->accountHeadings)
            <<  ';'
            <<  getCategoryName(pCatMan, this->accountCategory)
            <<  ';';
    } else {
        os  <<  this->accountHeadings   <<  ';'
            <<  this->accountCategory   <<  ';';
    }

    os  <<  this->productName   <<  ';'
        <<  this->unitPrice     <<  ';'
        <<  this->nQuantity     <<  ';'
        <<  this->cDiscount     <<  ';'
        <<  this->exclusiveTaxVal   <<  ';'
        <<  this->inclusiveTaxVal;

    return ( os );
}

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

}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END
