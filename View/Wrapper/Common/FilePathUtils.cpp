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
//    プロジェクトのディレクトリを取得する。
//

System::String^
FilePathUtils::getProjectRootDir(
        System::String^     pathName,
        System::String^     stripDir)
{
    return ( getAncestorDir(pathName, stripDir) );
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
