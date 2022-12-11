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
    StringIndex         lngIndex, lngResult;
    StringIndex         lngLeft, lngRight, lngTarget;
    System::String^     strCheck;

    lngLeft = 0;
    lngRight = this->nNumEntry - 1;
    lngResult = -1;

    while (lngRight - lngLeft >= 8) {
        lngTarget = (lngLeft + lngRight) / 2;
        lngIndex = this->nSortIndex[lngTarget];
        strCheck = this->sTableEntries[lngIndex];

        if ( strCheck == strText ) {
            //  見つかった   //
            lngResult = lngIndex;
            lngLeft = lngIndex;
            lngRight = lngIndex;
            break;
        }

        //  検索範囲を絞る  //
        if ( System::String::Compare(strCheck, strText) < 0 ) {
            //  検索しているデータは現在位置より右にある。  //
            lngLeft = lngTarget + 1;
        } else {
            //  検索しているデータは現在位置より左にある。  //
            lngRight = lngTarget - 1;
        }
    }

    //  ある程度範囲が小さくなったところで、単純検索に切り替える。  //
    for ( lngTarget = lngLeft; lngTarget <= lngRight; ++ lngTarget ) {
        lngIndex = this->nSortIndex[lngTarget];
        strCheck = this->sTableEntries[lngIndex];

        if ( strCheck == strText ) {
            lngResult = lngIndex;
            break;
        }
    }

    return ( lngIndex );
}

//----------------------------------------------------------------
//    新しいデータを挿入する。
//

StringIndex
StringTable::insertString(
        System::String^     strText)
{
    StringIndex         lngIndex, lngResult, lngInsertPos;
    StringIndex         bsLeft, bsRight, lngTarget;
    System::String^     strCheck;

    //  指定されたデータの検索と挿入位置の決定を行う。  //
    bsLeft  = 0;
    bsRight = this->nNumEntry - 1;
    lngResult = -1;

    while ( bsRight - bsLeft >= 8 ) {
        lngTarget = (bsLeft + bsRight) / 2;
        lngIndex = this->nSortIndex[lngTarget];
        strCheck = this->sTableEntries[lngIndex];

        if ( strCheck == strText ) {
            //  見つかった  //
            lngResult = lngIndex;
            bsLeft = lngTarget;
            bsRight =lngTarget;
            break;
        }

        //  検索範囲を絞る  //
        if ( System::String::Compare(strCheck, strText) < 0 ) {
            //  検索しているデータは現在位置より右にある。  //
            bsLeft  = lngTarget + 1;
        } else {
            //  検索しているデータは現在位置より左にある。  //
            bsRight = lngTarget - 1;
        }
    }

    //  ある程度範囲が小さくなったところで、単純検索に切り替える。  //
    lngInsertPos = bsRight + 1;
    for ( lngTarget = bsLeft; lngTarget <= bsRight; ++ lngTarget ) {
        lngIndex = this->nSortIndex[lngTarget];
        strCheck = this->sTableEntries[lngIndex];

        if ( strCheck == strText ) {
            //  見つかった  //
            lngResult = lngIndex;
            break;
        }
        if ( System::String::Compare(strCheck, strText) > 0 ) {
            //  この時点で指定されたデータがテーブル内に存在しない  //
            lngResult = -1;
            lngInsertPos = lngTarget;
            break;
        }
    }

    //  データが見つかった場合はそのインデックスを返して終了。  //
    if ( lngResult >= 0 ) {
        return ( lngResult );
    }

    //  データをテーブルの最後尾に追加し、  //
    //  ソートインデックスを更新する。      //
    lngIndex = this->nNumEntry ++;

    reserveBuffer(this->nNumEntry);
    appendString(strText);

    //  挿入位置より後ろにあるデータをずらす。  //
    for ( StringIndex i = this->nNumEntry - 1; i >= lngInsertPos + 1; -- i )
    {
        this->nSortIndex[i] = this->nSortIndex[i - 1];
    }
    //  挿入位置にインデックスを書き込む。  //
    this->nSortIndex[lngInsertPos] = lngIndex;

    //  挿入したデータのインデックスを返す。    //
    return ( lngIndex );
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

}   //  End of namespace  Wrappe
