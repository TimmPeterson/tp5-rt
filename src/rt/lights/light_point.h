/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : light_point.h
 * PURPOSE     : Raytracing project.
 *               Point light source class defenition header file.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __light_point_h_
#define __light_point_h_

#include "rt/lights/lights_def.h"

/* Base project namespace */
namespace tp5
{
  /* Point light representation type */
  class point_light : public light
  {
  private:
    vec3 LightPoint; // Light source point
    double Smooth;
  public:
    /* 'point_light' class constructor function.
     * ARGUMENTS:
     *   - light point:
     *       const vec3 &P;
     *   - light color:
     *       const vec3 &Color;
     *   - attenuation components:
     *       double Cc, Cl, Cq;
     */
    point_light( const vec3 &P, const vec3 &Col, double C = 1, double L = 0, double Q = 0, double S = 0. ) : LightPoint(P), light(Col, C, L, Q), Smooth(S)
    {
    } /* End of 'point_light' function */

    /* Get light properties for exact point. 
     * ARGUMENTS:
     *   - point:
     *       const vec3 &P;
     *   - strcture for result information about lighting:
     *       light_info *L;
     * RETURNS:
     *   (double) some varying light result.
     */
    double Shadow( const vec3 &P, light_info *L ) override
    {
      L->Color     = Color;
      L->Direction = LightPoint - (P + vec3::RndN0() * Smooth);
      L->Dist      = !L->Direction;
      L->Direction.Normalize();
      return 1.0 / (Cc + Cl * L->Dist + Cq * L->Dist * L->Dist);
    } /* End of 'Shadow' function */
  }; /* End of 'point_light' class */
}

#endif /* __light_point_h_ */

/* END OF 'light_point.h' FILE */
