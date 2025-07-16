/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : sphere.h
 * PURPOSE     : Raytracing project.
 *               Sphere shape class defenition header.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 23.07.2024.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __sphere_h_
#define __sphere_h_

#include "shape.h"

/* Base project namespace */
namespace tp5
{
  /* Sphere shape representation class */
  class sphere : public shape
  {
  private:
    vec3 Center;  // Sphere center
    double  Radius;  // Sphere radius
  public:
    /* 'sphere' class constructor function.
     * ARGUMENTS:
     *   - sphere center:
     *       const vec3 &C;
     *   - sphere radius:
     *       double R;
     */
    sphere( const vec3 &C, double R, material M = material()) : shape(M), Center(C), Radius(R)
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
    bool Intersect( const ray &R, intr *Intr ) override
    {
      vec3 
        a = Center - R.Org;
      double  
        oc2 = a & a,
        ok  = a & R.Dir,
        ok2 = ok * ok,
        r2  = Radius * Radius,
        h2  = r2 - (oc2 - ok2);

      Intr->Shp = this;

      if (oc2 < r2)
      {
        Intr->T = ok + sqrt(h2);
        return true;
      }
      if (ok < 0)
        return false;
      if (h2 < 0)
        return false;

      Intr->T = ok - sqrt(h2);
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
      Intr->N = (Intr->P - Center) / Radius;
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
      if (!(P - Center) - Radius < 0)
        return true;
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
      vec3 
        a = Center - R.Org;
      double
        oc2 = a & a,
        ok  = a & R.Dir,
        ok2 = ok * ok,
        r2  = Radius * Radius,
        h2  = r2 - (oc2 - ok2), t;
      int n = 0;

      if (h2 < 0)
        return 0;
      t = ok + sqrt(h2);
      if (t > 0)
      {
        IL << intr(t, this, R(t), vec3(0));
        n++;
      }

      t = ok - sqrt(h2);
      if (t > 0)
      {
        IL << intr(t, this, R(t), vec3(0));
        n++;
      }
      return n;
    } /* End of 'AllIntersections' function */
  }; /* End of 'sphere' class */
} /* end of 'tp5' namespace */

#endif /* __sphere_h_ */

/* END OF 'sphere.h' FILE */
