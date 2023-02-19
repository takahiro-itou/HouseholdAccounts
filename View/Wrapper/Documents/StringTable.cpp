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
**      An Implementation of StringTable class.
**
**      @file       Documents/StringTable.cpp
**/

#include    "PreCompile.h"

#include    "StringTable.h"

#include    "Account/Documents/StringTable.h"

#include    <msclr/marshal_cppstd.h>
using       namespace   msclr::interop;


namespace  Wrapper  {
namespace  Documents  {

namespace  {

}   //  End of (Unnamed) namespace

//========================================================================
//
//    StringTable  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

StringTable::StringTable()
    : m_ptrObj(new WrapTarget())
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する。
//  （デストラクタ）。
//

StringTable::~StringTable()
{
    //  マネージドリソースを破棄する。              //

    //  続いて、アンマネージドリソースも破棄する。  //
    this->!StringTable();
}

//----------------------------------------------------------------
//    アンマネージドリソースを破棄する。
//  （ファイナライザ）。
//

StringTable::!StringTable()
{
    delete  this->m_ptrObj;
    this->m_ptrObj  = nullptr;
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
//    テーブルの整合性を検査する。
//

System::Boolean
StringTable::checkIntegrity()
{
    return  fromNativeBoolean(this->m_ptrObj->checkIntegrity());
}

//----------------------------------------------------------------
//    指定された文字列を検索する。
//

StringIndex
StringTable::findString(
        System::String^     strText)
{
    const  StringIndex  retVal  =
        this->m_ptrObj->findString(marshal_as<std::string>(strText));
    return ( retVal );
}

//----------------------------------------------------------------
//    新しいデータを挿入する。
//

StringIndex
StringTable::insertString(
        System::String^     strText)
{
    const  StringIndex  retVal  =
        this->m_ptrObj->insertString(marshal_as<std::string>(strText));
    return ( retVal );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    ソートインデックスを直接設定する。
//

System::Boolean
StringTable::setSortIndexArray(
        IndexArray^     siArray)
{
    return ( false );
}

//========================================================================
//
//    Properties.
//

//----------------------------------------------------------------
//    エントリフラグ。
//

int
StringTable::EntryFlag::get(StringIndex idx)
{
    return  this->m_ptrObj->getEntryFlag(idx);
}

void
StringTable::EntryFlag::set(StringIndex idx, int val)
{
    this->m_ptrObj->setEntryFlag(idx, val);
}

//----------------------------------------------------------------
//    テーブルに格納されているデータ数。
//

StringIndex
StringTable::NumEntries::get()
{
    return  this->m_ptrObj->getNumEntries();
}

//----------------------------------------------------------------
//    ソートインデックスの配列。
//

StringTable::IndexArray ^
StringTable::SortIndex::get()
{
    IndexArray^ tmp = nullptr;
    return ( tmp );
}

//----------------------------------------------------------------
//    テーブルのエントリ。
//

System::String ^
StringTable::TableEntry::get(StringIndex idx)
{
    System::String^ tmp = nullptr;
    return ( tmp );
}

void
StringTable::TableEntry::set(StringIndex idx, System::String^ val)
{
    this->m_ptrObj->setEntryText(idx, marshal_as<std::string>(val));
}

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  Documents
}   //  End of namespace  Wrapper
