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
**      An Implementation of ReceiptFile class.
**
**      @file       Format/ReceiptFile.cpp
**/

#include    "Account/pch/PreCompile.h"
#include    "Account/Format/ReceiptFile.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Format  {

namespace  {
}   //  End of (Unnamed) namespace.

//========================================================================
//
//    ReceiptFile  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

ReceiptFile::ReceiptFile()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ReceiptFile::~ReceiptFile()
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

//----------------------------------------------------------------
//    データをテキストファイルから読み込む。
//

ErrCode
ReceiptFile::readFromTextFile(
        const   std::string   & fileName,
        DocCls::ReceiptInfo   * ptrDoc)
{
    return ( ErrCode::FAILURE );
}

//----------------------------------------------------------------
//    データをテキストストリームから読み込む。
//

ErrCode
ReceiptFile::readFromTextStream(
        std::istream          & inStr,
        DocCls::ReceiptInfo   * ptrDoc)
{
    return ( ErrCode::FAILURE );
}

//----------------------------------------------------------------
//    データをテキストストリームに書き込む。
//

ErrCode
ReceiptFile::saveToTextStream(
        const   DocCls::ReceiptInfo   & objDoc,
        std::ostream                  & outStr)
{
    return ( ErrCode::FAILURE );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Format
HOUSEHOLD_ACCOUNTS_NAMESPACE_END
