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
**      An Interface of TextOperation class.
**
**      @file       Common/FilePathUtils.h
**/

#if !defined( HAWRAPPER_COMMON_INCLUDED_FILE_PATH_UTILS_H )
#    define   HAWRAPPER_COMMON_INCLUDED_FILE_PATH_UTILS_H


#pragma     once

#include    "AccountsTypes.h"

namespace  Wrapper  {
namespace  Common  {

//========================================================================
//
//    FilePathUtils  class.
//

public ref  class  FilePathUtils
{
//========================================================================
//
//    Internal Type Definitions.
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
public:

    //----------------------------------------------------------------
    /**   指定したパスから特定のディレクトリまでを除外する。
    **
    **  @param [in] pathName
    **  @param [in] stripDir
    **/
    static  System::String^
    getAncestorDir(
            System::String^     pathName,
            System::String^     stripDir);

    //----------------------------------------------------------------
    /**   ディレクトリ名と拡張子を除いた部分を取得する。
    **
    **  @param [in] pathName
    **/
    static  System::String^
    getFileTitleFromPath(
            System::String^     pathName);

    //----------------------------------------------------------------
    /**   プロジェクトのディレクトリを取得する。
    **
    **  @param [in] pathName
    **  @param [in] stripDir
    **/
    static  System::String^
    getProjectRootDir(
            System::String^     pathName,
            System::String^     stripDir);

    //----------------------------------------------------------------
    /**   フルパスからディレクトリ名を除いた部分を取得する。
    **
    **  @param [in] pathName
    **/
    static  System::String^
    removeDirFromPath(
            System::String^     pathName);

    //----------------------------------------------------------------
    /**   フルパスから拡張子のみを除いた部分を取得する。
    **
    **  @param [in] pathName
    **/
    static  System::String^
    removeExtFromPath(
            System::String^     pathName);

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

//========================================================================
//
//    Member Variables.
//

};

}   //  End of namespace  Common
}   //  End of namespace  Wrapper

#endif
