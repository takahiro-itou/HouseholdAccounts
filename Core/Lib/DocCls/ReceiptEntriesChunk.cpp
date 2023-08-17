//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
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


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

namespace  {
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
