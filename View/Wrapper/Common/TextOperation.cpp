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
**      An Implementation of TextOperation class.
**
**      @file       Common/TextOperation.cpp
**/

#include    "PreCompile.h"

#include    "TextOperation.h"

namespace  Wrapper  {

namespace  {

}   //  End of (Unnamed) namespace

//========================================================================
//
//    TextOperation  class.
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
//    文字列をバイト列に変換する。
//

IOffsetType
TextOperation::toBytesFromString(
        System::String^         srcText,
        ByteArray^%             bufBytes,
        const  IOffsetType      posStart,
        const  IOffsetType      posEnd,
        const  System::Boolean  allocBuf)
{
    System::Text::Encoding^
            enc = System::Text::Encoding::GetEncoding("shift_jis");
    ByteArray^  bufTemp = enc->GetBytes(srcText);

    if ( allocBuf ) {
        bufBytes = gcnew ByteArray(posEnd + 1);
    }

    IOffsetType szCopy  = bufTemp->Length;
    if ( (posEnd - posStart + 1) < szCopy ) {
        //  コピー先バッファのサイズが足りない時は切り捨てる。  //
        szCopy  = posEnd - posStart + 1;
    }
    for ( IOffsetType i = posStart; i <= posEnd; ++ i ) {
        bufBytes[i] = 0;
    }
    for ( IOffsetType i = 0; i < szCopy; ++ i ) {
        bufBytes[posStart + i]  = bufTemp[i];
    }

    return ( szCopy );
}

IOffsetType
TextOperation::toBytesFromString(
        System::String^     srcText,
        ByteArray^          bufBytes,
        const  IOffsetType  posStart,
        const  IOffsetType  posEnd)
{
    return ( toBytesFromString(srcText, bufBytes, posStart, posEnd, false) );
}

//----------------------------------------------------------------
//    バイト列を文字列に変換する。
//

System::String^
TextOperation::toStringFromBytes(
        ByteArray^              bufBytes,
        const  IOffsetType      posStart,
        const  IOffsetType      posEnd,
        const  System::Boolean  termNull)
{
    //  指定された範囲を文字列に変換する。  //
    const  IOffsetType  idxLastConv = (posEnd - posStart);
    ByteArray^  bufTemp = gcnew ByteArray (idxLastConv + 1);
    for ( IOffsetType i = 0; i <= idxLastConv; ++  i ) {
        System::Byte  c = bufBytes[posStart + i];
        if ( (termNull) && (c == 0) && (i > 0) ) {
            System::Array::Resize(bufTemp, i);
            break;
        }
        bufTemp[i]  = c;
    }

    System::Text::Encoding^
            enc = System::Text::Encoding::GetEncoding("shift_jis");
    System::String^     trgText = enc->GetString(bufTemp);

    return ( trgText );
}

System::String^
TextOperation::toStringFromBytes(
        ByteArray^          bufBytes,
        const  IOffsetType  posStart,
        const  IOffsetType  posEnd)
{
    return ( toStringFromBytes(bufBytes, posStart, posEnd, true) );
}

//========================================================================
//
//    Accessors.
//

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
