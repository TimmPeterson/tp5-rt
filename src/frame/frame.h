#ifndef __frame_h_
#define __frame_h_

#include <cstring>
#include <cstdint>
#include <mutex>

#include "win/win.h"

namespace tp5 
{

class scene;

class frame
{
  friend class window;
  friend class scene;
private:
  int width, height;
  dword *pixels;

  mutable std::recursive_mutex frame_mutex;
public:
  frame( int W, int H );

  void Resize( int NewW, int NewH );

  void PutPixel( int X, int Y, dword Color );

  dword GetPixel( int X, int Y ) const;

  void Clear( dword Color );

  void Clear( void );

  static dword RGBA( byte R, byte G, byte B, byte A = 0xFF );

  void Save( const char *Path ) const;
  
  ~frame();
};

}

#endif /* __frame_h_ */