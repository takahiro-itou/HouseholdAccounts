﻿//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
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

//----------------------------------------------------------------
//    現在の値を取得する。
//

DecimalCurrency::DecimalType
DecimalCurrency::getValue()
{
    return ( static_cast<DecimalType>(this->m_intVal) );
}

//========================================================================
//
//    Accessors.
//

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
    return ( this->m_intVal );
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
