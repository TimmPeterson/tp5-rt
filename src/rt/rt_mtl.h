/* PROJECT     : tp5-rt 
 * FILE NAME   : rt_mtl.h
 * PROGRAMMER  : Tim Peterson
 * LAST UPDATE : 16.07.2025
 * PURPOSE     : 'material' structure defenition file.
 * LICENSE     : MIT License
 */

#ifndef __rt_mtl_h_
#define __rt_mtl_h_

#include "rt/rt_def.h"

/* Base project namespace */
namespace tp5
{
  /* Material representation structure */
  struct material
  {
  public:
    vec3 
      Ka,             // Ambient
      Kd,             // Diffuse
      Ks,             // Specular
      Kr,             // Reflect
      Kt;             // Refract
    double 
      Ph;             // Phong
    double 
      RefractionCoef;
    double
      Matte;          // Matteness
    int UsefullData;

    /* 'material' structure constructor function */
    material( 
      const vec3 &A    = vec3(0), 
      const vec3 &D    = vec3(0, 0.7, 0.7), 
      const vec3 &S    = vec3(0.5), 
      double      P    = 90.0, 
      const vec3 &R    = vec3(0.5), 
      const vec3 &T    = vec3(0), 
      double      Refr = 1.1, 
      double      M    = 0.0 
    ) :
      Ka(A), Kd(D), Ks(S), Ph(P), Kr(R), Kt(T), 
      UsefullData(0), RefractionCoef(Refr), Matte(M)
    {
    } /* End of 'material' function */
  }; /* End of 'material' structure */
} /* end of 'tp5' namespace */

#endif /* __rt_mtl_h_ */

/* END OF 'rt_mtl.h' FILE */
