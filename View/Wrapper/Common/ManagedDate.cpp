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

constexpr  int  MAXMONTH    = 12;

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
//    指定された日から、日付情報に分解する。
//

ParsedDate
ManagedDate::getDayFromIndex(
        const  int  lngYear,
        const  int  lngDayIndex,
        const  int  lngDayOffset_)
{
    ParsedDate  utDate;
    int lngMonth, lngDay;
    int lngDayInYear;
    int lngTempDay, lngUruu;
    int tmpYear = lngYear;
    int lngDayOffset    = lngDayOffset_;

    //  まずオフセットを除いて指定された日が元日から数えて何日目か調べる。  //
    if ( lngDayOffset < 0 ) {
        lngDayOffset = static_cast<int>( getWeekday(lngYear, 1, 1) );
    }
    lngDayInYear = lngDayIndex - lngDayOffset;
    lngTempDay = (lngDayIndex + 1);

    if ( lngDayInYear < 0 ) {
        //  去年の余り。    //
        lngMonth    = 12;
        -- tmpYear;
        lngDay = lngTempDay + 31;
    } else {
        lngMonth    = MAXMONTH + 1;
        lngUruu = isUruuYear(lngYear);
        for ( int i = 1; i <= MAXMONTH; ++ i ) {
            if ( lngDayInYear < g_firstDayTable[lngUruu][i + 1] ) {
                lngMonth    = i;
                break;
            }
        }
        if ( lngMonth == MAXMONTH + 1 ) {
            //  来年分。    //
            lngMonth    = 1;
            ++ tmpYear;
            lngDay = lngTempDay - g_firstDayTable[lngUruu][MAXMONTH + 1];
        } else {
            lngDay = lngTempDay - g_firstDayTable[lngUruu][lngMonth];
        }
    }

    utDate.nYear    = tmpYear;
    utDate.nMonth   = lngMonth;
    utDate.nDay     = lngDay;
    utDate.nDayInYear   = lngDayInYear;
    utDate.nDayOffset   = lngDayOffset;
    utDate.nDayIndex    = lngDayIndex;
    utDate.nWeek    = (lngDayIndex / 7);
    utDate.nWeekday = static_cast<Weekday>(lngDayIndex % 7);

    return ( utDate );
}

//----------------------------------------------------------------
//    元日から数えて何日目かを計算する。
//

int
ManagedDate::getDayInYear(
        const  int  lngYear,
        const  int  lngMonth,
        const  int  lngDay)
{
    int lngTemp = isUruuYear(lngYear);
    return ( g_firstDayTable[lngTemp][lngMonth] + lngDay - 1 );
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

//----------------------------------------------------------------
//    指定した西暦年が閏年か判定する。
//

int
ManagedDate::isUruuYear(
        const  int  lngYear)
{
    if ( (lngYear % 4) != 0 ) {
        return ( 0 );
    }
    if ( ((lngYear % 100) == 0) && ((lngYear % 400) != 0) ) {
        return ( 0 );
    }
    return ( 1 );
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
