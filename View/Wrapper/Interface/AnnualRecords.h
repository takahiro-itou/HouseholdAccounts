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
**      @file       Interface/AnnualRecords.h
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
public:

    typedef     cli::array<BookItemAnnualCounts, 1>     AnnualCountsArray;

    typedef     cli::array<BookItemDetailCounts, 1>     DetailCountsArray;

    typedef     cli::array<OneDayReceipts, 1>           OneDayReceiptArray;

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
    /**   年間レコード用のバッファを確保しなおす。
    **
    **  @param [in] itemBufferSize    項目バッファのサイズ。
    **  @param [in] startYear         開始西暦年。
    **  @param [in] numYears          年数。
    **/
    System::Boolean
    reallocBuffers(
            const  int  itemBufferSize,
            const  int  startYear,
            const  int  numYears);

    //----------------------------------------------------------------
    /**   年間レコードを再集計する。
    **
    **  @param [in] lngItemFlags        各項目のフラグ。
    **  @param [in] lngItemBufferSize   項目バッファのサイズ。
    **/
    System::Boolean
    recountAnnualRecords(
            cli::array<int, 1>^ lngItemFlags,
            const  int  lngItemBufferSize,
            const  int  lngYear,
            const  int  lngNumDays);

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

    property    AnnualCountsArray^  utItemAnnualCounts
    {
        AnnualCountsArray^  get()  {
            return ( this->m_itemAnnualCount );
        }
        void  set(AnnualCountsArray^  annualCounts)  {
            this->m_itemAnnualCount = annualCounts;
        }
    }

    property    DetailCountsArray^  utItemDetailCounts
    {
        DetailCountsArray^  get()  {
            return ( this->m_itemDetailCount );
        }
        void  set(DetailCountsArray^  detailCounts)  {
            this->m_itemDetailCount = detailCounts;
        }
    }

    /**   その年の各日のレコード。  **/
    property    OneDayReceiptArray^ utDayRecords
    {
        OneDayReceiptArray^ get()  {
            return ( this->m_dayRecords );
        }
        void  set(OneDayReceiptArray^  dayRecords) {
            this->m_dayRecords  = dayRecords;
        }
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

    AnnualCountsArray^      m_itemAnnualCount;
    DetailCountsArray^      m_itemDetailCount;
    OneDayReceiptArray^     m_dayRecords;
};

}   //  End of namespace  Wrapper

#endif
