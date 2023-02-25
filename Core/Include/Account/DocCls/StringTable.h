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
**      @file       DocCls/StringTable.h
**/

#if !defined( HACORE_DOCCLS_INCLUDED_STRING_TABLE_H )
#    define   HACORE_DOCCLS_INCLUDED_STRING_TABLE_H


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
namespace  DocCls  {

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

    /**
    **    テーブルのエントリ。
    **/
    struct  TEntry
    {
        std::string     steText;
        EntryFlags      steFlag;

        TEntry()
            : steText(), steFlag(0)
        { }
    };

    DECLARE_STRICT_VECTOR(TEntry, StringIndex, StringArray);

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
    **  @param [in] steText   追加するデータ。
    **  @param [in] steFlag   エントリフラグ。
    **  @return     追加したデータのインデックス。
    **/
    virtual  StringIndex
    allocEntry(
            const  std::string  &steText,
            const  EntryFlags   steFlag = 0);

    //----------------------------------------------------------------
    /**   テーブルの最後尾にデータを追加する。
    **
    **  @param [in] steText   追加するデータ。
    **  @return     追加したデータのインデックス。
    **/
    virtual  StringIndex
    appendString(
            const  std::string  &steText);

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
    /**   ソートインデックスを配列ごと取得する。
    **
    **  @return     ソートインデックスの配列。
    **/
    virtual  const  IndexArray  &
    getSortIndexArray()  const;

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
    /**   ソートインデックスを直接設定する。
    **
    **  @param [in] siIdx   ソートインデックス配列の添え字。
    **  @param [in] siVal   ソートインデックス配列の値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setSortIndex(
            const  StringIndex  siIdx,
            const  StringIndex  siVal);

    //----------------------------------------------------------------
    /**   ソートインデックスを直接設定する。
    **
    **  @param [in] siArray   ソートインデックスの配列。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setSortIndexArray(
            const  IndexArray  &siArray);

    virtual  ErrCode
    setSortIndexArray(
            IndexArray && siArray);

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
    /**   バッファのサイズを得る。
    **
    **  @return     バッファのサイズ。
    **/
    const   StringIndex
    getBufferCapacity()  const;

    //----------------------------------------------------------------
    /**   エントリフラグを取得する。
    **
    **  @param [in] drIndex   インデックス。
    **  @return     フラグ。
    **/
    const   EntryFlags
    getEntryFlag(
            const  StringIndex  drIndex)  const;

    //----------------------------------------------------------------
    /**   エントリフラグを設定する。
    **
    **  @param [in] drIndex
    **  @param [in] flagNew
    **  @return     以前の値。
    **/
    const   EntryFlags
    setEntryFlag(
            const  StringIndex  drIndex,
            const  EntryFlags   flagNew);

    //----------------------------------------------------------------
    /**   エントリのテキストを取得する。
    **
    **  @param [in] drIndex
    **  @return     テキスト。
    **/
    const  std::string  &
    getEntryText(
            const  StringIndex  drIndex)  const;

    //----------------------------------------------------------------
    /**   エントリのテキストを設定する。
    **
    **  @param [in] drIndex   インデックス。
    **  @param [in] steText   テキスト。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setEntryText(
            const  StringIndex  drIndex,
            const  std::string  &steText);

    //----------------------------------------------------------------
    /**   テーブルに格納されているデータ数を取得する。
    **
    **  @return     データ数
    **/
    const   StringIndex
    getNumEntries()  const;

    //----------------------------------------------------------------
    /**   ソート状態フラグを取得する。
    **
    **  @return     現在の値。
    **/
    StringTableSort
    getSortFlag()  const;

    //----------------------------------------------------------------
    /**   ソート状態フラグを設定する。
    **
    **  @param [in] flagNew
    **  @return     以前の値。
    **/
    StringTableSort
    setSortFlag(
            const  StringTableSort  flagNew);

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

    /**   文字列テーブル。      **/
    StringArray         m_entryArray;

    /**   昇順にソートした時の、インデックステーブル。  **/
    IndexArray          m_sortedIndex;

//========================================================================
//
//    Other Features.
//
private:
    typedef     StringTable     This;
    StringTable         (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   StringTableTest;

    //  ユニットテスト用インターフェイス。  //
    FindResult
    searchEntryTest(
            const  std::string  &strText)  const;

};

}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
