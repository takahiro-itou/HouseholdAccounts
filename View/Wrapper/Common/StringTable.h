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
**      An Interface of StringTable class.
**
**      @file       Interface/StringTable.h
**/

#if !defined( HAWRAPPER_COMMON_INCLUDED_STRING_TABLE_H )
#    define   HAWRAPPER_COMMON_INCLUDED_STRING_TABLE_H

#pragma     once

#include    "HouseholdAccounts/Common/AccountsTypes.h"

namespace  Wrapper  {

//========================================================================
//
//    StringTable  class.
//

public value struct StringTable
{
//========================================================================
//
//    Internal Type Definitions.
//
public:

    enum class StringTableSort {
        STRING_SORT_NONE        = 0,
        STRING_SORT_ASCENDING   = 1,
    };

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
public:

    //----------------------------------------------------------------
    /**   指定された文字列を検索する。
    **
    **  @param [in] strText   検索する文字列。
    **  @return
    **/
    int
    findString(
            System::String^  strText);

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Properties.
//
public:

    /**   テーブル用のバッファサイズ。  **/
    int     nTableBufferSize;

    /**   実際に格納されているデータ数。    **/
    int     nNumEntry;

    /**   ソート状態。  **/
    StringTableSort         nSorted;

    /**   各エントリのフラグ。  **/
    cli::array<int, 1>^     nEntryFlags;

    /**   文字列テーブル。      **/
    cli::array<System::String^, 1>^     sTableEntries;

    /**   昇順にソートした時の、インデックステーブル。  **/
    cli::array<int, 1>^     nSortIndex;

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//

};

}   //  End of namespace  Wrapper

#endif
