
##----------------------------------------------------------------
##
##    Package Configurations.
##    パッケージ設定。
##

##
##    要求するツールのバージョンを指定する。
##

cmake_minimum_required(VERSION  3.0.2)

##
##    パッケージの情報を指定する。
##

set(PROJECT_NAME        HouseholdAccounts)
set(serial              "0.0.0")

project(${PROJECT_NAME}     VERSION  1.0.0)

##----------------------------------------------------------------
##
##    デフォルトのコンパイルオプション。
##

If (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE    Release)
EndIf ()

message("Build Type = ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS_DEBUG       "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_C_FLAGS_DEBUG         "${CMAKE_C_FLAGS_DEBUG}   -D_DEBUG")

# set(CMAKE_CXX_FLAGS_RELEASE     "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG")
# set(CMAKE_C_FLAGS_RELEASE       "${CMAKE_C_FLAGS_RELEASE}   -DNDEBUG")

##----------------------------------------------------------------
##
##    プロジェクトの基本設定。
##

enable_testing()

set(COMMON_CMAKE_DIR        "${PROJECT_SOURCE_DIR}/.CMake")
set(INCTOP_DIR_NAME         "Include")
set(BINTOP_DIR_NAME         "Bin")
set(LIBTOP_DIR_NAME         "Lib")
set(INCPKG_DIR_NAME         "Account")
set(PACKAGE_INCLUDE_DIR     "${INCTOP_DIR_NAME}/${INCPKG_DIR_NAME}")

set(INCTOP_SOURCE_DIR       "${PROJECT_SOURCE_DIR}/${INCTOP_DIR_NAME}")
set(INCTOP_BINARY_DIR       "${PROJECT_BINARY_DIR}/${INCTOP_DIR_NAME}")
set(LIBTOP_SOURCE_DIR       "${PROJECT_SOURCE_DIR}/${LIBTOP_DIR_NAME}")
set(LIBTOP_BINARY_DIR       "${PROJECT_BINARY_DIR}/${LIBTOP_DIR_NAME}")

set(INCLUDE_SOURCE_DIR      "${INCTOP_SOURCE_DIR}/${INCPKG_DIR_NAME}")
set(INCLUDE_BINARY_DIR      "${INCTOP_BINARY_DIR}/${INCPKG_DIR_NAME}")

##
##    ターゲット名
##

set(LIBRARIES_TARGET_PREFIX     hac)

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

set(HOUSEHOLD_ACCOUNTS_CNF_NAMESPACE    HouseholdAccounts)

##----------------------------------------------------------------
##
##    インクルードパスの設定。
##

include_directories("${PROJECT_SOURCE_DIR}/Include")
include_directories("${PROJECT_BINARY_DIR}/Include")

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

configure_file(
    "${INCLUDE_SOURCE_DIR}/.Config/ConfiguredProject.h.in"
    "${INCLUDE_BINARY_DIR}/.Config/ConfiguredProject.h"
)

configure_file(
    "${INCLUDE_SOURCE_DIR}/.Config/Config.h.cmake.in"
    "${INCLUDE_BINARY_DIR}/.Config/.${PROJECT_NAME}.Config.h"
)

##----------------------------------------------------------------
##
##    パッケージコンフィグレーション。
##

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    @ONLY
)

install(FILES   "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION  .
)

##----------------------------------------------------------------
##
##    サブディレクトリの追加。
##

Add_SubDirectory (Lib)
Add_SubDirectory (Bin)
