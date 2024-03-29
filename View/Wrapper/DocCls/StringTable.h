﻿//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**              ---  Household Accounts  Wrapper Lib.  ---              **
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
**      An Interface of StringTable class.
**
**      @file       DocCls/StringTable.h
**/

#if !defined( HAWRAPPER_DOCCLS_INCLUDED_STRING_TABLE_H )
#    define   HAWRAPPER_DOCCLS_INCLUDED_STRING_TABLE_H

#pragma     once


#if !defined( HAWRAPPER_COMMON_INCLUDED_ACCOUNTS_TYPES_H )
#    include    "Wrapper/Common/AccountsTypes.h"
#endif

#if !defined( HACORE_DOCCLS_INCLUDED_STRING_TABLE_H )
#    include    <Account/DocCls/StringTable.h>
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

//  クラスの前方宣言。  //
namespace  DocCls  {

}   //  End of namespace  DocCls

HOUSEHOLD_ACCOUNTS_NAMESPACE_END


namespace  Wrapper  {
namespace  DocCls  {

//========================================================================
//
//    StringTable  class.
//

public ref  class  StringTable
{
//========================================================================
//
//    Internal Type Definitions.
//
private:

    typedef     HABook::DocCls::StringTable     WrapTarget;

    typedef     cli::array<StringIndex, 1>      IndexArray;

    typedef     WrapTarget::StringTableSort     CoreStringTableSort;

public:
    enum class  StringTableSort
    {
        TABLE_SORT_NONE         = CoreStringTableSort::TABLE_SORT_NONE,
        TABLE_SORT_ASCENDING    = CoreStringTableSort::TABLE_SORT_ASCENDING,
    };

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    StringTable();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する。
    **  （デストラクタ）。
    **
    **/
    ~StringTable();

    //----------------------------------------------------------------
    /**   アンマネージドリソースを破棄する。
    **  （ファイナライザ）。
    **
    **/
    !StringTable();

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
    /**   テーブルの最後尾にデータを追加する。
    **
    **  @param [in] steText   追加するデータ。
    **  @return     挿入したデータのインデックス。
    **/
    StringIndex
    appendString(
            System::String^     steText);

    //----------------------------------------------------------------
    /**   テーブルの整合性を検査する。
    **
    **/
    System::Boolean
    checkDataIntegrity();

    //----------------------------------------------------------------
    /**   テーブルがソートされているか検査する。
    **
    **/
    System::Boolean
    checkSortIntegrity();

    //----------------------------------------------------------------
    /**   指定された文字列を検索する。
    **
    **  @param [in] steText   検索する文字列。
    **  @return
    **/
    StringIndex
    findString(
            System::String^     steText);

    //----------------------------------------------------------------
    /**   新しいデータを挿入する。
    **
    **  @param [in] steText   新しく挿入するデータ。
    **  @return     挿入したデータのインデックス。
    **      既にデータが存在していた場合は何もせず、
    **      そのインデックスを返す。
    **/
    StringIndex
    insertString(
            System::String^     steText);

    //----------------------------------------------------------------
    /**   データ用のバッファを確保する。
    **
    **  @param [in] bufSize
    **/
    StringIndex
    reserveBuffer(
            const  StringIndex  bufSize);

    //----------------------------------------------------------------
    /**   テーブルをソートしなおす。
    **
    **/
    System::Boolean
    sortTable();

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   ソートインデックスを直接設定する。
    **
    **  @param [in] siArray   ソートインデックスの配列。
    **/
    System::Boolean
    setSortIndexArray(
            IndexArray^     siArray);

//========================================================================
//
//    Properties.
//
public:

    //----------------------------------------------------------------
    /**   バッファのサイズ。
    **
    **  @return     バッファのサイズ。
    **/
    property    StringIndex
    BufferCapacity
    {
        StringIndex     get();
    }

    //----------------------------------------------------------------
    /**   エントリフラグ。
    **
    **/
    property    int
    EntryFlag [StringIndex]
    {
        int get(StringIndex idx);
        void set(StringIndex idx, int val);
    }

    //----------------------------------------------------------------
    /**   テーブルに格納されているデータ数。
    **
    **/
    property    StringIndex
    NumEntries  {
        StringIndex     get();
    }

    //----------------------------------------------------------------
    /**   ソート状態フラグ。
    **
    **/
    property    StringTableSort
    SortFlag  {
        StringTableSort     get();
        void set(StringTableSort flagNew);
    }

    //----------------------------------------------------------------
    /**   ソートインデックスの配列。
    **
    **/
    property    IndexArray ^
    SortIndex  {
        IndexArray^     get();
    }

    //----------------------------------------------------------------
    /**   テーブルのエントリ。
    **
    **/
    property    System::String ^
    TableEntry [StringIndex]
    {
        System::String^ get(StringIndex idx);
        void set(StringIndex idx, System::String^ val);
    }

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
private:

    WrapTarget  *   m_ptrObj;

//========================================================================
//
//    Other Features.
//

};

}   //  End of namespace  DocCls
}   //  End of namespace  Wrapper

#endif
