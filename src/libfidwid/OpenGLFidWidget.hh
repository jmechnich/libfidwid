/**************************************************************************
**       Title: 
**    $RCSfile: OpenGLFidWidget.hh,v $
**   $Revision: 1.3 $$Name:  $
**       $Date: 2005/07/14 09:33:32 $
**   Copyright: GPL $Author: tschmidt $
** Description:
**
**    
**
**-------------------------------------------------------------------------
**
**  $Log: OpenGLFidWidget.hh,v $
**  Revision 1.3  2005/07/14 09:33:32  tschmidt
**  - added SubSampling capabilities
**
**  Revision 1.2  2005/02/27 23:16:13  mechnich
**  added sizeHint() and changed setImagePerLine() to a templated function
**
**  Revision 1.1  2004/07/26 15:21:12  mechnich
**  initial revision
**
**
**
**************************************************************************/

#ifndef OPENGLFIDWIDGET_HH
#define OPENGLFIDWIDGET_HH

#include <qgl.h>
#include <qapplication.h>
/*-------------------------------------------------------------------------
 *  OpenGLFBWidget class
 *-------------------------------------------------------------------------*/
class OpenGLFBWidget : public QGLWidget
{
public:
  QSize sizeHint() const;
  
protected:
  OpenGLFBWidget( QWidget * parent=0, const char * name=0, WFlags f=0);
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
  OpenGLTexWidget( QWidget * parent=0, const char * name=0, WFlags f=0);
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
