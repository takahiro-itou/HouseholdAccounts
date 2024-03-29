﻿//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
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
**      An Interface of StrictTypes template class.
**
**      @file       Common/StrictTypes.h
**/

#if !defined( HACORE_COMMON_INCLUDED_STRICT_TYPES_H )
#    define   HACORE_COMMON_INCLUDED_STRICT_TYPES_H


#if !defined( HACORE_COMMON_INCLUDED_ACCOUNTS_PROJECT_H )
#    include    "Account/Common/AccountsProject.h"
#endif


#if !defined( HACORE_SYS_INCLUDED_OSTREAM )
#    include    <ostream>
#    define   HACORE_SYS_INCLUDED_OSTREAM
#endif


HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN
namespace  Common  {

//  クラスの前方宣言。  //
template <typename T, typename Tag>
class  StrictTypes;

//----------------------------------------------------------------
//  フレンド関数の前方宣言。
//

#if 0
#define     ST_FWD_DECLARE_FRIEND_BIN_OP(OP)                    \
template <typename T, typename Tag>     StrictTypes<T, Tag>     \
operator OP (const T lhs, const StrictTypes<T, Tag> rhs)

ST_FWD_DECLARE_FRIEND_BIN_OP(*);
ST_FWD_DECLARE_FRIEND_BIN_OP(/);
ST_FWD_DECLARE_FRIEND_BIN_OP(%);
ST_FWD_DECLARE_FRIEND_BIN_OP(+);
ST_FWD_DECLARE_FRIEND_BIN_OP(-);
ST_FWD_DECLARE_FRIEND_BIN_OP(<<);
ST_FWD_DECLARE_FRIEND_BIN_OP(>>);
ST_FWD_DECLARE_FRIEND_BIN_OP(&);
ST_FWD_DECLARE_FRIEND_BIN_OP(^);
ST_FWD_DECLARE_FRIEND_BIN_OP(|);

#undef  ST_FWD_DECLARE_FRIEND_BIN_OP
#endif

#define     ST_FWD_DECLARE_FRIEND_BIN_CMP_OP(RType, OP)         \
template <typename T, typename Tag>                             \
RType   operator OP (const  StrictTypes<T, Tag> lhs,            \
                     const  StrictTypes<T, Tag> rhs);           \
                                                                \
template <typename T, typename Tag>     RType                   \
operator OP (const StrictTypes<T, Tag> lhs, const T rhs);       \
template <typename T, typename Tag>     RType                   \
operator OP (const T lhs, const StrictTypes<T, Tag> rhs)

ST_FWD_DECLARE_FRIEND_BIN_CMP_OP(bool, ==);
ST_FWD_DECLARE_FRIEND_BIN_CMP_OP(bool, !=);
ST_FWD_DECLARE_FRIEND_BIN_CMP_OP(bool, <);
ST_FWD_DECLARE_FRIEND_BIN_CMP_OP(bool, <=);
ST_FWD_DECLARE_FRIEND_BIN_CMP_OP(bool, >);
ST_FWD_DECLARE_FRIEND_BIN_CMP_OP(bool, >=);

#undef  ST_FWD_DECLARE_FRIEND_BIN_CMP_OP

template <typename T, typename Tag>     std::ostream  &
operator << (std::ostream & os, const StrictTypes<T, Tag> val);

//----------------------------------------------------------------

//========================================================================
//
//    StrictTypes  class.
//
/**
**    厳格な整数型クラス。
**
**    整数型同士でも異なる用途に使う場合に異なる型として扱われ、
**  原則として互いに代入・演算ができない。
**  必要ならば明示的に変換を行うことができる。
**/

template <typename T, typename Tag>
class  StrictTypes
{
//========================================================================
//
//    Internal Type Definitions.
//
public:

    /**   ベースとなっている値型。  **/
    typedef     T                       BaseValType;

private:

    typedef     StrictTypes<T, Tag>     This;

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスをゼロで初期化する
    **  （デフォルトコンストラクタ）。
    **
    **/
    StrictTypes();

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （コンストラクタ）。
    **
    **  @param [in] val   値。
    **/
    explicit
    StrictTypes(
            const T val);

