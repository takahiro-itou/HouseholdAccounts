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
**      An Implementation of TextParser class.
**
**      @file       Common/TextParser.cpp
**/

#include    "Account/pch/PreCompile.h"

#include    "Account/Common/TextParser.h"

#include    <stdlib.h>
#include    <string.h>


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

namespace  {
}   //  End of (Unnamed) namespace.

//========================================================================
//
//    TextParser  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

TextParser::TextParser()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

TextParser::~TextParser()
{
}

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
//    文字列を指定した文字で分割する。
//

ErrCode
TextParser::splitText(
        const  std::string  &inText,
        const  char  *      sepChrs,
        TextBuffer          &bufText,
        TokenArray          &vTokens)
{
    const   size_t  szText  = inText.size();
    bufText.clear();
    bufText.resize(szText + 1);
    char  *  const  ptrBuf  = &(bufText[0]);

    ::memcpy(ptrBuf, inText.c_str(), szText);
    ptrBuf[szText]  = '\0';

    return  splitTextSub(ptrBuf, sepChrs, vTokens);
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

//----------------------------------------------------------------
//    文字列を指定した文字で分割する。
//

ErrCode
TextParser::splitTextSub(
        char  *  const  ptrBuf,
        const  char  *  sepChrs,
        TokenArray     &vTokens)
{
    char  *         pSaved  = nullptr;
    const  char  *  pToken  = nullptr;

#if defined( _WIN32 )
    pToken  = strtok_s(ptrBuf, sepChrs, &pSaved);
#else
    pToken  = strtok_r(ptrBuf, sepChrs, &pSaved);
#endif

    while ( pToken != nullptr ) {
        vTokens.push_back(pToken);
#if defined( _WIN32 )
        pToken  = strtok_s(nullptr, sepChrs, &pSaved);
#else
        pToken  = strtok_r(nullptr, sepChrs, &pSaved);
#endif
    }

    return ( ErrCode::SUCCESS );
}

}   //  End of namespace  Common
HOUSEHOLD_ACCOUNTS_NAMESPACE_END
