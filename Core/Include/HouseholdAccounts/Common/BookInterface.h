//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Household Accounts Core.  ---                  **
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
**      Type Definitions.
**
**      @file       Common/BookInterface.h
**/

#if !defined( HACCOUNTS_COMMON_INCLUDED_BOOK_INTERFACE_H )
#    define   HACCOUNTS_COMMON_INCLUDED_BOOK_INTERFACE_H

#include    "HouseholdAccounts/Common/AccountsTypes.h"


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//========================================================================
//
//    Type Definitions.
//


//----------------------------------------------------------------
/**
**    レシートの商品項目情報。
**/

struct  ReceiptItem
{
    std::string     accountHeadings;    /**<  勘定科目。    **/
    std::string     accountCategory;    /**<  分類（内訳）  **/
    std::string     productName;        /**<  商品名。      **/
    int             itemUnitPrice;      /**<  単価。        **/
    int             itemQuantity;       /**<  数量。        **/
    int             itemDiscount;       /**<  値引額。      **/
    int             inclusiveTax;       /**<  内税額。      **/
    int             exclusiveTax;       /**<  外税額。      **/
};

/**   商品項目情報の配列型。    **/
typedef     std::vector<ReceiptItem>        ReceiptItemList;

//----------------------------------------------------------------
/**
**    集計単位。
**/

struct  CountingRecord
{
    std::string     flagInOut;          /**<  収支フラグ。  **/
    std::string     account1;           /**<  借方口座名。  **/
    std::string     account2;           /**<  貸方口座名。  **/
    ReceiptItemList receiptItems;       /**<  商品リスト。  **/
};

/**   集計単位の配列。  **/
typedef     std::vectror<CountingRecord>    CountingRecordList;

//----------------------------------------------------------------
/**
**    レシートの壱枚分の情報。
**/

struct  ReceiptInfo
{
    std::string         receiptDate;        /**<  日付。    **/
    std::string         receiptTime;        /**<  時刻。    **/
    std:string          storeName;          /**<  店名等。  **/
    CountingRecordList  countingRecords;    /**<  データ。  **/
};

/**   レシートの配列。  **/
typedef     std::vector<ReceiptInfo>        ReceiptList;

}   //  End of namespace  Common
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
