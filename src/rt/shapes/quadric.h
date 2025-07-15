/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : quadric.h
 * PURPOSE     : Raytracing project.
 *               Quadric shape class defenition header.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 23.07.2024.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __quadric_h_
#define __quadric_h_

#include "rt/rt_def.h"

/* Base project namespace */
namespace tp5
{
  /* Sphere shape representation class */
  class quadric : public shape
  {
  private:
    double 
      A, B, C, D, E, 
      F, G, H, I, J; // Matrix weights

  public:
    /* 'quadric' class constructor function.
     * ARGUMENTS:
     *   - matrix weights:
     *       double A0, B0, C0, D0, E0,
     *           F0, G0, H0, I0, J0;
     *   - material:
     *       const material &M;
     */
    quadric( double A0, double B0, double C0, double D0, double E0,
             double F0, double G0, double H0, double I0, double J0, const material &M = material() ) : 
      shape(M),
      A(A0), B(B0), C(C0), D(D0), E(E0),
      F(F0), G(G0), H(H0), I(I0), J(J0)
    {
    } /* End of 'quadric' function */

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
      double 
        a = A * R.Dir.X * R.Dir.X + 2 * B * R.Dir.X * R.Dir.Y + R.Dir.X * R.Dir.Z * 2 * C +
              R.Dir.Y * R.Dir.Y * E + R.Dir.Y * R.Dir.Z * 2 * F + H * R.Dir.Z * R.Dir.Z,
        b = 2 * (A * R.Org.X * R.Dir.X + B * (R.Org.X * R.Dir.Y + R.Dir.X * R.Org.Y) + C * (R.Org.X * R.Dir.Z + R.Dir.X * R.Org.Z) +
            D * R.Dir.X + E * R.Org.Y * R.Dir.Y + F * (R.Org.Y * R.Dir.Z + R.Dir.Y * R.Org.Z) + G * R.Dir.Y +
            H * R.Org.Z * R.Dir.Z + I * R.Dir.Z),
        c = A * R.Org.X * R.Org.X + 2 * B * R.Org.X * R.Org.Y + 2 * C * R.Org.X * R.Org.Z + 2 * D * R.Org.X +
            E * R.Org.Y * R.Org.Y + 2 * F * R.Org.Y * R.Org.Z + 2 * G * R.Org.Y +
            H * R.Org.Z * R.Org.Z + 2 * I * R.Org.Z + J;
      if (b * b - 4 * a * c < 0)
        return false;
      double
        t0 = (-b - sqrt(b * b - 4 * a * c)) / (2.0 * a),
        t1 = (-b + sqrt(b * b - 4 * a * c)) / (2.0 * a);
      if (t0 < 0 && t1 < 0)
        return false;
      Intr->T = min(max(t0, 0), max(t1, 0));
      Intr->Shp = this;
      return true;
    } /* End of 'Intersect' function */

    /* Get normal at intersection virtual function.
     * ARGUMENTS:
     *   - intersection:
     *       intr *Intr;
     * RETURNS: None.
     */
    void GetNormal( intr *Intr ) override
    {
      Intr->N = vec3(2 * A * Intr->P.X + 2 * B * Intr->P.Y + 2 * C * Intr->P.Z + 2 * D,
                     2 * E * Intr->P.Y + 2 * F * Intr->P.Z + 2 * G + 2 * B * Intr->P.X,
                     2 * H * Intr->P.Z + 2 * I + 2 * C * Intr->P.X + 2 * F * Intr->P.Y);
    } /* End of 'GetNormal' function */
  }; /* End of 'quadric' class */
} /* end of 'tp5' namespace */

#endif /* __quadric_h_ */

/* END OF 'quadric.h' FILE */
