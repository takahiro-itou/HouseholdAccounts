﻿//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
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
**      An Interface of CategoryManager class.
**
**      @file       DocCls/CategoryManager.h
**/

#if !defined( HAWRAPPER_DOCCLS_INCLUDED_CATEGORY_MANAGER_H )
#    define   HAWRAPPER_DOCCLS_INCLUDED_CATEGORY_MANAGER_H

#pragma     once


#include    "BookCategory.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

//  クラスの前方宣言。  //
namespace  DocCls  {
class   CategoryManager;
}   //  End of namespace  DocCls

HOUSEHOLD_ACCOUNTS_NAMESPACE_END


namespace  Wrapper  {
namespace  DocCls  {

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

    typedef     HABook::DocCls::CategoryManager     WrapTarget;

    typedef     HABook::DocCls::BookCategory
    CoreBookCategory;

    typedef     cli::array<BookCategory^, 1>        CategoryArray;

    typedef     Common::DecimalCurrency             DecimalCurrency;

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
public:

    //----------------------------------------------------------------
    /**   項目の種類を取得する。
    **
    **  @param [in] hCate   項目のハンドル。
    **  @return     項目フラグの内タイプの値を返す。
    **/
    CategoryFlags
    getCategoryType(
            const   CategoryHandle  hCate);

    //----------------------------------------------------------------
    /**   項目のルート項目のハンドルを取得する。
    **
    **  @param [in] idxCate   項目番号。
    **  @return     項目がルート項目を示している場合は、
    **      それ自身を返す。
    **/
    CategoryHandle
    getRootCategoryHandle(
            const   CategoryHandle  idxCate);

    //----------------------------------------------------------------
    /**   指定した項目に新しいサブ項目を追加する。
    **
    **  @param [in] cateParent      親項目のハンドル。
    **  @param [in] cateName        項目名。
    **  @param [in] cateFlags       項目フラグ。
    **  @param [in] startDate       開始日。
    **  @param [in] startBalance    開始時金額。
    **  @return     追加した項目のハンドル。
    **/
    CategoryHandle
    insertNewCategory(
            const  CategoryHandle   cateParent,
            System::String ^        cateName,
            const  CategoryFlags    cateFlags,
            const  DateSerial       startDate,
            DecimalCurrency ^       startBalance);

    //----------------------------------------------------------------
    /**   ルート項目データ用の領域を確保する。
    **
    **  @param [in] numRoot   確保する項目数。
    **  @return     最初の非ルート項目のインデックス。
    **/
    CategoryHandle
    reserveRootCategories(
            const   CategoryHandle  numRoot);

    //----------------------------------------------------------------
    /**   ルート項目のデータを設定する。
    **
    **  @param [in] cateHandle      項目のハンドル。
    **  @param [in] cateName        項目名。
    **  @param [in] cateFlags       項目フラグ。
    **  @param [in] startDate       開始日。
    **  @param [in] startBalance    開始時金額。
    **  @return     設定した項目のハンドル。
    **/
    CategoryHandle
    setupRootCategory(
            const  CategoryHandle   cateHandle,
            System::String ^        cateName,
            const  CategoryFlags    cateFlags,
            const  DateSerial       startDate,
            DecimalCurrency ^       startBalance);

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   項目データを取得する。
    **
    **  @param [in] hCate   項目ハンドル。
    **  @return     指定した項目。
    **/
    BookCategory^
    getBookCategory(
            const   CategoryHandle  hCate);

    //----------------------------------------------------------------
    /**   項目データを取得する。
    **
    **  @param [in] hCate   項目ハンドル。
    **  @return     指定した項目。
    **/
    const   CoreBookCategory  &
    getRawBookCategory(
            const   CategoryHandle  hCate);

//========================================================================
//
//    Properties.
//
public:

    //----------------------------------------------------------------
    /**   項目データを取得する
    **  （デフォルトプロパティ）。
    **
    **  @param [in] hCate   項目ハンドル。
    **  @return     指定した項目。
    **/
    property    BookCategory ^
    default [CategoryHandle]
    {
        BookCategory^   get(CategoryHandle hCate);
    }

    //----------------------------------------------------------------
    /**   項目用のバッファのサイズ。
    **
    **  @return     項目用バッファのサイズ。
    **/
    property    CategoryHandle
    BufferCapacity
    {
        CategoryHandle  get();
    }

    //----------------------------------------------------------------
    /**   内税項目のハンドル。
    **
    **/
    property    CategoryHandle
    InclusiveTaxHandle
    {
        CategoryHandle  get();
        void set(CategoryHandle hCate);
    }

    //----------------------------------------------------------------
    /**   項目データを取得する。
    **
    **  @param [in] hCate   項目ハンドル。
    **  @return     指定した項目。
    **/
    property    BookCategory ^
    Items [CategoryHandle]
    {
        BookCategory^   get(CategoryHandle hCate);
    }

    //----------------------------------------------------------------
    /**   外税項目のハンドル。
    **
    **/
    property    CategoryHandle
    ExclusiveTaxHandle
    {
        CategoryHandle  get();
        void set(CategoryHandle hCate);
    }

    //----------------------------------------------------------------
    /**   登録済みの項目数を取得する。
    **
    **  @return     登録済みの項目数を返す。
    **/
    property    CategoryHandle
    RegisteredCategoryCount
    {
        CategoryHandle  get();
    }

    //----------------------------------------------------------------
    /**   ルートにある項目数を取得する。
    **
    **  @return     ルートの項目数を返す。
    **/
    property    CategoryHandle
    RootCategoryCount
    {
        CategoryHandle  get();
    }

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

    WrapTarget  *   m_ptrObj;

//========================================================================
//
//    Other Features.
//

};

}   //  End of namespace  DocCls
}   //  End of namespace  Wrapper

#endif
