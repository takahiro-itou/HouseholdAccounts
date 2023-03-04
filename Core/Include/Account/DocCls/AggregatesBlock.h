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
**      An Interface of AggregatesBlock class.
**
**      @file       DocCls/AggregatesBlock.h
**/

#if !defined( HACORE_DOCCLS_INCLUDED_AGGREGATES_BLOCK_H )
#    define   HACORE_DOCCLS_INCLUDED_AGGREGATES_BLOCK_H


#if !defined( HACORE_DOCCLS_INCLUDED_MERCHANDISE_H )
#    include    "Merchandise.h"
#endif

#if !defined( HACORE_COMMON_INCLUDED_STRICT_VECTOR_H )
#    include    "Account/Common/StrictVector.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  DocCls  {

//  クラスの前方宣言。  //

//========================================================================
//
//    AggregatesBlock  struct.
//
/**
**    集計ブロック。
**/

struct  AggregatesBlock
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
    AggregatesBlock();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~AggregatesBlock();

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
    friend  class   AggregatesBlockTest;
};

}   //  End of namespace  DocCls
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
