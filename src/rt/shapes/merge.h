/* PROJECT     : tp5-rt 
 * FILE NAME   : merge.h
 * PROGRAMMER  : Tim Peterson
 * LAST UPDATE : 16.07.2025
 * PURPOSE     : Merge CSG defenition file.
 * LICENSE     : MIT License
 */

#ifndef __merge_h_
#define __merge_h_

#include "shape.h"

/* Base project namespace */
namespace tp5
{
  /* Constructive solid geometry operations namespace */
  namespace csg
  {
    /* Box shape representation class */
    class merge : public shape
    {
    private:
      shape *ShpA, *ShpB; // Shapes
    public:
      /* 'merge' class constructor function.
       * ARGUMENTS:
       *   - shapes fo operation:
       *       shape *S1, *S2;
       */
      merge( shape *S1, shape *S2 ) : shape(), ShpA(S1), ShpB(S2)
      {
      } /* End of 'merge' function */

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
          if (!ShpB->IsInside(in.P))
            if (t_best == -1 || (in.T > 0 && in.T < t_best))
            {
              t_best = in.T;
              in_best = in;
            }
        }

        for (auto &in : IL2)
        {
          if (!ShpA->IsInside(in.P))
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
    }; /* End of 'merge' class */
  } /* end of 'csg' namespace */
} /* end of 'tp5' namespace */

#endif /* __merge_h_ */

/* END OF 'merge.h' FILE */
