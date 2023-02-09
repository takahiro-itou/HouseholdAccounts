//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**              ---  Household Accounts  Wrapper Lib.  ---              **
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
**      @file       Documents/BookCategory.cpp
**/

#include    "PreCompile.h"

#include    "BookCategory.h"

#include    "Wrapper/Common/ArrayUtils.h"

#include    "Account/Documents/CategoryManager.h"

#include    <msclr/marshal_cppstd.h>
using       namespace   msclr::interop;


namespace  Wrapper  {
namespace  Documents  {

namespace  {

}   //  End of (Unnamed) namespace

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
    : m_ptrBuf(new WrapTarget()),
      m_ptrMan(nullptr),
      m_ptrObj(m_ptrBuf)
{
}

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

BookCategory::BookCategory(
        WrapTarget *            wrapTarget,
        CoreCategoryManager *   catMan)
    : m_ptrBuf(nullptr),
      m_ptrMan(catMan),
      m_ptrObj(wrapTarget)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する。
//  （デストラクタ）。
//

BookCategory::~BookCategory()
{
    //  マネージドリソースを破棄する。              //

    //  続いて、アンマネージドリソースも破棄する。  //
    this->!BookCategory();
}

//----------------------------------------------------------------
//    アンマネージドリソースを破棄する。
//  （ファイナライザ）。
//

BookCategory::!BookCategory()
{
    delete  this->m_ptrBuf;
    this->m_ptrBuf  = nullptr;
    this->m_ptrObj  = nullptr;
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
//    サブ項目以下を展開したり閉じたりする。
//

System::Boolean
BookCategory::expandCategory(
        const  System::Boolean  blnExpanded)
{
    return ( fromNativeBoolean(
                     this->m_ptrObj->expandCategory(
                             toNativeBoolean(blnExpanded)
    ) ) );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    項目のフラグを取得する。
//

CategoryFlags
BookCategory::getCategoryFlags()
{
    return ( static_cast<CategoryFlags>(this->m_ptrObj->getFlags()) );
}

//----------------------------------------------------------------
//    項目の種類を取得する。
//

CategoryFlags
BookCategory::getCategoryType()
{
    return ( static_cast<CategoryFlags>(this->m_ptrObj->getCategoryType()) );
}

//----------------------------------------------------------------
//    サブ項目のインデックスの配列を取得する。
//

BookCategory::CategoryHandleArray ^
BookCategory::getSubCategories()
{
    return ( toManageFromVector(this->m_ptrObj->getSubCategories()) );
}

//----------------------------------------------------------------
//    サブ項目が展開されているか調べる。
//

System::Boolean
BookCategory::isExpanded()
{
    return ( fromNativeBoolean(this->m_ptrObj->isExpanded()) );
}

//========================================================================
//
//    Properties.
//

//----------------------------------------------------------------
//    親項目のインデックス。
//

CategoryHandle
BookCategory::ParentHandle::get()
{
    return ( this->m_ptrObj->getParentHandle() );
}

//----------------------------------------------------------------
//    項目の名前。
//

System::String^
BookCategory::CategoryName::get()
{
    return ( marshal_as<System::String^>(this->m_ptrObj->getCategoryName()) );
}

//----------------------------------------------------------------
//    サブ項目数。
//

CategoryHandle
BookCategory::NumSubCategories::get()
{
    return ( this->m_ptrObj->getNumSubCategories() );
}

//----------------------------------------------------------------
//    開始時の残高。
//

Common::DecimalCurrency
BookCategory::StartBalance::get()
{
    return ( DecimalCurrency(this->m_ptrObj->getStartBalance()) );
}

//----------------------------------------------------------------
//    開始年月日。
//

DateSerial
BookCategory::StartDate::get()
{
    return ( this->m_ptrObj->getStartDate() );
}

//----------------------------------------------------------------
//    サブ項目のインデックス。
//

CategoryHandle
BookCategory::SubCategory::get(
        CategoryHandle  idxSub)
{
    return ( this->m_ptrObj->getSubCategory(idxSub) );
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
}   //  End of namespace  Wrapper
