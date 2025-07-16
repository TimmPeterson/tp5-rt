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

#ifndef __plane_h_
#define __plane_h_

#include "shape.h"

/* Base project namespace */
namespace tp5
{
  /* Sphere shape representation class */
  class plane : public shape
  {
  private:
    vec3 
      Point,  // Point on plane
      Normal; // Plane normal

  public:
    /* 'plane' class constructor function.
     * ARGUMENTS:
     *   - point on plane:
     *       const vec3 &P;
     *   - plane normal:
     *       const vec3 &N;
     */
    plane( const vec3 &P, const vec3 &N, const material &M = material()) : shape(M), Point(P), Normal(N.Normalizing())
    {
      shape::Mtl.UsefullData = 47;
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
      double dp = Normal & R.Dir, t = 0;

      if (std::abs(dp) < Trashold)
        return false;
      
      double T = (Normal & (Point - R.Org)) / dp;

      if (T > Trashold)
      {
        Intr->Shp = this;
        Intr->T   = T;
        Intr->P   = R(T);
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
      Intr->N = Normal;
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
      double dp = Normal & (P - Point);

      if (dp > 0)
        return false;
      return true;
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
      double dp = Normal & R.Dir, t = 0;

      if (std::abs(dp) < Trashold)
        return 0;
      
      double T = (Normal & (Point - R.Org)) / dp;

      if (T > Trashold)
      {
        IL << intr(T, this, R(T), Normal);
        return 1;
      }
      return 0;
    } /* End of 'AllIntersections' function */
  }; /* End of 'sphere' class */
} /* end of 'tp5' namespace */

#endif /* __plane_h_ */

/* END OF 'plane.h' FILE */
