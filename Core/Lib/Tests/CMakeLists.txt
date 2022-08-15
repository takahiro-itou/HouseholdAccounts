
##----------------------------------------------------------------
##
##    モジュールの設定。
##

set(MODULE_DIR_NAME         "TestDriver")
set(MODULE_OUTPUT_NAME      "TestDriver")
set(MODULE_TITLE            "TestDriver")

set(INCLIB_SOURCE_DIR       "${INCLUDE_SOURCE_DIR}/${MODULE_DIR_NAME}")
set(INCLIB_BINARY_DIR       "${INCLUDE_BINARY_DIR}/${MODULE_DIR_NAME}")

##----------------------------------------------------------------
##
##    ソースファイルとヘッダファイルのリスト。
##

set(LIBRARY_SOURCE_FILES
        TestDriver.cpp
)

set(INCLIB_HEADER_FILES
)

##----------------------------------------------------------------
##
##    ビルドとインストールの設定。
##

Include (${COMMON_CMAKE_DIR}/BuildLibraryCommon.cmake)

set(TEST_DRIVER_MODULE  "${PROJECT_NAME}-${MODULE_TARGET_NAME}")
message(STATUS  "TEST_DRIVER_MODULE = ${TEST_DRIVER_MODULE}")

If ( TARGET  CPPUNIT::CPPUNIT )
    target_link_libraries(${TEST_DRIVER_MODULE}     CPPUNIT::CPPUNIT)
    message(STATUS  "Target CPPUNIT::CPPUNIT is defined.")
Else  ()
    target_compile_definitions(
        ${TEST_DRIVER_MODULE}   PUBLIC  HAVE_CPPUNIT=0
    )
    message(WARNING "Target CPPUNIT::CPPUNIT is NOT defined.")
EndIf ()
