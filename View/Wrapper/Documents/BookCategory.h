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
**      An Interface of BookCategory class.
**
**      @file       Documents/BookCategory.h
**/

#if !defined( HAWRAPPER_DOCUMENTS_INCLUDED_BOOK_CATEGORY_H )
#    define   HAWRAPPER_DOCUMENTS_INCLUDED_BOOK_CATEGORY_H

#pragma     once

#include    "Common/AccountsTypes.h"
#include    "Common/DecimalCurrency.h"

namespace  Wrapper  {
namespace  Documents  {

//========================================================================
//
//    Type Definitions.
//

/**
**    項目用フラグ。
**/

public  enum class  CategoryFlags
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

public ref  class  BookCategory
{
//========================================================================
//
//    Internal Type Definitions.
//
private:

    typedef     cli::array<CategoryHandle, 1>
    CategoryHandleArray;

    typedef     Common::DecimalCurrency     DecimalCurrency;

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
    /**   インスタンスを破棄する。
    **  （デストラクタ）。
    **
    **/
    ~BookCategory();

    //----------------------------------------------------------------
    /**   アンマネージドリソースを破棄する。
    **  （ファイナライザ）。
    **
    **/
    !BookCategory();

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
private:

    /**   項目フラグ。              **/
    CategoryFlags           m_categoryFlags;

    /**  親項目のインデックス。     **/
    CategoryHandle          m_parentHandle;

    /**   項目名の ID  (文字列テーブル内のインデックス) 。  **/
    StringIndex             m_categoryNameId;

    /**   項目名。                  **/
    System::String^         m_categoryName;

    /**   サブ項目数。              **/
    CategoryHandle          m_numSubCategory;

    /**   サブ項目のインデックス。  **/
    CategoryHandleArray^    m_subCategories;

    /**   開始年月日 (残高の項目のみ) 。    **/
    int                     m_startDate;

    /**   開始時の残高 (残高の項目のみ) 。  **/
    DecimalCurrency^        m_startBalance;

//========================================================================
//
//    Other Features.
//

};

}   //  End of namespace  Documents
}   //  End of namespace  Wrapper

#endif
