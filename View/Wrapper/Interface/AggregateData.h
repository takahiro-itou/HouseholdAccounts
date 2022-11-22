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
**      An Interface of AggregateData class(es).
**
**      @file       Interface/AggregateData.h
**/

#if !defined( HAWRAPPER_INTERFACE_INCLUDED_AGGREGATE_DATA_H )
#    define   HAWRAPPER_INTERFACE_INCLUDED_AGGREGATE_DATA_H

#pragma     once

#include    "HouseholdAccounts/Common/AccountsTypes.h"

namespace  Wrapper  {

//========================================================================
//
//    集計されたデータの情報。
//

//========================================================================
/**
**    項目毎の年間集計。
**/

public value struct BookItemAnnualCounts
{
public:

    /**   開始時の数値。    **/
    property    cli::array<int, 1>^     nStartValues;

    /**   終了時の数値。    **/
    property    cli::array<int, 1>^     nEndValues;

    /**   各年の合計金額。  **/
    property    cli::array<int, 1>^     nYearTotal;
};

//========================================================================
/**
**    項目毎の詳細集計結果。
**/

public value struct BookItemDetailCounts
{
public:

    /**   日毎の合計金額 :  378 日分。  **/
    property    cli::array<int, 1>^     nDayTotal;

    /**   週毎の合計金額 : 54 週間分。  **/
    property    cli::array<int, 1>^     nWeekTotal;

    /**   月毎の合計金額 : 12 ヶ月分。  **/
    property    cli::array<int, 1>^     nMonthTotal;

};

}   //  End of namespace  Wrapper

#endif
