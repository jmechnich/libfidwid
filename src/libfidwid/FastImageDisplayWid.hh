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

#ifndef FASTIMAGEDISPLAYWID_HH
#define FASTIMAGEDISPLAYWID_HH

#include <QWidget>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <string>
#include <sstream>



/*======================================================================*/
/*!
 *  \class FastImageDisplayWid FastImageDisplayWid.hh
 *  \brief The FastImageDisplayWid class is a basic visualization 
 *         class for displaying image sequences.
 *
 */
/*======================================================================*/
class FastImageDisplayWid : public QWidget
{
public:
  /*-----------------------------------------------------------------------
   *  Error classes
   *-----------------------------------------------------------------------*/
  class UnsupportedBitDepth
  { 
  public: 
    UnsupportedBitDepth( std::string s) 
            : _message(s) 
          { }
    const std::string& what() const 
          { return _message;}
  private: 
    std::string _message;
  };  
  
  
  /*======================================================================*/
  /*! 
   *   Constructor 
   *
   *   \param parent   parent QT-Widget 
   *   \param name     name of Widget
   *   \param f        Drawing-flags
   *
   */
  /*======================================================================*/
  FastImageDisplayWid( QWidget * parent=0 );

  ~FastImageDisplayWid();
  
  /*======================================================================*/
  /*! 
   *   set size of image to be displayed
   *
   *   \param width  width of image
   *   \param height height of image
   *
   *   \exception UnsupportedBitDepth
   *         
   */
  /*======================================================================*/
  void setImageSize( unsigned int width, unsigned int height);
  
  /*======================================================================*/
  /*! 
   *   template method to set the image for displaying.  
   *
   *   \param begin iterator pointing to the beginning of the image
   *   \param end   iterator pointing to the end of the image
   *
   */
  /*======================================================================*/
  template< typename Iterator, typename Converter>
  void setImage( const Iterator& begin, const Iterator& end,
                 const Converter& conv);
  
  template<typename SourceIterator, typename Converter>
  void setImagePerLine( SourceIterator begin,
                        const Converter& conv,
                        unsigned int width=0,
                        unsigned int height=0,
                        unsigned int padding=0);
  
  /*======================================================================*/
  /*! 
   *   overloaded sizeHint returns recommended size for this Widget
   *
   *   \return recommended size for this Widget
   */
  /*======================================================================*/
  QSize sizeHint() const;

  /*======================================================================*/
  /*! 
   *   Returns a pointer to the image data
   *
   *   \return
   */
  /*======================================================================*/
  unsigned char* data();
  
  /*======================================================================*/
  /*! 
   *   Returns the x11 display depth
   *
   *   \return
   */
  /*======================================================================*/
  int depth() const;

  /*======================================================================*/
  /*! 
   *   Set the subsampling for visualization of the xImage
   *
   *   \param subSampling the subsampling to use for visualization
   */
  /*======================================================================*/
  void setSubSampling(const unsigned int subSampling);

  /*======================================================================*/
  /*! 
   *   Returns the currently set subsampling for the image display
   *
   *   \return current subsampling
   */
  /*======================================================================*/
  unsigned int subSampling() const;

protected:
  virtual void paintEvent( QPaintEvent * );
  
  
private:
  GC     _imageGC;  // graphic context for the image
  XImage *_xImage;  // image converted to actual screeen bit depth for redrawing
  int _depth;
  unsigned int _subSampling; // subsampling should be 1 for normal operation

};


#include "FastImageDisplayWid.icc"

#endif
