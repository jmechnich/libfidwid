AM_LDFLAGS = @qt3_LIBS@ -lGL -lglut
LDADD = $(top_builddir)/src/libfidwid/libfidwid.la

INCLUDES = -I$(top_srcdir)/src/libfidwid @qt3_CFLAGS@

bin_PROGRAMS = testFidWidget testX11FidWidget testOpenGLFBWidget testOpenGLTexWidget

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
