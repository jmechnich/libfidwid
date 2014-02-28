/**************************************************************************
**       Title: 
**    $RCSfile: FastImageDisplayWid_Templ.hh,v $
**   $Revision: 1.2 $$Name:  $
**       $Date: 2005/07/14 09:28:31 $
**   Copyright: GPL $Author: tschmidt $
** Description:
**
**    
**
**-------------------------------------------------------------------------
**
**  $Log: FastImageDisplayWid_Templ.hh,v $
**  Revision 1.2  2005/07/14 09:28:31  tschmidt
**  - added SubSampling interface
**
**  Revision 1.1  2005/03/04 18:09:16  mechnich
**  initial revision
**
**
**
**************************************************************************/

#ifndef FASTIMAGEDISPLAYWID_HH
#define FASTIMAGEDISPLAYWID_HH

#include <qwidget.h>

/*======================================================================*/
/*!
 *  \class FastImageDisplayWid_Templ FastImageDisplayWid_Templ.hh
 *  \brief The FastImageDisplayWid_Templ class is a basic visualization 
 *         class for displaying image sequences.
 *
 */
/*======================================================================*/
template<typename WidgetType>
class FastImageDisplayWid_Templ : public WidgetType
{
public:
   FastImageDisplayWid_Templ( QWidget* parent=0);
  
  void setImageSize( unsigned int width, unsigned int height);

  template<typename SourceIterator, typename Converter>
  void setImagePerLine( SourceIterator src, const Converter& conv);

  void setSubSampling(const unsigned int subSampling);
  
  unsigned int subSampling() const;
  
private:
  unsigned char** _rowStart;
};

#include "FastImageDisplayWid_Templ.icc"

#endif  



