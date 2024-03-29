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
**      An Interface of DecimalCurrency class.
**
**      @file       Common/DecimalCurrency.h
**/

#if !defined( HAWRAPPER_COMMON_INCLUDED_DECIMAL_CURRENCY_H )
#    define   HAWRAPPER_COMMON_INCLUDED_DECIMAL_CURRENCY_H

#pragma     once

#include    "AccountsTypes.h"

#include    "Account/Common/DecimalCurrency.h"


namespace  Wrapper  {
namespace  Common  {

//========================================================================
//
//    DecimalCurrency  class.
//

/**
**    固定小数点型の通貨クラス。
**/

public value class  DecimalCurrency
{
//========================================================================
//
//    Internal Type Definitions.
//
public:

    typedef     int64_t     TInternalValue;

    typedef     double      DecimalType;

private:

    typedef     HABook::Common::DecimalCurrency     WrapTarget;

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   アンマネージドリソースと同じ内容で初期化する
    **  （コンストラクタ）。
    **
    **  @param [in] srcCur    アンマネージド。
    **/
    DecimalCurrency(
            const   WrapTarget  &srcCur);

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
    /**   ラップ対象の型からインスタンスを生成する。
    **
    **  @param [in] srcVal    アンマネージド。
    **  @return     マネージド型のインスタンス。
    **/
    static  DecimalCurrency
    fromNativeInstance(
            const   WrapTarget  &srcVal);

    //----------------------------------------------------------------
    /**   ラップ対象の型を生成する。
    **
    **  @return     アンマネージド型のインスタンス。
    **/
    WrapTarget
    toNativeInstance();

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   現在の値を取得する。
    **
    **/
    DecimalType
    getValue();

    //----------------------------------------------------------------
    /**   値を設定する。
    **
    **  @param [in] intValue    内部の値。
    **  @param [in] intScale    スケール。
    **  @return     void.
    **/
    void
    setInternalValue(
            const   TInternalValue  intValue,
            const   TInternalValue  intScale);

//========================================================================
//
//    Properties.
//
public:

    //----------------------------------------------------------------
    /**   通貨型の値。
    **
    **/
    property    DecimalType
    DecimalValue
    {
        DecimalType     get();
    }

    //----------------------------------------------------------------
    /**   内部表現の値。
    **
    **/
    property    TInternalValue
    InternalValue
    {
        TInternalValue  get();
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

    TInternalValue      m_internValue;

    TInternalValue      m_scaleFactor;

//========================================================================
//
//    Other Features.
//

};

}   //  End of namespace  Common
}   //  End of namespace  Wrapper

#endif
