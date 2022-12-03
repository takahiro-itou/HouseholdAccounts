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
**      An Implementation of ManagedDate class.
**
**      @file       Interface/ManagedDate.cpp
**/

#include    "PreCompile.h"

#include    "ManagedDate.h"

namespace  Wrapper  {

namespace  {

}   //  End of (Unnamed) namespace

//========================================================================
//
//    ManagedDate  class.
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
//    二つの日付を比較する。
//

int
ManagedDate::compareDates(
        const  int  lngYear1,
        const  int  lngDayIndex1,
        const  int  lngYear2,
        const  int  lngDayIndex2)
{
    if ( lngYear1 < lngYear2 ) {
        return ( -1 );
    } else if ( lngYear1 > lngYear2 ) {
        return (  1 );
    }

    if ( lngDayIndex1 < lngDayIndex2 ) {
        return ( -1 );
    } else if ( lngDayIndex1 > lngDayIndex2 ) {
        return (  1 );
    }

    return ( 0 );
}

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

}   //  End of namespace  Wrappe
