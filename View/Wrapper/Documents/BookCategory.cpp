//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**              ---  Household Accounts  Wrapper Lib.  ---              **
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
**      An Implementation of BookCategory class.
**
**      @file       Documents/BookCategory.cpp
**/

#include    "PreCompile.h"

#include    "Account/Documents/BookCategory.h"

#include    "BookCategory.h"

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
    : m_ptrObj(new WrapTarget())
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する。
//  （デストラクタ）。
//

BookCategory::~BookCategory()
{
    //  マネージドリソースを破棄する。              //
    delete  this->m_categoryName;
    this->m_categoryName    = nullptr;

    delete  this->m_subCategories;
    this->m_subCategories   = nullptr;

    //  続いて、アンマネージドリソースも破棄する。  //
    this->!BookCategory();
}

//----------------------------------------------------------------
//    アンマネージドリソースを破棄する。
//  （ファイナライザ）。
//

BookCategory::!BookCategory()
{
    delete  this->m_ptrObj;
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
    return ( this->m_categoryFlags );
}

//----------------------------------------------------------------
//    サブ項目のインデックスの配列を取得する。
//

BookCategory::CategoryHandleArray^
BookCategory::getSubCategories()
{
    return ( this->m_subCategories );
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
    return ( this->m_categoryName );
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
}   //  End of namespace  Wrapper
