/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : img.h
 * PURPOSE     : Raytracing project.
 *               Light source class defenition header file.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __img_h_
#define __img_h_

#include <fstream>

#include "def.h"

/* Base project namespace */
namespace tp5
{
  /* g32 image representation type */
  class img
  {
  private:
    dword *Bits;
  public:
    int W, H;
    img() : Bits(nullptr), W(0), H(0)
    {
    }

    /* Img constructor by name */
    img( const char *FileName )
    {
      std::fstream f(FileName, std::fstream::in | std::fstream::binary);
      f.read((char *)&W, 2);
      f.read((char *)&H, 2);
      Bits = new dword[W * H];
      f.read((char *)Bits, W * H * sizeof(dword));
      f.close();
    } /* End of 'img' constructor */

    /* Img detructor */
    ~img( void )
    {
      delete[] Bits;
    } /* End of '~img' function */

    /* Get single pixel color by coords function. */
    dword GetPixel( int X, int Y )
    {
      if (X < 0 || Y < 0 || X >= W || Y >= H)
        return 0;
      return Bits[X + Y * W];
    } /* End of '' function */

    /* Convert dword value to rgb vector function. 
     * ARGUMENTS:
     *   - dword RGB;
     * RETURNS:
     *   (vec3) result vector.
     */
    static vec3 ToVec3( dword RGB )
    {
      return vec3((RGB >> 16) & 0xFF, (RGB >> 8) & 0xFF, RGB & 0xFF) / 255.0;
    } /* End of 'ToVec3' function */

    /* Convert float point 0..1 range color to dword function.
     * ARGUMENTS:
     *   - color RGB values:
     *       double R, G, B;
     * RETURNS:
     *   (dword) result packed color.
     */
    static dword ToRGB( const vec3 &V )
    {
      float R = V.X, G = V.Y, B = V.Z;

      auto clamp =
        []( float Value ) -> byte
        {
          if (Value < 0)
            return 0;
          if (Value > 1)
            return 255;
          return Value * 255;
        };
      return (clamp(R) << 16) | (clamp(G) << 8) | clamp(B);
    } /* End of 'ToRGB' function */

    /* Apply mono channel filter function */
    img * ApplyMono( void )
    {
      for (int i = 0; i < W * H; i++)
        Bits[i] = ToRGB(vec3(max(max(ToVec3(Bits[i]).X, ToVec3(Bits[i]).Y), ToVec3(Bits[i]).Z)));
      return this;
    } /* End of 'ApplyMono' function */
  }; /* End of 'img' class */
} /* end of 'tp5' namespace */

#endif /* __img_h_ */

/* END OF 'img.h' FILE */
