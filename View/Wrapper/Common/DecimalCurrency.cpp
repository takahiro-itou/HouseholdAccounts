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
**      An Implementation of DecimalCurrency class.
**
**      @file       Common/DecimalCurrency.cpp
**/

#include    "PreCompile.h"

#include    "DecimalCurrency.h"


namespace  Wrapper  {
namespace  Common  {

namespace  {

}   //  End of (Unnamed) namespace

//========================================================================
//
//    CategoryWiseAggregates  class.
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
        const   TInternalValue  intValue,
        const   TInternalValue  intScale)
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
//    インスタンスを破棄する
//  （デストラクタ）。
//

DecimalCurrency::~DecimalCurrency()
{
    //  マネージドリソースを破棄する。              //

    //  続いて、アンマネージドリソースも破棄する。  //
    this->!DecimalCurrency();
}

//----------------------------------------------------------------
//    アンマネージドリソースを破棄する
//  （ファイナライザ）。
//

DecimalCurrency::!DecimalCurrency()
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
//    現在の値を取得する。
//

DecimalCurrency::DecimalType
DecimalCurrency::getValue()
{
    return (
            static_cast<DecimalType>(this->m_internValue) /
            static_cast<DecimalType>(this->m_scaleFactor)
    );
}

//----------------------------------------------------------------
//    値を設定する。
//

void
DecimalCurrency::setInternalValue(
        const   TInternalValue  intValue,
        const   TInternalValue  intScale)
{
    this->m_internValue = intValue;
    this->m_scaleFactor = intScale;
}

//========================================================================
//
//    Properties.
//

//----------------------------------------------------------------
//    通貨型の値。
//

DecimalCurrency::DecimalType
DecimalCurrency::decimalValue::get()
{
    return ( getValue() );
}

//----------------------------------------------------------------
//    内部表現の値。
//

DecimalCurrency::TInternalValue
DecimalCurrency::internalValue::get()
{
    return ( this->m_internValue );
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
}   //  End of namespace  Wrapper
