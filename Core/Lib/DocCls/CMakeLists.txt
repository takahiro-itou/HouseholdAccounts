
##----------------------------------------------------------------
##
##    モジュールの設定。
##

set(MODULE_DIR_NAME         "DocCls")
set(MODULE_OUTPUT_NAME      "DocCls")
set(MODULE_TITLE            "DocCls")

set(INCLIB_SOURCE_DIR       "${INCLUDE_SOURCE_DIR}/${MODULE_DIR_NAME}")
set(INCLIB_BINARY_DIR       "${INCLUDE_BINARY_DIR}/${MODULE_DIR_NAME}")

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

set(LIBRARY_SOURCE_FILES
        AggregatesBlock.cpp
        BookCategory.cpp
        BookDocument.cpp
        CategoryManager.cpp
        PurchasedGoods.cpp
        ReceiptInfo.cpp
        StringTable.cpp
)

set(INCLIB_HEADER_FILES
        ${INCLIB_SOURCE_DIR}/AggregatesBlock.h
        ${INCLIB_SOURCE_DIR}/BookCategory.h
        ${INCLIB_SOURCE_DIR}/BookDocument.h
        ${INCLIB_SOURCE_DIR}/CategoryManager.h
        ${INCLIB_SOURCE_DIR}/PurchasedGoods.h
        ${INCLIB_SOURCE_DIR}/ReceiptInfo.h
        ${INCLIB_SOURCE_DIR}/StringTable.h
)

Set (MODULE_NEEDS_LIBRARIES
        ${PROJECT_NAME}-${LIBRARIES_TARGET_PREFIX}Common
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

