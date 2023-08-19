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
#include    "Account/DocCls/CategoryManager.h"

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
    ErrCode         retErr  = ErrCode::SUCCESS;

    DocCls::ReceiptInfo *           ptrRecInfo  = nullptr;
    DocCls::ReceiptEntriesChunk *   ptrRecChunk = nullptr;

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
        if ( (vTokens[numSkipCols + 5][0] != '\0')
                || (vTokens[numSkipCols + 6][0] != '\0')
                || (vTokens[numSkipCols + 7][0] != '\0')
        ) {
            //  収支フラグおよび口座が異なる。  //
            DocCls::ReceiptEntriesChunk chunk;
            ptrRecInfo->m_recordChunk.push_back(chunk);
            ptrRecChunk = &(ptrRecInfo->m_recordChunk.back());

            ptrRecChunk->chlDebitAccount    = findCategory(
                    vTokens[numSkipCols + 6],
                    static_cast<CategoryHandle>(-1) );
            ptrRecChunk->chrCreditAccount   = findCategory(
                    vTokens[numSkipCols + 7],
                    static_cast<CategoryHandle>(-1) );
        }

        DocCls::PurchasedGoods  pg;
        pg.accountHeadings  = findCategory(
                vTokens[numSkipCols + 8],
                static_cast<CategoryHandle>(-1));
        pg.accountCategory  = findCategory(
                vTokens[numSkipCols + 9],
                pg.accountHeadings);
        pg.productName      = vTokens[numSkipCols + 10];

        pg.unitPrice        = static_cast<CurrencyNumerator>(
                atol(vTokens[numSkipCols + 11]));
        pg.nQuantity        = atoi(vTokens[numSkipCols + 12]);
        pg.cDiscount        = static_cast<CurrencyNumerator>(
                atoi(vTokens[numSkipCols + 13]));
        pg.exclusiveTaxVal  = static_cast<CurrencyNumerator>(
                atoi(vTokens[numSkipCols + 14]));
        pg.inclusiveTaxVal  = static_cast<CurrencyNumerator>(
                atoi(vTokens[numSkipCols + 15]));

        pg.cSubTotal    = (pg.unitPrice * pg.nQuantity
                           - pg.cDiscount + pg.exclusiveTaxVal);
        ptrRecChunk->goodsList.push_back(pg);

        if ( ptrRecChunk->chlDebitAccount >= 0 ) {
            ptrRecChunk->cnlDebitAmount     += pg.cSubTotal;
        }
        if ( ptrRecChunk->chrCreditAccount >= 0 ) {
            ptrRecChunk->cnrCreditAmount    += pg.cSubTotal;
        }
    }

    return ( retErr );
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
    const   ReceiptNumber   numReceipts = objDoc.size();
    for ( ReceiptNumber
            i = static_cast<ReceiptNumber>(0); i < numReceipts; ++ i )
    {
        outStr  <<  "NEW;"  <<  i   <<  ';'
                <<  objDoc.at(i)    <<  std::endl;
    }

    return ( ErrCode::SUCCESS );
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

//----------------------------------------------------------------
//    名前から項目を検索する。
//

const   CategoryHandle
ReceiptFile::findCategory(
        const   char *   const  cateName,
        const   CategoryHandle  cateParent)  const
{
    if ( (cateName == nullptr) || (cateName[0] == '\0') ) {
        return ( static_cast<CategoryHandle>(-1) );
    }
    return  this->m_pCatMan->findCategory(cateName, cateParent);
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Format
HOUSEHOLD_ACCOUNTS_NAMESPACE_END
