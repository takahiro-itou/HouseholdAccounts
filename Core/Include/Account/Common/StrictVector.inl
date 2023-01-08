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
**      An Implementation of StrictVector template class.
**
**      @file       Common/StrictVector.inl
**/

#if !defined( HACORE_COMMON_INCLUDED_STRICT_VECTOR_INL )
#    define   HACORE_COMMON_INCLUDED_STRICT_VECTOR_INL


#if !defined( HACORE_COMMON_INCLUDED_STRICT_VECTOR_H )
#    include    "StrictVector.h"
#endif


#if !defined( HACORE_COMMON_INCLUDED_STRICT_TYPES_H )
#    include    "StrictTypes.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

namespace  {
}   //  End of (Unnamed) namespace.

//========================================================================
//
//    StrictVector  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （デフォルトコンストラクタ）。
//

template <typename T, typename Id, class Allocator>
inline
StrictVector<T, Id, Allocator>::StrictVector()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

template <typename T, typename Id, class Allocator>
inline
StrictVector<T, Id, Allocator>::~StrictVector()
{
}

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

template <typename T, typename Id, class Allocator>
inline  const  Id
StrictVector<T, Id, Allocator>::capacity()  const
{
    return ( static_cast<Id>(Super::capacity()) );
}

template <typename T, typename Id, class Allocator>
inline  const  Id
StrictVector<T, Id, Allocator>::max_size()  const
{
    return ( static_cast<Id>(Super::max_size()) );
}

template <typename T, typename Id, class Allocator>
inline  const  Id
StrictVector<T, Id, Allocator>::size()  const
{
    return ( static_cast<Id>(Super::size()) );
}

template <typename T, typename Id, class Allocator>
inline  void
StrictVector<T, Id, Allocator>::resize(const Id n)
{
    Super::resize( getValueFromStrict(n) );
}

template <typename T, typename Id, class Allocator>
inline  void
StrictVector<T, Id, Allocator>::resize(const Id n, const T &c)
{
    Super::resize( getValueFromStrict(n), c );
}

template <typename T, typename Id, class Allocator>
inline  void
StrictVector<T, Id, Allocator>::reserve(const Id n)
{
}

//========================================================================
//
//    Public Member Functions (Operators).
//

template <typename T, typename Id, class Allocator>
inline  typename  StrictVector<T, Id, Allocator>::reference
StrictVector<T, Id, Allocator>::operator [] (const Id n)
{
    return ( Super::operator [] (getValueFromStrict(n)) );
}

template <typename T, typename Id, class Allocator>
inline  typename  StrictVector<T, Id, Allocator>::const_reference
StrictVector<T, Id, Allocator>::operator [] (const Id n) const
{
    return ( Super::operator [] (getValueFromStrict(n)) );
}

template <typename T, typename Id, class Allocator>
inline  typename  StrictVector<T, Id, Allocator>::reference
StrictVector<T, Id, Allocator>::at(const Id n)
{
    return ( Super::at(getValueFromStrict(n)) );
}

template <typename T, typename Id, class Allocator>
inline  typename  StrictVector<T, Id, Allocator>::const_reference
StrictVector<T, Id, Allocator>::at(const Id n) const
{
    return ( Super::at(getValueFromStrict(n)) );
}

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

}   //  End of namespace  Common
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
