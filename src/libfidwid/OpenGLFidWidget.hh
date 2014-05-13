// This file is part of libfidwid.
//
// libfidwid is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libfidwid is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with libfidwid.  If not, see <http://www.gnu.org/licenses/>.

#ifndef OPENGLFIDWIDGET_HH
#define OPENGLFIDWIDGET_HH

#include <QApplication>
#include <QGLWidget>
#include <QPaintEvent>
#ifdef HOST_DARWIN
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
/*-------------------------------------------------------------------------
 *  OpenGLFBWidget class
 *-------------------------------------------------------------------------*/
class OpenGLFBWidget : public QGLWidget
{
public:
  QSize sizeHint() const;
  
protected:
  OpenGLFBWidget( QWidget * parent=0);
  ~OpenGLFBWidget();
  
  void setImageSize( unsigned int width, unsigned int height);
  template<typename SRCTYPE, typename Converter>
  void setImagePerLine( SRCTYPE src, const Converter& conv);

  void setSubSampling(const unsigned int subSampling);
  unsigned int subSampling() const;

  void initializeGL();
  void resizeGL( int width, int height);
  void paintGL();
  
private:
  unsigned int _subSampling;
  GLubyte* _data;
  GLubyte** _rowStart;
};
  
/*-------------------------------------------------------------------------
 *  OpenGLTexWidget class
 *-------------------------------------------------------------------------*/
class OpenGLTexWidget : public QGLWidget
{
public:
  QSize sizeHint() const;
  
protected:
  OpenGLTexWidget( QWidget * parent=0);
  ~OpenGLTexWidget();
  
  void setImageSize( unsigned int width, unsigned int height);
  template<typename SRCTYPE, typename Converter>
  void setImagePerLine( SRCTYPE src, const Converter& conv);

  void setSubSampling(const unsigned int subSampling);
  unsigned int subSampling() const;

  void initializeGL();
  void resizeGL( int width, int height);
  void paintGL();
  void keyPressEvent( QKeyEvent* e);
  
private:
  unsigned int _subSampling;
  GLubyte* _data;
  GLubyte** _rowStart;

  GLuint _texName;
  GLdouble _texMat[16];
  int _angle;
  unsigned int _tex_width, _tex_height;
};

#include "OpenGLFidWidget.icc"

#endif
