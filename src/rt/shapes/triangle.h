/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : triangle.h
 * PURPOSE     : Raytracing project.
 *               Triangle shape class defenition header.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 23.07.2024.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __triangle_h_
#define __triangle_h_

#include "shape.h"

/* Base project namespace */
namespace tp5
{
  /* Box shape representation class */
  class triangle : public shape
  {
    friend class obj;
    friend class g3dm;
  protected:
    vec3 P0, P1, P2;    // Triangle vertexes
    vec3 N, N1, N2, N3; // Normal (evaluated in constructor)
    vec3 U1, V1;        // Cashed vector for intersection evaluating
    vec3 S1, S2;        // Vertex differences
    double  U0, V0;        // Constant for intersection evaluating
    double  D;             // Constant for plane intersection
    bool Smooth;        // Use smooth normals
  public:
    /* 'triangle' class constructor function.
     * ARGUMENTS:
     *   - triangle vertexes:
     *       const vec3 &P00, &P11, &P22;
     *   - plane normal:
     *       const vec3 &N;
     */
    triangle( const vec3 &P00, const vec3 &P11, const vec3 &P22, const material &M = material() ) : shape(M), P0(P00), P1(P11), P2(P22), Smooth(false)
    {
      S1 = P1 - P0;
      S2 = P2 - P0;
      N  = (S1 % S2).Normalizing();
      D  = N & P0;
      U1 = (S1 * (S2 & S2) - S2 * (S1 & S2)) / 
           ((S1 & S1) * (S2 & S2) - (S1 & S2) * (S1 & S2));
      U0 = (P0 & U1);
      V1 = (S2 * (S1 & S1) - S1 * (S1 & S2)) / ((S1 & S1) * (S2 & S2) - (S1 & S2) * (S1 & S2));
      V0 = P0 & V1;
    } /* End of 'plane' function */

    /* 'triangle' class constructor function.
     * ARGUMENTS:
     *   - triangle vertexes:
     *       const vec3 &P00, &P11, &P22;
     *   - plane normal:
     *       const vec3 &N;
     */
    triangle( const vec3 &P00, const vec3 &P11, const vec3 &P22, const vec3 &Norm, const vec3 &Norm1, const vec3 &Norm2, const vec3 &Norm3, const material &M = material() ) : 
      shape(M), P0(P00), P1(P11), P2(P22), Smooth(true), N1(Norm1), N2(Norm2), N3(Norm3), N(Norm)
    {
      S1 = P1 - P0;
      S2 = P2 - P0;
      D  = N & P0;
      U1 = (S1 * (S2 & S2) - S2 * (S1 & S2)) / 
           ((S1 & S1) * (S2 & S2) - (S1 & S2) * (S1 & S2));
      U0 = (P0 & U1);
      V1 = (S2 * (S1 & S1) - S1 * (S1 & S2)) / ((S1 & S1) * (S2 & S2) - (S1 & S2) * (S1 & S2));
      V0 = P0 & V1;
    } /* End of 'plane' function */

    /* Shape intersect virtual function.
     * ARGUMENTS:
     *   - ray to intersect with:
     *       const ray &R;
     *   - intersection structure:
     *       intr *Intr;
     * RETURNS:
     *   (bool) true if intersected, false otherwise.
     */
    bool Intersect( const ray &R, intr *Intr ) override
    {
      double t = (N & (P1 - R.Org)) / (N & R.Dir);
      vec3 P = R(t);
      double u = (P & U1) - U0;
      double v = (P & V1) - V0;
      double w = 1 - v - u;

      if (t < 0)
        return false;
      if (u > 0 && v > 0 && u + v <= 1)
      {
        Intr->T = t;
        Intr->Shp = this;
        if (Smooth)
          Intr->N = N1 * w + N2 * u + N3 * v;
        else
          Intr->N = N;
        return true;
      }

      return false;
    } /* End of 'Intersect' function */

    /* Get normal at intersection virtual function.
     * ARGUMENTS:
     *   - intersection:
     *       intr *Intr;
     * RETURNS: None.
     */
    void GetNormal( intr *Intr ) override
    {
    } /* End of 'GetNormal' function */
  }; /* End of 'triangle' class */
} /* end of 'tp5' namespace */

#endif /* __triangle_h_ */

/* END OF 'triangle.h' FILE */
