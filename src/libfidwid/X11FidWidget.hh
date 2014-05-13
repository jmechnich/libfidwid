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

#ifndef X11FIDWIDGET_HH
#define X11FIDWIDGET_HH

#include <QWidget>
#include <QX11Info>
#include <QPaintEvent>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <string>
#include <sstream>

class X11FidWidget : public QWidget
{
public:
  QSize sizeHint() const;
  
protected:
  X11FidWidget( QWidget* parent=0);
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
