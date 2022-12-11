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
**      An Implementation of FilePathUtils class.
**
**      @file       Common/FilePathUtils.cpp
**/

#include    "PreCompile.h"

#include    "FilePathUtils.h"

namespace  Wrapper  {
namespace  Common  {

namespace  {

}   //  End of (Unnamed) namespace

//========================================================================
//
//    FilePathUtils  class.
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
//    指定したパスから特定のディレクトリまでを除外する。
//

System::String^
FilePathUtils::getAncestorDir(
        System::String^     pathName,
        System::String^     stripDir)
{
    System::String^  tmpPath = gcnew System::String(pathName);
    System::String^  strDir;

    while ( (tmpPath != nullptr) && (tmpPath->Length != 0) ) {
        strDir  = System::IO::Path::GetDirectoryName(tmpPath);
        System::String^
                strFile = System::IO::Path::GetFileName(tmpPath);

        if ( strFile == stripDir ) {
            return ( strDir );
        }
        tmpPath = strDir;
    }

    return ( pathName );
}

//----------------------------------------------------------------
//    ファイルの拡張子を取得する。
//

System::String^
FilePathUtils::getFileExt(
        System::String^     pathName)
{
    if ( (pathName == nullptr) || (pathName->Length == 0) ) {
        return ( System::String::Empty );
    }

    //  一番最後のピリオドの後を取り出す。  //
    const  int  posFind = pathName->LastIndexOf('.');
    if ( posFind >= 0 ) {
        return pathName->Substring(posFind + 1);
    }

    //  ピリオドが見つからないので、このパスには拡張子が無い。  //
    return ( pathName );
}

//----------------------------------------------------------------
//    ディレクトリ名と拡張子を除いた部分を取得する。
//

System::String^
FilePathUtils::getFileTitleFromPath(
        System::String^     pathName)
{
    System::String^ strTemp;

    //  フルパスからディレクトリ名を除く。  //
    strTemp = removeDirFromPath(pathName);

    //  さらに拡張子も除く。    //
    return ( removeExtFromPath(strTemp) );
}

//----------------------------------------------------------------
//    プロジェクトのディレクトリを取得する。
//

System::String^
FilePathUtils::getProjectRootDir(
        System::String^     pathName,
        System::String^     stripDir)
{
    return ( getAncestorDir(pathName, stripDir) );
}

//----------------------------------------------------------------
//    フルパスからディレクトリ名を除いた部分を取得する。
//

System::String^
FilePathUtils::removeDirFromPath(
        System::String^     pathName)
{
    return ( System::IO::Path::GetFileName(pathName) );
}

//----------------------------------------------------------------
//    フルパスから拡張子のみを除いた部分を取得する。
//

System::String^
FilePathUtils::removeExtFromPath(
        System::String^     pathName)
{
    if ( (pathName == nullptr) || (pathName->Length == 0) ) {
        return ( System::String::Empty );
    }

    //  一番最後のピリオドの前までを取り出す。  //
    const  int  posFind = pathName->LastIndexOf('.');
    if ( posFind >= 0 ){
        return pathName->Substring(0, posFind);
    }

    //  ピリオドが見つからないので、このパスには拡張子が無い。  //
    return ( pathName );
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

}   //  End of namespace  Common
}   //  End of namespace  Wrapper
