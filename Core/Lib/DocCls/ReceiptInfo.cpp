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

//========================================================================
//
//    Public Member Functions (Operators).
//

//========================================================================
//
//    Accessors.
//

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
