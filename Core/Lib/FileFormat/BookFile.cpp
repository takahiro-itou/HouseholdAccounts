﻿//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
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
**      An Implementation of BookFile class.
**
**      @file       FileFormat/BookFile.cpp
**/

#include    "HouseholdAccounts/FileFormat/BookFile.h"

HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  FileFormat  {

namespace  {
}   //  End of (Unnamed) namespace.

//========================================================================
//
//    BookFile  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

BookFile::BookFile()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

BookFile::~BookFile()
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
//    データをテキストストリームから読み込む。
//

ErrCode
BookFile::readFromTextStream(
        std::istream            &inStr,
        Documents::BookDocument *ptrDoc)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    データをテキストストリームに書き込む。
//

ErrCode
BookFile::saveToTextStream(
        const   Documents::BookDocument &objDoc,
        std::ostream                    &outStr)
{
    return ( ERR_FAILURE );
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  FileFormat
HOUSEHOLD_ACCOUNTS_NAMESPACE_END