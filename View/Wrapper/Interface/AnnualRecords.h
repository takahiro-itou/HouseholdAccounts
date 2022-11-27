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
**      An Interface of AnnualRecords class.
**
**      @file       Interface/AnnualRecordsh
**/

#if !defined( HAWRAPPER_INTERFACE_INCLUDED_ANNUAL_RECORDS_H )
#    define   HAWRAPPER_INTERFACE_INCLUDED_ANNUAL_RECORDS_H

#pragma     once

#include    "HouseholdAccounts/Common/AccountsTypes.h"

#include    "Common/AccountsConst.h"

#include    "AggregateData.h"
#include    "Receipt.h"

namespace  Wrapper  {

//========================================================================
//
//    集計されたデータの情報。
//

//========================================================================
/**
**    AnnualRecords  class.
**/

public value struct AnnualRecords
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
public:

    //----------------------------------------------------------------
    /**   項目の一日の合計金額を取得する。
    **
    **  @param [in] lngItemIndex    項目インデックス。
    **  @param [in] lngDate         日付。
    **/
    int
    getItemDayTotal(
            const  int  lngItemIndex,
            const  int  lngDate);

    //----------------------------------------------------------------
    /**   項目の一ヶ月の合計金額を取得する。
    **
    **  @param [in] lngItemIndex    項目インデックス。
    **  @param [in] lngMonth        月。
    **/
    int
    getItemMonthTotal(
            const  int  lngItemIndex,
            const  int  lngMonth);

    //----------------------------------------------------------------
    /**   項目の一週間の合計金額を取得する。
    **
    **  @param [in] lngItemIndex    項目インデックス。
    **  @param [in] lngWeek         週。
    **/
    int
    getItemWeekTotal(
            const  int  lngItemIndex,
            const  int  lngWeek);

    //----------------------------------------------------------------
    /**   項目の一年間の合計金額を取得する。
    **
    **  @param [in] lngItemIndex    項目インデックス。
    **  @param [in] lngYear         西暦年。
    **/
    int
    getItemYearTotal(
            const  int  lngItemIndex,
            const  int  lngYear);

//========================================================================
//
//    Properties.
//
public:

    property    int     nItemBufferSize;

    property    cli::array<BookItemAnnualCounts, 1>^    utItemAnnualCounts;

    property    cli::array<BookItemDetailCounts, 1>^    utItemDetailCounts;

    /**   その年の各日のレコード。  **/
    property    cli::array<OneDayReceipts, 1>^  utDayRecords;

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
