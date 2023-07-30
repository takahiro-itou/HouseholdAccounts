//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Household Accounts Core.  ---                  **
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
**      An Interface of AccountAmountChange struct.
**
**      @file       DocCls/AccountAmountChange.h
**/

#if !defined( HACORE_DOCCLS_INCLUDED_ACCOUNT_AMOUNT_CHANGE_H )
#    define   HACORE_DOCCLS_INCLUDED_ACCOUNT_AMOUNT_CHANGE_H


#if !defined( HACORE_COMMON_INCLUDED_ACCOUTNS_TYPES_H )
#    include    "Account/Common/AccountsTypes.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    AccountAmountChange  struct.
//
/**
**    残高の差分情報を格納する構造体。
**/

struct  AccountAmountChange
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

//========================================================================
//
//    Public Member Functions (Operators).
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
public:

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   AccountAmountChangeTest;
};

}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
