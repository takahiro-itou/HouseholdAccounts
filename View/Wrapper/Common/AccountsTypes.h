//  -*-  coding: utf-8-with-signature;  mode: c++  -*-  //
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
**      Type Definitions.
**
**      @file       Common/AccountsTypes.h
**/

#pragma     once

#include    "HouseholdAccounts/Common/AccountsTypes.h"

namespace  AccountsWrapper  {

public  enum class  ErrCode
{
    ERR_SUCCESS             = HouseholdAccounts::ERR_SUCCESS,
    ERR_FAILURE             = HouseholdAccounts::ERR_FAILURE,
    ERR_FILE_OPEN_ERROR     = HouseholdAccounts::ERR_FILE_OPEN_ERROR,
    ERR_FILE_IO_ERROR       = HouseholdAccounts::ERR_FILE_IO_ERROR,
    ERR_INDEX_OUT_OF_RANGE  = HouseholdAccounts::ERR_INDEX_OUT_OF_RANGE
};

}   //  End of namespace  AccountsWrapper
