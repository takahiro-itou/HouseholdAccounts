
Include (CheckCXXCompilerFlag)

check_cxx_compiler_flag("-std=gnu++14"  COMPILER_ACCEPTS_GNU14)
check_cxx_Compiler_flag("-std=gnu++11"  COMPILER_ACCEPTS_GNU11)
check_cxx_compiler_flag("-std=c++11"    COMPILER_ACCEPTS_CXX11)
check_cxx_compiler_flag("-std=c++0x"    COMPILER_ACCEPTS_CXX0X)

If ( COMPILER_ACCEPTS_GNU14 )
    message(STATUS  "Compiler ${CMAKE_CXX_COMPILER} Accepts -std=gnu++14")
    set(CXXFLAGS_ENABLE_CPLUSPLUS11    "-std=gnu++14")
ElseIf ( COMPILER_ACCEPTS_GNU11 )
    message(STATUS  "Compiler ${CMAKE_CXX_COMPILER} Accepts -std=gnu++11")
    set(CXXFLAGS_ENABLE_CPLUSPLUS11    "-std=gnu++11")
ElseIf ( COMPILER_ACCEPTS_CXX11 )
    message(STATUS  "Compiler ${CMAKE_CXX_COMPILER} Accepts -std=c++11")
    set(CXXFLAGS_ENABLE_CPLUSPLUS11    "-std=c++11")
ElseIf ( COMPILER_ACCEPTS_CXX0X )
    message(STATUS  "Compiler ${CMAKE_CXX_COMPILER} Accepts -std=c++0x")
    set(CXXFLAGS_ENABLE_CPLUSPLUS11    "-std=c++0x")
Else  ()
    message(STATUS  "Compiler ${CMAKE_CXX_COMPILER} : No Support c++11")
    set(CXXFLAGS_ENABLE_CPLUSPLUS11    "")
EndIf ()

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  ${CXXFLAGS_ENABLE_CPLUSPLUS11}")
message(STATUS  "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")

