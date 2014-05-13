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
   FastImageDisplayWid_Templ( QWidget* parent=0)
           : WidgetType( parent)
        {}
  
  void setImageSize( unsigned int width, unsigned int height)
        {
          WidgetType::setImageSize( width, height);
        }

  template<typename SourceIterator, typename Converter>
  void setImagePerLine( SourceIterator src, const Converter& conv)
        {
          WidgetType::setImagePerLine( src, conv);
        }
  
  void setSubSampling( unsigned int subSampling)
        {
          WidgetType::setSubSampling(subSampling);
        }
  
  unsigned int subSampling() const
        {
          return WidgetType::subSampling();
        }
  
private:
  unsigned char** _rowStart;
};

#endif
