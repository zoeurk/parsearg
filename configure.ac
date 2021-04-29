#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([libparsearg.so], [1.0], [zoeurk@gmail.com])
AC_CONFIG_SRCDIR([src/parsearg.h])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
LT_INIT
AM_INIT_AUTOMAKE([foreign])
# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([memset strchr])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
