//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**              ---  Household Accounts  Wrapper Lib.  ---              **
**                                                                      **
**          Copyright (C), 2017-2022, Takahiro Itou                     **
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
**      @file       Interface/StringTable.cpp
**/

#include    "PreCompile.h"

#include    "StringTable.h"

namespace  Wrapper  {

namespace  {

}   //  End of (Unnamed) namespace

//========================================================================
//
//    StringTable  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

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
//    テーブルの最後尾にデータを追加する。
//

StringIndex
StringTable::appendString(
        System::String^     strText)
{
    const  StringIndex  idx = this->nNumEntry ++;
    reserveBuffer(this->nNumEntry);

    this->nEntryFlags[idx]      = 0;
    this->nSortIndex[idx]       = idx;
    this->sTableEntries[idx]    = strText;

    return ( idx );
}

//----------------------------------------------------------------
//    指定された文字列を検索する。
//

StringIndex
StringTable::findString(
        System::String^  strText)
{
    FindResult  resFind = searchEntry(strText);
    return ( resFind.siResult );
}

//----------------------------------------------------------------
//    新しいデータを挿入する。
//

StringIndex
StringTable::insertString(
        System::String^     strText)
{
    FindResult  resFind = searchEntry(strText);

    //  データが見つかった場合はそのインデックスを返して終了。  //
    if ( resFind.bFound ) {
        return ( resFind.siResult );
    }

    //  データをテーブルの最後尾に追加し、  //
    //  ソートインデックスを更新する。      //
    const  StringIndex  bsInsertPos = resFind.siInsert;
    const  StringIndex  siNewEntry  = this->nNumEntry;
    reserveBuffer(this->nNumEntry);
    appendString(strText);

    //  挿入位置より後ろにあるデータをずらす。  //
    for ( StringIndex i = this->nNumEntry - 1; i >= bsInsertPos + 1; -- i )
    {
        this->nSortIndex[i] = this->nSortIndex[i - 1];
    }
    //  挿入位置にインデックスを書き込む。  //
    this->nSortIndex[bsInsertPos]   = siNewEntry;

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
    if ( siAlloc <= this->nTableBufferSize ) {
        return ( this->nTableBufferSize );
    }

    System::Array::Resize(this->nEntryFlags, siAlloc);
    System::Array::Resize(this->sTableEntries, siAlloc);
    System::Array::Resize(this->nSortIndex, siAlloc);

    return ( this->nTableBufferSize = siAlloc );
}

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Properties.
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

StringTable::FindResult
StringTable::searchEntry(
        System::String^     strText)
{
    FindResult      result;
    StringIndex     bsLeft, bsRight, bsPivot;
    StringIndex     siCheck;
    System::String^ trgText;

    //  二分探索である程度まで範囲を絞る。  //
    bsLeft  = 0;
    bsRight = this->nNumEntry - 1;

    while ( bsRight - bsLeft >= 8 ) {
        bsPivot = (bsLeft + bsRight) / 2;
        siCheck = this->nSortIndex[bsPivot];
        trgText = this->sTableEntries[siCheck];

        if ( trgText == strText ) {
            //  見つかった  //
            result.bFound   = true;
            result.siResult = siCheck;
            result.siInsert = bsPivot;
            return ( result );
        }

        //  検索範囲を絞る  //
        if ( System::String::Compare(trgText, strText) > 0 ) {
            //  検索しているデータは現在位置より左にある。  //
            bsRight = bsPivot - 1;
        } else {
            //  検索しているデータは現在位置より右にある。  //
            bsLeft  = bsPivot + 1;
        }
    }

    //  念のため番兵を立てる。  //
    result.bFound   = false;
    result.siResult = -1;
    result.siInsert = bsRight + 1;

    //  ある程度範囲が小さくなったところで、単純検索に切り替える。  //
    for ( bsPivot = bsLeft; bsPivot <= bsRight; ++ bsPivot ) {
        siCheck = this->nSortIndex[bsPivot];
        trgText = this->sTableEntries[siCheck];

        if ( trgText == strText ) {
            //  見つかった  //
            result.bFound   = true;
            result.siResult = siCheck;
            result.siInsert = bsPivot;
            return ( result );
        }
        if ( System::String::Compare(trgText, strText) > 0 ) {
            //  テーブル内のデータはソートされているから、  //
            //  この時点でデータがテーブル内に存在しない。  //
            //  また、データを挿入する時はこの場所になる。  //
            result.bFound   = false;
            result.siResult = -1;
            result.siInsert = bsPivot;
            break;
        }
    }

    return ( result );
}

}   //  End of namespace  Wrappe
