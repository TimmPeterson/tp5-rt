/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : light.h
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

#ifndef __lights_def_h_
#define __lights_def_h_

#include "rt/rt_def.h"

/* Base project namespace */
namespace tp5
{
  /* Light information structure */
  struct light_info
  {
    vec3 Direction;   // Light source direction
    vec3 Color;       // Light source color
    double Dist;         // Distance to light source
  }; /* End of 'light_info' structure */

  /* Light source representation type */
  class light
  {
  protected:
    /* Attenuation coefficients */
    double
      Cc,             // Constant component
      Cl,             // Linear coefficient
      Cq;             // Quadratic coefficient
    vec3              
      Color;          //  Light source color
  public:
    /* 'light' class constructor function.
     * ARGUMENTS:
     *   - light color:
     *       const vec3 &Col;
     */
    light( const vec3 &Col = vec3(0), double C = 0, double L = 0, double Q = 0 ) : Color(Col), Cc(C), Cl(L), Cq(Q)
    {
    } /* End of 'light' function */

    /* Get light properties for exact point. 
     * ARGUMENTS:
     *   - point:
     *       const vec3 &P;
     *   - strcture for result information about lighting:
     *       light_info *L;
     * RETURNS:
     *   (double) some varying light result.
     */
    virtual double Shadow( const vec3 &P, light_info *L )
    {
      return 0;
    } /* End of 'Shadow' function */
  }; /* end of 'tp5' namespace */
} /* end of 'tp5' namespace */

#endif /* __lights_def_h_ */

/* END OF 'lights_def.h' FILE */
