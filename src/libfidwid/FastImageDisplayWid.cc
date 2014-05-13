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

#include "FastImageDisplayWid.hh"

#include <iostream>
#include <QX11Info>

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:  Constructor
 *  ==> see headerfile
 *=======================================================================*/
FastImageDisplayWid::FastImageDisplayWid( QWidget * parent)
        :QWidget( parent),
         _xImage( 0), _depth( QX11Info::appDepth()), _subSampling(1)
{
  setAttribute( Qt::WA_NoBackground);
  setAttribute( Qt::WA_PaintOnScreen);
  /*-----------------------------------------------------------------------
   *  create the GC
   *-----------------------------------------------------------------------*/
  _imageGC = XCreateGC(QX11Info::display(), winId(), 0, NULL);
}

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:  Destructor
 *  ==> see headerfile
 *=======================================================================*/
FastImageDisplayWid::~FastImageDisplayWid()
{
  if( _xImage)
      XDestroyImage( _xImage);
  XFreeGC( QX11Info::display(), _imageGC);
}

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:  setImageSize()
 *  ==> see headerfile
 *=======================================================================*/
void FastImageDisplayWid::setImageSize( unsigned int width, unsigned int height)
{

  unsigned int subWidth = width / _subSampling;
  unsigned int subHeight = height / _subSampling;

  /*-----------------------------------------------------------------------
   *  check if xImage needs to be resized
   *-----------------------------------------------------------------------*/
  if( _xImage == 0 
      || subHeight != (unsigned int)_xImage->height 
      || subWidth != (unsigned int)_xImage->width)
  {
    if( _xImage != 0)
    {
      XDestroyImage( _xImage);
    }

    /*---------------------------------------------------------------------
     *  find out how many bytes per pixel are required
     *---------------------------------------------------------------------*/
    int padding;
    
    switch( _depth)
    {
    case 16:
      std::cerr << "Bit depth not supperted !" << std::endl;
      padding = 2;
      break;
    case 24:
      padding = 4;
      break;
    case 32:
      padding = 4;
      break;
    default:
    {
      std::ostringstream errmsg;
      errmsg << "Requested bit depth (" << _depth << ") not supported. "
          "Please Set your Screen to 16, 24 or 32 bits, or use command "
          "line argument '-visual TrueColor' on SGI's";
      throw UnsupportedBitDepth( errmsg.str());
    }
    }
    
    /*---------------------------------------------------------------------
     *  create an XImage (ownership of allocated data is passed to xImage)
     *---------------------------------------------------------------------*/
    _xImage = XCreateImage(QX11Info::display(), 
                           (Visual*)QX11Info::appVisual(),
                           QX11Info::appDepth(), 
                           ZPixmap, 0,
                           (char*) malloc( subHeight * subWidth * padding), 
                           subWidth, subHeight, padding*8, 0);
  }

  setFixedSize( subWidth, subHeight);
}

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:
 *  ==> see headerfile
 *=======================================================================*/
QSize FastImageDisplayWid::sizeHint() const
{
  return QSize( _xImage->width, _xImage->height);
}

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:
 *  ==> see headerfile
 *=======================================================================*/
void FastImageDisplayWid::paintEvent( QPaintEvent * )
{
  /*-----------------------------------------------------------------------
   *  Just redraw the whole widget (don't take regions into accout)
   *-----------------------------------------------------------------------*/
  if( _xImage != 0)
  {
    XPutImage(QX11Info::display(), winId(), _imageGC, _xImage,
              0, 0, 0, 0, _xImage->width, _xImage->height);
  }
}

