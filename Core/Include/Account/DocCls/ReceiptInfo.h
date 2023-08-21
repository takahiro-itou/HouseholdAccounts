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
**      An Interface of ReceiptInfo class.
**
**      @file       DocCls/ReceiptInfo.h
**/

#if !defined( HACORE_DOCCLS_INCLUDED_RECEIPT_INFO_H )
#    define   HACORE_DOCCLS_INCLUDED_RECEIPT_INFO_H


#if !defined( HACORE_DOCCLS_INCLUDED_RECEIPT_ENTRIES_CHUNK_H )
#    include    "ReceiptEntriesChunk.h"
#endif

#if !defined( HACORE_COMMON_INCLUDED_DATE_TIME_FORMAT_H )
#    include    "Account/Common/DateTimeFormat.h"
#endif

#if !defined( HACORE_COMMON_INCLUDED_STRICT_VECTOR_H )
#    include    "Account/Common/StrictVector.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    ReceiptInfo  class.
//
/**
**    一回の買い物 (レシート一枚分) のデータ。
**/

class  ReceiptInfo
{
//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**
    **    集計ブロックのインデックス型。
    **/
    DECLARE_STRICT_TYPE(int,    ChunkIndex);

    DECLARE_STRICT_VECTOR(
            ReceiptEntriesChunk,    ChunkIndex,
            ChunkArray
    );

private:

    typedef     Common::DateTimeFormat          DateTimeFormat;

    typedef     int                             ReceiptDate;

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
    ReceiptInfo();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~ReceiptInfo();

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
    /**   レシート情報を初期化する。
    **
    **  @param [in] recDate     レシートの日付
    **  @param [in] recTime     レシートの時刻
    **  @param [in] shopName    店名
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    initializeReceiptInfo(
            const  std::string  &recDate,
            const  std::string  &recTime,
            const  std::string  &shopName);

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
public:

    //----------------------------------------------------------------
    /**   レコードを取得する。
    **
    **  @return     レコードチェンクの配列。
    **/
    const   ChunkArray  &
    getRecordChunks()  const;

    //----------------------------------------------------------------
    /**   店名を取得する。
    **
    **  @return     店名。
    **/
    const  std::string  &
    getShopName()  const;

    //----------------------------------------------------------------
    /**   店名を設定する。
    **
    **  @param [in] shopName    店名。
    **/
    ReceiptInfo  &
    setShopName(
            const  std::string  &shopName);

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

    /**   レシートの日付。  **/
    std::string         m_receiptDate;

    /**   レシートの時刻。  **/
    std::string         m_receiptTime;

    /**   店名コード。      **/
    int                 m_shopIdx;

    /**   店名。            **/
    std::string         m_shopName;

    /**   レコード。        **/
    ChunkArray          m_recordChunk;

    /**   合計の計算状態。  **/
    Boolean             m_totalCached;

    /**   小計。    **/
    int                 m_subTotal;

    /**   内税の合計。  **/
    CurrencyNumerator   m_sumInclusiveTax;

    /**   外税の合計。  **/
    CurrencyNumerator   m_sumExclusiveTax;

    /**   合計の金額。  **/
    int                 m_totalPrice;

    /**   内税を加える項目のハンドル。  **/
    CategoryHandle      m_chInclusiveTax;

    /**   外税を加える項目のハンドル。  **/
    CategoryHandle      m_chExclusiveTax;

    /**   項目を管理するインスタンス。  **/
    const   CategoryManager *   pCatMan;

//========================================================================
//
//    Other Features.
//
public:
    typedef     ReceiptInfo     This;
    ReceiptInfo         (const  This  &)    = default;
    This &  operator =  (const  This  &)    = default;
public:
    //  テストクラス。  //
    friend  class   ReceiptInfoTest;
};

//========================================================================
//
//    Functions (Operators).
//

inline  std::ostream  &
operator << (std::ostream & os, const ReceiptInfo & rhs)
{
    return  rhs.writeToStream(os);
}

//========================================================================
/**
**    レシートの配列。
**/

DECLARE_STRICT_VECTOR(ReceiptInfo,  ReceiptNumber,  ReceiptList);


}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
