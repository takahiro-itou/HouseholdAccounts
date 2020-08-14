
AC_MSG_CHECKING([Compiler Accepts override])
AC_TRY_COMPILE(
   [class A { virtual void f() { } };
    class B : public A { virtual void f() override { } };
],
   [;],
   [CONFIG_CHECK_CXX_OVERRIDE_ENABLED=1],
   [CONFIG_CHECK_CXX_OVERRIDE_ENABLED=0]
)
AC_MSG_RESULT(${CONFIG_CHECK_CXX_OVERRIDE_ENABLED})
AC_SUBST(CONFIG_CHECK_CXX_OVERRIDE_ENABLED)

