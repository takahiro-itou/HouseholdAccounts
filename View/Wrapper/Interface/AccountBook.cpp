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
**      An Implementation of AccountBook class.
**
**      @file       Interface/AccountBook.cpp
**/

#include    "PreCompile.h"

#include    "AccountBook.h"

namespace  Wrapper  {

namespace  {

}   //  End of (Unnamed) namespace

//========================================================================
//
//    AccountBook  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

AccountBook::AccountBook()
    : bEnabled(false),
      sTempFileDir(nullptr),
      utSettingsStringTable(),
      utRecordsStringTable(),
      nStartYear(0),
      nStartDayIndex(0),
      nNumYears(0),
      utStartDate(),
      nCurrentYear(0),
      nNumWeeks(0),
      utAnnualRecords(),
      nStartWeekday(0),
      nPreviousDays(0),
      m_cateBufferSize(0)
{
    this->BookCategories    = gcnew Documents::CategoryManager ();
}

//----------------------------------------------------------------
//    インスタンスを破棄する。
//  （デストラクタ）。
//

AccountBook::~AccountBook()
{
    //  マネージドリソースを破棄する。              //

    //  続いて、アンマネージドリソースも破棄する。  //
    this->!AccountBook();
}

//----------------------------------------------------------------
//    アンマネージドリソースを破棄する。
//  （ファイナライザ）。
//

AccountBook::!AccountBook()
{
}

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
//    項目の合計金額に指定したデータを加算する。
//

System::Boolean
AccountBook::addDataToItemTotal(
        const  int  lngYearIndex,
        const  int  lngDayIndex,
        const  int  lngItemIndex,
        const  int  lngValue)
{
    int     parentItem;
    bool    blnAddToParent, blnAddToRoot;

    blnAddToParent  = true;
    blnAddToRoot    = true;

    int lngYear = this->nStartYear + lngYearIndex;

    //  日付から週と月を計算しておく。  //
    const  ParsedDate
        utDate  = ManagedDate::getDayFromIndex(lngYear, lngDayIndex, -1);
    const  int lngWeek  = utDate.nWeek;
    const  int lngMonth = utDate.nMonth;
    lngYear = utDate.nYear;

    BookItems      % bi = this->utBookItems;
    AnnualRecords  % ar = this->utAnnualRecords;

    Documents::CategoryManager ^ cm = this->BookCategories;

    int itemHandle  = lngItemIndex;
    while ( itemHandle >= 0 ) {
        const   HouseholdAccounts::Documents::BookCategory  &
            cbc = cm->getRawBookCategory(itemHandle);
        parentItem  = cbc.getParentHandle();
        const int  flag = static_cast<int>(cbc.getFlags());

        if ( flag & static_cast<int>(ItemFlag::ITEM_FLAG_NOCOUNT_PARENT) ) {
            blnAddToParent  = false;
            blnAddToRoot    = false;
        }
        if ( flag & static_cast<int>(ItemFlag::ITEM_FLAG_NOCOUNT_ROOT) ) {
            blnAddToRoot    = false;
        }
        if ( (parentItem == -1) && (blnAddToRoot == false) ) {
            break;
        }

        BookItemDetailCounts   % dc = ar.m_itemDetailCount[itemHandle];
        dc.nDayTotal[lngDayIndex]   += lngValue;
        dc.nWeekTotal[lngWeek]      += lngValue;
        dc.nMonthTotal[lngMonth]    += lngValue;

        BookItemAnnualCounts   % ac = ar.m_itemAnnualCount[itemHandle];
        ac.nYearTotal[lngYearIndex] += lngValue;

        if ( (blnAddToParent == false) || (parentItem == -1) ) {
            break;
        }
        itemHandle  = parentItem;
    }

    return ( blnAddToRoot );
}

//----------------------------------------------------------------
//    項目データ用バッファを確保する。
//

int
AccountBook::allocItemBuffers(
        const  int  bufSize)
{
    const  int  startYear = this->nStartYear;
    const  int  numYear = this->nNumYears;

    //  バッファをリサイズし、増えた部分の先頭を記録しておく。  //
    const  int  sizeCur = this->m_cateBufferSize;
    const  int  sizeNew = (bufSize + 15) & ~15;

    this->m_cateBufferSize = sizeNew;
    this->utAnnualRecords.reallocBuffers(sizeNew, startYear, numYear);

    return ( sizeCur );
}

//----------------------------------------------------------------
//    指定した項目に新しいサブ項目を追加する。
//

CategoryHandle
AccountBook::insertNewCategory(
        const  CategoryHandle   cateParent,
        System::String ^        cateName,
        const  CategoryFlags    cateFlags,
        const  DateSerial       startDate,
        const  int              startBalance)
{
    const   CategoryHandle
        cateNew = this->BookCategories->insertNewCategory(
                        cateParent, cateName,
                        static_cast<Documents::CategoryFlags>(cateFlags),
                        startDate,
                        Common::DecimalCurrency(startBalance) );

    const   CategoryHandle  bufSize = (this->BookCategories->BufferCapacity);
    if ( this->m_cateBufferSize < bufSize ) {
        allocItemBuffers(bufSize);
    }

    return ( cateNew );
}

//----------------------------------------------------------------
//    指定した日付が、家計簿の開始日より前か調べる。
//

System::Boolean
AccountBook::isDayBeforeStart(
        const  int  lngYear,
        const  int  lngDayIndex)
{
    if ( ManagedDate::compareDates(
                    lngYear, lngDayIndex, this->nStartYear,
                    this->nStartDayIndex) < 0 )
    {
        return ( true );
    }
    return ( false );
}

//----------------------------------------------------------------
//    データを再集計する。
//

void
AccountBook::recountData(
        const  int  lngYear)
{
}

//----------------------------------------------------------------
//    開始日を設定する。
//

void
AccountBook::setStartDate(
        const  int  startYear,
        const  int  startMonth,
        const  int  startDay)
{
    int dayIndex, dayOffset;

    dayOffset = static_cast<int>( ManagedDate::getWeekday(startYear, 1, 1) );
    dayIndex  = ManagedDate::getDayInYear(startYear, startMonth, startDay);
    dayIndex  += dayOffset;

    this->utStartDate = ManagedDate::getDayFromIndex(
                                startYear, dayIndex, dayOffset);
    this->nStartYear  = this->utStartDate.nYear;
    this->nStartDayIndex  = dayIndex;
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    家計簿を有効／無効にする。
//

System::Boolean
AccountBook::enableAccountBook(
        const  System::Boolean  blnEnabled)
{
    return ( this->bEnabled  = blnEnabled );
}

//----------------------------------------------------------------
//    家計簿データが有効なデータかどうか判断する。
//

System::Boolean
AccountBook::isEnabled()
{
    return ( this->bEnabled );
}

//----------------------------------------------------------------
//    家計簿のデータが何年分あるかを取得する。
//

int
AccountBook::getNumYears()
{
    return ( this->nNumYears );
}

//----------------------------------------------------------------
//    データの年数を設定する。
//

void
AccountBook::setNumYears(
        const  int  numYears)
{
    this->utAnnualRecords.reallocBuffers(-1, this->nStartYear, numYears);
    this->nNumYears = numYears;
}

//----------------------------------------------------------------
//    家計簿の開始年を取得する。
//

int
AccountBook::getStartYear()
{
    return ( this->nStartYear );
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

}   //  End of namespace  Wrappe
