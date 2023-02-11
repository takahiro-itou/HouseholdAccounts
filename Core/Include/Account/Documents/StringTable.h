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
**      An Interface of StringTable class.
**
**      @file       Documents/StringTable.h
**/

#if !defined( HACORE_DOCUMENTS_INCLUDED_STRING_TABLE_H )
#    define   HACORE_DOCUMENTS_INCLUDED_STRING_TABLE_H


#if !defined( HACORE_COMMON_INCLUDED_ACCOUTNS_TYPES_H )
#    include    "Account/Common/AccountsTypes.h"
#endif

#if !defined( HACORE_SYS_INCLUDED_STL_STRING )
#    include    <string>
#    define   HACORE_SYS_INCLUDED_STL_STRING
#endif

#if !defined( HACORE_SYS_INCLUDED_STL_VECTOR )
#    include    <vector>
#    define   HACORE_SYS_INCLUDED_STL_VECTOR
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Documents  {

//  クラスの前方宣言。  //

//========================================================================
//
//    StringTable  class.
//
/**
**
**/

class  StringTable
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    enum  class  StringTableSort
    {
        TABLE_SORT_NONE         = 0,
        TABLE_SORT_ASCENDING    = 1,
    };

    /**
    **    データの検索結果。
    **/
    struct  FindResult
    {
        Boolean         flgFound;
        StringIndex     siResult;
        StringIndex     siInsert;
    };

public:

    typedef     std::vector<std::string>        StringArray;

    typedef     std::vector<StringIndex>        IndexArray;

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
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~StringTable();

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

    /**   テーブル用のバッファサイズ。  **/
    BufferSize          m_tableBufferSize;

    /**   実際に格納されているデータ数。    **/
    StringIndex         m_numEntries;

    /**   ソート状態。  **/
    StringTableSort     m_flagSorted;

    /**   各エントリのフラグ。  **/
    std::vector<int>    m_entryFlags;

    /**   文字列テーブル。      **/
    StringArray         m_tableEntry;

    /**   昇順にソートした時の、インデックステーブル。  **/
    IndexArray          m_sortedIndex;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   StringTableTest;
};

}   //  End of namespace  Documents
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
