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
**      An Implementation of ReceiptInfo class.
**
**      @file       DocCls/ReceiptInfo.cpp
**/

#include    "Account/pch/PreCompile.h"
#include    "Account/DocCls/ReceiptInfo.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

namespace  {
}   //  End of (Unnamed) namespace.

//========================================================================
//
//    ReceiptInfo  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

ReceiptInfo::ReceiptInfo()
    : m_receiptDate(),
      m_receiptTime(),
      m_shopIdx(-1),
      m_shopName(),
      m_recordChunk(),
      m_totalCached(Boolean::BOOL_FALSE),
      m_subTotal(),
      m_sumInclusiveTax(0),
      m_sumExclusiveTax(0),
      m_totalPrice(0),
      m_chInclusiveTax(-1),
      m_chExclusiveTax(-1)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ReceiptInfo::~ReceiptInfo()
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
//    レシート情報を初期化する。
//

ErrCode
ReceiptInfo::initializeReceiptInfo(
        const  std::string  &recDate,
        const  std::string  &recTime,
        const  std::string  &shopName)
{
    this->m_receiptDate = recDate;
    this->m_receiptTime = recTime;
    this->m_shopName    = shopName;

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    インスタンスを文字列表現に変換する。
//

const   std::string
ReceiptInfo::toString()  const
{
    std::stringstream   ss;
    this->writeToStream(ss);
    return  ss.str();
}

//----------------------------------------------------------------
//    インスタンスの文字列表現をストリームに書き込む。
//

std::ostream  &
ReceiptInfo::writeToStream(
        std::ostream  & os)  const
{
    return  writeToStream("\n", os);
}

//----------------------------------------------------------------
//    インスタンスの文字列表現をストリームに書き込む。
//

std::ostream  &
ReceiptInfo::writeToStream(
        const  std::string  & sep,
        std::ostream        & os)  const
{
    os  <<  this->m_receiptDate <<  ';'
        <<  this->m_receiptTime <<  ';'
        <<  this->m_shopName    <<  ';';

    const  std::string  lineSep(sep + ";;;");

    ChunkIndex          idx = static_cast<ChunkIndex>(0);
    const   ChunkIndex
        num = static_cast<ChunkIndex>(this->m_recordChunk.size());

    if ( idx < num ) {
        this->m_recordChunk[idx].writeToStream(lineSep, os);
    }
    for ( ++ idx; idx < num; ++ idx ) {
        os  <<  lineSep;
        this->m_recordChunk.at(idx).writeToStream(lineSep, os);
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

//----------------------------------------------------------------
//    レコードを取得する。
//

const   ReceiptInfo::ChunkArray  &
ReceiptInfo::getRecordChunks()  const
{
    return ( this->m_recordChunk );
}

//----------------------------------------------------------------
//    店名を取得する。
//

const  std::string  &
ReceiptInfo::getShopName()  const
{
    return ( this->m_shopName );
}

//----------------------------------------------------------------
//    店名を設定する。
//

ReceiptInfo  &
ReceiptInfo::setShopName(
        const  std::string  &shopName)
{
    this->m_shopName    = shopName;
    return ( *this );
}

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
