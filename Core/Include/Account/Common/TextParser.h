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
**      An Interface of TextParser class.
**
**      @file       Common/TextParser.h
**/

#if !defined( HACORE_COMMON_INCLUDED_TEXT_PARSER_H )
#    define   HACORE_COMMON_INCLUDED_TEXT_PARSER_H


#if !defined( HACORE_COMMON_INCLUDED_ACCOUTNS_TYPES_H )
#    include    "AccountsTypes.h"
#endif

#include    <string>
#include    <vector>


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //


//========================================================================
//
//    TextParser  class.
//
/**
**
**/

class  TextParser
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    typedef     std::vector<char>           TextBuffer;

    typedef     std::vector<const char *>   TokenArray;

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
    TextParser();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~TextParser();

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
    /**   文字列を指定した文字で分割する。
    **
    **  @param [in] inText    入力テキスト。
    **  @param [in] sepChar   区切り文字。
    **  @param[out] bufText   テキストバッファ。
    **  @param[out] vTokens   分割結果を追記する変数。
    **      必要なら呼び出す前に内容をクリアする。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    splitText(
            const  std::string  &inText,
            const  char  *      sepChrs,
            TextBuffer          &bufText,
            TokenArray          &vTokens);

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
    friend  class   TextParserTest;
};

}   //  End of namespace  Common
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
