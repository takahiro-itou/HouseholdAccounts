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
**      An Implementation of ManagedDate class.
**
**      @file       Interface/ManagedDate.cpp
**/

#include    "PreCompile.h"

#include    "ManagedDate.h"

namespace  Wrapper  {

namespace  {

constexpr  int  g_firstDayTable[2][14] = {
    //  Jan, Feb, Mar, Apl, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec,
    { 0,  0,  31,  59,  90, 120, 151, 181, 212, 243, 273, 304, 334, 365 },
    { 0,  0,  31,  60,  91, 121, 152, 182, 213, 244, 274, 305, 335, 366 }
};

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

//----------------------------------------------------------------
//    指定した日付（西暦年・月・日）から曜日を得る。
//

Weekday
ManagedDate::getWeekday(
        const  int  lngYear,
        const  int  lngMonth,
        const  int  lngDay)
{
    int lngWeekday;
    int tYear   = lngYear;
    int tMonth  = lngMonth;

    if ( tMonth <= 2 ) {
        tMonth    += 12;
        -- tYear;
    }

    lngWeekday = (tYear + (tYear / 4) - (tYear / 100) + (tYear / 400));
    lngWeekday += ((tMonth * 13 + 8) / 5) + lngDay;

    return ( static_cast<Weekday>(lngWeekday % 7) );
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
