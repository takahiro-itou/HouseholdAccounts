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
**      An Interface of Receipt class.
**
**      @file       DocCls/Receipt.h
**/

#if !defined( HACORE_DOCCLS_INCLUDED_RECEIPT_H )
#    define   HACORE_DOCCLS_INCLUDED_RECEIPT_H


#if !defined( HACORE_DOCCLS_INCLUDED_MERCHANDISE_H )
#    include    "Merchandise.h"
#endif

#if !defined( HACORE_COMMON_INCLUDED_STRICT_VECTOR_H )
#    include    "Account/Common/StrictVector.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    Receipt  class.
//
/**
**    一回の買い物 (レシート一枚分) のデータ。
**/

class  Receipt
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
    Receipt();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~Receipt();

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
private:

    /**   店舗コード。      **/
    int                 m_shopIdx;

    /**   レシートの日付。  **/
    int                 m_receiptDate;

    /**   レシートの時刻。  **/
    int                 m_receiptTime;

    /**   購入した商品の数。    **/
    int                 m_numMerchandise;

    /**   購入した商品のデータ。    **/
    std::vector<Merchandise>    m_goodsArray;

    /**   合計の計算状態。  **/
    Boolean             m_totalCached;

    /**   小計。    **/
    int                 m_subTotal;

    /**   内税の合計。  **/
    int                 m_sumInnerTax;

    /**   外税の合計。  **/
    int                 m_sumOuterTax;

    /**   合計の金額。  **/
    int                 m_totalPrice;

    /**   内税を加える項目のハンドル。  **/
    CategoryHandle      m_chInnerTax;

    /**   外税を加える項目のハンドル。  **/
    CategoryHandle      m_chOuterTax;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   ReceiptTest;
};

}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
