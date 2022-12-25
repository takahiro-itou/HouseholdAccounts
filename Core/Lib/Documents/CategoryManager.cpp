//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
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
**      An Implementation of CategoryManager class.
**
**      @file       Documents/CategoryManager.cpp
**/

#include    "Account/pch/PreCompile.h"

#include    "Account/Documents/CategoryManager.h"

#include    "Account/Documents/BookCategory.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Documents  {

namespace  {
}   //  End of (Unnamed) namespace.

//========================================================================
//
//    CategoryManager  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

CategoryManager::CategoryManager()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

CategoryManager::~CategoryManager()
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
//    項目データ用バッファを確保する。
//

const   CategoryHandle
CategoryManager::allocCategoryBuffers(
        const   CategoryHandle  bufSize)
{
    //  バッファをリサイズし、増えた部分の先頭を記録しておく。  //
    const   CategoryHandle  sizeCur = this->m_cateBufferSize;
    const   CategoryHandle  sizeNew = (bufSize + 15) & ~15;

    this->m_cateBufferSize  = sizeNew;
    this->m_bufCategory.resize(sizeNew);

    return ( sizeCur );
}

//----------------------------------------------------------------
//    新しい項目用の領域を確保する。
//

const   CategoryHandle
CategoryManager::allocNewCategory()
{
    CategoryHandle  cateResult  = -1;

    //  バッファサイズと登録済み項目数を比較し、    //
    //  バッファに空きがある場合は、空きを探して    //
    //  そのハンドル（インデックス）を返す。        //
    const   CategoryHandle  bufSize = this->m_cateBufferSize;
    if ( this->m_numUsedCategory < bufSize ) {
        for ( CategoryHandle i = this->m_numRootCategory; i < bufSize; ++ i ) {
            const  BookCategory &bc = this->m_bufCategory.at(i);
            if ( bc.getCategoryFlags() == CategoryFlags::CTYPE_NOTUSED ) {
                cateResult  = i;
                break;
            }
        }
    }

    if ( cateResult >= 0 ) {
        return ( cateResult );
    }

    //  バッファをリサイズし、増えた部分の先頭を確保する。  //
    return ( allocCategoryBuffers(bufSize + 1) );
}

//----------------------------------------------------------------
//    項目のルート項目のハンドルを取得する。
//

const   CategoryHandle
CategoryManager::getRootCategoryHandle(
        const   CategoryHandle  idxCate)  const
{
    CategoryHandle  catePar;
    CategoryHandle  cateCur = idxCate;

    catePar = this->m_bufCategory.at(cateCur).getParentHandle();
    while ( catePar >= 0 ) {
        cateCur = catePar;
        catePar = this->m_bufCategory.at(cateCur).getParentHandle();
    }
    return ( cateCur );
}

//----------------------------------------------------------------
//    指定した項目に新しいサブ項目を追加する。
//

const   CategoryHandle
CategoryManager::insertNewCategory(
        const  CategoryHandle   cateParent,
        const  std::string     &cateName,
        const  CategoryFlags    cateFlags,
        const  int              startDate,
        const  DecimalCurrency &startBalance)
{
    //  新しい項目用のインデックスを取得する。  //
    const   CategoryHandle  cateNew = 0;

    //  この項目に初期値を書き込む。            //

    //  親項目の内容を更新する。                //

    //  追加した新しい項目のハンドルを返す。    //
    return ( cateNew );
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
//    項目用のバッファのサイズを得る。
//

const   CategoryHandle
CategoryManager::getBufferCapacity()  const
{
    return ( this->m_cateBufferSize );
}

//----------------------------------------------------------------
//    登録済みの項目数を取得する。
//

const   CategoryHandle
CategoryManager::getRegisteredCategoryCount()  const
{
    return ( this->m_numUsedCategory );
}

//----------------------------------------------------------------
//    ルートにある項目数を取得する。
//

const   CategoryHandle
CategoryManager::getRootCategoryCount()  const
{
    return ( this->m_numRootCategory );
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Documents
HOUSEHOLD_ACCOUNTS_NAMESPACE_END
