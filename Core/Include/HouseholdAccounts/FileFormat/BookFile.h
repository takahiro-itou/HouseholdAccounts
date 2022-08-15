//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Household Accounts Core.  ---                  **
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
**      An Interface of BookFile class.
**
**      @file       FileFormat/BookFile.h
**/

#if !defined( HACCOUNTS_FILEFORMAT_INCLUDED_BOOK_FILE_H )
#    define   HACCOUNTS_FILEFORMAT_INCLUDED_BOOK_FILE_H

#include    "HouseholdAccounts/Common/AccountsTypes.h"

#include    <iosfwd>

HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

//  クラスの前方宣言。  //
namespace  Documents  {
class   BookDocument;
}   //  End of namespace  Documents.

namespace  FileFormat  {

//========================================================================
//
//    BookFile  class.
//
/**
**
**/

class  BookFile
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
    BookFile();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~BookFile();

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
    /**   データをテキストストリームから読み込む。
    **
    **  @param [in,out] inStr     入力ストリーム。
    **  @param    [out] ptrDoc    ドキュメントを格納する変数。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    readFromTextStream(
            std::istream            &inStr,
            Documents::BookDocument *ptrDoc);

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
    static  ErrCode
    saveToTextStream(
            const   Documents::BookDocument &objDoc,
            std::ostream                    &outStr);

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

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   BookFileTest;
};

}   //  End of namespace  Documents
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
