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

#include "X11FidWidget.hh"

#include <iostream>

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:  Constructor
 *  ==> see headerfile
 *=======================================================================*/
X11FidWidget::X11FidWidget( QWidget * parent)
:QWidget( parent),
    _xImage( 0), _depth( QX11Info::appDepth()), _rowStart( 0), _subSampling(1)
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
X11FidWidget::~X11FidWidget()
{
  if( _xImage)
      XDestroyImage( _xImage);
  
  if( _rowStart)
      delete[] _rowStart;

  XFreeGC( QX11Info::display(), _imageGC);
}

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:  setImageSize()
 *  ==> see headerfile
 *=======================================================================*/
void
X11FidWidget::setImageSize( unsigned int width, unsigned int height)
{

  unsigned int subWidth = width / _subSampling;
  unsigned int subHeight = height / _subSampling;

//   std::cerr << "X11FidWidget::setImageSize(): " << std::endl
//             << "  original size:   " << width << "x" << height << std::endl
//             << "  subSampled size: " << subWidth << "x" << subHeight << std::endl;
  
  /*-----------------------------------------------------------------------
   *  Check if xImage needs to be resized
   *-----------------------------------------------------------------------*/
  if( _xImage == 0 
      || subHeight != (unsigned int)_xImage->height 
      || subWidth != (unsigned int)_xImage->width)
  {
    if( _xImage)
    {
      XDestroyImage( _xImage);
    }

    /*---------------------------------------------------------------------
     *  find out, how man bytes per pixel are required
     *---------------------------------------------------------------------*/
    int padding=0;
    
    switch( _depth)
    {
    case 16:
      padding = 2;
      break;
    case 24:
      padding = 4;
    case 32:
      padding = 4;
      break;
    default:
      std::cerr << "Unsupported display depth " << depth() << std::endl;
      exit(1);
      break;
    }
    
    int lineWidth = subWidth * padding;
    /*---------------------------------------------------------------------
     *  create an XImage (ownership of allocated data is passed to xImage)
     *---------------------------------------------------------------------*/
    _xImage = XCreateImage( QX11Info::display(), 
                            (Visual*)QX11Info::appVisual(),
                            _depth, 
                            ZPixmap, 0,
                            (char*) malloc( subHeight * lineWidth), 
                            subWidth, subHeight, padding*8, 0);

//    std::cerr << "X11FidWidget::setImageSize(): new XImage created" << std::endl;
    
    if( _rowStart)
        delete[] _rowStart;
    _rowStart = new unsigned char*[subHeight];
    for( unsigned i=0; i < subHeight; ++i)
    {
      _rowStart[i] = reinterpret_cast<unsigned char*>
          (_xImage->data + i * lineWidth);
    }

//    std::cerr << "X11FidWidget::setImageSize(): lineStartPointers set" << std::endl;

    setFixedSize(subWidth, subHeight);
    
  }
}

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:
 *  ==> see headerfile
 *=======================================================================*/
void
X11FidWidget::paintEvent( QPaintEvent* repaintEvent)
{
  /*-----------------------------------------------------------------------
   *  Redraw the rectangular portion of the Image the QPaintEvent requests
   *-----------------------------------------------------------------------*/
  if( _xImage != 0)
  {
    
//     std::cerr << "X11FidWidget::paintEvent(): do repaint... " << std::flush;
    
    
    XPutImage(QX11Info::display(), winId(), _imageGC, _xImage,
              repaintEvent->rect().left(), repaintEvent->rect().top(),
              repaintEvent->rect().left(), repaintEvent->rect().top(),
              repaintEvent->rect().width(), repaintEvent->rect().height());

//     std::cerr << "done" << std::endl;

  }
}
