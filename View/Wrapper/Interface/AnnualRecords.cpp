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
**      An Implementation of AnnualRecords class.
**
**      @file       Interface/AnnualRecords.cpp
**/

#include    "PreCompile.h"

#include    "AnnualRecords.h"

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
