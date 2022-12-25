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
**      An Implementation of CategoryManager class.
**
**      @file       Documents/CategoryManager.cpp
**/

#include    "PreCompile.h"

#include    "Account/Documents/CategoryManager.h"

#include    "CategoryManager.h"

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
//    項目のルート項目のハンドルを取得する。
//

CategoryHandle
CategoryManager::getRootCategoryHandle(
        const   CategoryHandle  idxCate)
{
    CategoryHandle  catePar;
    CategoryHandle  cateCur = idxCate;

    catePar = this->m_bufCategory[cateCur]->parentHandle;
    while ( catePar >= 0 ) {
        cateCur = catePar;
        catePar = this->m_bufCategory[cateCur]->parentHandle;
    }
    return ( cateCur );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    項目用のバッファのサイズを得る。
//

CategoryHandle
CategoryManager::getBufferCapacity()
{
    return ( this->m_cateBufferSize );
}

//----------------------------------------------------------------
//    登録済みの項目数を取得する。
//

CategoryHandle
CategoryManager::getRegisteredCategoryCount()
{
    return ( this->m_numUsedCategory );
}

//----------------------------------------------------------------
//    ルートにある項目数を取得する。
//

CategoryHandle
CategoryManager::getRootCategoryCount()
{
    return ( this->m_numRootCategory );
}

//========================================================================
//
//    Properties.
//

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
