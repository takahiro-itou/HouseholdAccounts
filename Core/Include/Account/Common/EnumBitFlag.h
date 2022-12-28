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
**      Helper Functions.
**
**      @file       Common/EnumBitFlag.h
**/

#if !defined( HACORE_COMMON_INCLUDED_ENUM_BIT_FLAG_H )
#    define   HACORE_COMMON_INCLUDED_ENUM_BIT_FLAG_H


#if !defined( HACORE_COMMON_INCLUDED_ACCOUTNS_TYPES_H )
#    include    "Account/Common/AccountsTypes.h"
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN

//========================================================================
//
//    列挙型をビットフラグとして仕えるようにする便利関数。
//

//----------------------------------------------------------------
/**   列挙型の値の論理積（ビットマスク）を取る
**  （二項演算子  & ）。
**
**/

template <typename T>
const T  operator & (const T lhs, const T rhs)
{
    typedef     typename  std::underlying_type<T>::type     UT;
    return ( static_cast<T>(
            static_cast<UT>(lhs) & static_cast<UT>(rhs)
    ) );
}

//----------------------------------------------------------------
/**   列挙型の値の論理積（ビットマスク）を取る
**  （複合代入演算子 &= ）。
**/

template <typename T>
const T& operator &= (T & lhs, const T rhs)
{
    typedef     typename  std::underlying_type<T>::type     UT;
    lhs = static_cast<T>(
            static_cast<UT>(lhs) & static_cast<UT>(rhs)
    );
    return ( lhs );
}

//----------------------------------------------------------------
/**   列挙型の値の論理和を取る
**  （二項演算子  | ）。
**
**/

template <typename T>
const T  operator | (const T lhs, const T rhs)
{
    typedef     typename  std::underlying_type<T>::type     UT;
    return ( static_cast<T>(
            static_cast<UT>(lhs) | static_cast<UT>(rhs)
    ) );
}

//----------------------------------------------------------------
/**   列挙型の値の論理和を取る
**  （複合代入演算子 |= ）。
**/

template <typename T>
const T& operator |= (T & lhs, const T rhs)
{
    typedef     typename  std::underlying_type<T>::type     UT;
    lhs = static_cast<T>(
            static_cast<UT>(lhs) | static_cast<UT>(rhs)
    );
    return ( lhs );
}

//----------------------------------------------------------------
/**   列挙型のビット反転を取る
**  （単項演算子  ~ ）。
**
**/

template <typename T>
const T  operator ~ (const T rhs)
{
    typedef     typename  std::underlying_type<T>::type     UT;
    return ( static_cast<T>(
            ~ static_cast<UT>(rhs)
    ) );
}

HOUSEHOLD_ACCOUNTS_NAMESPACE_END

#endif
