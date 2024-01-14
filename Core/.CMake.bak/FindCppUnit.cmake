
##
##    ヘッダファイルを検索する。
##

If ( CPPUNIT_DIR )
    Set (CPPUNIT_INCLUDE_SEARCH_DIRS  ${CPPUNIT_DIR}/include)
Else  ()
    Set (CPPUNIT_INCLUDE_SEARCH_DIRS
        /usr/local/include  /usr/include
    )
Endif ()

Message (STATUS  "Searching CPPUNIT : ${CPPUNIT_INCLUDE_SEARCH_DIRS}")
Find_Path (CPPUNIT_INCLUDE_DIR  cppunit/TestRunner.h
    PATHS
      ${CPPUNIT_INCLUDE_SEARCH_DIRS}
    NO_DEFAULT_PATH
)

##
##    ライブラリファイルを検索する。
##

If ( CPPUNIT_DIR )
    Set (CPPUNIT_LIBRARY_SEARCH_DIRS
        ${CPPUNIT_DIR}/lib
        ${CPPUNIT_INCLUDE_DIR}/../lib
    )
Else  ()
    Set (CPPUNIT_LIBRARY_SEARCH_DIRS
        ${CPPUNIT_INCLUDE_DIR}/../lib
        /usr/local/lib  /usr/lib
    )
Endif ()

Message (STATUS  "Searching CPPUNIT : ${CPPUNIT_LIBRARY_SEARCH_DIRS}")
Find_Library (CPPUNIT_LIBRARY  cppunit
    ${CPPUNIT_LIBRARY_SEARCH_DIRS}
    NO_DEFAULT_PATH
)

##
##    検索結果を変数に格納する。
##

If ( CPPUNIT_INCLUDE_DIR  AND  CPPUNIT_LIBRARY )
    Set (CPPUNIT_FOUND      "YES")
    Set (CPPUNIT_LIBRARIES  ${CPPUNIT_LIBRARY}  ${CMAKE_DL_LIBS})
    Message (STATUS  "CPPUNIT Found.")
    Message (STATUS  "CPPUNIT_INCLUDE_DIR = ${CPPUNIT_INCLUDE_DIR}")
    Message (STATUS  "CPPUNIT_LIBRARIES   = ${CPPUNIT_LIBRARIES}")
Else  ()
    Set (CPPUNIT_FOUND      "NO")
    Message (STATUS  "CPPUNIT Not Found.")
Endif ()

