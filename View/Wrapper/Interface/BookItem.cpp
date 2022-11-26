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

//----------------------------------------------------------------
//    家計簿の項目を並べなおす。
//

int
BookItems::relocateItems(
        cli::array<int, 1>^ lpNewIndex)
{
    return ( -1 );
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
//    項目のフラグを得る。
//

ItemFlag
BookItems::getItemFlags(
        const  int  lngItemIndex)
{
    return ( static_cast<ItemFlag>(this->nFlags[lngItemIndex]) );
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
//    項目の種類を取得する。
//

int
BookItems::getItemType(
        const  int  lngItemIndex)
{
    int lngType, lngParentHandle;
    int curIdx  = lngItemIndex;

    while ( curIdx >= 0 ) {
        lngType = (this->nFlags[curIdx] &
                   static_cast<int>(ItemFlag::ITEM_FLAG_TYPEMASK));
        lngParentHandle = this->utItemEntries[curIdx].nParentHandle;

        if ( lngType == static_cast<int>(ItemFlag::ITEM_FLAG_INHERIT) ) {
            curIdx  = lngParentHandle;
        } else {
            break;
        }
    }

    return ( lngType );
}

//----------------------------------------------------------------
//    使用済みの項目数を取得する。
//

int
BookItems::getRegisteredItemCount()
{
    return ( this->nRegisteredItemCount );
}

//----------------------------------------------------------------
//    ルートにある項目数を取得する。
//

int
BookItems::getRootItemCount()
{
    return ( this->nRootItemCount );
}

//----------------------------------------------------------------
//    項目のルート項目のハンドルを取得する。
//

int
BookItems::getRootItemHandle(
        const  int  lngItemIndex)
{
    int lngParentHandle;
    int curIdx  = lngItemIndex;

    lngParentHandle = this->utItemEntries[curIdx].nParentHandle;
    while ( lngParentHandle >= 0 ) {
        curIdx  = lngParentHandle;
        lngParentHandle = this->utItemEntries[curIdx].nParentHandle;
    }
    return ( curIdx );
}

//----------------------------------------------------------------
//    項目が持つサブ項目の個数を取得する。
//

int
BookItems::getSubItemCount(
        const  int  lngItemIndex)
{
    return ( this->utItemEntries[lngItemIndex].nSubItemCount );
}

//----------------------------------------------------------------
//    項目が持つサブ項目のハンドルを取得する。
//

int
BookItems::getSubItemHandle(
        const  int  lngItemIndex,
        const  int  lngSubItemIndex)
{
    return ( this->utItemEntries[lngItemIndex].nSubItems[lngSubItemIndex] );
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
