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

#if !defined( HACORE_COMMON_INCLUDED_STRICT_VECTOR_H )
#    include    "Account/Common/StrictVector.h"
#endif

#if !defined( HACORE_SYS_INCLUDED_STL_STRING )
#    include    <string>
#    define   HACORE_SYS_INCLUDED_STL_STRING
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

        FindResult()
            : flgFound(Boolean::BOOL_FALSE), siResult(-1), siInsert(0)
        { }
    };

private:

    typedef     int     EntryFlags;

    DECLARE_STRICT_VECTOR(std::string, StringIndex, StringArray);

    DECLARE_STRICT_VECTOR(EntryFlags,  StringIndex, FlagsArray);

    DECLARE_STRICT_VECTOR(StringIndex, StringIndex, IndexArray);

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
public:

    //----------------------------------------------------------------
    /**   テーブルの最後尾にデータを追加する。
    **
    **  @param [in] strText   追加するデータ。
    **/
    virtual  StringIndex
    appendString(
            const  std::string  &strText);

    //----------------------------------------------------------------
    /**   テーブルの整合性を検査する。
    **
    **/
    virtual  Boolean
    checkIntegrity()  const;

    //----------------------------------------------------------------
    /**   指定された文字列を検索する。
    **
    **  @param [in] strText   検索する文字列。
    **  @return
    **/
    virtual  StringIndex
    findString(
            const  std::string  &strText)  const;

    //----------------------------------------------------------------
    /**   新しいデータを挿入する。
    **
    **  @param [in] strText   新しく挿入するデータ。
    **  @return     挿入したデータのインデックス。
    **      既にデータが存在していた場合は何もせず、
    **      そのインデックスを返す。
    **/
    virtual  StringIndex
    insertString(
            const  std::string  &strText);

    //----------------------------------------------------------------
    /**   データ用のバッファを確保する。
    **
    **  @param [in] bufSize
    **/
    virtual  StringIndex
    reserveBuffer(
            const  StringIndex  bufSize);

    //----------------------------------------------------------------
    /**   テーブルのエントリを直接設定する。
    **
    **  @param [in] drIndex
    **  @param [in] steText
    **  @param [in] steFlag
    **/
    virtual  StringIndex
    setTableEntry(
            const  StringIndex  drIndex,
            const  std::string  &steText,
            const  EntryFlags   steFlag);

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   テーブルに格納されているデータ数を取得する。
    **
    **  @return     データ数
    **/
    const   StringIndex
    getNumEntries()  const;

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//
private:

    //----------------------------------------------------------------
    /**   データを検索する。
    **
    **  @param [in] strText
    **/
    inline  FindResult
    searchEntry(
            const  std::string  &strText)  const;

//========================================================================
//
//    Member Variables.
//
private:

    /**   テーブル用のバッファサイズ。  **/
    StringIndex         m_bufferSize;

    /**   実際に格納されているデータ数。    **/
    StringIndex         m_numEntries;

    /**   ソート状態。  **/
    StringTableSort     m_flagSorted;

    /**   各エントリのフラグ。  **/
    FlagsArray          m_entryFlags;

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

    //  ユニットテスト用インターフェイス。  //
    FindResult
    searchEntryTest(
            const  std::string  &strText)  const;

};

}   //  End of namespace  Documents
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
