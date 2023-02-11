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
**      An Implementation of StringTable class.
**
**      @file       Documents/StringTable.cpp
**/

#include    "Account/pch/PreCompile.h"

#include    "Account/Documents/StringTable.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Documents  {

namespace  {
}   //  End of (Unnamed) namespace.

//========================================================================
//
//    StringTable  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

StringTable::StringTable()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

StringTable::~StringTable()
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
//    テーブルの最後尾にデータを追加する。
//

StringIndex
StringTable::appendString(
        const  std::string  &strText)
{
    return ( static_cast<StringIndex>(0) );
}

//----------------------------------------------------------------
//    テーブルの整合性を検査する。
//

Boolean
StringTable::checkIntegrity()  const
{
    return ( Boolean::BOOL_FALSE );
}

//----------------------------------------------------------------
//    指定された文字列を検索する。
//

StringIndex
StringTable::findString(
        const  std::string  &strText)  const
{
    return ( static_cast<StringIndex>(-1) );
}

//----------------------------------------------------------------
//    新しいデータを挿入する。
//

StringIndex
StringTable::insertString(
        const  std::string  &strText)
{
    return ( static_cast<StringIndex>(-1) );
}

//----------------------------------------------------------------
//    データ用のバッファを確保する。
//

StringIndex
StringTable::reserveBuffer(
        const  StringIndex  bufSize)
{
    return ( static_cast<StringIndex>(-1) );
}

//----------------------------------------------------------------
//    テーブルのエントリを直接設定する。
//

StringIndex
StringTable::setTableEntry(
        const  StringIndex  drIndex,
        const  std::string  &steText,
        const  int          steFlag)
{
    return ( static_cast<StringIndex>(-1) );
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

}   //  End of namespace  Documents
HOUSEHOLD_ACCOUNTS_NAMESPACE_END
