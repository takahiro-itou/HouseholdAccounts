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
**      An Interface of ReceiptEntriesChunk class.
**
**      @file       DocCls/ReceiptEntriesChunk.h
**/

#if !defined( HACORE_DOCCLS_INCLUDED_RECEIPT_ENTRIES_CHUNK_H )
#    define   HACORE_DOCCLS_INCLUDED_RECEIPT_ENTRIES_CHUNK_H


#if !defined( HACORE_DOCCLS_INCLUDED_PURCHASED_GOODS_H )
#    include    "PurchasedGoods.h"
#endif

#if !defined( HACORE_COMMON_INCLUDED_STRICT_VECTOR_H )
#    include    "Account/Common/StrictVector.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    ReceiptEntriesChunk  struct.
//
/**
**    集計ブロック。
**/

struct  ReceiptEntriesChunk
{
//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**   収支フラグ。  **/
    enum class  ChunkInOutFlags
    {
        DOUBLE_ENTRY,
        INCOME,
        OUTLAY,
        BANK_WITHDRAW,
        BANK_DEPOSIT,
        BANK_TRANSFER,
    };

    DECLARE_STRICT_VECTOR(
            PurchasedGoods,     PurchaseNumber,
            PurchasingList
    );

private:

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
    ReceiptEntriesChunk();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~ReceiptEntriesChunk();

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
    /**   インスタンスを文字列表現に変換する。
    **
    **  @return     文字列表現を返す。
    **/
    const   std::string
    toString()  const;

    //----------------------------------------------------------------
    /**   インスタンスの文字列表現をストリームに書き込む。
    **
    **  @param [in,out] os    出力ストリーム。
    **  @return     出力後のストリームの参照を返す。
    **/
    std::ostream  &
    writeToStream(
            std::ostream  & os)  const;

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

    /**   収支フラグ。  **/
    ChunkInOutFlags     blockFlags;

    /**   借方口座。    **/
    CategoryHandle      chlDebitAccount;

    /**   貸方口座。    **/
    CategoryHandle      chrCreditAccount;

    /**   借方金額。    **/
    CurrencyNumerator   cnlDebitAmount;

    /**   貸方金額。    */
    CurrencyNumerator   cnrCreditAmount;

    /**   商品リスト。  **/
    PurchasingList      goodsList;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   ReceiptEntriesChunkTest;
};

//========================================================================
//
//    Functions (Operators).
//

inline  std::ostream  &
operator << (std::ostream & os, const ReceiptEntriesChunk & rhs)
{
    return  rhs.writeToStream(os);
}

}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
