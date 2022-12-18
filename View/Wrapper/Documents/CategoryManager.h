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
**      An Interface of CategoryManager class.
**
**      @file       Documents/CategoryManager.h
**/

#if !defined( HAWRAPPER_DOCUMENTS_INCLUDED_CATEGORY_MANAGER_H )
#    define   HAWRAPPER_DOCUMENTS_INCLUDED_CATEGORY_MANAGER_H

#pragma     once

#include    "BookCategory.h"

namespace  Wrapper  {
namespace  Documents  {

//========================================================================
//
//    CategoryManager  class.
//

/**
**    家計簿の勘定科目、内訳などの項目を管理するクラス。
**/

public ref  class  CategoryManager
{
//========================================================================
//
//    Internal Type Definitions.
//
private:

    typedef     cli::array<BookCategory^, 1>    CategoryArray;

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    CategoryManager();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する。
    **  （デストラクタ）。
    **
    **/
    ~CategoryManager();

    //----------------------------------------------------------------
    /**   アンマネージドリソースを破棄する。
    **  （ファイナライザ）。
    **
    **/
    !CategoryManager();

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

//========================================================================
//
//    Member Variables.
//
private:

    /**   項目用バッファサイズ。    **/
    CategoryHandle      m_cateBufferSize;

    /**   登録済みの項目の数。      **/
    CategoryHandle      m_numUsedCategory;

    /**   ルートになる項目の個数。  **/
    CategoryHandle      m_numRootCategory;

    /**   項目のデータ。            **/
    CategoryArray^      m_bufCategory;

    /**   「内税」項目のハンドル。  **/
    CategoryHandle      m_chInnerTax;

    /**   「外税」項目のハンドル。  **/
    CategoryHandle      m_chOuterTax;

//========================================================================
//
//    Other Features.
//

};

}   //  End of namespace  Documents
}   //  End of namespace  Wrapper

#endif
