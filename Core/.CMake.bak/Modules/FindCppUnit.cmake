
set(CPPUNIT_FOUND   FALSE)

Include (FindPackageHandleStandardArgs)

If ( NOT ( "${CPPUNIT_DIR}" STREQUAL "no" ) )
    find_path(
        CPPUNIT_INCLUDE_DIR
        NAMES   cppunit/extensions/HelperMacros.h
        PATHS
            ${CPPUNIT_DIR}/include
            /usr/include
            /usr/local/include
    )

    find_library(
        CPPUNIT_LIBRARY
        NAMES   cppunit
        PATHS
            ${CPPUNIT_DIR}/lib
            /usr/lib
            /usr/local/lib
        )
    find_package_handle_standard_args(
        CPPUNIT     DEFAULT_MSG
        CPPUNIT_LIBRARY
        CPPUNIT_INCLUDE_DIR
    )
EndIf ()

If ( CPPUNIT_INCLUDE_DIR )
    If ( CPPUNIT_LIBRARY )
            message(STATUS  "CPPUNIT is enabled.")
    Else ()
        message(WARNING "Could not find cppunit library.")
    EndIf ()
Else ()
    message(WARNING "Could not find cppunit includes.")
EndIf ()

message(STATUS  "CPPUNIT_FOUND       = ${CPPUNIT_FOUND}")
message(STATUS  "CPPUNIT_INCLUDE_DIR = ${CPPUNIT_INCLUDE_DIR}")
message(STATUS  "CPPUNIT_LIBRARY     = ${CPPUNIT_LIBRARY}")

If ( NOT TARGET CPPUNIT::CPPUNIT )
    If ( CPPUNIT_FOUND )
        add_library(CPPUNIT::CPPUNIT    UNKNOWN     IMPORTED)
        set_target_properties(CPPUNIT::CPPUNIT
            PROPERTIES
            IMPORTED_LINK_INTERFACE_LANGUAGES   "CXX"
            IMPORTED_LOCATION                   "${CPPUNIT_LIBRARY}"
            INTERFACE_COMPILE_DEFINITIONS       "HAVE_CPPUNIT=1"
            INTERFACE_INCLUDE_DIRECTORIES       "${CPPUNIT_INCLUDE_DIR}"
        )
        message(STATUS  "Define target CPPUNIT::CPPUNIT")
    Else ()
        add_library(CPPUNIT::CPPUNIT    INTERFACE   IMPORTED)
        set_target_properties(CPPUNIT::CPPUNIT
            PROPERTIES
            INTERFACE_COMPILE_DEFINITIONS       "HAVE_CPPUNIT=0"
        )
        message(STATUS  "Define target CPPUNIT::CPPUNIT")
    EndIf ()
EndIf ()
