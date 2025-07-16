/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_def.h
 * PURPOSE     : Raytracing project.
 *               Definitions for math module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_def_h_
#define __mth_def_h_

#include <cmath>

/* Pi math constant */
#define PI 3.14159265358979323846

/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define R2D(A) ((A) * (180.0 / PI))
#define Degree2Radian(A) D2R(A)

/* Math library namespace */
namespace mth
{
  template<typename Type> class vec2;
  template<typename Type> class vec3;
  template<typename Type> class vec4;
  template<typename Type> class matr;
  template<typename Type> class ray;
  template<typename Type> class camera;

  inline double min( double A, double B )
  {
    return A < B ? A : B;
  }

  inline double max( double A, double B )
  {
    return A > B ? A : B;
  }
  
  inline double abs( double X )
  {
    return X > 0 ? X : -X;
  }
} /* end of 'mth' namespace */
#endif /* __mth_def_h_ */

/* END OF 'mth_def.h' FILE */
