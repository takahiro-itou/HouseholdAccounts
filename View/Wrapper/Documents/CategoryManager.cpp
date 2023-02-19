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
**      An Implementation of CategoryManager class.
**
**      @file       Documents/CategoryManager.cpp
**/

#include    "PreCompile.h"
#include    "CategoryManager.h"

#include    <Account/DocCls/CategoryManager.h>

#include    <msclr/marshal_cppstd.h>
using       namespace   msclr::interop;


namespace  Wrapper  {
namespace  Documents  {

namespace  {

}   //  End of (Unnamed) namespace

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
    : m_ptrObj(new WrapTarget())
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する。
//  （デストラクタ）。
//

CategoryManager::~CategoryManager()
{
    //  マネージドリソースを破棄する。              //

    //  続いて、アンマネージドリソースも破棄する。  //
    this->!CategoryManager();
}

//----------------------------------------------------------------
//    アンマネージドリソースを破棄する。
//  （ファイナライザ）。
//

CategoryManager::!CategoryManager()
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

//----------------------------------------------------------------
//    項目の種類を取得する。
//

CategoryFlags
CategoryManager::getCategoryType(
        const   CategoryHandle  hCate)
{
    return  static_cast<CategoryFlags>(
                this->m_ptrObj->getCategoryType(hCate)
    );
}

//----------------------------------------------------------------
//    項目のルート項目のハンドルを取得する。
//

CategoryHandle
CategoryManager::getRootCategoryHandle(
        const   CategoryHandle  idxCate)
{
    return  this->m_ptrObj->getRootCategoryHandle(idxCate);
}

//----------------------------------------------------------------
//    指定した項目に新しいサブ項目を追加する。
//

CategoryHandle
CategoryManager::insertNewCategory(
        const  CategoryHandle   cateParent,
        System::String ^        cateName,
        const  CategoryFlags    cateFlags,
        const  DateSerial       startDate,
        DecimalCurrency ^       startBalance)
{
    const   CategoryHandle  retVal  = this->m_ptrObj->insertNewCategory(
                cateParent,
                marshal_as<std::string>(cateName),
                static_cast<CoreCategoryFlags>(cateFlags),
                startDate,
                startBalance->toNativeInstance() );
    return ( retVal );
}

//----------------------------------------------------------------
//    ルート項目データ用の領域を確保する。
//

CategoryHandle
CategoryManager::reserveRootCategories(
        const   CategoryHandle  numRoot)
{
    const   CategoryHandle  retVal
        = this->m_ptrObj->reserveRootCategories(numRoot);
    return ( retVal );
}

//----------------------------------------------------------------
//    ルート項目のデータを設定する。
//

CategoryHandle
CategoryManager::setupRootCategory(
        const  CategoryHandle   cateHandle,
        System::String ^        cateName,
        const  CategoryFlags    cateFlags,
        const  DateSerial       startDate,
        DecimalCurrency ^       startBalance)
{
    const   CategoryHandle  retVal  = this->m_ptrObj->setupRootCategory(
                cateHandle,
                marshal_as<std::string>(cateName),
                static_cast<CoreCategoryFlags>(cateFlags),
                startDate,
                startBalance->toNativeInstance() );
    return ( retVal );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    項目データを取得する。
//

BookCategory^
CategoryManager::getBookCategory(
        const   CategoryHandle  hCate)
{
    CoreBookCategory  & cbc = this->m_ptrObj->getBookCategory(hCate);
    BookCategory      ^ wbc = gcnew BookCategory(&cbc, this->m_ptrObj);
    return ( wbc );
}

//----------------------------------------------------------------
//    項目データを取得する。
//

const   CategoryManager::CoreBookCategory  &
CategoryManager::getRawBookCategory(
        const   CategoryHandle  hCate)
{
    return  this->m_ptrObj->getBookCategory(hCate);
}

//========================================================================
//
//    Properties.
//

//----------------------------------------------------------------
//    項目データを取得する
//  （デフォルトプロパティ）。
//

BookCategory ^
CategoryManager::default::get(CategoryHandle hCate)
{
    return  getBookCategory(hCate);
}

//----------------------------------------------------------------
//    項目用のバッファのサイズを得る。
//

CategoryHandle
CategoryManager::BufferCapacity::get()
{
    return  this->m_ptrObj->getBufferCapacity();
}

//----------------------------------------------------------------
//    内税項目のハンドル。
//

CategoryHandle
CategoryManager::InnerTaxHandle::get()
{
    return  this->m_ptrObj->getInnerTaxCategoryHandle();
}

void
CategoryManager::InnerTaxHandle::set(CategoryHandle hCate)
{
    this->m_ptrObj->setInnerTaxCategoryHandle(hCate);
}

//----------------------------------------------------------------
//    項目データを取得する。
//

BookCategory ^
CategoryManager::Items::get(CategoryHandle hCate)
{
    return  getBookCategory(hCate);
}

//----------------------------------------------------------------
//    外税項目のハンドル。
//

CategoryHandle
CategoryManager::OuterTaxHandle::get()
{
    return  this->m_ptrObj->getOuterTaxCategoryHandle();
}

void
CategoryManager::OuterTaxHandle::set(CategoryHandle hCate)
{
    this->m_ptrObj->setOuterTaxCategoryHandle(hCate);
}

//----------------------------------------------------------------
//    登録済みの項目数を取得する。
//

CategoryHandle
CategoryManager::RegisteredCategoryCount::get()
{
    return  this->m_ptrObj->getRegisteredCategoryCount();
}

//----------------------------------------------------------------
//    ルートにある項目数を取得する。
//

CategoryHandle
CategoryManager::RootCategoryCount::get()
{
    return  this->m_ptrObj->getRootCategoryCount();
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
