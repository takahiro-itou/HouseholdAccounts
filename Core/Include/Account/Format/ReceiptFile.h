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
**      An Interface of ReceiptFile class.
**
**      @file       Format/ReceiptFile.h
**/

#if !defined( HACORE_FORMAT_INCLUDED_RECEIPT_FILE_H )
#    define   HACORE_FORMAT_INCLUDED_RECEIPT_FILE_H


#if !defined( HACORE_DOCCLS_INCLUDED_RECEIPT_INFO_H )
#    include    "Account/DocCls/ReceiptInfo.h"
#endif

#if !defined( HACORE_SYS_INCLUDED_IOS_FWD )
#    include    <iosfwd>
#    define   HACORE_SYS_INCLUDED_IOS_FWD
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

//  クラスの前方宣言。  //
namespace  DocCls  {
class   CategoryManager;
class   ReceiptInfo;
}   //  End of namespace  DocCls.

namespace  Format  {

//========================================================================
//
//    ReceiptFile  class.
//
/**
**
**/

class  ReceiptFile
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

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
    ReceiptFile();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~ReceiptFile();

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
    /**   データをテキストファイルから読み込む。
    **
    **  @param [in] fileName    ファイル名。
    **  @param[out] ptrDoc      ドキュメントを格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    readFromTextFile(
            const   std::string   & fileName,
            DocCls::ReceiptList   * ptrDoc);

    //----------------------------------------------------------------
    /**   データをテキストストリームから読み込む。
    **
    **  @param [in,out] inStr     入力ストリーム。
    **  @param    [out] ptrDoc    ドキュメントを格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    readFromTextStream(
            std::istream          & inStr,
            DocCls::ReceiptList   * ptrDoc);

    //----------------------------------------------------------------
    /**   データをテキストストリームに書き込む。
    **
    **  @param [in] objDoc      ドキュメント。
    **  @param [in] fileName    ファイル名。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    saveToTextFile(
            const  DocCls::ReceiptList  & objDoc,
            const  std::string          & fileName);

    //----------------------------------------------------------------
    /**   データをテキストストリームに書き込む。
    **
    **  @param [in] objDoc    ドキュメント。
    **  @param[out] outStr    出力ストリーム。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    saveToTextStream(
            const  DocCls::ReceiptList  & objDoc,
            std::ostream                & outStr);

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
    /**   読み飛ばすカラム数を設定する。
    **
    **  @param [in] numSkipCols   スキップするカラム数。
    **      指定したカラム数だけ先頭カラムを読み飛ばす。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    setNumSkipColumns(
            const  int  numSkipCols);

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

    /**   読み飛ばす左端カラム数。  **/
    int     m_numSkipCols;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   ReceiptFileTest;
};

}   //  End of namespace  Format
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
