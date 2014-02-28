/**************************************************************************
**       Title: 
**    $RCSfile: X11FidWidget.hh,v $
**   $Revision: 1.3 $$Name:  $
**       $Date: 2005/07/14 09:35:22 $
**   Copyright: GPL $Author: tschmidt $
** Description:
**
**    
**
**-------------------------------------------------------------------------
**
**  $Log: X11FidWidget.hh,v $
**  Revision 1.3  2005/07/14 09:35:22  tschmidt
**  - added SubSampling capabilities
**
**  Revision 1.2  2005/02/27 23:21:45  mechnich
**  added sizeHint() and added SRCTYPE as template parameter for setImagePerLine()
**
**  Revision 1.1  2004/07/26 15:21:12  mechnich
**  initial revision
**
**
**
**************************************************************************/

#ifndef X11FIDWIDGET_HH
#define X11FIDWIDGET_HH

#include <qwidget.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <string>
#include <sstream>

class X11FidWidget : public QWidget
{
public:
  QSize sizeHint() const;
  
protected:
  X11FidWidget( QWidget* parent=0, const char* name=0, WFlags f=0);
  ~X11FidWidget();

  void setImageSize( unsigned int width, unsigned int height);
  template<typename SRCTYPE, typename Converter>
  void setImagePerLine( SRCTYPE src, const Converter& conv);
  
  void paintEvent( QPaintEvent* repaintEvent);
  
  /*======================================================================*/
  /*! 
   *   Returns the x11 display depth
   *
   *   \return
   */
  /*======================================================================*/
  int depth() const;

  void setSubSampling(const unsigned int subSampling);
  unsigned int subSampling() const;
  
private:
  GC     _imageGC;  // graphic context for the image
  XImage *_xImage;  // image converted to actual screeen bit depth for redrawing
  int _depth;
  unsigned char** _rowStart;
  unsigned int _subSampling;
};

#include "X11FidWidget.icc"

#endif  
