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
**      An Interface of TextOperation class.
**
**      @file       Common/TextOperation.h
**/

#if !defined( HAWRAPPER_COMMON_INCLUDED_TEXT_OPERATION_H )
#    define   HAWRAPPER_COMMON_INCLUDED_TEXT_OPERATION_H


#pragma     once

#include    "AccountsTypes.h"

namespace  Wrapper  {

//========================================================================
//
//    TextOperation  class.
//

public ref  class  TextOperation
{
//========================================================================
//
//    Internal Type Definitions.
//
public:

    typedef     cli::array<System::Byte, 1>     ByteArray;

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
public:

    //----------------------------------------------------------------
    /**   文字列中の定数名に値を代入して返す。
    **
    **  @param [in] srcText     文字列。
    **  @param [in] varNames    定数名のリスト。
    **  @param [in] varVals     定数値のリスト。
    **/
    static  System::String^
    replaceConstant(
            System::String^     srcText,
            StringArray^        varNames,
            StringArray^        varVals);

    //----------------------------------------------------------------
    /**   文字列をバイト列に変換する。
    **
    **/
    static  IOffsetType
    toBytesFromString(
            System::String^         srcText,
            ByteArray^%             bufBytes,
            const  IOffsetType      posStart,
            const  IOffsetType      posEnd,
            const  System::Boolean  allocBuf);

    static  IOffsetType
    toBytesFromString(
            System::String^     srcText,
            ByteArray^          bufBytes,
            const  IOffsetType  posStart,
            const  IOffsetType  posEnd);

    //----------------------------------------------------------------
    /**   バイト列を文字列に変換する。
    **
    **/
    static  System::String^
    toStringFromBytes(
            ByteArray^              bufBytes,
            const  IOffsetType      posStart,
            const  IOffsetType      posEnd,
            const  System::Boolean  termNull);

    static  System::String^
    toStringFromBytes(
            ByteArray^          bufBytes,
            const  IOffsetType  posStart,
            const  IOffsetType  posEnd);

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    Properties.
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

};

}   //  End of namespace  Wrapper

#endif
