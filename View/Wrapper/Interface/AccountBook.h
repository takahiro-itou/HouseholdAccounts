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
**      An Interface of AccountBook class.
**
**      @file       Interface/AccountBook.h
**/

#if !defined( HAWRAPPER_INTERFACE_INCLUDED_ACCOUNT_BOOK_H )
#    define   HAWRAPPER_INTERFACE_INCLUDED_ACCOUNT_BOOK_H

#pragma     once

#include    "HouseholdAccounts/Common/AccountsTypes.h"

#include    "AnnualRecords.h"
#include    "BookItem.h"
#include    "Common/ManagedDate.h"
#include    "Common/StringTable.h"

namespace  Wrapper  {

//========================================================================
//
//    家計簿一冊。
//

//========================================================================
/**
**    AccountBook  class.
**/

public value struct AccountBook
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
public:

    //----------------------------------------------------------------
    /**   項目データ用バッファを確保する。
    **
    **  @param [in] bufSize   確保する項目数。
    **  @return     増えた部分の先頭のインデックス。
    **/
    int
    allocItemBuffers(
            const  int  bufSize);

    //----------------------------------------------------------------
    /**   新しい項目用の領域を確保する。
    **
    **  @return     新しい項目用のハンドル。
    **/
    int
    allocNewItem();

    //----------------------------------------------------------------
    /**   指定した日付が、家計簿の開始日より前か調べる。
    **
    **  @param [in] lngYear       西暦年。
    **  @param [in] lngDayIndex   元日からの日数（オフセット付）。
    **/
    System::Boolean
    isDayBeforeStart(
            const  int  lngYear,
            const  int  lngDayIndex);

    //----------------------------------------------------------------
    /**   開始日を設定する。
    **
    **  @param [in] startYear     開始年。
    **  @param [in] startMonth    開始月。
    **  @param [in] startDay      開始日。
    **/
    void
    setStartDate(
            const  int  startYear,
            const  int  startMonth,
            const  int  startDay);

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   家計簿を有効／無効にする。
    **
    **/
    System::Boolean
    enableAccountBook(
            const  System::Boolean  blnEnabled);

    //----------------------------------------------------------------
    /**   家計簿データが有効なデータかどうか判断する。
    **
    **/
    System::Boolean
    isEnabled();

    //----------------------------------------------------------------
    /**   家計簿のデータが何年分あるかを取得する。
    **
    **/
    int
    getNumYears();

    //----------------------------------------------------------------
    /**   家計簿の開始年を取得する。
    **
    **  @return     開始西暦年。
    **/
    int
    getStartYear();

//========================================================================
//
//    Properties.
//
public:

    /**   家計簿データが有効か。    **/
    System::Boolean     bEnabled;

    /**   テンポラリファイルのディレクトリ。    **/
    System::String^     sTempFileDir;

    /**   設定データ用文字列テーブル。  **/
    StringTable         utSettingsStringTable;

    /**   レコード用文字列テーブル。    **/
    StringTable         utRecordsStringTable;

    /**   開始西暦年。  **/
    int     nStartYear;

    /**   開始日。      **/
    int     nStartDayIndex;

    /**   データの存在する年数。    **/
    int     nNumYears;

    ParsedDate  utStartDate;

    BookItems   utBookItems;

    /**   一年分ずつバッファに記憶する。    **/
    int         nCurrentYear;

    /**   この年の週数。    **/
    int         nNumWeeks;

    /**   この年のレコード。    **/
    AnnualRecords   utAnnualRecords;

    /**   本年の元日の曜日。    **/
    int     nStartWeekday;

    /**   レコード内に本年分の前に去年分が何日分入っているか。  **/
    int     nPreviousDays;

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
