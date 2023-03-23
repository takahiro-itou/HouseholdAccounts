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
**      An Implementation of DecimalCurrency class.
**
**      @file       Common/DecimalCurrency.cpp
**/

#include    "Account/pch/PreCompile.h"

#include    "Account/Common/DecimalCurrency.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

namespace  {
}   //  End of (Unnamed) namespace.

//========================================================================
//
//    DecimalCurrency  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

DecimalCurrency::DecimalCurrency()
    : m_internValue(0),
      m_scaleFactor(1)
{
}

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

DecimalCurrency::DecimalCurrency(
        const  CurrencyNumerator    intValue,
        const  CurrencyDenominator  intScale)
    : m_internValue(intValue),
      m_scaleFactor(intScale)
{
}

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

DecimalCurrency::DecimalCurrency(
        const   TInternalValue  intValue)
    : m_internValue(intValue),
      m_scaleFactor(1)
{
}

//----------------------------------------------------------------
//    別のインスタンスと同じ内容で初期化する。
//  （コピーコンストラクタ）。
//

DecimalCurrency::DecimalCurrency(
        const  DecimalCurrency  &src)
    : m_internValue(src.m_internValue),
      m_scaleFactor(src.m_scaleFactor)
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

DecimalCurrency::~DecimalCurrency()
{
}

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

//----------------------------------------------------------------
//    現在の内部表現の値を取得する。
//

const   CurrencyNumerator
DecimalCurrency::getInternalValue()  const
{
    return ( this->m_internValue );
}

//----------------------------------------------------------------
//    値を設定する。
//

DecimalCurrency  &
DecimalCurrency::setInternalValue(
        const   CurrencyNumerator   intValue)
{
    this->m_internValue = intValue;
    return  ( *this );
}

//----------------------------------------------------------------
//    値を設定する。
//

DecimalCurrency  &
DecimalCurrency::setInternalValue(
        const  CurrencyNumerator    intValue,
        const  CurrencyDenominator  intScale)
{
    this->m_internValue = intValue;
    this->m_scaleFactor = intScale;
    return ( *this );
}

//----------------------------------------------------------------
//    現在のスケールファクタを取得する。
//

const   CurrencyDenominator
DecimalCurrency::getScaleFactor()  const
{
    return ( this->m_scaleFactor );
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Common
HOUSEHOLD_ACCOUNTS_NAMESPACE_END
