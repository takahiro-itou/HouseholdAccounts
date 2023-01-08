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

#if !defined( HACORE_SYS_INCLUDED_STL_VECTOR )
#    include    <vector>
#    define   HACORE_SYS_INCLUDED_STL_VECTOR
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

    typedef   typename  Super::allocator_type   allocator_type;
    typedef   typename  Super::difference_type  difference_type;
    typedef   typename  Super::iterator         iterator;
    typedef   typename  Super::const_iterator   const_iterator;
    typedef   typename  Super::pointer          pointer;
    typedef   typename  Super::const_pointer    const_pointer;
    typedef   typename  Super::reference        reference;
    typedef   typename  Super::const_reference  const_reference;
    typedef   typename
            Super::reverse_iterator             reverse_iterator;
    typedef   typename
            Super::const_reverse_iterator       const_reverse_iterator;
    typedef   typename  Super::size_type        size_type;
    typedef   typename  Super::value_type       value_type;

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
//    Public Member Functions (Using Super).
//
public:

    //----------------------------------------------------------------
    //    イテレータ。
    //
    using   Super::begin;
    using   Super::end;
    using   Super::rbegin;
    using   Super::rend;

#if ( __cplusplus >= 201103L )
    using   Super::cbegin;
    using   Super::cend;
    using   Super::crbegin;
    using   Super::crend;
#endif

    //----------------------------------------------------------------
    ///   領域。
    //
    //  using   Super::size;
    using   Super::max_size;
    using   Super::resize;
    using   Super::capacity;
    using   Super::empty;
    using   Super::reserve;
#if ( __cplusplus >= 201103L )
    using   Super::shrink_to_fit;
#endif

    //----------------------------------------------------------------
    //    要素アクセス。
    //
    using   Super::data;
    using   Super::front;
    using   Super::back;

    //----------------------------------------------------------------
    //    コンテナの変更。
    //
    using   Super::assign;
    using   Super::push_back;
    using   Super::pop_back;
    using   Super::insert;
    using   Super::erase;
    using   Super::swap;
    using   Super::clear;
#if ( __cplusplus >= 201103L )
    using   Super::emplace_back;
    using   Super::emplace;
#endif

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    ///   領域。
    //

    const  Id   size() const;

//========================================================================
//
//    Public Member Functions (Operators).
//
public:

    reference       operator [] (const Id n);
    const_reference operator [] (const Id n) const;

    reference       at(const Id n);
    const_reference at(const Id n) const;

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
