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
**      An Interface of ManagedDate class.
**
**      @file       Interface/ManagedDate.h
**/

#if !defined( HAWRAPPER_COMMON_INCLUDED_MANAGED_DATE_H )
#    define   HAWRAPPER_COMMON_INCLUDED_MANAGED_DATE_H

#pragma     once

#include    "HouseholdAccounts/Common/AccountsTypes.h"

namespace  Wrapper  {

public  enum class  Weekday
{
    ewdSunday       = 0,
    ewdMonday       = 1,
    ewdTuesday      = 2,
    ewdWednesday    = 3,
    ewdThursday     = 4,
    ewdFriday       = 5,
    ewdSaturday     = 6,
};

//========================================================================
//
//    ParsedDate  structure.
//

public value struct ParsedDate
{
    int     nYear;      /**<  西暦年。  **/
    int     nMonth;     /**<  月。      **/
    int     nDay;       /**<  日。      **/

    /**
    **    その年の中で何日目か。
    **
    **    つまり、元日からの経過日数（元日をゼロ）。
    **/
    int     nDayInYear;

    /**   元日の前に何日分のデータがあるか（一週間の端数処理）。    **/
    int     nDayOffset;

    /**   その日が去年の端数を含むデータ内で何番目か。  **/
    int     nDayIndex;

    /**   何週目。  **/
    int     nWeek;

    /**   曜日。    **/
    Weekday     nWeekday;
};

//========================================================================
//
//    ManagedDate  class.
//

public ref  class  ManagedDate
{
//========================================================================
//
//    Internal Type Definitions.
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
