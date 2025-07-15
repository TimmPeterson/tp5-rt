/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : triangle.h
 * PURPOSE     : Raytracing project.
 *               Subtraction csg operation class defenition header.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 23.07.2024.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __intersection_h_
#define __intersection_h_

#include "rt/rt_def.h"

/* Base project namespace */
namespace tp5
{
  /* Constructive solid geometry operations namespace */
  namespace csg
  {
    /* Box shape representation class */
    class intersection : public shape
    {
    private:
      shape *ShpA, *ShpB; // Shapes
    public:
      /* 'intersection' class constructor function.
       * ARGUMENTS:
       *   - shapes fo operation:
       *       shape *S1, *S2;
       */
      intersection( shape *S1, shape *S2 ) : shape(), ShpA(S1), ShpB(S2)
      {
      } /* End of 'intersection' function */

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
        intr_list IL1, IL2;
        int n1, n2;
        double t_best = -1;
        intr in_best;

        n1 = ShpA->AllIntersections(R, IL1);
        n2 = ShpB->AllIntersections(R, IL2);

        for (auto &in : IL1)
        {
          if (ShpB->IsInside(in.P))
            if (t_best == -1 || (in.T > 0 && in.T < t_best))
            {
              t_best = in.T;
              in_best = in;
            }
        }

        for (auto &in : IL2)
        {
          if (ShpA->IsInside(in.P))
            if (t_best == -1 || (in.T > 0 && in.T < t_best))
            {
              t_best = in.T;
              in_best = in;
              in_best.I[0] = 1;
            }
        }

        if (t_best == -1 || t_best < 0)
          return false;
        *Intr = in_best;
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
      } /* End of 'GetNormal' function */
    }; /* End of 'intersection' class */
  } /* end of 'csg' namespace */
} /* end of 'tp5' namespace */

#endif /* __intersection_h_ */

/* END OF 'intersection.h' FILE */
