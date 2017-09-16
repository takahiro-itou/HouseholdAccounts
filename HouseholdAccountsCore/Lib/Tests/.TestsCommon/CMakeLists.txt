
##----------------------------------------------------------------
##
##    モジュールの設定。
##

Set (TARGET_TESTEE_LIBRARY  "${MODULE_TITLE}")

Set (DRIVER_SOURCE_DIR      "${LIBTOP_SOURCE_DIR}/Tests")
Set (DRIVER_BINARY_DIR      "${LIBTOP_BINARY_DIR}/Tests")

##----------------------------------------------------------------
##
##    テストの設定。
##

Set (TESTER_LINK_LIBRARIES
        ${PROJECT_NAME}-${TARGET_TESTEE_LIBRARY}
        ${PROJECT_NAME}-TestDriver
)

If ( CPPUNIT_FOUND )
    Include_Directories ("${CPPUNIT_INCLUDE_DIR}")
    Link_Libraries      ("${CPPUNIT_LIBRARIES}")
    Set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -DHAVE_CPPUNIT=1")
Else  ()
    Set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -DHAVE_CPPUNIT=0")
Endif ()

Include_Directories (${PROJECT_SOURCE_DIR}/Lib/Tests)
Link_Libraries      (${TESTER_LINK_LIBRARIES})

Include (TestConf.cmake)

