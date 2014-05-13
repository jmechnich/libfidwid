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

#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#include <QApplication>
#include <QObject>
#include <PixelConverter.hh>

#ifdef WIDGETTYPE
#include <FastImageDisplayWid_Templ.hh>
#include <X11FidWidget.hh>
#include <OpenGLFidWidget.hh>
typedef FastImageDisplayWid_Templ<WIDGETTYPE> FastImageDisplayWid;
#else
#include <FastImageDisplayWid.hh>
#endif

// from http://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html
int
timespec_subtract( timespec *result, timespec *x,  timespec *y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_nsec < y->tv_nsec) {
    int nsec = (y->tv_nsec - x->tv_nsec) / 1000000000 + 1;
         y->tv_nsec -= 1000000000 * nsec;
         y->tv_sec += nsec;
  }
  if (x->tv_nsec - y->tv_nsec > 1000000000) {
    int nsec = (x->tv_nsec - y->tv_nsec) / 1000000000;
    y->tv_nsec += 1000000000 * nsec;
    y->tv_sec -= nsec;
  }
  
  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_nsec = x->tv_nsec - y->tv_nsec;
  
  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}

inline
timespec diff( const timespec& start, const timespec& end)
{
  timespec temp = { end.tv_sec-start.tv_sec, 0 };
  if( end.tv_nsec < start.tv_nsec)
  {
    temp.tv_sec  -= 1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}

static std::istream& 
_eatWsAndComments(std::istream &s)
{
  s >> std::ws;
          
  while (s.peek()=='#')
  {
    s.ignore(10000, '\n');  // ignore characters until line end
    s >> std::ws;
  }
  return s;
}

struct EXAMPLE_RGB8
{
  unsigned char red, green, blue;
};


int main( int argc, char** argv)
{
  QApplication app( argc, argv);
  
  std::string filename = "test.ppm";
  std::cout << "Trying '" << filename << "'" << std::endl;
  std::ifstream infile( filename.c_str());
  if( !infile.is_open())
  {
    std::cout << "Could not open '" << filename << "'" << std::endl;
    filename = std::string(DATADIR) + "/" + filename;
    std::cout << "Trying '" << filename << "'" << std::endl;
    infile.open( filename.c_str());
    if( !infile.is_open())
    {
      std::cout << "Could not open '" << filename << "', exiting" << std::endl;
      std::exit(1);
    }
  }
  
  std::string magic;
  int width, height, maxvalue;
  infile >> magic 
         >> _eatWsAndComments >> width 
         >> _eatWsAndComments >> height
         >> _eatWsAndComments >> maxvalue;
  char dummyChar;
  infile.get(dummyChar);

  int imagesize =  width * height;
  unsigned char* image = new unsigned char[imagesize*3];
  infile.read( reinterpret_cast<char*>(image), imagesize*3);
 
  /*---------------------------------------------------------------------
   *  Create a pixel converter object
   *---------------------------------------------------------------------*/
  RGB_RGBConverter conv;
    
  /*---------------------------------------------------------------------
   *  Create a FastImageDisplayWidget
   *---------------------------------------------------------------------*/
  FastImageDisplayWid fidw;
  fidw.setImageSize( width, height);
  fidw.show();
 
  /*---------------------------------------------------------------------
   *  Run our own main loop for Qt
   *---------------------------------------------------------------------*/
  int frames = 0;
  timespec prev, now, dt;
  clock_gettime( CLOCK_MONOTONIC, &prev);
  
  while( fidw.isVisible())
  {
    /*-------------------------------------------------------------------
     *  process image
     *-------------------------------------------------------------------*/
    EXAMPLE_RGB8* p = reinterpret_cast<EXAMPLE_RGB8*>( image);
    for( int i = 0; i < imagesize; ++i)
    {
      p->red -= 2;
      p->green -= 2;
      p->blue -= 2;
      ++p;
    }
    /*-------------------------------------------------------------------
     *  display image
     *-------------------------------------------------------------------*/
    fidw.setImagePerLine( image, conv);
      
    /*-------------------------------------------------------------------
     *  process Qt Events for at least 1 ms
     *-------------------------------------------------------------------*/
    app.processEvents();

    /*-------------------------------------------------------------------
     *  Display frames per second
     *-------------------------------------------------------------------*/
    ++frames;
    clock_gettime( CLOCK_MONOTONIC, &now);
    //dt = diff( prev, now);
    timespec_subtract( &dt, &now, &prev);
    if( dt.tv_sec > 2 )
    {
      fprintf( stderr, "frames per second = %f\n",
               frames / (dt.tv_sec + 1e-9*dt.tv_nsec));
      frames = 0;
      prev = now;
    }
  }
  
  delete[] image;
  
  return 0;
}
