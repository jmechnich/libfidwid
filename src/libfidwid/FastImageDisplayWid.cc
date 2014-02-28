/**************************************************************************
**       Title: Widget for fast display of images 
**    $RCSfile: FastImageDisplayWid.cc,v $
**   $Revision: 1.4 $$Name:  $
**       $Date: 2005/07/14 09:26:30 $
**   Copyright: DWD GF-MM $Author: tschmidt $
** Description:
**
**    
**
**-------------------------------------------------------------------------
**
**  $Log: FastImageDisplayWid.cc,v $
**  Revision 1.4  2005/07/14 09:26:30  tschmidt
**  - added SubSampling capabilities
**
**  Revision 1.3  2005/02/27 23:12:05  mechnich
**  re-added old X11 widget
**
**  Revision 1.2  2003/10/23 17:21:45  mechnich
**  added depth() and data() functions
**
**  Revision 1.1.1.1  2003/01/23 12:30:31  ronneber
**  initial revision
**
**  Revision 1.1  2002/01/10 17:52:16  ronneber
**  imported sources from last year
**
**
**************************************************************************/

#include "FastImageDisplayWid.hh"

#include <iostream>

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:  Constructor
 *  ==> see headerfile
 *=======================================================================*/
FastImageDisplayWid::FastImageDisplayWid( QWidget * parent, 
                                          const char * name, WFlags f)
        :QWidget( parent, name, f | WRepaintNoErase),
         _xImage( 0), _depth( x11Depth()), _subSampling(1)
{
  /*-----------------------------------------------------------------------
   *  create the GC
   *-----------------------------------------------------------------------*/
  _imageGC = XCreateGC(qt_xdisplay(), winId(), 0, NULL);
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
   *  Check if xImage needs to be resized
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
     *  find out, how man bytes per pixel are required
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
      errmsg << "Requested bit depth (" << x11Depth() << ") not supported. "
          "Please Set your Screen to 16, 24 or 32 bits, or use command "
          "line argument '-visual TrueColor' on SGI's";
      throw UnsupportedBitDepth( errmsg.str());
    }
    }
    
    /*---------------------------------------------------------------------
     *  create an XImage (ownership of allocated data is passed to xImage)
     *---------------------------------------------------------------------*/
    _xImage = XCreateImage(qt_xdisplay(), 
                           (Visual*)x11Visual(),
                           x11Depth(), 
                           ZPixmap, 0,
                           (char*) malloc( subHeight * subWidth * padding), 
                           subWidth, subHeight, padding*8, 0);
  }

  /*-----------------------------------------------------------------------
   *  the QtWidget should not be resized to bigger sizes
   *-----------------------------------------------------------------------*/
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
    XPutImage(qt_xdisplay(), winId(), _imageGC, _xImage,
              0, 0, 0, 0, _xImage->width, _xImage->height);
  }
  
}


