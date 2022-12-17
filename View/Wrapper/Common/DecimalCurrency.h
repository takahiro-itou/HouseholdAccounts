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
**      An Interface of DecimalCurrency class.
**
**      @file       Common/DecimalCurrency.h
**/

#if !defined( HAWRAPPER_COMMON_INCLUDED_DECIMAL_CURRENCY_H )
#    define   HAWRAPPER_COMMON_INCLUDED_DECIMAL_CURRENCY_H

#pragma     once

#include    "AccountsTypes.h"

namespace  Wrapper  {
namespace  Common  {

//========================================================================
//
//    DecimalCurrency  class.
//

/**
**    固定小数点型の通貨クラス。
**/

public ref  class  DecimalCurrency
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
    /**   現在の値を取得する。
    **
    **/
    DecimalType
    getValue();

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
    decimalValue
    {
        DecimalType     get();
    }

    //----------------------------------------------------------------
    /**   内部表現の値。
    **
    **/
    property    TInternalValue
    internalValue
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

    TInternalValue      m_intVal;

//========================================================================
//
//    Other Features.
//

};

}   //  End of namespace  Common
}   //  End of namespace  Wrapper

#endif
