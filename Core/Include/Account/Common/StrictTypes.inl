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
**      An Implementation of StrictTypes template class.
**
**      @file       Common/StrictTypes.inl
**/

#if !defined( HACORE_COMMON_INCLUDED_STRICT_INTEGER_INL )
#    define   HACORE_COMMON_INCLUDED_STRICT_INTEGER_INL

#if !defined( HACORE_COMMON_INCLUDED_STRICT_INTEGER_H )
#    include    "StrictTypes.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

namespace  {
}   //  End of (Unnamed) namespace.

//========================================================================
//
//    補助関数。
//

template <typename T>
inline  const  T
getValueFromStrict(const  T  val)
{
    return ( val );
}

template <typename T, typename Tag>
inline  const  T
getValueFromStrict(const  StrictTypes<T, Tag>  sv)
{
    return ( sv.getValue() );
}

//========================================================================
//
//    StrictTypes  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスをゼロで初期化する
//  （デフォルトコンストラクタ）。
//

template <typename T, typename Tag>
inline
StrictTypes<T, Tag>::StrictTypes()
    : m_cValue(0)
{ }

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

template <typename T, typename Tag>
inline
StrictTypes<T, Tag>::StrictTypes(
        const T val)
    : m_cValue(val)
{ }

//----------------------------------------------------------------
//    別のインスタンスと同じ内容で初期化する
//  （コピーコンストラクタ）。
//

template <typename T, typename Tag>
inline
StrictTypes<T, Tag>::StrictTypes(
        const This &src)
    : m_cValue(src.m_cValue)
{ }

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
//    Public Member Functions (Operators).
//

//----------------------------------------------------------------
//    値を指定した内容に設定する
//  （代入演算子 =  ）。
//

template <typename T, typename Tag>
inline  const  StrictTypes<T, Tag>  &
StrictTypes<T, Tag>::operator =  (
            const  This  & rhs)
{
    this->m_cValue  = rhs.m_cValue;
    return ( *this );
}

//----------------------------------------------------------------
//    インスタンスの内容を +1 し、その値を返す。
//  （前置インクリメント演算子 ++ ）。
//

template <typename T, typename Tag>
inline  const  StrictTypes<T, Tag>  &
StrictTypes<T, Tag>::operator ++ ()
{
    ++ this->m_cValue;
    return ( *this );
}

//----------------------------------------------------------------
//    インスタンスの内容を +1 し、直前の値を返す。
//  （後置インクリメント演算子 ++ )。
//

template <typename T, typename Tag>
inline  const  StrictTypes<T, Tag>
StrictTypes<T, Tag>::operator ++ (int)
{
    This    prv(*this);
    ++ this->m_cValue;
    return ( prv );
}

//----------------------------------------------------------------
//    インスタンスの内容を -1 し、その値を返す。
//  （前置デクリメント演算子 -- ）。
//

template <typename T, typename Tag>
inline  const  StrictTypes<T, Tag>  &
StrictTypes<T, Tag>::operator -- ()
{
    -- this->m_cValue;
    return ( *this );
}

//----------------------------------------------------------------
//    インスタンスの内容を -1 し、直前の値を返す。
//  （後置デクリメント演算子）。
//

template <typename T, typename Tag>
inline  const  StrictTypes<T, Tag>
StrictTypes<T, Tag>::operator -- (int)
{
    This    prv(*this);
    -- this->m_cValue;
    return ( prv );
}

//----------------------------------------------------------------
//    比較演算子。
//

#define     SI_IMPLEMENT_FRIEND_BINOP_CMP(RType, OP)        \
template <typename T, typename Tag>                         \
inline  RType   operator OP (                               \
    const StrictTypes<T, Tag> lhs,                          \
    const StrictTypes<T, Tag> rhs)                          \
{ return ( lhs.m_cValue OP rhs.m_cValue ); }                \
                                                            \
template <typename T, typename Tag>                         \
inline  RType   operator OP (                               \
    const StrictTypes<T, Tag> lhs, const T rhs)             \
{ return ( lhs.m_cValue OP rhs ); }                         \
                                                            \
template <typename T, typename Tag>                         \
inline  RType   operator OP (                               \
    const T lhs, const StrictTypes<T, Tag> rhs)             \
{ return ( lhs OP rhs.m_cValue ); }

SI_IMPLEMENT_FRIEND_BINOP_CMP(bool, ==);
SI_IMPLEMENT_FRIEND_BINOP_CMP(bool, !=);
SI_IMPLEMENT_FRIEND_BINOP_CMP(bool, <);
SI_IMPLEMENT_FRIEND_BINOP_CMP(bool, <=);
SI_IMPLEMENT_FRIEND_BINOP_CMP(bool, >);
SI_IMPLEMENT_FRIEND_BINOP_CMP(bool, >=);

#undef      SI_IMPLEMENT_FRIEND_BINOP_CMP

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    値を元の型で取得する。
//

template <typename T, typename Tag>
inline  const  T
StrictTypes<T, Tag>::getValue()  const
{
    return ( this->m_cValue );
}

//----------------------------------------------------------------
//    値を設定する。
//

template <typename T, typename Tag>
inline  const  StrictTypes<T, Tag>  &
StrictTypes<T, Tag>::setValue(const  T  val)
{
    this->m_cValue  = val;
    return ( *this );
}

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
