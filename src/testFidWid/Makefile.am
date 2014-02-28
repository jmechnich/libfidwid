AM_LDFLAGS = @QtCore_LIBS@ @QtGui_LIBS@ @QtOpenGL_LIBS@ ${GL_LIBS}
LDADD = $(top_builddir)/src/libfidwid/libfidwid.la

AM_CPPFLAGS = -I$(top_srcdir)/src/libfidwid @QtCore_CFLAGS@ @QtGui_CFLAGS@ @QtOpenGL_CFLAGS@ ${GL_CPPFLAGS}

PROGS = testOpenGLTexWidget
if LINUX
PROGS += testFidWidget testX11FidWidget testOpenGLFBWidget
endif
bin_PROGRAMS = $(PROGS)

testFidWidget_CXXFLAGS = -Wall -g
testFidWidget_SOURCES = testFidWid.cc
testFidWidget_DEPENDENCIES = $(top_builddir)/src/libfidwid/libfidwid.la

testX11FidWidget_CXXFLAGS = -Wall -g -DWIDGETTYPE=X11FidWidget
testX11FidWidget_SOURCES = testFidWid.cc
testX11FidWidget_DEPENDENCIES = $(top_builddir)/src/libfidwid/libfidwid.la

testOpenGLFBWidget_CXXFLAGS = -Wall -g -DWIDGETTYPE=OpenGLFBWidget
testOpenGLFBWidget_SOURCES = testFidWid.cc
testOpenGLFBWidget_DEPENDENCIES = $(top_builddir)/src/libfidwid/libfidwid.la

testOpenGLTexWidget_CXXFLAGS = -Wall -g -DWIDGETTYPE=OpenGLTexWidget
testOpenGLTexWidget_SOURCES = testFidWid.cc
testOpenGLTexWidget_DEPENDENCIES = $(top_builddir)/src/libfidwid/libfidwid.la

EXTRA_DIST = test.ppm
