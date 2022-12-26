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
**      An Interface of DecimalCurrency class.
**
**      @file       Common/DecimalCurrency.h
**/

#if !defined( HACORE_COMMON_INCLUDED_DECIMAL_CURRENCY_H )
#    define   HACORE_COMMON_INCLUDED_DECIMAL_CURRENCY_H


#if !defined( HACORE_COMMON_INCLUDED_ACCOUTNS_TYPES_H )
#    include    "AccountsTypes.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //

//========================================================================
//
//    DecimalCurrency  class.
//
/**
**    固定小数点型の通貨クラス。
**/

class  DecimalCurrency
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    typedef     int64_t     TInternalValue;

    typedef     double      DecimalType;

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
    DecimalCurrency();

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （コンストラクタ）。
    **
    **  @param [in] intValue    内部の値。
    **  @param [in] intScale    スケール。
    **/
    DecimalCurrency(
            const   TInternalValue  intValue,
            const   TInternalValue  intScale);

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （コンストラクタ）。
    **
    **  @param [in] intValue    内部の値。
    **/
    DecimalCurrency(
            const   TInternalValue  intValue);

    //----------------------------------------------------------------
    /**   別のインスタンスと同じ内容で初期化する。
    **  （コピーコンストラクタ）。
    **
    **  @param [in] src   コピー元インスタンス。
    **/
    DecimalCurrency(
            const  DecimalCurrency  &src);

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~DecimalCurrency();

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
public:

    //----------------------------------------------------------------
    /**   現在の内部表現の値を取得する。
    **
    **  @return     内部表現の値。
    **/
    const   TInternalValue
    getInternalValue()  const;

    //----------------------------------------------------------------
    /**   値を設定する。
    **
    **  @param [in] intValue    内部表現の数値。
    **  @return     インスタンス自身の参照。
    **/
    DecimalCurrency  &
    setInternalValue(
            const   TInternalValue  intValue);

    //----------------------------------------------------------------
    /**   値を設定する。
    **
    **  @param [in] intValue    内部表現の数値。
    **  @param [in] intScale    スケール。
    **  @return     インスタンス自身の参照。
    **/
    DecimalCurrency  &
    setInternalValue(
            const   TInternalValue  intValue,
            const   TInternalValue  intScale);

    //----------------------------------------------------------------
    /**   現在のスケールファクタを取得する。
    **
    **  @return     現在のスケールファクタの値。
    **/
    const   TInternalValue
    getScaleFactor()  const;

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

    TInternalValue      m_internValue;

    TInternalValue      m_scaleFactor;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   DecimalCurrencyTest;
};

}   //  End of namespace  Common
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
