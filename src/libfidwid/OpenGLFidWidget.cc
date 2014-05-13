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
      delete[] _data;
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
      delete[] _data;
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
