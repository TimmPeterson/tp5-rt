/* PROJECT     : tp5-rt 
 * FILE NAME   : box.h
 * PROGRAMMER  : Tim Peterson
 * LAST UPDATE : 16.07.2025
 * PURPOSE     : Box shape defenition file.
 * LICENSE     : MIT License
 */

#ifndef __box_h_
#define __box_h_

#include "shape.h"

/* Base project namespace */
namespace tp5
{
  /* Box shape representation class */
  class box : public shape
  {
  private:
    vec3 P0, P1; // Bound box vectors

  public:
    /* 'box' class constructor function.
     * ARGUMENTS:
     *   - point on plane:
     *       const vec3 &P;
     *   - plane normal:
     *       const vec3 &N;
     */
    box( const vec3 &P00, const vec3 &P11, const material &M = material() ) : shape(M), P0(P00), P1(P11)
    {
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
      static vec3 normals[6] =
      {
        vec3(-1, 0, 0), vec3(1, 0, 0),
        vec3(0, -1, 0), vec3(0, 1, 0),
        vec3(0, 0, -1), vec3(0, 0, 1),
      };
      vec3 points[6] =
      {
        vec3(P0.X, 0, 0), vec3(P1.X, 0, 0),
        vec3(0, P0.Y, 0), vec3(0, P1.Y, 0),
        vec3(0, 0, P0.Z), vec3(0, 0, P1.Z),
      };
      double t_best = -1;
      vec3 n_best;

      for (int i = 0; i < 6; i++)
      {
        double dp = normals[i] & R.Dir, t = 0;

        if (std::abs(dp) < Trashold)
          continue;
      
        double T = (normals[i] & (points[i] - R.Org)) / dp;
        vec3 I = R(T);
        if (I.X > P0.X - Trashold && I.X < P1.X + Trashold && I.Y > P0.Y - Trashold && I.Y < P1.Y + Trashold && I.Z > P0.Z - Trashold && I.Z < P1.Z + Trashold)
        {
          if (t_best == -1 || T < t_best)
            t_best = T, n_best = normals[i];
        }
      }
      if (t_best == -1)
        return false;
      else
      {
        Intr->T = t_best;
        Intr->N = n_best;
        Intr->Shp = this;
        return true;
      }
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
      if (P.X < P0.X || P.X > P1.X || P.Y < P0.Y || P.Y > P1.Y || P.Z < P0.Z || P.Z > P1.Z)
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
      static vec3 normals[6] =
      {
        vec3(-1, 0, 0), vec3(1, 0, 0),
        vec3(0, -1, 0), vec3(0, 1, 0),
        vec3(0, 0, -1), vec3(0, 0, 1),
      };
      vec3 points[6] =
      {
        vec3(P0.X, 0, 0), vec3(P1.X, 0, 0),
        vec3(0, P0.Y, 0), vec3(0, P1.Y, 0),
        vec3(0, 0, P0.Z), vec3(0, 0, P1.Z),
      };
      double t_best = -1;
      vec3 n_best;
      int n = 0;

      for (int i = 0; i < 6; i++)
      {
        double dp = normals[i] & R.Dir, t = 0;

        if (std::abs(dp) < Trashold)
          continue;
      
        double T = (normals[i] & (points[i] - R.Org)) / dp;
        vec3 I = R(T);
        if (I.X > P0.X - Trashold && I.X < P1.X + Trashold && I.Y > P0.Y - Trashold && I.Y < P1.Y + Trashold && I.Z > P0.Z - Trashold && I.Z < P1.Z + Trashold)
          IL << intr(T, this, R(T), normals[i]), n++;
      }
      return n;
    } /* End of 'AllIntersections' function */
  }; /* End of 'box' class */
} /* end of 'tp5' namespace */

#endif /* __box_h_ */

/* END OF 'box.h' FILE */
