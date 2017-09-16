
Include (CheckCXXCompilerFlag)

Check_CXX_Compiler_Flag("-std=c++11"  COMPILER_ACCEPTS_CXX11)
Check_CXX_Compiler_Flag("-std=c++0x"  COMPILER_ACCEPTS_CXX0X)

If ( COMPILER_ACCEPTS_CXX11 )
    Message(STATUS  "Compiler ${CMAKE_CXX_COMPILER} Accepts -std=c++11")
    Set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -std=c++11")
ElseIf ( COMPILER_ACCEPTS_CXX0X )
    Message(STATUS  "Compiler ${CMAKE_CXX_COMPILER} Accepts -std=c++0x")
    Set (CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS}  -std=c++0x")
Else  ()
    Message(STATUS  "Compiler ${CMAKE_CXX_COMPILER} : No Support c++11")
EndIf ()

