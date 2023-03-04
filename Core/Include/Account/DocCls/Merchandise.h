//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
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
**      An Interface of Merchandise struct.
**
**      @file       DocCls/Merchandise.h
**/

#if !defined( HACORE_DOCCLS_INCLUDED_MERCHANDISE_H )
#    define   HACORE_DOCCLS_INCLUDED_MERCHANDISE_H


#if !defined( HACORE_COMMON_INCLUDED_ACCOUTNS_TYPES_H )
#    include    "Account/Common/AccountsTypes.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    Merchandise  struct.
//
/**
**    一個の商品。
**/

struct  Merchandise
{
//========================================================================
//
//    Internal Type Definitions.
//

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
    Merchandise();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~Merchandise();

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
//    Public Member Functions (Operators).
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
public:

    /**   ルート項目インデックス。  **/
    CategoryHandle  hRootCate;

    /**   項目インデックス。        **/
    CategoryHandle  hCategory;

    /**   商品名の ID  (文字列テーブル内のインデックス) 。  **/
    StringIndex     siGoodsId;

    /**   商品名。  **/
    std::string     goodsName;

    /**   単価。    **/
    int             unitPrice;

    /**   数量。    **/
    int             nQuantity;

    /**   値引額。  **/
    int             cDiscount;

    /**   小計。    **/
    int             cSubTotal;

private:

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   MerchandiseTest;
};

}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
