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
    return ( -1 );
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
    return ( -1 );
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
