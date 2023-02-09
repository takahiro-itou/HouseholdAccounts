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
**      An Interface of BookCategory class.
**
**      @file       Documents/BookCategory.h
**/

#if !defined( HAWRAPPER_DOCUMENTS_INCLUDED_BOOK_CATEGORY_H )
#    define   HAWRAPPER_DOCUMENTS_INCLUDED_BOOK_CATEGORY_H

#pragma     once


#if !defined( HAWRAPPER_COMMON_INCLUDED_ACCOUNTS_TYPES_H )
#    include    "Wrapper/Common/AccountsTypes.h"
#endif

#if !defined( HAWRAPPER_COMMON_INCLUDED_DECIMAL_CURRENCY_H )
#    include    "Wrapper/Common/DecimalCurrency.h"
#endif

#if !defined( HACORE_DOCUMENTS_INCLUDED_BOOK_CATEGORY_H )
#    include    "Account/Documents/BookCategory.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

//  クラスの前方宣言。  //
namespace  Documents  {
class   BookCategory;
class   CategoryManager;
}   //  End of namespace  Documents

HOUSEHOLD_ACCOUNTS_NAMESPACE_END


namespace  Wrapper  {
namespace  Documents  {

//========================================================================
//
//    Type Definitions.
//

typedef     HouseholdAccounts::Documents::CategoryFlags
CoreCategoryFlags;

/**
**    項目用フラグ。
**/

public  enum class  CategoryFlags
{
    CTYPE_MASK              = CoreCategoryFlags::CTYPE_MASK,
    CTYPE_NOTUSED           = CoreCategoryFlags::CTYPE_NOTUSED,
    CTYPE_INHERIT           = CoreCategoryFlags::CTYPE_INHERIT,
    CTYPE_BALANCE           = CoreCategoryFlags::CTYPE_BALANCE,
    CTYPE_INCOME            = CoreCategoryFlags::CTYPE_INCOME,
    CTYPE_OUTLAY            = CoreCategoryFlags::CTYPE_OUTLAY,
    CTYPE_BANK              = CoreCategoryFlags::CTYPE_BANK,
    CTYPE_BANK_WITHDRAW     = CoreCategoryFlags::CTYPE_BANK_WITHDRAW,
    CTYPE_BANK_DEPOSIT      = CoreCategoryFlags::CTYPE_BANK_DEPOSIT,
    CTYPE_BANK_TRANSFER     = CoreCategoryFlags::CTYPE_BANK_TRANSFER,

    /**   サブ項目を展開表示する。          **/
    CFLAG_EXPANDED          = CoreCategoryFlags::CFLAG_EXPANDED,

    /**   親の項目の合計に加算しない。      **/
    CFLAG_NOCOUNT_PARENT    = CoreCategoryFlags::CFLAG_NOCOUNT_PARENT,

    /**   ルート項目の合計に加算しない。    **/
    CFLAG_NOCOUNT_ROOT      = CoreCategoryFlags::CFLAG_NOCOUNT_ROOT,

    /**   表示しない隠し属性。  **/
    CFLAG_HIDDEN            = CoreCategoryFlags::CFLAG_HIDDEN,

    /**   削除不能な予約項目。  **/
    CFLAG_UNERASABLE        = CoreCategoryFlags::CFLAG_UNERASABLE,

    /**   読み取り専用属性。    **/
    CFLAG_READ_ONLY         = CoreCategoryFlags::CFLAG_READ_ONLY,
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

    typedef     HouseholdAccounts::Documents::BookCategory
    WrapTarget;

    typedef     HouseholdAccounts::Documents::CategoryManager
    CoreCategoryManager;

    typedef     cli::array<CategoryHandle, 1>
    CategoryHandleArray;

    typedef     Common::DecimalCurrency     DecimalCurrency;

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

private:
    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    BookCategory();

public:
    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （コンストラクタ）。
    **
    **/
    BookCategory(
            WrapTarget *            wrapTarget,
            CoreCategoryManager *   catMan);

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
public:

    //----------------------------------------------------------------
    /**   サブ項目以下を展開したり閉じたりする。
    **
    **  @param [in] blnExpanded   展開または折畳。
    **  @return     直前の状態。
    **/
    System::Boolean
    expandCategory(
            const  System::Boolean  blnExpanded);

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   項目の種類を取得する。
    **
    **/
    CategoryFlags
    getCategoryType();

    //----------------------------------------------------------------
    /**   項目のフラグを取得する。
    **
    **/
    CategoryFlags
    getFlags();

    //----------------------------------------------------------------
    /**   サブ項目のインデックスの配列を取得する。
    **
    **/
    CategoryHandleArray^
    getSubCategories();

    //----------------------------------------------------------------
    /**   サブ項目が展開されているか調べる。
    **
    **/
    System::Boolean
    isExpanded();

//========================================================================
//
//    Properties.
//
public:

    //----------------------------------------------------------------
    /**   項目のフラグ。
    **
    **/
    property    CategoryFlags
    Flags
    {
        CategoryFlags   get();
    }

    //----------------------------------------------------------------
    /**   親項目のインデックス。
    **
    **/
    property    CategoryHandle
    ParentHandle
    {
        CategoryHandle  get();
    }

    //----------------------------------------------------------------
    /**   項目の名前。
    **
    **/
    property    System::String^
    CategoryName
    {
        System::String^ get();
    }

    //----------------------------------------------------------------
    /**   サブ項目数。
    **
    **/
    property    CategoryHandle
    NumSubCategories
    {
        CategoryHandle  get();
    }

    //----------------------------------------------------------------
    /**   開始時の残高。
    **
    **/
    property    DecimalCurrency
    StartBalance
    {
        DecimalCurrency get();
    }

    //----------------------------------------------------------------
    /**   開始年月日。
    **
    **/
    property    DateSerial
    StartDate
    {
        DateSerial  get();
    }

    //----------------------------------------------------------------
    /**   サブ項目のインデックス。
    **
    **/
    property    CategoryHandle
    SubCategory[CategoryHandle]
    {
        CategoryHandle  get(CategoryHandle  idxSub);
    }

//========================================================================
//
//    Protected Member Functions.
//

//========================================================================
//
//    For Internal Use Only.
//
private:

//========================================================================
//
//    Member Variables.
//
private:

    WrapTarget  *           m_ptrBuf;

    CoreCategoryManager *   m_ptrMan;

    WrapTarget  *           m_ptrObj;

//========================================================================
//
//    Other Features.
//

};

}   //  End of namespace  Documents
}   //  End of namespace  Wrapper

#endif
