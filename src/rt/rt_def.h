/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : rt_def.h
 * PURPOSE     : Raytracing project.
 *               Ray tracing default defenitions header file.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __rt_def_h_
#define __rt_def_h_

#include <functional>

#include "def.h"
#include "mods/mods.h"

/* Base project namespace */
namespace tp5
{
  /* distance trashold */
  const double Trashold = 0.001;

  /* Forwrd declaration of shape class */
  class shape;

  /* Forward declaration of material struct */
  struct material;

  /* Intersection for ray tracing representation type */
  class intr
  {
  public:
    double T;    // Distance from ray origin
    shape *Shp;  // Intersected shape
    vec3   P;    // Intersection point
    vec3   N;    // Intersection normal
    int I[5];    // Additional integer data

    enum ENTER_TYPE
    {
      ENTER,     // Ray entered shape after this intersection
      LEAVE,     // Ray left    shape after this intersection
    } EnterFlag; // Intersection entering type

    /* Default intr cconstructor function */
    intr( void ) : T {}, Shp {}, P {}, N {}, I {}, EnterFlag {}
    {
    } /* End of 'intr' function */

    /* intr constructor function.
     * ARGUMENTS:
     *   - distance from ray origin:
     *       double Rt;
     *   - intersected shape:
     *       shape *Shp;
     *   - intersection point:
     *       vec3 Point;
     *   - intersection normal:
     *       vec3 Normal;
     */
    intr( double Rt, shape *Shape, vec3 Point, vec3 Normal ) : T(Rt), Shp(Shape), P(Point), N(Normal), I {}, EnterFlag {}
    {
    } /* End of 'intr' function */
  }; /* End of 'intr' class */

  /* Stock of intersetions representation type */
  typedef stock<intr> intr_list;
} /* end of 'tp5' namespace */

#endif /* __rt_def_h_ */

/* END OF 'rt_def.h' FILE */
