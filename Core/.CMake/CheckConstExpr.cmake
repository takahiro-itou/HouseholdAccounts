
Include (CheckCXXSourceCompiles)

check_cxx_source_compiles (
   "constexpr  int  a = 0;
    int main () {
        return ( a );
    }"
    CMAKE_CHECK_CXX_CONSTEXPR_ENABLED
)
If ( CMAKE_CHECK_CXX_CONSTEXPR_ENABLED )
    set(CONFIG_CHECK_CXX_CONSTEXPR_ENABLED  1)
Else  ()
    set(CONFIG_CHECK_CXX_CONSTEXPR_ENABLED  0)
EndIf ()
