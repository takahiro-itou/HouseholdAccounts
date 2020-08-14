
Include (CheckCXXSourceCompiles)

Check_CXX_Source_Compiles (
   "class A { virtual void f() { } };
    class B : public A { virtual void f() override { } };
    int main () {
        return ( 0 );
    }"
    CMAKE_CHECK_CXX_OVERRIDE_ENABLED
)
If ( CMAKE_CHECK_CXX_OVERRIDE_ENABLED )
    Set (CONFIG_CHECK_CXX_OVERRIDE_ENABLED  1)
Else  ()
    Set (CONFIG_CHECK_CXX_OVERRIDE_ENABLED  0)
EndIf ()

