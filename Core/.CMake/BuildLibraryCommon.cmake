##################################################################
##
##    ライブラリモジュールのビルドとインストールを設定する
##
##    豫め決められた変数を設定して、
##  このファイルをインクルードする。
##
##    インクルードする前に設定すべき変数：
##
##  -   プロジェクト全体で共通にする事が多い変数
##    --  INCTOP_DIR_NAME
##    --  INCTOP_SOURCE_DIR
##    --  LIBRARIES_TARGET_PREFIX
##    --  LIBRARIES_NAME_PREFIX
##    --  LIBTOP_DIR_NAME
##    --  OUTPUT_DEBUG_SUFFIX
##    --  OUTPUT_RELEASE_SUFFIX
##    --  PACKAGE_INCLUDE_DIR
##    --  PROJECT_NAME
##  -   モジュール毎に設定する必要がある変数：
##    --  INCLIB_HEADER_FILES
##    --  LIBRARY_SOURCE_FILES
##    --  MODULE_DIR_NAME
##    --  MODULE_TITLE
##    --  MODULE_OUTPUT_NAME
##

##----------------------------------------------------------------
##
##    ターゲットの設定
##

##  ターゲットの名前。

set(MODULE_TARGET_NAME  "${LIBRARIES_TARGET_PREFIX}${MODULE_TITLE}")

##  ソースファイルの有無を確認する。

If ( NOT("${LIBRARY_SOURCE_FILES}" STREQUAL "") )
    ##  通常通りライブラリファイルを生成する。
    add_library(${PROJECT_NAME}-${MODULE_TARGET_NAME}
            ${LIBRARY_SOURCE_FILES})

    ##  出力するファイル名。
    If ( "${MODULE_OUTPUT_NAME}" STREQUAL "" )
        set(LIBRARY_OUTPUT_NAME
                ${LIBRARIES_NAME_PREFIX}${MODULE_TARGET_NAME}
        )
    Else  ()
        set(LIBRARY_OUTPUT_NAME
                ${LIBRARIES_NAME_PREFIX}${MODULE_OUTPUT_NAME}
        )
    EndIf ()

    set_property(TARGET     ${PROJECT_NAME}-${MODULE_TARGET_NAME}
            PROPERTY        OUTPUT_NAME
            ${LIBRARY_OUTPUT_NAME}
    )
    set_property(TARGET     ${PROJECT_NAME}-${MODULE_TARGET_NAME}
            PROPERTY        OUTPUT_NAME_DEBUG
            ${LIBRARY_OUTPUT_NAME}${OUTPUT_DEBUG_SUFFIX}
    )
    set_property (TARGET    ${PROJECT_NAME}-${MODULE_TARGET_NAME}
            PROPERTY        OUTPUT_NAME_RELEASE
            ${LIBRARY_OUTPUT_NAME}${OUTPUT_RELEASE_SUFFIX}
    )

Else  ()
    ##  ヘッダのみのインターフェイスライブラリ。
    add_library(${PROJECT_NAME}-${MODULE_TARGET_NAME}   INTERFACE)
EndIf ()

##----------------------------------------------------------------
##
##    ターゲットが必要とするライブラリがあれば設定する。
##

If ( NOT ( "${MODULE_NEEDS_LIBRARIES}" STREQUAL "" ) )
    target_link_libraries(
            ${PROJECT_NAME}-${MODULE_TARGET_NAME}
            ${MODULE_NEEDS_LIBRARIES}
    )
EndIf ()

##----------------------------------------------------------------
##
##    インクルードディレクトリを設定する。
##

set_property(TARGET     ${PROJECT_NAME}-${MODULE_TARGET_NAME}
        APPEND  PROPERTY   INTERFACE_INCLUDE_DIRECTORIES
        $<BUILD_INTERFACE:${INCTOP_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${INCTOP_DIR_NAME}>
)

##----------------------------------------------------------------
##
##    ファイルのインストール。
##


##  ヘッダファイルをインストールする。

install(FILES           ${INCLIB_HEADER_FILES}
        DESTINATION     ${PACKAGE_INCLUDE_DIR}/${MODULE_DIR_NAME}
)

##  ライブラリファイルをインストールする。

install(TARGETS     ${PROJECT_NAME}-${MODULE_TARGET_NAME}
        EXPORT      ${PROJECT_NAME}-${MODULE_TITLE}-Export
        ARCHIVE     DESTINATION  ${LIBTOP_DIR_NAME}/${MODULE_DIR_NAME}
        LIBRARY     DESTINATION  ${LIBTOP_DIR_NAME}/${MODULE_DIR_NAME}
)

##----------------------------------------------------------------
##
##    エクスポート設定。
##

##  インストールツリー向けのエクスポート。

install(EXPORT          ${PROJECT_NAME}-${MODULE_TITLE}-Export
        FILE            ${PROJECT_NAME}-${MODULE_TITLE}-Export.cmake
        DESTINATION     ${LIBTOP_DIR_NAME}/${MODULE_DIR_NAME}
        EXPORT_LINK_INTERFACE_LIBRARIES
)

##  ビルドツリー向けのエクスポート。

export(
    TARGETS     ${PROJECT_NAME}-${MODULE_TARGET_NAME}
    FILE        ${PROJECT_NAME}-${MODULE_TITLE}-BuildTree-Export.cmake
)
