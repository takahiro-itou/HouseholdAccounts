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
**      An Implementation of BookCategory class.
**
**      @file       DocCls/BookCategory.cpp
**/

#include    "Account/pch/PreCompile.h"

#include    "Account/DocCls/BookCategory.h"

#include    "Account/Documents/CategoryManager.h"

#include    "Account/Common/EnumBitFlag.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Documents  {

namespace  {
}   //  End of (Unnamed) namespace.

//========================================================================
//
//    BookCategory  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

BookCategory::BookCategory()
    : m_ptrManager(nullptr),
      m_selfCateHandle(-1),
      m_categoryFlags(CategoryFlags::CTYPE_NOTUSED),
      m_parentHandle  (-1),
      m_categoryNameId(-1),
      m_categoryName(),
      m_numSubCategory(0),
      m_subCategories(),
      m_startDate(0),
      m_startBalance()
{
}

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コピーコンストラクタ）。
//

BookCategory::BookCategory(
        const  BookCategory  &src)
    : m_ptrManager    (src.m_ptrManager),
      m_selfCateHandle(src.m_selfCateHandle),
      m_categoryFlags (src.m_categoryFlags),
      m_parentHandle  (src.m_parentHandle),
      m_categoryNameId(src.m_categoryNameId),
      m_categoryName  (src.m_categoryName),
      m_numSubCategory(src.m_numSubCategory),
      m_subCategories (src.m_subCategories),
      m_startDate     (src.m_startDate),
      m_startBalance  (src.m_startBalance)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

BookCategory::~BookCategory()
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
//    サブ項目を追加する。
//

const   SubCategoryIdx
BookCategory::appendSubCategory(
        const   CategoryHandle  cateSub)
{
    const   SubCategoryIdx  idxPos  = this->m_numSubCategory;
    this->m_subCategories.resize(++ this->m_numSubCategory);
    this->m_subCategories[idxPos]   = cateSub;
    return ( idxPos );
}

//----------------------------------------------------------------
//    サブ項目を全て消去する。
//

void
BookCategory::clearSubCategories()
{
    this->m_numSubCategory  = static_cast<SubCategoryIdx>(0);
    this->m_subCategories.clear();
    return;
}

//----------------------------------------------------------------
//    項目を展開または閉じる。
//

const   Boolean
BookCategory::expandCategory(
        const  Boolean  flgExpand)
{
    CategoryFlags   cFlags  = this->m_categoryFlags;
    CategoryFlags   cfPrev  = cFlags & CategoryFlags::CFLAG_EXPANDED;

    if ( TO_BOOL_FROM_STRICT(flgExpand) ) {
        cFlags  |=  CategoryFlags::CFLAG_EXPANDED;
    } else {
        cFlags  &= ~CategoryFlags::CFLAG_EXPANDED;
    }

    this->m_categoryFlags   = cFlags;
    return ( TO_STRICT_FROM_BOOL(cfPrev == CategoryFlags::CFLAG_EXPANDED) );
}

//----------------------------------------------------------------
//    項目のデータを設定する。
//

void
BookCategory::setupCategory(
        const  CategoryManager &cateManager,
        const  CategoryHandle   cateSelf,
        const  CategoryHandle   cateParent,
        const  std::string     &cateName,
        const  CategoryFlags    cateFlags,
        const  DateSerial       startDate,
        const  DecimalCurrency &startBalance)
{
    this->m_ptrManager      = &cateManager;
    this->m_selfCateHandle  = cateSelf;

    this->m_categoryFlags   = cateFlags;
    this->m_parentHandle    = cateParent;
    this->m_categoryName    = cateName;
    this->m_startDate       = startDate;
    this->m_startBalance    = startBalance;

    this->m_numSubCategory  = static_cast<SubCategoryIdx>(0);
    this->m_subCategories.clear();

    return;
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
//    項目のフラグを取得する。
//

const   CategoryFlags
BookCategory::getFlags()  const
{
    return ( this->m_categoryFlags );
}

//----------------------------------------------------------------
//    項目のフラグを設定する。
//

const   CategoryFlags
BookCategory::setFlags(
        const   CategoryFlags   flagNew)
{
    const CategoryFlags flagOld = this->m_categoryFlags;
    this->m_categoryFlags   = flagNew;
    return ( flagOld );
}

//----------------------------------------------------------------
//    項目の名前を取得する。
//

const   std::string  &
BookCategory::getCategoryName()  const
{
    return ( this->m_categoryName );
}

//----------------------------------------------------------------
//    項目の名前を設定する。
//

void
BookCategory::setCategoryName(
        const  std::string  &cateName)
{
    this->m_categoryName    = cateName;
}

//----------------------------------------------------------------
//    項目の種類を取得する。
//

const   CategoryFlags
BookCategory::getCategoryType()  const
{
    if ( (this->m_ptrManager == nullptr) || (this->m_selfCateHandle == -1) )
    {
        return ( this->m_categoryFlags & CategoryFlags::CTYPE_MASK );
    }
    return ( this->m_ptrManager->getCategoryType(this->m_selfCateHandle) );
}

//----------------------------------------------------------------
//    サブ項目が展開されているか調べる。
//

const   Boolean
BookCategory::isExpanded()
{
    const   CategoryFlags   cFlags  = this->m_categoryFlags;
    return ( TO_SBOOLEAN_FROM_INT(cFlags & CategoryFlags::CFLAG_EXPANDED) );
}

//----------------------------------------------------------------
//    サブ項目の個数を取得する。
//

const   SubCategoryIdx
BookCategory::getNumSubCategories()  const
{
    return ( this->m_numSubCategory );
}

//----------------------------------------------------------------
//    親項目のインデックスを取得する。
//

const   CategoryHandle
BookCategory::getParentHandle()  const
{
    return ( this->m_parentHandle );
}

//----------------------------------------------------------------
//    親項目のインデックスを設定する。
//

const   CategoryHandle
BookCategory::setParentHandle(
        const   CategoryHandle  parentNew)
{
    CategoryHandle  oldVal  = this->m_parentHandle;
    this->m_parentHandle    = parentNew;
    return ( oldVal );
}

//----------------------------------------------------------------
//    開始年月日を取得する。
//

const   DateSerial
BookCategory::getStartDate()  const
{
    return ( this->m_startDate );
}

//----------------------------------------------------------------
//    開始年月日を設定する。
//

void
BookCategory::setStartDate(
        const   DateSerial  valNew)
{
    this->m_startDate   = valNew;
}

//----------------------------------------------------------------
//    開始時の残高を取得する。
//

const   Common::DecimalCurrency  &
BookCategory::getStartBalance()  const
{
    return ( this->m_startBalance );
}

//----------------------------------------------------------------
//    開始時の残高を設定する。
//

void
BookCategory::setStartBalance(
        const  DecimalCurrency  &valNew)
{
    this->m_startBalance    = valNew;
}

//----------------------------------------------------------------
//    サブ項目のインデックスの配列を取得する。
//

const   BookCategory::CategoryHandleArray  &
BookCategory::getSubCategories()  const
{
    return ( this->m_subCategories );
}

//----------------------------------------------------------------
//    サブ項目のインデックスを取得する。
//

const   CategoryHandle
BookCategory::getSubCategory(
        const   SubCategoryIdx  idxSub)  const
{
    return ( this->m_subCategories[idxSub] );
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
