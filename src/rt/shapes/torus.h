/* PROJECT     : tp5-rt 
 * FILE NAME   : torus.h
 * PROGRAMMER  : Tim Peterson
 * LAST UPDATE : 16.07.2025
 * PURPOSE     : Torus shape defenition file.
 * LICENSE     : MIT License
 */

#ifndef __torus_h_
#define __torus_h_

#include "mth/mth_poly.h"
#include "shape.h"

/* Base project namespace */
namespace tp5
{
  /* Sphere shape representation class */
  class torus : public shape
  {
  private:
    vec3 Center;  // Sphere center
    double  R, R0;   // Torus big and small radiuses
  public:
    /* 'sphere' class constructor function.
     * ARGUMENTS:
     *   - sphere center:
     *       const vec3 &C;
     *   - sphere radius:
     *       double R;
     */
    torus( const vec3 &C, double R1, double R01, material M = material()) : shape(M), Center(C), R(R1), R0(R01) 
    {
    } /* End of 'sphere' function */

    /* Shape intersect virtual function.
     * ARGUMENTS:
     *   - ray to intersect with:
     *       const ray &R;
     *   - intersection structure:
     *       intr *Intr;
     * RETURNS:
     *   (bool) true if intersected, false otherwise.
     */
    bool Intersect( const ray &Ray, intr *Intr ) override
    {
      double
        R2 = R * R,
        R02 = R0 * R0; 
      double 
        A = Ray.Org & Ray.Org,
        B = Ray.Org & Ray.Dir * 2.,
        C = Ray.Dir & Ray.Dir,
        D = R2 - R02,
        E = A - Ray.Org.Z * Ray.Org.Z,
        F = B - Ray.Dir.Z * Ray.Org.Z * 2.,
        G = C - Ray.Dir.Z * Ray.Dir.Z;
      double
        A_D = A + D,
        C2  = C * C,
        R42 = 4. * R2;
      double
        A0 = 2. * B / C,
        B0 = (B * B + 2. * C * A_D - R42 * G) / C2,
        C0 = (2. * B * A_D - R42 * F) / C2,
        D0 = (A_D * A_D - R42 * E) / C2;

      //mth::DComplex *x = new mth::DComplex[4];
      mth::DComplex *x = mth::poly::solveP4(A0, B0, C0, D0);

      float bestx = 10000.;
      int   besti = -1;
      bool  yes   = false;

      for (int i = 0; i < 4; i++)
      {
        if (abs(x[i].imag()) < 0.000001)
        {
          if (x[i].real() < bestx && x[i].real() > 0)
          {
            bestx = x[i].real();
            besti = i;
          }
        }
      }

      delete[] x;

      Intr->Shp = this;
      Intr->T   = bestx; 
      return besti != -1;
    } /* End of 'Intersect' function */

    /* Get normal at intersection virtual function.
     * ARGUMENTS:
     *   - intersection:
     *       intr *Intr;
     * RETURNS: None.
     */
    void GetNormal( intr *Intr ) override
    {
      Intr->N = (Intr->P - vec3(Intr->P.X, Intr->P.Y, 0).Normalizing() * R).Normalizing();
    } /* End of 'GetNormal' function */

    /* Check if point is inside shape function.
     * ARGUMENTS:
     *   - point to check:
     *       const vec3 &P;
     * RETURNS:
     *   (bool) true if is inside, false, otherwise
     */
    bool IsInside( const vec3 &P ) override
    {
      return false;
    } /* End of 'IsInside' function */

    /* Get list of all intersections with ray function.
     * ARGUMENTS:
     *   - list of all intersections:
     *       intr_list &IL;
     * RETURNS:
     *   (int) number of intersections.
     */
    int AllIntersections( const ray &R, intr_list &IL ) override
    {
      return 0;
    } /* End of 'AllIntersections' function */
  }; /* End of 'sphere' class */
} /* end of 'tp5' namespace */

#endif /* __torus_h_ */

/* END OF 'torus.h' FILE */
