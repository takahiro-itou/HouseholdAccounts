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
**      An Implementation of StringTable class.
**
**      @file       DocCls/StringTable.cpp
**/

#include    "Account/pch/PreCompile.h"
#include    "Account/DocCls/StringTable.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

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
      m_entryArray(),
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
StringTable::allocEntry(
        const  std::string  &steText,
        const  EntryFlags   steFlag)
{
    const  StringIndex  si  = this->m_numEntries ++;
    reserveBuffer(this->m_numEntries);

    this->m_entryArray[si].steText  = steText;
    this->m_entryArray[si].steFlag  = steFlag;
    this->m_sortedIndex[si] = si;

    return ( si );
}

//----------------------------------------------------------------
//    テーブルの最後尾にデータを追加する。
//

StringIndex
StringTable::appendString(
        const  std::string  &steText)
{
    const  StringIndex  si  = this->m_numEntries ++;
    reserveBuffer(this->m_numEntries);

    this->m_entryArray[si].steText  = steText;

    return ( si );
}

//----------------------------------------------------------------
//    テーブルの整合性を検査する。
//

Boolean
StringTable::checkIntegrity()  const
{
    for ( StringIndex i = static_cast<StringIndex>(1);
            i < this->m_numEntries; ++ i )
    {
        const  StringIndex  siL = this->m_sortedIndex[i - 1];
        const  StringIndex  siR = this->m_sortedIndex[i];

        const  std::string  &sL = this->m_entryArray.at(siL).steText;
        const  std::string  &sR = this->m_entryArray.at(siR).steText;

        if ( sL >= sR ) {
            return ( Boolean::BOOL_FALSE );
        }
    }

    return ( Boolean::BOOL_TRUE );
}

//----------------------------------------------------------------
//    指定された文字列を検索する。
//

StringIndex
StringTable::findString(
        const  std::string  &strText)  const
{
    FindResult  resFind = searchEntry(strText);
    return ( resFind.siResult );
}

//----------------------------------------------------------------
//    ソートインデックスを配列ごと取得する。
//

const   StringTable::IndexArray  &
StringTable::getSortIndexArray()  const
{
    return ( this->m_sortedIndex );
}

//----------------------------------------------------------------
//    新しいデータを挿入する。
//

StringIndex
StringTable::insertString(
        const  std::string  &strText)
{
    FindResult  resFind = searchEntry(strText);

    //  データが見つかった場合はそのインデックスを返して終了。  //
    if ( TO_BOOL_FROM_STRICT(resFind.flgFound) ) {
        return ( resFind.siResult );
    }

    //  データをテーブルの最後尾に追加し、  //
    //  ソートインデックスを更新する。      //
    const  StringIndex  bsInsertPos = resFind.siInsert;
    const  StringIndex  siNewEntry  = allocEntry(strText);

    //  挿入位置より後ろにあるデータをずらす。  //
    for ( StringIndex i = this->m_numEntries - 1; i >= bsInsertPos + 1; -- i )
    {
        this->m_sortedIndex[i]  = this->m_sortedIndex[i - 1];
    }

    //  挿入位置にインデックスを書き込む。      //
    this->m_sortedIndex.at(bsInsertPos) = siNewEntry;

    //  挿入したデータのインデックスを返す。    //
    return ( siNewEntry );
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

    this->m_entryArray.resize(siAlloc);
    this->m_sortedIndex.resize(siAlloc);

    return ( this->m_bufferSize = siAlloc );
}

//----------------------------------------------------------------
//    ソートインデックスを直接設定する。
//

