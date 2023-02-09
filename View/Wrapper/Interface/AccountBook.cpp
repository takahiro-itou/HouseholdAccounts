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
#if 0
        parentItem  = bi.utItemEntries[itemHandle].nParentHandle;
        const int flag = (bi.nFlags[itemHandle]);
#endif

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
    const  int  sizeCur = this->utBookItems.nItemBufferSize;
    const  int  sizeNew = (bufSize + 15) & ~15;

    this->utBookItems.nItemBufferSize = sizeNew;
    System::Array::Resize(this->utBookItems.nFlags, sizeNew);
    System::Array::Resize(this->utBookItems.utItemEntries, sizeNew);

    this->utAnnualRecords.reallocBuffers(sizeNew, startYear, numYear);

    return ( sizeCur );
}

//----------------------------------------------------------------
//    新しい項目用の領域を確保する。
//

int
AccountBook::allocNewItem()
{
    int iResult = -1;

    //  バッファサイズと登録済み項目数を比較し、    //
    //  バッファに空きがある場合は、空きを探して    //
    //  そのハンドル（インデックス）を返す。        //
    const   BookItems  % bi = this->utBookItems;
    if ( bi.nRegisteredItemCount < bi.nItemBufferSize ) {
        for ( int i = bi.nRootItemCount; i < bi.nItemBufferSize; ++ i ) {
            if ( bi.nFlags[i] == static_cast<int>(ItemFlag::ITEM_FLAG_NOTUSED) )
            {
                iResult = i;
                break;
            }
        }
    }

    if ( iResult >= 0 ){
        return ( iResult );
    }

    //  バッファをリサイズし、増えた部分の先頭を確保する。  //
    return ( allocItemBuffers(bi.nItemBufferSize + 1) );
}

//----------------------------------------------------------------
//    指定した項目に新しいサブ項目を追加する。
//

int
AccountBook::insertNewItem(
        const   int         parentItemHandle,
        System::String^     strName,
        const   ItemFlag    lngFlags,
        const   int         startDate,
        const   int         startBalance)
{
    //  新しい項目用のインデックスを取得する。  //
    const  int  iNewHandle  = allocNewItem();

    //  この項目に初期値を書き込む。
    BookItems  % bi = this->utBookItems;
    bi.nFlags[iNewHandle]   = static_cast<int>(lngFlags);

    BookItemEntry  % entry  = bi.utItemEntries[iNewHandle];
    entry.nParentHandle = parentItemHandle;
    entry.sItemName     = strName;
    entry.nSubItemCount = 0;
    entry.nStartDate    = startDate;
    entry.nStartBalance = startBalance;

    ++ bi.nRegisteredItemCount;

    //  親項目の内容を更新する。    //
    BookItemEntry  % parent = bi.utItemEntries[parentItemHandle];
    System::Array::Resize(parent.nSubItems, parent.nSubItemCount + 1);
    parent.nSubItems[parent.nSubItemCount] = iNewHandle;
    ++ parent.nSubItemCount;

    this->BookCategories->insertNewCategory(
            parentItemHandle, strName,
            static_cast<Documents::CategoryFlags>(lngFlags),
            startDate,
            Common::DecimalCurrency(startBalance) );

    //  追加した新しい項目のハンドルを返す。    //
    return ( iNewHandle );
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
