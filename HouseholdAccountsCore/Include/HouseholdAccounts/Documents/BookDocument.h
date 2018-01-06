//  -*-  coding: utf-8; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                  ---  Household Accounts Core.  ---                  **
**                                                                      **
**          Copyright (C), 2017-2018, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      An Interface of BookDocument class.
**
**      @file       Documents/BookDocument.h
**/

#if !defined( HACCOUNTS_DOCUMENTS_INCLUDED_BOOK_DOCUMENT_H )
#    define   HACCOUNTS_DOCUMENTS_INCLUDED_BOOK_DOCUMENT_H

#include    "HouseholdAccounts/Common/HouseholdAccountsSettings.h"

HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Documents  {

//  クラスの前方宣言。  //

//========================================================================
//
//    BookDocument  class.
//
/**
**
**/

class  BookDocument
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    BookDocument();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~BookDocument();

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
    friend  class   BookDocumentTest;
};

}   //  End of namespace  Documents
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
