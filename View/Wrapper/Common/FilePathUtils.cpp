﻿//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
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
//    フルパスからディレクトリ名を取得する。
//

System::String^
FilePathUtils::getDirFromPath(
        System::String^     pathName)
{
    return ( System::IO::Path::GetDirectoryName(pathName) );
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
//    相対パスからフルパスを取得する。
//

System::String^
FilePathUtils::getFullPathName(
        System::String^     baseDir,
        System::String^     relPath)
{
    int posFind;
    System::String^ strLeft;

    System::String^ strTemp = gcnew System::String(relPath);
    System::String^ relTemp = gcnew System::String(relPath);

    while ( (relTemp != nullptr) && (relTemp->Length > 0) ) {
        posFind = relTemp->IndexOf('\\');
        if ( posFind == 0 ) {
            //  ディレクトリ指定がもうないので  //
            //  ファイル名を最後にくっつける。  //
            strTemp = System::String::Concat(strTemp, "\\", relTemp);
            relTemp = System::String::Empty;
            break;
        }
        strLeft = relTemp->Substring(0, posFind);
        relTemp = relTemp->Substring(posFind + 1);
        if ( strLeft == ".\\" ) {
            //  現在のディレクトリ。    //
        } else if ( strLeft = "..\\" ) {
            //  親ディレクトリに移動。  //
            strTemp = removeDirFromPath(strTemp);
        } else {
            //  指定されたディレクトリに移動。  //
            strTemp = System::String::Concat(strTemp, "\\", strLeft);
        }
    }

    return ( strTemp );
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
//    フルパスから相対パスを取得する。
//

System::String^
FilePathUtils::getRelativePath(
        System::String^     pathName,
        System::String^     baseDir)
{
    if ( (baseDir == nullptr) || (baseDir->Length == 0) ) {
        return ( pathName );
    }

    System::String^ strBaseDir  = gcnew System::String(baseDir);
    System::String^ strPath     = gcnew System::String(pathName);
    System::String^ strTemp     = System::String::Empty;

    int posFind;
    System::String^ strBaseTemp;
    System::String^ strNameTemp;

    posFind = -1;
    while ( posFind == -1 ) {
        strBaseTemp = strBaseDir->ToLower();
        strNameTemp = strPath->ToLower();
        posFind = strNameTemp->IndexOf(strBaseTemp);
        if ( posFind >= 0 ) {
            strTemp = System::String::Concat(
                            strTemp, strPath->Substring(strBaseDir->Length + 2)
            );
            break;
        }
        strBaseDir = removeDirFromPath(strBaseDir);
        strTemp = System::String::Concat(strTemp, "..\\");
    }

    return ( strTemp) ;
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
