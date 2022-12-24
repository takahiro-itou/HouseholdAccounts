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
**      An Interface of BookCategory class.
**
**      @file       Documents/BookCategory.h
**/

#if !defined( HACORE_DOCUMENTS_INCLUDED_BOOK_CATEGORY_H )
#    define   HACORE_DOCUMENTS_INCLUDED_BOOK_CATEGORY_H

#include    "HouseholdAccounts/Common/AccountsTypes.h"

HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Documents  {

//  クラスの前方宣言。  //

//========================================================================
//
//    Type Definitions.
//

/**
**    項目用フラグ。
**/

enum class  CategoryFlags
{
    CTYPE_MASK              = 0x000000ff,
    CTYPE_NOTUSED           = 0,    /**<  未使用。          **/
    CTYE_INHERIT            = 1,    /**<  親の設定を継承。  **/
    CTYPE_BALANCE           = 9,    /**<  残高表示。        **/
    CTYPE_INCOME            = 17,   /**<  収入。            **/
    CTYPE_OUTLAY            = 18,   /**<  支出。            **/
    CTYPE_BANK              = 25,   /**<  銀行口座。        **/
    CTYPE_BANK_WITHDRAW     = 26,   /**<  口座引出。        **/
    CTYPE_BANK_DEPOSIT      = 27,   /**<  口座入金。        **/
    CTYPE_BANK_TRANSFER     = 28,   /**<  口座振替。        **/

    /**   サブ項目を展開表示する。          **/
    CFLAG_EXPANDED          = 0x00000100,

    /**   親の項目の合計に加算しない。      **/
    CFLAG_NOCOUNT_PARENT    = 0x00010000,

    /**   ルート項目の合計に加算しない。    **/
    CFLAG_NOCOUNT_ROOT      = 0x00020000,

    /**   表示しない隠し属性。  **/
    CFLAG_HIDDEN            = 0x10000000,

    /**   削除不能な予約項目。  **/
    CFLAG_UNERASABLE        = 0x20000000,

    /**   読み取り専用属性。    **/
    CFLAG_READ_ONLY         = 0x40000000,
};

//========================================================================
//
//    BookCategory  class.
//
/**
**    家計簿の勘定科目、内訳などの項目を管理するクラス。
**/

class  BookCategory
{

//========================================================================
//
//    Internal Type Definitions.
//

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
    BookCategory();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~BookCategory();

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
    friend  class   BookCategoryTest;
};

}   //  End of namespace  Documents
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
