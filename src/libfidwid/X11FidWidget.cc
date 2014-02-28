/**************************************************************************_
**       Title: 
**    $RCSfile: X11FidWidget.cc,v $
**   $Revision: 1.3 $$Name:  $
**       $Date: 2005/07/14 09:35:22 $
**   Copyright: GPL $Author: tschmidt $
** Description:
**
**    
**
**-------------------------------------------------------------------------
**
**  $Log: X11FidWidget.cc,v $
**  Revision 1.3  2005/07/14 09:35:22  tschmidt
**  - added SubSampling capabilities
**
**  Revision 1.2  2005/06/21 11:21:21  emmenlau
**   - changed cast: new unsigned char*[height] (gcc-4.0 compliant)
**
**  Revision 1.1  2004/07/26 15:21:12  mechnich
**  initial revision
**
**
**
**************************************************************************/

#include "X11FidWidget.hh"

#include <iostream>

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:  Constructor
 *  ==> see headerfile
 *=======================================================================*/
X11FidWidget::X11FidWidget( QWidget * parent, const char * name, WFlags f)
        :QWidget( parent, name, f | WRepaintNoErase),
         _xImage( 0), _depth( x11Depth()), _rowStart( 0), _subSampling(1)
{
  /*-----------------------------------------------------------------------
   *  create the GC
   *-----------------------------------------------------------------------*/
  _imageGC = XCreateGC(qt_xdisplay(), winId(), 0, NULL);
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
    _xImage = XCreateImage( qt_xdisplay(), 
                            (Visual*)x11Visual(),
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
    
      
      XPutImage(qt_xdisplay(), winId(), _imageGC, _xImage,
                repaintEvent->rect().left(), repaintEvent->rect().top(),
                repaintEvent->rect().left(), repaintEvent->rect().top(),
                repaintEvent->rect().width(), repaintEvent->rect().height());

//     std::cerr << "done" << std::endl;

  }
}
