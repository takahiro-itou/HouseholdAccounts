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
**      An Interface of BookItem class(es).
**
**      @file       Interface/BookItem.h
**/

#pragma     once

#include    "HouseholdAccounts/Common/AccountsTypes.h"

namespace  Wrapper  {

//========================================================================
//
//    Type Definitions.
//

//----------------------------------------------------------------
/**
**    データ項目。
**/

public value struct BookItemEntry
{
public:

    /**   親項目のハンドル。    **/
    property    int     nParentHandle;

    /**   項目名の ID  (文字列テーブル内のインデックス) 。  **/
    property    int     nItemNameID;

    /**   項目名。  **/
    property    System::String^     sItemName;

    /**   サブ項目数。  **/
    property    int     nSubItemCount;

    /**   サブ項目のハンドル (インデックス) 。  **/
    property    cli::array<int, 1>^     nSubItems;

    /**   開始年月日 (残高の項目のみ) 。    **/
    property    int     nStartDate;

    /**   開始時の残高 (残高の項目のみ) 。  **/
    property    int     nStartBalance;
};

}   //  End of namespace  Wrapper
