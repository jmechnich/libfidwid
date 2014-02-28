/**************************************************************************
**       Title: test FastImageDisplayWidget
**    $RCSfile: testFidWid.cc,v $
**   $Revision: 1.4 $$Name:  $
**       $Date: 2005/06/21 11:21:46 $
**   Copyright: GPL $Author: emmenlau $
** Description:
**
**    
**
**-------------------------------------------------------------------------
**
**  $Log: testFidWid.cc,v $
**  Revision 1.4  2005/06/21 11:21:46  emmenlau
**   - changed cast: new unsigned char[imagesize*3] (gcc-4.0 compliant)
**
**  Revision 1.3  2005/02/27 23:09:59  mechnich
**  re-added old X11 widget
**
**  Revision 1.2  2004/07/26 15:20:18  mechnich
**  added OpenGL display widgets and tests
**
**  Revision 1.1.1.1  2003/01/23 12:30:31  ronneber
**  initial revision
**
**  Revision 1.1  2002/01/10 17:50:17  ronneber
**  initial revision
**
**
**
**************************************************************************/

#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#include <qapplication.h>
#include <qobject.h>
#include <PixelConverter.hh>

#ifdef WIDGETTYPE
#include <FastImageDisplayWid_Templ.hh>
#include <X11FidWidget.hh>
#include <OpenGLFidWidget.hh>
typedef FastImageDisplayWid_Templ<WIDGETTYPE> FastImageDisplayWid;
#else
#include <FastImageDisplayWid.hh>
#endif

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

  clock_t start_time = clock();
  
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
    float elapsed_time = (float)(clock() - start_time) / CLOCKS_PER_SEC;
    if( elapsed_time > 1 )
    {
      cout << "frames per second = " << (float)frames / elapsed_time
           << endl;
      frames = 0;
      start_time = clock();
    }
  }
    
  return 0;
}
