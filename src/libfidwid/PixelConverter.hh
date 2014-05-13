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

#ifndef PIXELCONVERTER_HH
#define PIXELCONVERTER_HH

#include <cstring>
#include <iostream>

void yuv2rgb( unsigned char y,
              unsigned char u,
              unsigned char v,
              unsigned char* r,
              unsigned char* g,
              unsigned char* b);

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
                   unsigned int width, unsigned int subSampling = 1) const;
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

template<int U, int Y1, int V, int Y2>
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

typedef YUV422_RGBConverter<1,0,3,2> YUYV_RGBConverter;
typedef YUV422_RGBConverter<0,1,2,3> UYVY_RGBConverter;
typedef YUV422_RGBConverter<1,2,3,0> YVYU_RGBConverter;
typedef YUV422_RGBConverter<2,1,0,3> VYUY_RGBConverter;

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

class BGR_RGBConverter : public PixelConverter
{
public:
  typedef unsigned char* SRCTYPE;
  
  BGR_RGBConverter()
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
