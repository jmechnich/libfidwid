
AM_CXXFLAGS = -Wall -g @QtCore_CFLAGS@ @QtGui_CFLAGS@  @QtOpenGL_CFLAGS@

lib_LTLIBRARIES = libfidwid.la
	
libfidwid_la_LDFLAGS = \
	-version-info @lt_major@:@lt_revision@:@lt_age@ @QtCore_LIBS@ @QtGui_LIBS@ @QtOpenGL_LIBS@

libfidwid_la_SOURCES = \
	FastImageDisplayWid.cc \
	OpenGLFidWidget.cc \
	PixelConverter.cc \
	X11FidWidget.cc

pkginclude_HEADERS = \
	FastImageDisplayWid.hh \
	FastImageDisplayWid.icc \
	FastImageDisplayWid_Templ.hh \
	FastImageDisplayWid_Templ.icc \
	OpenGLFidWidget.hh \
	OpenGLFidWidget.icc \
	PixelConverter.hh \
	PixelConverter.icc \
	X11FidWidget.hh \
	X11FidWidget.icc
