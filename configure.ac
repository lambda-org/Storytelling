AC_INIT([storytelling], [0.0.0])
AC_CONFIG_SRCDIR([src/main.cpp])
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_TYPE_SIZE_T

CPPFLAGS="$CPPFLAGS -I/usr/include/"

PKG_CHECK_MODULES([SFML], [sfml-graphics sfml-window sfml-system])
AC_CHECK_HEADERS([spdlog/version.h], [], [
                  AC_MSG_ERROR([spdlog/spdlog.h not found, please install spdlog library])
                  ])

for dir in `echo $CPPFLAGS | tr ' ' '\n' | grep -E '^-I' | sed 's/-I//'`; do
    AC_CHECK_FILE([$dir/tl/expected.hpp], 
                  [AC_MSG_NOTICE([tl/expected.hpp found in $dir])],
                  [AC_MSG_ERROR([tl/expected.hpp not found in $dir])])
    
    AC_CHECK_FILE([$dir/spdlog/spdlog.h], 
                  [AC_MSG_NOTICE([spdlog/spdlog.h found in $dir])],
                  [AC_MSG_ERROR([spdlog/spdlog.h not found in $dir])])
done

AC_OUTPUT
