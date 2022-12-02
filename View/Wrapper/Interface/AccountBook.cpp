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
//    指定した日付が、家計簿の開始日より前か調べる。
//

System::Boolean
AccountBook::isDayBeforeStart(
        const  int  lngYear,
        const  int  lngDayIndex)
{
    return ( false );
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
