﻿//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
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
**      An Interface of CategoryManager class.
**
**      @file       DocCls/CategoryManager.h
**/

#if !defined( HACORE_DOCCLS_INCLUDED_CATEGORY_MANAGER_H )
#    define   HACORE_DOCCLS_INCLUDED_CATEGORY_MANAGER_H


#if !defined( HACORE_DOCCLS_INCLUDED_BOOK_CATEGORY_H )
#    include    "BookCategory.h"
#endif

#if !defined( HACORE_COMMON_INCLUDED_STRICT_VECTOR_H )
#    include    "Account/Common/StrictVector.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

//  クラスの前方宣言。  //
namespace  Common  {
class   DecimalCurrency;
}   //  End of namespace  Common

namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    CategoryManager  class.
//
/**
**
**/

class  CategoryManager
{
//========================================================================
//
//    Internal Type Definitions.
//
private:

    DECLARE_STRICT_VECTOR(BookCategory, CategoryHandle, CategoryArray);

    typedef     Common::DecimalCurrency     DecimalCurrency;

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
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~CategoryManager();

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
public:

    //----------------------------------------------------------------
    /**   項目データ用バッファを確保する。
    **
    **  @param [in] bufSize   確保する項目数。
    **  @return     増えた部分の先頭のインデックス。
    **/
    virtual  const  CategoryHandle
    allocCategoryBuffers(
            const   CategoryHandle  bufSize);

    //----------------------------------------------------------------
    /**   新しい項目用の領域を確保する。
    **
    **  @return     新しい項目用のハンドル。
    **/
    virtual  const  CategoryHandle
    allocNewCategory();

    //----------------------------------------------------------------
    /**   名前から項目を検索する。
    **
    **  @param [in] cateName      項目名。
    **  @param [in] cateParent    検索を開始する親ハンドル。
    **  @return     項目名に対応する項目のハンドル。
    **/
    virtual  const  CategoryHandle
    findCategory(
            const   std::string    &cateName,
            const   CategoryHandle  cateParent = CategoryHandle(-1)) const;

    //----------------------------------------------------------------
    /**   項目の種類を取得する。
    **
    **  @param [in] hCate   項目のハンドル。
    **  @return     項目フラグの内タイプの値を返す。
    **/
    virtual  const  CategoryFlags
    getCategoryType(
            const   CategoryHandle  hCate)  const;

    //----------------------------------------------------------------
    /**   項目のルート項目のハンドルを取得する。
    **
    **  @param [in] idxCate   項目番号。
    **  @return     項目がルート項目を示している場合は、
    **      それ自身を返す。
    **/
    virtual  const  CategoryHandle
    getRootCategoryHandle(
            const   CategoryHandle  idxCate)  const;

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
    virtual  const  CategoryHandle
    insertNewCategory(
            const  CategoryHandle   cateParent,
            const  std::string     &cateName,
            const  CategoryFlags    cateFlags,
            const  DateSerial       startDate,
            const  DecimalCurrency &startBalance);

    //----------------------------------------------------------------
    /**   指定した項目のサブ項目（子孫）にあたるか判定する。
    **
    **  サブ項目のさらにサブ項目等、いわゆる子孫も含む。
    **
    **  @param [in] cateToCheck     検査する項目のハンドル。
    **  @param [in] cateUpstream    先祖と期待される項目。
    **  @retval     BOOL_TRUE   : 子孫に該当。
    **      項目 cateCheck  は cateUpstream の子孫の項目。
    **      なお両者が等しい場合を含む。
    **  @retval     BOOL_FALSE  : 上記以外の場合。
    **/
    virtual  const  Boolean
    isDescendantCategory(
            const   CategoryHandle  cateToCheck,
            const   CategoryHandle  cateUpstream)  const;

    //----------------------------------------------------------------
    /**   ルート項目データ用の領域を確保する。
    **
    **  @param [in] numRoot   確保する項目数。
    **  @return     最初の非ルート項目のインデックス。
    **/
    virtual  const  CategoryHandle
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
    virtual  const  CategoryHandle
    setupRootCategory(
            const  CategoryHandle   cateHandle,
            const  std::string     &cateName,
            const  CategoryFlags    cateFlags,
            const  DateSerial       startDate,
            const  DecimalCurrency &startBalance);

//========================================================================
//
//    Public Member Functions.
//

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
    BookCategory  &
    getBookCategory(
            const   CategoryHandle  hCate);

    const   BookCategory  &
    getBookCategory(
            const   CategoryHandle  hCate)  const;

    //----------------------------------------------------------------
    /**   項目用のバッファのサイズを得る。
    **
    **  @return     項目用バッファのサイズ。
    **/
    const   CategoryHandle
    getBufferCapacity()  const;

    //----------------------------------------------------------------
    /**   内税項目のハンドルを取得する。
    **
    **  @return     項目のハンドル。
    **/
    const   CategoryHandle
    getInclusiveTaxCategoryHandle()  const;

    //----------------------------------------------------------------
    /**   内税項目のハンドルを設定する。
    **
    **  @param [in] hCate   項目ハンドル。
    **/
    void
    setInclusiveTaxCategoryHandle(
            const   CategoryHandle  hCate);

    //----------------------------------------------------------------
    /**   外税項目のハンドルを取得する。
    **
    **  @return     項目のハンドル。
    **/
    const   CategoryHandle
    getExclusiveTaxCategoryHandle()  const;

    //----------------------------------------------------------------
    /**   外税項目のハンドルを設定する。
    **
    **  @param [in] hCate   項目ハンドル。
    **/
    void
    setExclusiveTaxCategoryHandle(
            const   CategoryHandle  hCate);

    //----------------------------------------------------------------
    /**   登録済みの項目数を取得する。
    **
    **  @return     登録済みの項目数を返す。
    **/
    const   CategoryHandle
    getRegisteredCategoryCount()  const;

    //----------------------------------------------------------------
    /**   ルートにある項目数を取得する。
    **
    **  @return     ルートの項目数を返す。
    **/
    const   CategoryHandle
    getRootCategoryCount()  const;

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
    CategoryArray       m_bufCategory;

    /**   「内税」項目のハンドル。  **/
    CategoryHandle      m_chInclusiveTax;

    /**   「外税」項目のハンドル。  **/
    CategoryHandle      m_chExclusiveTax;

//========================================================================
//
//    Other Features.
//
private:
    typedef     CategoryManager     This;
    CategoryManager     (const  This  &);
    This &  operator =  (const  This  &);
public:
    //  テストクラス。  //
    friend  class   CategoryManagerTest;
};

}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
