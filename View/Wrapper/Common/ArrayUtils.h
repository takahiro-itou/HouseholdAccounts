//  -*-  coding: utf-8-with-signature-unix; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**              ---  Household Accounts  Wrapper Lib.  ---              **
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
**      配列操作のユーティリティ。
**
**      @file       Interface/ArrayUtils.h
**/

#if !defined( HAWRAPPER_COMMON_INCLUDED_ARRAY_UTILS_H )
#    define   HAWRAPPER_COMMON_INCLUDED_ARRAY_UTILS_H

#pragma     once


#include    "Wrapper/Common/AccountsTypes.h"

#if !defined( HACORE_SYS_INCLUDED_STL_VECTOR )
#    if !defined( HAWRAPPER_SYS_INCLUDED_STL_VECTOR )
#        include    <vector>
#        define   HAWRAPPER_SYS_INCLUDED_STL_VECTOR
#    endif
#endif


namespace  Wrapper  {

//========================================================================
//
//    配列操作のユーティリティ。
//

//----------------------------------------------------------------
/**   ネイティブ動的配列をマネージド型配列に変換する。
**
**/

template <typename T>
cli::array<T, 1> ^
toManageFromVector(
        const  std::vector<T> & vecSrc)
{
    const  int  num = static_cast<int>(vecSrc.size());
    cli::array<T, 1> ^  vecDest = gcnew cli::array<T, 1>(num);
    for ( int i = 0; i < num; ++ i ) {
        vecDest[i]  = vecSrc[i];
    }

    return ( vecDest );
}


}   //  End of namespace  Wrapper

#endif
