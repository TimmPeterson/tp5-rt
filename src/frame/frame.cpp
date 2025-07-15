#include "frame.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "lib/stb_image_write.h"

namespace tp5
{

frame::frame( int W, int H ) : width(W), height(H), pixels(nullptr)
{
  pixels = new dword[W * H];
}

void frame::Resize( int NewW, int NewH )
{
  const std::lock_guard<std::recursive_mutex> lock(frame_mutex);

  if (pixels != nullptr)
    delete[] pixels;
  pixels = nullptr;
  width = height = 0;
  if (NewW != 0 && NewH != 0)
  {
    pixels = new dword[NewW * NewH];
    memset(pixels, 0, NewW * NewH * 4);
    width = NewW;
    height = NewH;
  }
}

void frame::PutPixel( int X, int Y, dword Color )
{
  const std::lock_guard<std::recursive_mutex> lock(frame_mutex);

  if (X < 0 || Y < 0 || X >= width || Y >= height)
    return;
  pixels[X + Y * width] = Color;
}

dword frame::GetPixel( int X, int Y ) const
{
  const std::lock_guard<std::recursive_mutex> lock(frame_mutex);

  if (X < 0 || Y < 0 || X >= width || Y >= height)
    return 0;
  return pixels[X + Y * width];
}

void frame::Clear( dword Color )
{
  const std::lock_guard<std::recursive_mutex> lock(frame_mutex);

  int i = width * height;
  dword *p = pixels;
  if (p == 0)
    return;
  while (i-- > 0)
    *p++ = Color;
}

void frame::Clear( void )
{
  const std::lock_guard<std::recursive_mutex> lock(frame_mutex);
  memset(pixels, 0, width * height * 4);
}

dword frame::RGBA( byte R, byte G, byte B, byte A )
{
  return (R << 24) | (G << 16) | (B << 8) | A;
}

void frame::Save( const char *Path ) const
{
  const std::lock_guard<std::recursive_mutex> lock(frame_mutex);

  dword *pixels_c = new dword[width * height];
  memcpy(pixels_c, pixels, 4 * width * height); 
  for (int i = 0; i < width * height; ++i)
    pixels_c[i] = 
      RGBA(
        pixels_c[i] & 0xFF, 
        (pixels_c[i] >> 8) & 0xFF, 
        (pixels_c[i] >> 16) & 0xFF, 
        (pixels_c[i] >> 24) & 0xFF
      );

  stbi_write_png(Path, width, height, 4, pixels_c, 4 * width);
  delete[] pixels_c;
}

frame::~frame()
{
  delete[] pixels;
}

}