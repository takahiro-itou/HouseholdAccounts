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
**      An Interface of CategoryWiseAggregates class.
**
**      @file       Documents/CategoryWiseAggregates.h
**/

#if !defined( HAWRAPPER_DOCUMENTS_INCLUDED_CATEGORY_WISE_AGGREGATES_H )
#    define   HAWRAPPER_DOCUMENTS_INCLUDED_CATEGORY_WISE_AGGREGATES_H

#pragma     once

#include    "Common/AccountsTypes.h"
#include    "Common/DecimalCurrency.h"

namespace  Wrapper  {
namespace  Documents  {

//========================================================================
//
//    CategoryWiseAggregates  class.
//

/**
**    項目ごとの集計した結果を管理するクラス。
**/

public ref  class  CategoryWiseAggregates
{

//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**   集計結果を保存する配列型。    **/
    typedef     cli::array<Common::DecimalCurrency, 1>
    AggregatesList;

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
    CategoryWiseAggregates();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する。
    **  （デストラクタ）。
    **
    **/
    ~CategoryWiseAggregates();

    //----------------------------------------------------------------
    /**   アンマネージドリソースを破棄する。
    **  （ファイナライザ）。
    **
    **/
    !CategoryWiseAggregates();

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
public:

    property    Common::DecimalCurrency
    categoryValue[int]
    {
        Common::DecimalCurrency     get(CategoryHandle  idxCategory);
    }

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

    /**   集計した結果を格納する配列。  **/
    AggregatesList^     m_aggregateResult;

//========================================================================
//
//    Other Features.
//

};

}   //  End of namespace  Documents
}   //  End of namespace  Wrapper

#endif
