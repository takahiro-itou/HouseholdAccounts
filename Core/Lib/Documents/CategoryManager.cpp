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
**      An Implementation of CategoryManager class.
**
**      @file       Documents/CategoryManager.cpp
**/

#include    "Account/pch/PreCompile.h"

#include    "Account/Documents/CategoryManager.h"

#include    "Account/Documents/BookCategory.h"

#include    "Account/Common/EnumBitFlag.h"

#include    <stdexcept>


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
    : m_cateBufferSize(0),
      m_numUsedCategory(0),
      m_numRootCategory(0),
      m_bufCategory(),
      m_chInnerTax(-1),
      m_chOuterTax(-1)
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
    CategoryHandle  cateResult  = static_cast<CategoryHandle>(-1);

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
//    項目の種類を取得する。
//

const   CategoryFlags
CategoryManager::getCategoryType(
        const   CategoryHandle  hCate)  const
{
    CategoryHandle  catePar;
    CategoryFlags   cfType;
    CategoryHandle  cateCur = hCate;

    while ( cateCur >= 0 ) {
        const   BookCategory  & bc  = this->m_bufCategory.at(cateCur);
        cfType  = bc.getCategoryFlags() & CategoryFlags::CTYPE_MASK;
        catePar = bc.getParentHandle();

        if ( cfType == CategoryFlags::CTYPE_INHERIT ) {
            cateCur = catePar;
        } else {
            break;
        }
    }

    return ( cfType );
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
        const  DateSerial       startDate,
        const  DecimalCurrency &startBalance)
{
    //  新しい項目用のインデックスを取得する。  //
    const   CategoryHandle  cateNew = allocNewCategory();

    //  この項目に初期値を書き込む。            //
    BookCategory   & entry  = this->m_bufCategory.at(cateNew);
    entry.setupCategory(
            cateParent, cateName, cateFlags, startDate, startBalance);
    ++ this->m_numUsedCategory;

    //  親項目の内容を更新する。                //
    BookCategory   & parent = this->m_bufCategory.at(cateParent);
    parent.appendSubCategory(cateNew);

    //  追加した新しい項目のハンドルを返す。    //
    return ( cateNew );
}

//----------------------------------------------------------------
//    ルート項目データ用の領域を確保する。
//

const   CategoryHandle
CategoryManager::reserveRootCategories(
        const   CategoryHandle  numRoot)
{
    if ( this->m_cateBufferSize < numRoot ) {
        allocCategoryBuffers(numRoot);
    }

    this->m_numUsedCategory = numRoot;
    this->m_numRootCategory = numRoot;

    return ( numRoot );
}

//----------------------------------------------------------------
//    ルート項目のデータを設定する。
//

const   CategoryHandle
CategoryManager::setupRootCategory(
        const  CategoryHandle   cateHandle,
        const  std::string     &cateName,
        const  CategoryFlags    cateFlags,
        const  DateSerial       startDate,
        const  DecimalCurrency &startBalance)
{
    if ( (cateHandle < 0) || (this->m_numRootCategory <= cateHandle) ) {
        throw  std::out_of_range("root category handle is out of range.");
    }

    //  この項目に初期値を書き込む。            //
    BookCategory   & entry  = this->m_bufCategory.at(cateHandle);
    entry.setupCategory(
            static_cast<CategoryHandle>(-1), cateName,
            cateFlags, startDate, startBalance);
    return ( cateHandle );
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
//    項目データを取得する。
//

BookCategory  &
CategoryManager::getBookCategory(
        const   CategoryHandle  hCate)
{
    return ( this->m_bufCategory.at(hCate) );
}

const   BookCategory  &
CategoryManager::getBookCategory(
        const   CategoryHandle  hCate)  const
{
    return ( this->m_bufCategory.at(hCate) );
}

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
