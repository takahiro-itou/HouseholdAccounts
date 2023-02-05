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
**      An Interface of BookCategory class.
**
**      @file       Documents/BookCategory.h
**/

#if !defined( HACORE_DOCUMENTS_INCLUDED_BOOK_CATEGORY_H )
#    define   HACORE_DOCUMENTS_INCLUDED_BOOK_CATEGORY_H


#if !defined( HACORE_COMMON_INCLUDED_ACCOUTNS_TYPES_H )
#    include    "Account/Common/AccountsTypes.h"
#endif

#if !defined( HACORE_COMMON_INCLUDED_DECIMAL_CURRENCY_H )
#    include    "Account/Common/DecimalCurrency.h"
#endif

#if !defined( HACORE_COMMON_INCLUDED_STRICT_VECTOR_H )
#    include    "Account/Common/StrictVector.h"
#endif

#if !defined( HACORE_SYS_INCLUDED_STL_STRING )
#    include    <string>
#    define   HACORE_SYS_INCLUDED_STL_STRING
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Documents  {

//  クラスの前方宣言。  //
class   CategoryManager;


//========================================================================
//
//    Type Definitions.
//

/**
**    項目用フラグ。
**/

enum class  CategoryFlags : int32_t
{
    CTYPE_MASK              = 0x000000ff,
    CTYPE_NOTUSED           = 0,    /**<  未使用。          **/
    CTYPE_INHERIT           = 1,    /**<  親の設定を継承。  **/
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
private:

    DECLARE_STRICT_VECTOR(
            CategoryHandle,     SubCategoryIdx,
            CategoryHandleArray
    );

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
    /**   インスタンスを初期化する
    **  （コピーコンストラクタ）。
    **
    **  @param [in] src   コピー元インスタンス。
    **/
    BookCategory(
            const  BookCategory  &src);

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
public:

    //----------------------------------------------------------------
    /**   サブ項目を追加する。
    **
    **  @param [in] cateSub   項目のハンドル。
    **  @return     何番目の子になるかを返す。
    **/
    virtual  const  SubCategoryIdx
    appendSubCategory(
            const   CategoryHandle  cateSub);

    //----------------------------------------------------------------
    /**   サブ項目を全て消去する。
    **
    **  @return     void.
    **/
    virtual  void
    clearSubCategories();

    //----------------------------------------------------------------
    /**   項目を展開または閉じる。
    **
    **  @param [in] flgExpand   真の場合は展開。
    **                          偽の場合は折畳。
    **  @return     直前の状態を返す。
    **/
    virtual  const  Boolean
    expandCategory(
            const  Boolean  flgExpand);

    //----------------------------------------------------------------
    /**   項目のデータを設定する。
    **
    **  @param [in] cateSelf        自身のハンドル。
    **  @param [in] cateParent      親項目のハンドル。
    **  @param [in] cateName        項目名。
    **  @param [in] cateFlags       項目フラグ。
    **  @param [in] startDate       開始日。
    **  @param [in] startBalance    開始時金額。
    **/
    virtual  void
    setupCategory(
            const  CategoryHandle   cateSelf,
            const  CategoryHandle   cateParent,
            const  std::string     &cateName,
            const  CategoryFlags    cateFlags,
            const  DateSerial       startDate,
            const  DecimalCurrency &startBalance);

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   項目のフラグを取得する。
    **
    **/
    const   CategoryFlags
    getCategoryFlags()  const;

    //----------------------------------------------------------------
    /**   項目のフラグを設定する。
    **
    **  @param [in] flagNew
    **  @return     以前の値。
    **/
    const   CategoryFlags
    setCategoryFlags(
            const   CategoryFlags   flagNew);

    //----------------------------------------------------------------
    /**   項目の名前を取得する。
    **
    **/
    const   std::string  &
    getCategoryName()  const;

    //----------------------------------------------------------------
    /**   項目の名前を設定する。
    **
    **  @param [in] cateName
    **/
    void
    setCategoryName(
            const  std::string  &cateName);

    //----------------------------------------------------------------
    /**   項目の種類を取得する。
    **
    **/
    const   CategoryFlags
    getCategoryType()  const;

    //----------------------------------------------------------------
    /**   サブ項目が展開されているか調べる。
    **
    **/
    const   Boolean
    isExpanded();

    //----------------------------------------------------------------
    /**   サブ項目の個数を取得する。
    **
    **/
    const   SubCategoryIdx
    getNumSubCategories()  const;

    //----------------------------------------------------------------
    /**   親項目のインデックスを取得する。
    **
    **/
    const   CategoryHandle
    getParentHandle()  const;

    //----------------------------------------------------------------
    /**   親項目のインデックスを設定する。
    **
    **  @param [in] parentNew
    **  @return     以前の値。
    **/
    const   CategoryHandle
    setParentHandle(
            const   CategoryHandle  parentNew);

    //----------------------------------------------------------------
    /**   開始年月日を取得する。
    **
    **/
    const   DateSerial
    getStartDate()  const;

    //----------------------------------------------------------------
    /**   開始年月日を設定する。
    **
    **  @param [in] valNew
    **  @return     void.
    **/
    void
    setStartDate(
            const   DateSerial  valNew);

    //----------------------------------------------------------------
    /**   開始時の残高を取得する。
    **
    **/
    const   DecimalCurrency  &
    getStartBalance()  const;

    //----------------------------------------------------------------
    /**   開始時の残高を設定する。
    **
    **  @param [in] valNew
    **  @return     void.
    **/
    void
    setStartBalance(
            const  DecimalCurrency  &valNew);

    //----------------------------------------------------------------
    /**   サブ項目のインデックスの配列を取得する。
    **
    **/
    const   CategoryHandleArray  &
    getSubCategories()  const;

    //----------------------------------------------------------------
    /**   サブ項目のインデックスを取得する。
    **
    **  @param [in] idxSub    サブ項目番号。
    **  @return     指定した番号のサブ項目のインデックス。
    **/
    const   CategoryHandle
    getSubCategory(
            const   SubCategoryIdx  idxSub)  const;

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

    /**   項目を管理するインスタンス。  **/
    CategoryManager *       m_ptrManager;

    /**  自身の項目インデックス。       **/
    CategoryHandle          m_selfCateHandle;

    /**   項目フラグ。                  **/
    CategoryFlags           m_categoryFlags;

    /**  親項目のインデックス。         **/
    CategoryHandle          m_parentHandle;

    /**   項目名の ID  (文字列テーブル内のインデックス) 。  **/
    StringIndex             m_categoryNameId;

    /**   項目名。                      **/
    std::string             m_categoryName;

    /**   サブ項目数。                  **/
    SubCategoryIdx          m_numSubCategory;

    /**   サブ項目のインデックス。      **/
    CategoryHandleArray     m_subCategories;

    /**   開始年月日 (残高の項目のみ) 。    **/
    DateSerial              m_startDate;

    /**   開始時の残高 (残高の項目のみ) 。  **/
    DecimalCurrency         m_startBalance;

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
