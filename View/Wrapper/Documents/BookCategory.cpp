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
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する。
//  （デストラクタ）。
//

BookCategory::~BookCategory()
{
}

//----------------------------------------------------------------
//    アンマネージドリソースを破棄する。
//  （ファイナライザ）。
//

BookCategory::!BookCategory()
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
BookCategory::parentHandle::get()
{
    return ( this->m_parentHandle );
}

//----------------------------------------------------------------
//    項目の名前。
//

System::String^
BookCategory::categoryName::get()
{
    return ( this->m_categoryName );
}

//----------------------------------------------------------------
//    サブ項目数。
//

CategoryHandle
BookCategory::numSubCategories::get()
{
    return ( this->m_numSubCategory );
}

//----------------------------------------------------------------
//    サブ項目のインデックス。
//

CategoryHandle
BookCategory::subCategory::get(
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
