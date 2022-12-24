
##----------------------------------------------------------------
##
##    Package Configurations.
##    パッケージ設定。
##

##
##    要求するツールのバージョンを指定する。
##

CMake_Minimum_Required (VERSION  3.0.2)

##
##    パッケージの情報を指定する。
##

Set     (PROJECT_NAME      HouseholdAccounts)
Set     (serial            "0.0.0")

Project (${PROJECT_NAME}   VERSION  1.0.0)

##----------------------------------------------------------------
##
##    プロジェクトの基本設定。
##

Enable_Testing ()

Set (COMMON_CMAKE_DIR      "${PROJECT_SOURCE_DIR}/.CMake")
Set (INCTOP_DIR_NAME       "Include")
Set (LIBTOP_DIR_NAME       "Lib")
Set (INCPKG_DIR_NAME       "Account")
Set (PACKAGE_INCLUDE_DIR   "${INCTOP_DIR_NAME}/${INCPKG_DIR_NAME}")

Set (INCTOP_SOURCE_DIR     "${PROJECT_SOURCE_DIR}/${INCTOP_DIR_NAME}")
Set (INCTOP_BINARY_DIR     "${PROJECT_BINARY_DIR}/${INCTOP_DIR_NAME}")
Set (LIBTOP_SOURCE_DIR     "${PROJECT_SOURCE_DIR}/${LIBTOP_DIR_NAME}")
Set (LIBTOP_BINARY_DIR     "${PROJECT_BINARY_DIR}/${LIBTOP_DIR_NAME}")

Set (INCLUDE_SOURCE_DIR    "${INCTOP_SOURCE_DIR}/${INCPKG_DIR_NAME}")
Set (INCLUDE_BINARY_DIR    "${INCTOP_BINARY_DIR}/${INCPKG_DIR_NAME}")

##
##    ターゲット名
##

Set (LIBRARIES_TARGET_PREFIX    hac)

##----------------------------------------------------------------
##
##    ビルド環境の検査。
##

Include (${COMMON_CMAKE_DIR}/EnableCxx11.cmake)

Include (${COMMON_CMAKE_DIR}/CheckConstExpr.cmake)
Include (${COMMON_CMAKE_DIR}/CheckNullPtr.cmake)
Include (${COMMON_CMAKE_DIR}/CheckOverride.cmake)

##
##    Project Name Space.
##

Set (HOUSEHOLD_ACCOUNTS_CNF_NAMESPACE   HouseholdAccounts)

##----------------------------------------------------------------
##
##    インクルードパスの設定。
##

Include_Directories ("${PROJECT_SOURCE_DIR}/Include")
Include_Directories ("${PROJECT_BINARY_DIR}/Include")

##----------------------------------------------------------------
##
##    Additional Packages.
##    外部ライブラリ。
##

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}  ${COMMON_CMAKE_DIR}/Modules
)

Find_Package (CppUnit)

##----------------------------------------------------------------
##
##    設定を書き込んだファイルを生成。
##

Configure_File (
    "${INCLUDE_SOURCE_DIR}/.Config/ConfiguredHouseholdAccounts.h.in"
    "${INCLUDE_BINARY_DIR}/.Config/ConfiguredHouseholdAccounts.h"
)

Configure_File (
    "${INCLUDE_SOURCE_DIR}/.Config/Config.h.cmake.in"
    "${INCLUDE_BINARY_DIR}/.Config/.${PROJECT_NAME}.Config.h"
)

##----------------------------------------------------------------
##
##    パッケージコンフィグレーション。
##

Configure_File (
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    @ONLY
)

Install (FILES  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION  .
)

##----------------------------------------------------------------
##
##    サブディレクトリの追加。
##

Add_SubDirectory (Lib)
Add_SubDirectory (Bin)

