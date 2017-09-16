
Include (CheckCXXSourceCompiles)

Check_CXX_Source_Compiles (
   "constexpr  int  a = 0;
    int main () {
        return ( a );
    }"
    CMAKE_CHECK_CXX_CONSTEXPR_ENABLED
)
If ( CMAKE_CHECK_CXX_CONSTEXPR_ENABLED )
    Set (CONFIG_CHECK_CXX_CONSTEXPR_ENABLED  1)
Else  ()
    Set (CONFIG_CHECK_CXX_CONSTEXPR_ENABLED  0)
EndIf ()

