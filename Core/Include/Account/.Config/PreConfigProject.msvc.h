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
**      スクリプトによる設定値が書き込まれるヘッダファイル。
**
**      @file       .Config/PreConfigProject.msvc.h
**/

#if !defined( HACORE_CONFIG_INCLUDED_PRE_CONFIG_PROJECT_MSVC_H )
#    define   HACORE_CONFIG_INCLUDED_PRE_CONFIG_PROJECT_MSVC_H

//========================================================================
//
//    Name Space.
//

/**
**    スクリプトによって設定された名前空間。
**/

#define     HOUSEHOLD_ACCOUNTS_CNF_NS               \
    HABook

/**
**    名前空間。
**/

#define     HOUSEHOLD_ACCOUNTS_NAMESPACE            \
    HOUSEHOLD_ACCOUNTS_CNF_NS

#define     HOUSEHOLD_ACCOUNTS_NAMESPACE_BEGIN      \
    namespace  HOUSEHOLD_ACCOUNTS_CNF_NS  {

#define     HOUSEHOLD_ACCOUNTS_NAMESPACE_END        \
    }


//========================================================================
//
//    Compile Features.
//

//
//    キーワード constexpr  の検査。
//

#if ( 1 )
#    define     HOUSEHOLD_ACCOUNTS_ENABLE_CONSTEXPR         1
#else
#    undef      HOUSEHOLD_ACCOUNTS_ENABLE_CONSTEXPR
#endif

#if !defined( CONSTEXPR_VAR ) && !defined( CONSTEXPR_FUNC )
#    if ( HOUSEHOLD_ACCOUNTS_ENABLE_CONSTEXPR )
#        define     CONSTEXPR_VAR       constexpr
#        define     CONSTEXPR_FUNC      constexpr
#    else
#        define     CONSTEXPR_VAR       const
#        define     CONSTEXPR_FUNC
#    endif
#endif

//
//    キーワード nullptr  の検査。
//

#if ( 1 )
#    define     HOUSEHOLD_ACCOUNTS_ENABLE_NULLPTR           1
#else
#    if !defined( nullptr )
#        define     nullptr     NULL
#    endif
#    undef      HOUSEHOLD_ACCOUNTS_ENABLE_NULLPTR
#endif

//
//    キーワード override の検査。
//

#if ( 1 )
#    define     HOUSEHOLD_ACCOUNTS_ENABLE_OVERRIDE          1
#else
#    if !defined( override )
#        define     override
#    endif
#    undef      HOUSEHOLD_ACCOUNTS_ENABLE_OVERRIDE
#endif

//========================================================================
//
//    後でラッパープロジェクトから参照されることを
//  考慮して、厳格な整数型の利用は避ける。
//

#define     HACORE_DISABLE_STRICT_TYPES

//========================================================================
//
//    後でラッパープロジェクトから参照されることを
//  考慮して、標準入出力ストリームの利用は避ける。
//

#define     HACORE_DISABLE_STDIO

#endif
