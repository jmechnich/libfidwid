AC_INIT([libfidwid],[0.1.0])
AC_CONFIG_SRCDIR([src/libfidwid/FastImageDisplayWid.hh])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE
AC_PROG_CC
AC_PROG_CXX
AC_LANG(C++)
AM_PROG_LIBTOOL
AC_PROG_LIBTOOL
AC_PROG_INSTALL
AC_CANONICAL_HOST

PKG_CHECK_MODULES([QtCore], [QtCore >= 4.8.4])
PKG_CHECK_MODULES([QtGui], [QtGui >= 4.8.4])
PKG_CHECK_MODULES([QtOpenGL], [QtOpenGL >= 4.8.4])
AC_CHECK_PROG(MOC, [moc], [moc])

GL_CPPFLAGS=""
GL_LIBS=""
HOST_DARWIN=0
HOST_LINUX=0
case $host_os in
  darwin* )
        # Do something specific for mac
        GL_CPPFLAGS="-DHOST_DARWIN -framework OpenGL" 
        GL_LIBS="-framework OpenGL"
        HOST_DARWIN=1
        ;;
  linux*)
        AC_CHECK_HEADERS(GL/glu.h, ,
	[AC_MSG_ERROR([No glu.h found.])])
        GL_LIBS="-lGLU -lGL"
        HOST_LINUX=1
        ;;
    *)
        #Default Case
        AC_MSG_ERROR([Your platform is not currently supported])
        ;;
esac
AC_SUBST(GL_CPPFLAGS)
AC_SUBST(GL_LIBS)
AM_CONDITIONAL([DARWIN], [test x$HOST_DARWIN = x1])
AM_CONDITIONAL([LINUX], [test x$HOST_LINUX = x1])

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
