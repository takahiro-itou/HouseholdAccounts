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

#if !defined( HACORE_SYS_INCLUDED_STL_VECTOR )
#    include    <vector>
#    define   HACORE_SYS_INCLUDED_STL_VECTOR
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
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
