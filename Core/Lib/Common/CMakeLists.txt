
##----------------------------------------------------------------
##
##    モジュールの設定。
##

set(MODULE_DIR_NAME         "Common")
set(MODULE_OUTPUT_NAME      "Common")
set(MODULE_TITLE            "Common")

set(INCLIB_SOURCE_DIR       "${INCLUDE_SOURCE_DIR}/${MODULE_DIR_NAME}")
set(INCLIB_BINARY_DIR       "${INCLUDE_BINARY_DIR}/${MODULE_DIR_NAME}")

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

set(LIBRARY_SOURCE_FILES
        DecimalCurrency.cpp
        TextParser.cpp
)

set(INCLIB_HEADER_FILES
        ${INCLIB_SOURCE_DIR}/AccountsTypes.h
        ${INCLIB_SOURCE_DIR}/BookInterface.h
        ${INCLIB_SOURCE_DIR}/DecimalCurrency.h
        ${INCLIB_SOURCE_DIR}/EnumBitFlag.h
        ${INCLIB_SOURCE_DIR}/HouseholdAccountsSettings.h
        ${INCLIB_SOURCE_DIR}/TextParser.h
)

##----------------------------------------------------------------
##
##    ビルドとインストールの設定。
##

Include (${COMMON_CMAKE_DIR}/BuildLibraryCommon.cmake)

##----------------------------------------------------------------
##
##    テストの設定。
##

add_subdirectory(Tests)