    //----------------------------------------------------------------
    /**   別のインスタンスと同じ内容で初期化する
    **  （コピーコンストラクタ）。
    **
    **/
    StrictTypes(
            const This &src);

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
public:

    //----------------------------------------------------------------
    /**   値を指定した内容に設定する
    **  （代入演算子 =  ）。
    **
    **/
    inline  const  This  &
    operator =  (
            const  This  & rhs);

    //----------------------------------------------------------------
    /**   インスタンスの内容を +1 し、その値を返す。
    **  （前置インクリメント演算子 ++ ）。
    **
    **/
    inline  const  This  &
    operator ++ ();

    //----------------------------------------------------------------
    /**   インスタンスの内容を +1 し、直前の値を返す。
    **  （後置インクリメント演算子 ++ )。
    **
    **/
    inline  const  This
    operator ++ (int);

    //----------------------------------------------------------------
    /**   インスタンスの内容を -1 し、その値を返す。
    **  （前置デクリメント演算子 -- ）。
    **
    **/
    inline  const  This  &
    operator -- ();

    //----------------------------------------------------------------
    /**   インスタンスの内容を -1 し、直前の値を返す。
    **  （後置デクリメント演算子）。
    **
    **/
    inline  const  This
    operator -- (int);

public:

    //----------------------------------------------------------------
    //    比較演算子以外の二項演算子と複合代入演算子。
    //
    //  算術演算子、論理演算子、シフト演算子。
    //
#define     ST_DECLARE_BIN_AND_ASSIGN_OP(OP)                    \
    inline  const This  operator OP (const This &rhs) const;    \
    inline  const This  operator OP (const T rhs) const;        \
    inline  const This& operator OP##= (const This &rhs);       \
    inline  const This& operator OP##= (const T rhs)

    ST_DECLARE_BIN_AND_ASSIGN_OP(*);
    ST_DECLARE_BIN_AND_ASSIGN_OP(/);
    ST_DECLARE_BIN_AND_ASSIGN_OP(%);
    ST_DECLARE_BIN_AND_ASSIGN_OP(+);
    ST_DECLARE_BIN_AND_ASSIGN_OP(-);
    ST_DECLARE_BIN_AND_ASSIGN_OP(<<);
    ST_DECLARE_BIN_AND_ASSIGN_OP(>>);
    ST_DECLARE_BIN_AND_ASSIGN_OP(&);
    ST_DECLARE_BIN_AND_ASSIGN_OP(^);
    ST_DECLARE_BIN_AND_ASSIGN_OP(|);

#undef      ST_DECLARE_BIN_AND_ASSIGN_OP

    //----------------------------------------------------------------
    //    比較演算子。
    //
#define     ST_DECLARE_FRIEND_BIN_CMP_OP(RType, OP)             \
friend  RType                                                   \
operator OP <T, Tag> (const This lhs, const This rhs);          \
friend  RType                                                   \
operator OP <T, Tag> (const This lhs, const T rhs);             \
friend  RType                                                   \
operator OP <T, Tag> (const T lhs, const This rhs)

    ST_DECLARE_FRIEND_BIN_CMP_OP(bool, ==);
    ST_DECLARE_FRIEND_BIN_CMP_OP(bool, !=);
    ST_DECLARE_FRIEND_BIN_CMP_OP(bool, <);
    ST_DECLARE_FRIEND_BIN_CMP_OP(bool, <=);
    ST_DECLARE_FRIEND_BIN_CMP_OP(bool, >);
    ST_DECLARE_FRIEND_BIN_CMP_OP(bool, >=);

#undef  ST_DECLARE_FRIEND_BIN_CMP_OP


//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   値を元の型で取得する。
    **
    **/
    const  T
    getValue()  const;

    //----------------------------------------------------------------
    /**   値を設定する。
    **
    **/
    const  This  &
    setValue(const  T  val);

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

    T   m_cValue;

//========================================================================
//
//    Other Features.
//
public:
    //  テストクラス。  //
    friend  class   StrictTypesTest;
};

}   //  End of namespace  Common
HOUSEHOLD_ACCOUNTS_NAMESPACE_END

//  Implementation.
#include    "StrictTypes.inl"

#endif
