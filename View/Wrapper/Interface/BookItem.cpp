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
**      An Implementation of BookItem class(es).
**
**      @file       Interface/BookItem.cpp
**/

#include    "PreCompile.h"

#include    "BookItem.h"

namespace  Wrapper  {

namespace  {

}   //  End of (Unnamed) namespace

//========================================================================
//
//    BookItems  class.
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
//    指定した項目を展開したり閉じたりする。
//

void
BookItems::expandItem(
        const  int              lngItemIndex,
        const  System::Boolean  blnExpanded)
{
    int iFlags  = this->nFlags[lngItemIndex];

    if ( blnExpanded ) {
        iFlags  |=   static_cast<int>(ItemFlag::ITEM_FLAG_EXPANDED) ;
    } else {
        iFlags  &= ~(static_cast<int>(ItemFlag::ITEM_FLAG_EXPANDED));
    }

    this->nFlags[lngItemIndex]  = iFlags;
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
//    項目用のバッファのサイズを得る。
//

int
BookItems::getItemBufferSize()
{
    return ( this->nItemBufferSize );
}

//----------------------------------------------------------------
//    項目の名前を取得する。
//

System::String^
BookItems::getItemName(
        const  int  lngItemIndex)
{
    return ( this->utItemEntries[lngItemIndex].sItemName );
}

//----------------------------------------------------------------
//    指定した項目が展開されているか調べる。
//

System::Boolean
BookItems::isItemExpanded(
        const  int  lngItemIndex)
{
    const  int  iFlags  = this->nFlags[lngItemIndex];
    return ( iFlags & static_cast<int>(ItemFlag::ITEM_FLAG_EXPANDED) );
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
