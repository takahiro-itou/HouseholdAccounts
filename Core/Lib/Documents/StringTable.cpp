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
    : m_bufferSize(0),
      m_numEntries(0),
      m_flagSorted(StringTableSort::TABLE_SORT_NONE),
      m_entryFlags(),
      m_tableEntry(),
      m_sortedIndex()
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
    const  StringIndex  si  = this->m_numEntries ++;
    reserveBuffer(this->m_numEntries);

    this->m_entryFlags [si] = 0;
    this->m_tableEntry [si] = strText;
    this->m_sortedIndex[si] = si;

    return ( si );
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
    const  StringIndex  siAlloc = (bufSize + 15) & ~15;
    if ( siAlloc <= this->m_bufferSize ) {
        return ( this->m_bufferSize );
    }

    this->m_entryFlags.resize(siAlloc);
    this->m_tableEntry.resize(siAlloc);
    this->m_sortedIndex.resize(siAlloc);

    return ( this->m_bufferSize = siAlloc );
}

//----------------------------------------------------------------
//    テーブルのエントリを直接設定する。
//

StringIndex
StringTable::setTableEntry(
        const  StringIndex  drIndex,
        const  std::string  &steText,
        const  EntryFlags   steFlag)
{
    reserveBuffer(drIndex + 1);

    this->m_entryFlags[drIndex] = steFlag;
    this->m_tableEntry[drIndex] = steText;

    return ( drIndex );
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

//----------------------------------------------------------------
//    データを検索する。
//

inline  StringTable::FindResult
StringTable::searchEntry(
        const  std::string  &strText)  const
{
    FindResult      result;

    //  念のため番兵を立てる。  //
    result.flgFound = Boolean::BOOL_FALSE;
    result.siResult = static_cast<StringIndex>(-1);
    result.siInsert = static_cast<StringIndex>(-1);

    return ( result );
}

//========================================================================
//
//    Other Features.
//

//----------------------------------------------------------------
//    ユニットテスト用インターフェイス。
//

StringTable::FindResult
StringTable::searchEntryTest(
        const  std::string  &strText)  const
{
    return ( searchEntry(strText) );
}

}   //  End of namespace  Documents
HOUSEHOLD_ACCOUNTS_NAMESPACE_END
