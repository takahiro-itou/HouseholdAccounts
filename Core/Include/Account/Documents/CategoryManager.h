//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Household Accounts Core.  ---                  **
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

#if !defined( HACORE_DOCUMENTS_INCLUDED_CATEGORY_MANAGER_H )
#    define   HACORE_DOCUMENTS_INCLUDED_CATEGORY_MANAGER_H


#if !defined( HACORE_DOCUMENTS_INCLUDED_BOOK_CATEGORY_H )
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

namespace  Documents  {

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

    typedef     std::vector<BookCategory>
    CategoryArray;

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
    /**   項目用のバッファのサイズを得る。
    **
    **  @return     項目用バッファのサイズ。
    **/
    const   CategoryHandle
    getBufferCapacity()  const;

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
    CategoryHandle      m_chInnerTax;

    /**   「外税」項目のハンドル。  **/
    CategoryHandle      m_chOuterTax;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   CategoryManagerTest;
};

}   //  End of namespace  Documents
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
