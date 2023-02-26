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

#include    "Wrapper/Common/ArrayUtils.h"

#include    <Account/DocCls/StringTable.h>

#include    <msclr/marshal_cppstd.h>
using       namespace   msclr::interop;


namespace  Wrapper  {
namespace  DocCls  {

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
//    テーブルの最後尾にデータを追加する。
//

StringIndex
StringTable::appendString(
        System::String^     steText)
{
    const  StringIndex  retVal  =
        this->m_ptrObj->appendString(marshal_as<std::string>(steText));
    return ( retVal );
}

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
        System::String^     steText)
{
    const  StringIndex  retVal  =
        this->m_ptrObj->findString(marshal_as<std::string>(steText));
    return ( retVal );
}

//----------------------------------------------------------------
//    新しいデータを挿入する。
//

StringIndex
StringTable::insertString(
        System::String^     steText)
{
    const  StringIndex  retVal  =
        this->m_ptrObj->insertString(marshal_as<std::string>(steText));
    return ( retVal );
}

//----------------------------------------------------------------
//    データ用のバッファを確保する。
//

StringIndex
StringTable::reserveBuffer(
        const  StringIndex  bufSize)
{
    const  StringIndex  retVal  = this->m_ptrObj->reserveBuffer(bufSize);
    return ( retVal );
}

//----------------------------------------------------------------
//    テーブルをソートしなおす。
//

System::Boolean
StringTable::sortTable()
{
    const  CoreErrCode  retCode = this->m_ptrObj->sortTable();
    return ( retCode == CoreErrCode::SUCCESS );
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
    const  int  bufLen  = this->m_ptrObj->getBufferCapacity();

    int num = siArray->Length;
    if ( bufLen < num ) {
        num = bufLen;
    }

    for ( int i = 0; i < num; ++ i ) {
        this->m_ptrObj->setSortIndex(i, siArray[i]);
    }

    return ( true );
}

//========================================================================
//
//    Properties.
//

//----------------------------------------------------------------
//    バッファのサイズ。
//

StringIndex
StringTable::BufferCapacity::get()
{
    return  this->m_ptrObj->getBufferCapacity();
}

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
//    ソート状態フラグ。
//

StringTable::StringTableSort
StringTable::SortFlag::get()
{
    return  static_cast<StringTableSort>(this->m_ptrObj->getSortFlag());
}

void
StringTable::SortFlag::set(StringTableSort flagNew)
{
    this->m_ptrObj->setSortFlag(static_cast<CoreStringTableSort>(flagNew));
}

//----------------------------------------------------------------
//    ソートインデックスの配列。
//

StringTable::IndexArray ^
StringTable::SortIndex::get()
{
    return  toManageFromVector(this->m_ptrObj->getSortIndexArray());
}

//----------------------------------------------------------------
//    テーブルのエントリ。
//

System::String ^
StringTable::TableEntry::get(StringIndex idx)
{
    return  marshal_as<System::String^>(this->m_ptrObj->getEntryText(idx));
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

}   //  End of namespace  DocCls
}   //  End of namespace  Wrapper
