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
**      An Implementation of ReceiptFile class.
**
**      @file       Format/ReceiptFile.cpp
**/

#include    "Account/pch/PreCompile.h"
#include    "Account/Format/ReceiptFile.h"

#include    "Account/Common/TextParser.h"

#include    <fstream>


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Format  {

namespace  {
}   //  End of (Unnamed) namespace.

//========================================================================
//
//    ReceiptFile  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

ReceiptFile::ReceiptFile()
    : m_numSkipCols(0),
      m_pCatMan(nullptr)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

ReceiptFile::~ReceiptFile()
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

//----------------------------------------------------------------
//    データをテキストファイルから読み込む。
//

ErrCode
ReceiptFile::readFromTextFile(
        const   std::string   & fileName,
        DocCls::ReceiptList   * ptrDoc)
{
    std::ifstream   ifs(fileName.c_str());
    return  readFromTextStream(ifs, ptrDoc);
}

//----------------------------------------------------------------
//    データをテキストストリームから読み込む。
//

ErrCode
ReceiptFile::readFromTextStream(
        std::istream          & inStr,
        DocCls::ReceiptList   * ptrDoc)
{
    std::string     strLine;
    ErrCode         retErr;

    DocCls::ReceiptInfo *   ptrRecInfo;

    Common::TextParser::TextBuffer  bufText;
    Common::TextParser::TokenArray  vTokens;

    const  int  numSkipCols = this->m_numSkipCols;

    for (;;) {
        if ( !inStr ) {
            break;
        }
        std::getline(inStr, strLine);

        if ( strLine.empty() ) {
            //  空行スキップ。  //
            continue;
        }

        vTokens.clear();
        Common::TextParser::splitText(strLine, ";,", bufText, vTokens);

        if ( vTokens[numSkipCols][0] != '\0' ) {
            //  先頭のカラムが空文字列でなければ新しいデータ。  //
            DocCls::ReceiptInfo     recInfo;
            recInfo.initializeReceiptInfo(
                    (vTokens[numSkipCols + 2]),
                    (vTokens[numSkipCols + 3]),
                    (vTokens[numSkipCols + 4]) );
            ptrDoc->push_back(recInfo);

            ptrRecInfo  = &(ptrDoc->back());
        }
    }

    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    データをテキストストリームに書き込む。
//

ErrCode
ReceiptFile::saveToTextFile(
        const  DocCls::ReceiptList  & objDoc,
        const  std::string          & fileName)
{
    std::ofstream   ofs(fileName.c_str());
    return  saveToTextStream(objDoc, ofs);
}

//----------------------------------------------------------------
//    データをテキストストリームに書き込む。
//

ErrCode
ReceiptFile::saveToTextStream(
        const  DocCls::ReceiptList  & objDoc,
        std::ostream                & outStr)
{
    return ( ErrCode::FAILURE );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    項目を管理するインスタンスを設定する。
//

ErrCode
ReceiptFile::setCategoryManager(
        const  DocCls::CategoryManager  &cateManager)
{
    this->m_pCatMan = &cateManager;
    return ( ErrCode::SUCCESS );
}

//----------------------------------------------------------------
//    読み飛ばすカラム数を設定する。
//

ErrCode
ReceiptFile::setNumSkipColumns(
        const  int  numSkipCols)
{
    this->m_numSkipCols = numSkipCols;
    return ( ErrCode::SUCCESS );
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Format
HOUSEHOLD_ACCOUNTS_NAMESPACE_END
