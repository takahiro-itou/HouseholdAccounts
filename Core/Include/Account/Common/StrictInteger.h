//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
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
**      An Interface of StrictInteger template class.
**
**      @file       Common/StrictInteger.h
**/

#if !defined( HACORE_COMMON_INCLUDED_STRICT_INTEGER_H )
#    define   HACORE_COMMON_INCLUDED_STRICT_INTEGER_H


#if !defined( HACORE_COMMON_INCLUDED_ACCOUNTS_PROJECT_H )
#    include    "Account/Common/AccountsProject.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //

//========================================================================
//
//    StrictInteger  class.
//
/**
**    厳格な整数型クラス。
**
**    整数型同士でも異なる用途に使う場合に異なる型として扱われ、
**  原則として互いに代入・演算ができない。
**  必要ならば明示的に変換を行うことができる。
**/

template <typename T, typename Tag>
class  StrictInteger
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

//========================================================================
//
//    Accessors.
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

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   StrictIntegerTest;
};

}   //  End of namespace  Common
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

//  Implementation.
#include    "StrictInteger.inl"

#endif