ErrCode
StringTable::setSortIndex(
        const  StringIndex  siIdx,
        const  StringIndex  siVal)
{
    this->m_sortedIndex[siIdx]  = siVal;
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    ソートインデックスを直接設定する。
//

ErrCode
StringTable::setSortIndexArray(
        const  IndexArray  &siArray)
{
    this->m_sortedIndex = siArray;
    return ( ErrCode::SUCCESS );
}

ErrCode
StringTable::setSortIndexArray(
        IndexArray && siArray)
{
    this->m_sortedIndex = std::move(siArray);
    return ( ErrCode::SUCCESS );
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

    if ( this->m_numEntries <= drIndex ) {
        this->m_numEntries  = drIndex + 1;
    }

    this->m_entryArray[drIndex].steFlag = steFlag;
    this->m_entryArray[drIndex].steText = steText;

    return ( drIndex );
}

//----------------------------------------------------------------
//    テーブルをソートしなおす。
//

ErrCode
StringTable::sortTable()
{
    //  原則としてほとんど整列しているデータが  //
    //  対象なので、シェーカーソートを行う。    //
    StringIndex idxHead = static_cast<StringIndex>(0);
    StringIndex idxTail = this->m_numEntries;

    while ( idxHead < idxTail ) {
        StringIndex idxLastSwap;

        idxLastSwap = idxHead;
        for ( StringIndex i = idxHead; i < idxTail; ++ i ) {
            const  StringIndex  siL = this->m_sortedIndex[i];
            const  StringIndex  siR = this->m_sortedIndex[i + 1];
            const  std::string  &sL = this->m_entryArray.at(siL).steText;
            const  std::string  &sR = this->m_entryArray.at(siR).steText;
            if ( sL >= sR ) {
                std::swap(this->m_sortedIndex[i], this->m_sortedIndex[i+1]);
                idxLastSwap = i;
            }
        }
        idxTail = idxLastSwap;

        if ( idxHead == idxTail ) {
            break;
        }

        idxLastSwap = idxTail;
        for ( StringIndex i = idxTail; i > idxHead; -- i ) {
            const  StringIndex  siL = this->m_sortedIndex[i - 1];
            const  StringIndex  siR = this->m_sortedIndex[i];
            const  std::string  &sL = this->m_entryArray.at(siL).steText;
            const  std::string  &sR = this->m_entryArray.at(siR).steText;
            if ( sL >= sR ) {
                std::swap(this->m_sortedIndex[i-1], this->m_sortedIndex[i]);
                idxLastSwap = i;
            }
        }

        idxHead = idxLastSwap;
    }

    return ( ErrCode::SUCCESS );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    バッファのサイズを得る。
//

const   StringIndex
StringTable::getBufferCapacity()  const
{
    return ( this->m_bufferSize );
}

//----------------------------------------------------------------
//    エントリフラグを取得する。
//

const   StringTable::EntryFlags
StringTable::getEntryFlag(
        const  StringIndex  drIndex)  const
{
    return ( this->m_entryArray.at(drIndex).steFlag );
}

//----------------------------------------------------------------
//    エントリフラグを設定する。
//

const   StringTable::EntryFlags
StringTable::setEntryFlag(
        const  StringIndex  drIndex,
        const  EntryFlags   flagNew)
{
    TEntry &stEntry = this->m_entryArray.at(drIndex);
    const   EntryFlags  flagOld = stEntry.steFlag;
    stEntry.steFlag = flagNew;
    return ( flagOld );
}

//----------------------------------------------------------------
//    エントリのテキストを取得する。
//

const   std::string  &
StringTable::getEntryText(
        const  StringIndex  drIndex)  const
{
    const  TEntry  &stEntry = this->m_entryArray.at(drIndex);
    return ( stEntry.steText );
}

//----------------------------------------------------------------
//    エントリのテキストを設定する。
//

ErrCode
StringTable::setEntryText(
        const  StringIndex  drIndex,
        const  std::string  &steText)
{
    TEntry &stEntry = this->m_entryArray.at(drIndex);
    stEntry.steText = steText;
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    テーブルに格納されているデータ数を取得する。
//

const   StringIndex
StringTable::getNumEntries()  const
{
    return ( this->m_numEntries );
}

//----------------------------------------------------------------
//    ソート状態フラグを取得する。
//

StringTable::StringTableSort
StringTable::getSortFlag()  const
{
    return ( this->m_flagSorted );
}

//----------------------------------------------------------------
//    ソート状態フラグを設定する。
//

StringTable::StringTableSort
StringTable::setSortFlag(
        const  StringTableSort  flagNew)
{
    StringTableSort flagOld = this->m_flagSorted;
    this->m_flagSorted  = flagNew;
    return ( flagOld );
}

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
    StringIndex     bsLeft, bsRight, bsPivot;
    StringIndex     siCheck;

    //  二分探索である程度まで範囲を絞る。  //
    bsLeft  = static_cast<StringIndex>(0);
    bsRight = this->m_numEntries - 1;

    while ( bsRight - bsLeft >= 8 ) {
        bsPivot = (bsLeft + bsRight) / 2;
        siCheck = this->m_sortedIndex[bsPivot];
        const  std::string &trgText = this->m_entryArray.at(siCheck).steText;

        if ( trgText == strText ) {
            //  見つかった  //
            result.flgFound = Boolean::BOOL_TRUE;
            result.siResult = siCheck;
            result.siInsert = bsPivot;
            return ( result );
        }

        //  検索範囲を絞る。    //
        if ( strText < trgText ) {
            //  検索しているデータは現在位置より左にある。  //
            bsRight = bsPivot - 1;
        } else {
            //  検索しているデータは現在位置より右にある。  //
            bsLeft  = bsPivot + 1;
        }
    }

    //  念のため番兵を立てる。  //
    result.flgFound = Boolean::BOOL_FALSE;
    result.siResult = static_cast<StringIndex>(-1);
    result.siInsert = bsRight + 1;

    //  ある程度範囲が小さくなったところで、単純検索に切り替える。  //
    for ( bsPivot = bsLeft; bsPivot <= bsRight; ++ bsPivot ) {
        siCheck = this->m_sortedIndex[bsPivot];
        const  std::string &trgText = this->m_entryArray.at(siCheck).steText;

        if ( trgText == strText ) {
            //  見つかった  //
            result.flgFound = Boolean::BOOL_TRUE;
            result.siResult = siCheck;
            result.siInsert = bsPivot;
            return ( result );
        }
        if ( strText < trgText ) {
            //  テーブル内のデータはソートされているから、  //
            //  この時点でデータがテーブル内に存在しない。  //
            //  また、データを挿入する時はこの場所になる。  //
            result.flgFound = Boolean::BOOL_FALSE;
            result.siResult = static_cast<StringIndex>(-1);
            result.siInsert = bsPivot;
            break;
        }
    }

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

}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END
