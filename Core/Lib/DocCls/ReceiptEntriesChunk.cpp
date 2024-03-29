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
**      An Implementation of ReceiptEntriesChunk class.
**
**      @file       DocCls/ReceiptEntriesChunk.cpp
**/

#include    "Account/pch/PreCompile.h"
#include    "Account/DocCls/ReceiptEntriesChunk.h"

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
//    ReceiptEntriesChunk  struct.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

ReceiptEntriesChunk::ReceiptEntriesChunk()
    : blockFlags(),
      chlDebitAccount (-1),
      chrCreditAccount(-1),
      cnlDebitAmount  ( 0),
      cnrCreditAmount ( 0),
      goodsList(),
      pCatMan(nullptr)
{
}

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

ReceiptEntriesChunk::ReceiptEntriesChunk(
        const  CategoryManager  &cateManager)
    : blockFlags(),
      chlDebitAccount (-1),
      chrCreditAccount(-1),
      cnlDebitAmount  ( 0),
      cnrCreditAmount ( 0),
      goodsList(),
      pCatMan(&cateManager)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ReceiptEntriesChunk::~ReceiptEntriesChunk()
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
ReceiptEntriesChunk::toString()  const
{
    std::stringstream   ss;
    this->writeToStream(ss);
    return  ss.str();
}

//----------------------------------------------------------------
//    インスタンスの文字列表現をストリームに書き込む。
//

std::ostream  &
ReceiptEntriesChunk::writeToStream(
        std::ostream  & os)  const
{
    return  writeToStream("\n", os);
}

//----------------------------------------------------------------
//    インスタンスの文字列表現をストリームに書き込む。
//

std::ostream  &
ReceiptEntriesChunk::writeToStream(
        const  std::string  & sep,
        std::ostream        & os)  const
{
    switch ( this->blockFlags ) {
    case  ChunkInOutFlags::DOUBLE_ENTRY:
        os  <<  "複式";
        break;
    case  ChunkInOutFlags::INCOME:
        os  <<  "収入";
        break;
    case  ChunkInOutFlags::OUTLAY:
        os  <<  "支出";
        break;
    case  ChunkInOutFlags::BANK_WITHDRAW:
        os  <<  "口座引出";
        break;
    case  ChunkInOutFlags::BANK_DEPOSIT:
        os  <<  "口座預入";
        break;
    case  ChunkInOutFlags::BANK_TRANSFER:
        os  <<  "口座振替";
        break;
    }

    os  <<  ';';
    if ( this->chlDebitAccount >= 0 ) {
        os  <<  getCategoryName(this->pCatMan, chlDebitAccount);
    }
    os  <<  ';';
    if ( this->chrCreditAccount >= 0 ) {
        os  <<  getCategoryName(this->pCatMan, chrCreditAccount);
    }
    os  <<  ';';

    const  std::string  lineSep(sep + ";;;");

    PurchaseNumber  idx = static_cast<PurchaseNumber>(0);
    const   PurchaseNumber  num = this->goodsList.size();

    if ( idx < num ) {
        this->goodsList[idx].writeToStream(os);
    }
    for ( ++ idx; idx < num; ++ idx )
    {
        os  <<  lineSep;
        this->goodsList[idx].writeToStream(os);
    }

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
