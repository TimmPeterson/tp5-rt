/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : bound.h
 * PURPOSE     : Raytracing project.
 *               Bound shape class defenition header.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 23.07.2024.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __bound_h_
#define __bound_h_

#include "shape.h"

/* Base project namespace */
namespace tp5
{
  /* Box shape representation class */
  class bound : public shape
  {
  private:
    shape 
      *Shape, // Base shape
      *Bound; // Bound shape
  public:
    /* 'bound' class constructor function.
      * ARGUMENTS:
      *   - shapes fo operation:
      *       shape *S1, *S2;
      */
    bound( shape *S, shape *B ) : shape(), Shape(S), Bound(B)
    {
    } /* End of 'bound' function */

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
      if (Bound->Intersect(R, Intr))
        return Shape->Intersect(R, Intr);
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

    /* Check if point is inside shape function.
     * ARGUMENTS:
     *   - point to check:
     *       const vec3 &P;
     * RETURNS:
     *   (bool) true if is inside, false, otherwise
     */
    bool IsInside( const vec3 &P ) override
    {
      return Shape->IsInside(P);
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
      intr in;
      if (!Bound->Intersect(R, &in))
        return 0;

      return Shape->AllIntersections(R, IL);
    } /* End of 'AllIntersections' function */
  }; /* End of 'bound' class */
} /* end of 'tp5' namespace */

#endif /* __bound_h_ */

/* END OF 'bound.h' FILE */
