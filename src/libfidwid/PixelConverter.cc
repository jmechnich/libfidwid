/**************************************************************************
**       Title: 
**    $RCSfile: PixelConverter.cc,v $
**   $Revision: 1.1 $$Name:  $
**       $Date: 2004/07/26 15:21:12 $
**   Copyright: GPL $Author: mechnich $
** Description:
**
**    
**
**-------------------------------------------------------------------------
**
**  $Log: PixelConverter.cc,v $
**  Revision 1.1  2004/07/26 15:21:12  mechnich
**  initial revision
**
**
**
**************************************************************************/

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
