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
**      An Interface of StrictVector template class.
**
**      @file       Common/StrictVector.h
**/

#if !defined( HACORE_COMMON_INCLUDED_STRICT_VECTOR_H )
#    define   HACORE_COMMON_INCLUDED_STRICT_VECTOR_H


#if !defined( HACORE_COMMON_INCLUDED_ACCOUNTS_PROJECT_H )
#    include    "Account/Common/AccountsProject.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //

//========================================================================
//
//    StrictVector  class.
//
/**
**
**/

template <typename T, typename Id, class Allocator = std::allocator<T> >
class  StrictVector : protected std::vector<T, Allocator>
{
//========================================================================
//
//    Internal Type Definitions.
//
private:

    typedef     std::vector<T, Allocator>   Super;

public:

    using   Super::allocator_type;
    using   Super::difference_type;
    using   Super::iterator;
    using   Super::const_iterator;
    using   Super::pointer;
    using   Super::const_pointer;
    using   Super::reference;
    using   Super::const_reference;
    using   Super::reverse_iterator;
    using   Super::const_reverse_iterator;
    using   Super::size_type;
    using   Super::value_type;

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
    StrictVector();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~StrictVector();

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
    //    イテレータ。
    //
    using   Super::begin;
    using   Super::end;
    using   Super::rbegin;
    using   Super::rend;

#if (__cplusplus >= 201103L)
    using   Super::cbegin;
    using   Super::cend;
    using   Super::crbegin;
    using   Super::crend;
#endif

    //----------------------------------------------------------------
    ///   領域。
    //
    using   Super::size;
    using   Super::max_size;
    using   Super::resize;
    using   Super::capacity;
    using   Super::empty;
    using   Super::reserve;
#if (__cplusplus >= 201103L)
    using   Super::shrink_to_fit;
#endif

    //----------------------------------------------------------------
    //    要素アクセス。
    //
    using   Super::operator [];
    using   Super::at;
    using   Super::data;
    using   Super::front;
    using   Super::back;

    //----------------------------------------------------------------
    //    コンテナの変更。
    //

    using   Super::push_back;

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

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    //  friend  class   StrictVectorTest;
};

}   //  End of namespace  Common
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

//  Implementation.
#include    "StrictVector.inl"

#endif
