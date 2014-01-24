dnl ====================================================================
dnl   configure.in for METIS
dnl ====================================================================
AC_PREREQ(2.61)
AC_INIT(metis, 0.1.2, [acy@hiemalis.org])
AC_CONFIG_SRCDIR([cattr.cpp])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE


dnl =======================================
dnl   Checks for programs.
dnl =======================================
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB
AC_PROG_YACC
AC_PROG_LEX


dnl ===================================
dnl   Checks for libraries.
dnl ===================================


dnl ===================================
dnl   Checks for header files.
dnl ===================================
AC_FUNC_ALLOCA
AC_HEADER_STDC
AC_CHECK_HEADERS([libintl.h malloc.h stddef.h stdlib.h unistd.h])


dnl ==================================================================
dnl   Checks for typedefs, structures, and compiler characteristics.
dnl ==================================================================
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T


dnl ==================================================================
dnl   Checks for library functions.
dnl ==================================================================
AC_HEADER_STDC
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strdup])




dnl =====================================
dnl   Output
dnl =====================================
AC_CONFIG_FILES([Makefile])
AC_OUTPUT


dnl EOF
