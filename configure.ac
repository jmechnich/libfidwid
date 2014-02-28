AC_INIT([libfidwid],[0.1.0])
AC_CONFIG_SRCDIR([src/libfidwid/FastImageDisplayWid.hh])
AM_INIT_AUTOMAKE
AC_PROG_CC
AC_PROG_CXX
AC_LANG(C++)
AM_PROG_LIBTOOL
AC_PROG_LIBTOOL
AC_PROG_INSTALL

dnl PKG_CHECK_MODULES([qt3], [qt-mt >= 3.3.0])
dnl AC_PATH_PROG([qt3_MOC], [moc-qt3], [no])
dnl if test $qt3_MOC = "no"; then
dnl    AC_PATH_PROG([qt3_MOC], [moc], [no])
dnl    if test $qt3_MOC = "no"; then
dnl       AC_MSG_ERROR( Could not find moc)
dnl    fi
dnl fi

PKG_CHECK_MODULES([QtCore], [QtCore >= 4.8.4])
PKG_CHECK_MODULES([QtGui], [QtGui >= 4.8.4])
PKG_CHECK_MODULES([QtOpenGL], [QtOpenGL >= 4.8.4])
AC_CHECK_PROG(MOC, [moc], [moc])

dnl Check for GLUT headers first.
AC_CHECK_HEADERS(GL/glut.h, ,
	[AC_MSG_ERROR([No glut.h found.])])

lt_major=1
lt_revision=0
lt_age=0

AC_SUBST(lt_major)
AC_SUBST(lt_revision)
AC_SUBST(lt_age)

AC_OUTPUT([
        Makefile
	src/Makefile
	scripts/Makefile
	src/libfidwid/Makefile
	src/testFidWid/Makefile
        ])
