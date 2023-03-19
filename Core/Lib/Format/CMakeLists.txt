
##----------------------------------------------------------------
##
##    モジュールの設定。
##

Set (MODULE_DIR_NAME       "Format")
Set (MODULE_OUTPUT_NAME    "Format")
Set (MODULE_TITLE          "Format")

Set (INCLIB_SOURCE_DIR     "${INCLUDE_SOURCE_DIR}/${MODULE_DIR_NAME}")
Set (INCLIB_BINARY_DIR     "${INCLUDE_BINARY_DIR}/${MODULE_DIR_NAME}")

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

Set (LIBRARY_SOURCE_FILES
        BookFile.cpp
        ReceiptFile.cpp
)

Set (INCLIB_HEADER_FILES
        ${INCLIB_SOURCE_DIR}/BookFile.h
        ${INCLIB_SOURCE_DIR}/ReceiptFile.h
)

Set (MODULE_NEEDS_LIBRARIES
        ${PROJECT_NAME}-${LIBRARIES_TARGET_PREFIX}DocCls
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

Add_SubDirectory (Tests)

