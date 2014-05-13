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

#include "PixelConverter.hh"

PixelConverter::_uint16
PixelConverter::_red16Table[256];
PixelConverter::_uint16
PixelConverter::_green16Table[256];
PixelConverter::_uint16
PixelConverter::_blue16Table[256];

PixelConverter::_uint16
PixelConverter::_convTable8To16[256];

bool
PixelConverter::_uninitialized = true;

/*=========================================================================
 *  DESCRIPTION OF FUNCTION:
 *  ==> see headerfile
 *=======================================================================*/
PixelConverter::PixelConverter()
{
  /*-----------------------------------------------------------------------
   *  Initialize Conversion Tables
   *-----------------------------------------------------------------------*/
  if( _uninitialized)
  {
    for( unsigned int i=0; i < 256; ++i)
    {
      _red16Table[i] = (i & 0xf8) << 8;
      _green16Table[i] = (i & 0xfc) << 3;
      _blue16Table[i] = (i & 0xf8) >> 3;

      _convTable8To16[i]=i*256;
    }
    _uninitialized = false;
  }
}
