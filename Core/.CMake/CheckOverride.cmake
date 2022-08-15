
Include (CheckCXXSourceCompiles)

check_cxx_source_compiles (
   "class A { virtual void f() { } };
    class B : public A { virtual void f() override { } };
    int main () {
        return ( 0 );
    }"
    CMAKE_CHECK_CXX_OVERRIDE_ENABLED
)
If ( CMAKE_CHECK_CXX_OVERRIDE_ENABLED )
    set(CONFIG_CHECK_CXX_OVERRIDE_ENABLED   1)
Else  ()
    set(CONFIG_CHECK_CXX_OVERRIDE_ENABLED   0)
EndIf ()

