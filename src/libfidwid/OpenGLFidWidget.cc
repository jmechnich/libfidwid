/**************************************************************************
**       Title: 
**    $RCSfile: OpenGLFidWidget.cc,v $
**   $Revision: 1.2 $$Name:  $
**       $Date: 2005/07/14 09:33:32 $
**   Copyright: GPL $Author: tschmidt $
** Description:
**
**    
**
**-------------------------------------------------------------------------
**
**  $Log: OpenGLFidWidget.cc,v $
**  Revision 1.2  2005/07/14 09:33:32  tschmidt
**  - added SubSampling capabilities
**
**  Revision 1.1  2004/07/26 15:21:12  mechnich
**  initial revision
**
**
**
**************************************************************************/

#include "OpenGLFidWidget.hh"


/*-------------------------------------------------------------------------
 *  OpenGLFBWidget class
 *-------------------------------------------------------------------------*/

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:  Constructor
 *  ==> see headerfile
 *=======================================================================*/
OpenGLFBWidget::OpenGLFBWidget( QWidget * parent)
        :QGLWidget( parent), _subSampling(1), _data( 0),
         _rowStart( 0)
{}

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:  Destructor
 *  ==> see headerfile
 *=======================================================================*/
OpenGLFBWidget::~OpenGLFBWidget()
{
  if( _data)
      delete _data;
  if( _rowStart)
      delete[] _rowStart;
}


/*-------------------------------------------------------------------------
 *  OpenGLTexWidget class
 *-------------------------------------------------------------------------*/

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:  Constructor
 *  ==> see headerfile
 *=======================================================================*/
OpenGLTexWidget::OpenGLTexWidget( QWidget * parent)
        :QGLWidget( parent), _subSampling(1), _data( 0),
         _rowStart( 0), _angle( 0),
         _tex_width( 0), _tex_height( 0)
{
  for( unsigned int i=0; i < 16; ++i)
      _texMat[i] = 0.0;

  _texMat[10] = _texMat[15] = 1.0;
}

/*=========================================================================
 *  DESCRIPTION OF FUNCTION: Destructor
 *  ==> see headerfile
 *=======================================================================*/
OpenGLTexWidget::~OpenGLTexWidget()
{
  if( _data)
      delete _data;
  if( _rowStart)
      delete[] _rowStart;
}

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:
 *  ==> see headerfile
 *=======================================================================*/
void
OpenGLTexWidget::keyPressEvent( QKeyEvent* e)
{
  switch( e->key())
  {
  case Qt::Key_Left:
    _angle -=1;
    _angle %= 360;
    e->accept();
    break;
  case Qt::Key_Right:
    _angle +=1;
    _angle %= 360;
    e->accept();
    break;
  case Qt::Key_Q:
  case Qt::Key_Escape:
    close();
    e->accept();
    break;
  default:
    break;
  }
}
