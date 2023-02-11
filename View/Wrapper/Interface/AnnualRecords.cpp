//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**              ---  Household Accounts  Wrapper Lib.  ---              **
**                                                                      **
**          Copyright (C), 2017-2023, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
**          License: (See COPYING and LICENSE files)                    **
**          GNU Affero General Public License (AGPL) version 3,         **
**          or (at your option) any later version.                      **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of AnnualRecords class.
**
**      @file       Interface/AnnualRecords.cpp
**/

#include    "PreCompile.h"

#include    "AnnualRecords.h"

#include    "BookItem.h"
#include    "Wrapper/Common/ManagedDate.h"

namespace  Wrapper  {

namespace  {

}   //  End of (Unnamed) namespace

//========================================================================
//
//    AnnualRecords  class.
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
//    年間レコード用のバッファを確保しなおす。
//

System::Boolean
AnnualRecords::reallocBuffers(
        const  int  itemBufferSize,
        const  int  startYear,
        const  int  numYears)
{
    int bufSize = itemBufferSize;
    if ( bufSize < 0 ) {
        bufSize = this->nItemBufferSize;
    }

    System::Array::Resize(this->m_itemAnnualCount, bufSize);
    System::Array::Resize(this->m_itemDetailCount, bufSize);
    this->nItemBufferSize   = bufSize;

    if ( numYears > 0 ) {
        for ( int i = 0; i < bufSize; ++  i ) {
            BookItemAnnualCounts  % ac  = this->m_itemAnnualCount[i];
            System::Array::Resize(ac.nStartValues, numYears);
            System::Array::Resize(ac.nEndValues,   numYears);
            System::Array::Resize(ac.nYearTotal,   numYears);
        }
    }

    for ( int i = 0; i < bufSize; ++ i ) {
        BookItemDetailCounts  % dc  = this->m_itemDetailCount[i];
        System::Array::Resize(dc.nDayTotal, MAX_DAYS);
        System::Array::Resize(dc.nWeekTotal, MAX_WEEKS);
        System::Array::Resize(dc.nMonthTotal, MAX_MONTH + 1);
    }

    return ( true );
}

//----------------------------------------------------------------
//    年間レコードを再集計する。
//

System::Boolean
AnnualRecords::recountAnnualRecords(
        cli::array<int, 1>^ lngItemFlags,
        const  int  itemBufferSize,
        const  int  lngYear,
        const  int  numDays)
{
    typedef     Documents::CategoryFlags    CategoryFlags;

    int dayIndexStart, dayIndexEnd;

    //  初期値を書き込む。  //
    for ( int i = 0; i < itemBufferSize; ++ i ) {
        CategoryFlags flag = static_cast<CategoryFlags>(lngItemFlags[i]);
        if ( (flag & CategoryFlags::CTYPE_MASK)
                == CategoryFlags::CTYPE_BALANCE )
        {
            this->m_itemDetailCount[i].nDayTotal[0]
                    = this->m_itemAnnualCount[i].nStartValues[lngYear];
        }
    }

    dayIndexStart = static_cast<int>(ManagedDate::getWeekday(lngYear, 1, 1));
    dayIndexEnd = ManagedDate::getDayInYear(lngYear, 12, 31) + dayIndexStart;

    //  全てのレシートを集計する。  //
    for ( int trgDate = 0; trgDate < numDays; ++ trgDate ) {
        for ( int i = 0; i < itemBufferSize; ++ i ) {
            CategoryFlags flag = static_cast<CategoryFlags>(lngItemFlags[i]);
            if ( (flag & CategoryFlags::CTYPE_MASK)
                    == CategoryFlags::CTYPE_BALANCE )
            {
            } else {
                this->m_itemDetailCount[i].nDayTotal[trgDate] = 0;
            }
        }
    }

    return ( true );
}

//========================================================================
//
//    Public Member Functions (Static).
//

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    項目の一日の合計金額を取得する。
//

int
AnnualRecords::getItemDayTotal(
        const  int  lngItemIndex,
        const  int  lngDate)
{
    return ( this->utItemDetailCounts[lngItemIndex].nDayTotal[lngDate] );
}

//----------------------------------------------------------------
//    項目の一ヶ月の合計金額を取得する。
//

int
AnnualRecords::getItemMonthTotal(
        const  int  lngItemIndex,
        const  int  lngMonth)
{
    if ( lngItemIndex >= MAXITEMS ) {
        return ( 0 );
    }
    return ( this->utItemDetailCounts[lngItemIndex].nMonthTotal[lngMonth] );
}

//----------------------------------------------------------------
//    項目の一週間の合計金額を取得する。
//

int
AnnualRecords::getItemWeekTotal(
        const  int  lngItemIndex,
        const  int  lngWeek)
{
    if ( lngItemIndex >= MAXITEMS ) {
        return ( 0 );
    }
    return ( this->utItemDetailCounts[lngItemIndex].nWeekTotal[lngWeek] );
}

//----------------------------------------------------------------
//    項目の一年間の合計金額を取得する。
//

int
AnnualRecords::getItemYearTotal(
        const  int  lngItemIndex,
        const  int  lngYear)
{
    return ( this->utItemAnnualCounts[lngItemIndex].nYearTotal[lngYear] );
}

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

}   //  End of namespace  Wrapper
