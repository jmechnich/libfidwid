/**************************************************************************
**       Title: 
**    $RCSfile: PixelConverter.hh,v $
**   $Revision: 1.6 $$Name:  $
**       $Date: 2005/07/14 09:34:56 $
**   Copyright: GPL $Author: tschmidt $
** Description:
**
**    
**
**-------------------------------------------------------------------------
**
**  $Log: PixelConverter.hh,v $
**  Revision 1.6  2005/07/14 09:34:56  tschmidt
**  - added SubSampling capabilities
**
**  Revision 1.5  2005/02/27 23:17:42  mechnich
**  made the source pixel type a template parameter
**
**  Revision 1.4  2004/09/27 15:54:20  mechnich
**  *** empty log message ***
**
**  Revision 1.3  2004/07/26 15:21:35  mechnich
**  added OpenGL display widgets
**
**  Revision 1.2  2003/10/08 19:52:31  mechnich
**  added MONO16 and RGB16 converters
**
**  Revision 1.1  2003/04/23 13:13:56  mechnich
**  initial revision
**
**  Revision 1.1  2003/04/17 01:12:47  mechnich
**  initial revision
**
**
**
**************************************************************************/

#ifndef PIXELCONVERTER_HH
#define PIXELCONVERTER_HH

#include <cstring>
#include <iostream>

class PixelConverter
{
protected:
  typedef unsigned char  _uint8;
  typedef unsigned short _uint16;
  typedef unsigned int   _uint32;
  
  PixelConverter();
  
  static _uint16 _red16Table[256];   // conversion tables for 16 Bit Color
  static _uint16 _green16Table[256];
  static _uint16 _blue16Table[256];

  static _uint16 _convTable8To16[256];

  static bool _uninitialized;
};

class YUV411_RGBConverter : public PixelConverter
{
public:
  typedef unsigned char* SRCTYPE;
  
  YUV411_RGBConverter()
        {}
  
  void lineToRgb8( SRCTYPE src, unsigned char* trg,
                   unsigned int width,
                   unsigned int subSampling = 1) const;
  void lineToBgr8( SRCTYPE src, unsigned char* trg,
                   unsigned int width, unsigned int padding,
                   unsigned int subSampling = 1) const;
  void lineToRgba8( SRCTYPE src, unsigned char* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;
  void lineToRgb16( SRCTYPE src, unsigned short* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;

  float srcBytePerPixel() const
        {
          return 1.5;
        }
 };

class YUV422_RGBConverter : public PixelConverter
{
public:
  typedef unsigned char* SRCTYPE;
  
  YUV422_RGBConverter()
        {}
  
  void lineToRgb8( SRCTYPE src, unsigned char* trg,
                   unsigned int width,
                   unsigned int subSampling = 1) const;
  void lineToBgr8( SRCTYPE src, unsigned char* trg,
                   unsigned int width, unsigned int padding,
                   unsigned int subSampling = 1) const;
  void lineToRgba8( SRCTYPE src, unsigned char* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;
  void lineToRgb16( SRCTYPE src, unsigned short* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;

  float srcBytePerPixel() const
        {
          return 2;
        }
};

class YUV444_RGBConverter : public PixelConverter
{
public:
  typedef unsigned char* SRCTYPE;
  
  YUV444_RGBConverter()
        {};
  
  void lineToRgb8( SRCTYPE src, unsigned char* trg,
                   unsigned int width,
                   unsigned int subSampling = 1) const;
  void lineToBgr8( SRCTYPE src, unsigned char* trg,
                   unsigned int width, unsigned int padding,
                   unsigned int subSampling = 1) const;
  void lineToRgba8( SRCTYPE src, unsigned char* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;
  void lineToRgb16( SRCTYPE src, unsigned short* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;

  float srcBytePerPixel() const
        {
          return 3;
        }
};

class RGB_RGBConverter : public PixelConverter
{
public:
  typedef unsigned char* SRCTYPE;
  
  RGB_RGBConverter()
        {}
    
  void lineToRgb8( SRCTYPE src, unsigned char* trg,
                   unsigned int width,
                   unsigned int subSampling = 1) const;
  void lineToBgr8( SRCTYPE src, unsigned char* trg,
                   unsigned int width, unsigned int padding,
                   unsigned int subSampling = 1) const;
  void lineToRgba8( SRCTYPE src, unsigned char* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;
  void lineToRgb16( SRCTYPE src, unsigned short* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;
  
  float srcBytePerPixel() const
        {
          return 3;
        }
};

class RGB16_RGBConverter : public PixelConverter
{
public:
  typedef unsigned short* SRCTYPE;
  
  RGB16_RGBConverter()
        {}
    
  void lineToRgb8( SRCTYPE src, unsigned char* trg,
                   unsigned int width,
                   unsigned int subSampling = 1) const;
  void lineToBgr8( SRCTYPE src, unsigned char* trg,
                   unsigned int width, unsigned int padding,
                   unsigned int subSampling = 1) const;
  void lineToRgba8( SRCTYPE src, unsigned char* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;
  void lineToRgb16( SRCTYPE src, unsigned short* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;

  float srcBytePerPixel() const
        {
          return 6;
        }
};

class MONO_RGBConverter : public PixelConverter
{
public:
  typedef unsigned char* SRCTYPE;
  
  MONO_RGBConverter()
        {}
    
  void lineToRgb8( SRCTYPE src, unsigned char* trg,
                   unsigned int width,
                   unsigned int subSampling = 1) const;
  void lineToBgr8( SRCTYPE src, unsigned char* trg,
                   unsigned int width, unsigned int padding,
                   unsigned int subSampling = 1) const;
  void lineToRgba8( SRCTYPE src, unsigned char* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;
  void lineToRgb16( SRCTYPE src, unsigned short* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;

  float srcBytePerPixel() const
        {
          return 1;
        }
};

class MONO16_RGBConverter : public PixelConverter
{
public:
  typedef unsigned short* SRCTYPE;
  
  MONO16_RGBConverter()
        {}
    
  void lineToRgb8( SRCTYPE src, unsigned char* trg,
                   unsigned int width,
                   unsigned int subSampling = 1) const;
  void lineToBgr8( SRCTYPE src, unsigned char* trg,
                   unsigned int width, unsigned int padding,
                   unsigned int subSampling = 1) const;
  void lineToRgba8( SRCTYPE src, unsigned char* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;
  void lineToRgb16( SRCTYPE src, unsigned short* trg,
                    unsigned int width,
                    unsigned int subSampling = 1) const;

  float srcBytePerPixel() const
        {
          return 2;
        }
};

#include "PixelConverter.icc"

#endif
