/**************************************************************************
**       Title: Widget for fast display of images 
**    $RCSfile: FastImageDisplayWid.hh,v $
**   $Revision: 1.6 $$Name:  $
**       $Date: 2005/07/14 09:27:30 $
**   Copyright: GPL $Author: tschmidt $
** Description:
**
**    
**
**-------------------------------------------------------------------------
**
**  $Log: FastImageDisplayWid.hh,v $
**  Revision 1.6  2005/07/14 09:27:30  tschmidt
**  - added SubSampling capabilities
**
**  Revision 1.5  2005/02/27 23:25:15  mechnich
**  reverted to old X11 widget and renamed new one to FastImageDisplayWid_Templ
**
**  Revision 1.4  2004/07/26 15:21:35  mechnich
**  added OpenGL display widgets
**
**  Revision 1.3  2003/10/23 17:21:45  mechnich
**  added depth() and data() functions
**
**  Revision 1.2  2003/04/23 13:16:19  mechnich
**  added linewise conversion
**
**  Revision 1.1.1.1  2003/01/23 12:30:31  ronneber
**  initial revision
**
**  Revision 1.2  2002/02/12 15:26:03  baumgaer
**  comments added
**
**  Revision 1.1  2002/01/10 17:52:16  ronneber
**  imported sources from last year
**
**
**
**************************************************************************/

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
