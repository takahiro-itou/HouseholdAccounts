
##----------------------------------------------------------------
##
##    モジュールの設定。
##

Set (MODULE_DIR_NAME       "TestDriver")
Set (MODULE_OUTPUT_NAME    "TestDriver")
Set (MODULE_TITLE          "TestDriver")

Set (INCLIB_SOURCE_DIR     "${INCLUDE_SOURCE_DIR}/${MODULE_DIR_NAME}")
Set (INCLIB_BINARY_DIR     "${INCLUDE_BINARY_DIR}/${MODULE_DIR_NAME}")

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

Set (LIBRARY_SOURCE_FILES
        TestDriver.cpp
)

Set (INCLIB_HEADER_FILES
)

##----------------------------------------------------------------
##
##    ビルドとインストールの設定。
##

If ( CPPUNIT_FOUND )
    Include_Directories ("${CPPUNIT_INCLUDE_DIR}")
    Link_Libraries      ("${CPPUNIT_LIBRARIES}")
    Set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -DHAVE_CPPUNIT=1")
Else  ()
    Set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -DHAVE_CPPUNIT=0")
Endif ()

Include (${COMMON_CMAKE_DIR}/BuildLibraryCommon.cmake)

