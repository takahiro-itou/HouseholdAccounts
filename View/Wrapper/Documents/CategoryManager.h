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


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

//  クラスの前方宣言。  //
namespace  Documents  {
class   CategoryManager;
}   //  End of namespace  Documents

HOUSEHOLD_ACCOUNTS_NAMESPACE_END


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

    typedef     HouseholdAccounts::Documents::CategoryManager
    WrapTarget;

    typedef     cli::array<BookCategory^, 1>    CategoryArray;

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
            const  CategoryFlags        cateFlags,
            const  DateSerial           startDate,
            Common::DecimalCurrency ^   startBalance);

//========================================================================
//
//    Accessors.
//
public:

//========================================================================
//
//    Properties.
//
public:

    //----------------------------------------------------------------
    /**   項目用のバッファのサイズを得る。
    **
    **  @return     項目用バッファのサイズ。
    **/
    property    CategoryHandle
    BufferCapacity
    {
        CategoryHandle  get();
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

}   //  End of namespace  Documents
}   //  End of namespace  Wrapper

#endif
