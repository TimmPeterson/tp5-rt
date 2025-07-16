/* PROJECT     : tp5-rt 
 * FILE NAME   : obj.h
 * PROGRAMMER  : Tim Peterson
 * LAST UPDATE : 16.07.2025
 * PURPOSE     : Obj model shape defenition file.
 * LICENSE     : MIT License
 */

#ifndef __obj_h_
#define __obj_h_

#include <cstdio>
#include <fstream>

#include "shape.h"
#include "triangle.h"

/* Base project namespace */
namespace tp5
{
  /* Box shape representation class */
  class obj : public shape
  {
  private:
    stock<triangle *> Tris;

    struct vertex
    {
      vec3 P;
      vec3 N;
      int NoofN;
      vertex( vec3 Po, vec3 No = vec3(0), int Num = 0) : P(Po), N(No), NoofN(Num)
      {
      }
    };

  public:
    /* 'obj' class constructor function.
     * ARGUMENTS:
     *   - point on plane:
     *       const vec3 &P;
     *   - plane normal:
     *       const vec3 &N;
     */
    obj( const char *FileName, const material &M = material() ) : shape(M)
    {
      
      stock<vertex> vertexes;
      stock<int>    indicies;
      static char line[1000] = "";
      std::ifstream f(FileName, std::ios::in);
      
      while (!f.eof())
      {
        f.getline(line, 1000);

        if (line[0] == 'v' && line[1] != 'n')
        {
          double x, y, z;
          
          std::sscanf(line + 2, "%lf %lf %lf", &x, &y, &z);
          vertexes << vertex(vec3(x, y, z));
        }
        else if (line[0] == 'f')
        {
          int v1, vn1, v2, vn2, v3, vn3;
          std::sscanf(line + 2, "%d//%d %d//%d %d//%d", &v1, &vn1, &v2, &vn2, &v3, &vn3);
          vec3 P0 = vertexes[v1 - 1].P, P1 = vertexes[v2 - 1].P, P2 = vertexes[v3 - 1].P;
          vec3 N = ((P1 - P0) % (P2 - P0)).Normalizing();

          vertexes[v1].N += N;
          vertexes[v2].N += N;
          vertexes[v3].N += N;
          indicies << v1 - 1 << v2 - 1 << v3 - 1;
          Tris << new triangle(P0, P1, P2, M);
        }
      }
      for (int i = 0; i < indicies.size(); i += 3)
      {
        int v1 = indicies[i], v2 = indicies[i + 1], v3 = indicies[i + 2];
        vec3 P0 = vertexes[v1].P, P1 = vertexes[v2].P, P2 = vertexes[v3].P;
        vec3 N = ((P1 - P0) % (P2 - P0)).Normalizing();
        //Tris << new triangle(vertexes[v1].P, vertexes[v2].P, vertexes[v3].P, N, vertexes[v1].N.Normalizing(), vertexes[v2].N.Normalizing(), vertexes[v3].N.Normalizing(), M);
      }
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
      double T = -1;
      intr in, best;

      for (auto Tri : Tris)
      {
        if (Tri->Intersect(R, &in))
          if (T == -1 || in.T < T)
              T = in.T, best = in;
      }

      if (T == -1)
        return false;
      best.Shp = this;
      *Intr = best;
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

    /* Check if point is inside shape function.
     * ARGUMENTS:
     *   - point to check:
     *       const vec3 &P;
     * RETURNS:
     *   (bool) true if is inside, false, otherwise
     */
    bool IsInside( const vec3 &P ) override
    {
      intr in, best;
      int n = 0;
      ray r = ray(P, vec3(0, 0, 1));

      for (auto Tri : Tris)
      {
        if (Tri->Intersect(r, &in))
          n++;
      }
      if (n % 2 == 0)
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
      double T = -1;
      intr in, best;
      int n = 0;

      for (auto Tri : Tris)
      {
        if (Tri->Intersect(R, &in))
        {
          in.P   = R(in.T);
          IL << in, n++;
        }
      }
      return n;
    } /* End of 'AllIntersections' function */

    /* Get bound box vectors of mash function. 
     * ARGUMENTS:
     *   - vector references:
     *       vec3 &B0, vec3 &B1;
     * RETURNS: None.
     */
    void GetBoundBox( vec3 &B0, vec3 &B1 )
    {
      B0 = B1 = vec3(Tris[0]->P0.X, Tris[0]->P0.Y, Tris[0]->P0.Z);
      for (auto tri : Tris)
      {
        if (tri->P0.X > B1.X)
          B1.X = tri->P0.X;
        if (tri->P1.X > B1.X)
          B1.X = tri->P1.X;
        if (tri->P2.X > B1.X)
          B1.X = tri->P2.X;
        if (tri->P0.X < B0.X)
          B0.X = tri->P0.X;
        if (tri->P1.X < B0.X)
          B0.X = tri->P1.X;
        if (tri->P2.X < B0.X)
          B0.X = tri->P2.X;

        if (tri->P0.Y > B1.Y)
          B1.Y = tri->P0.Y;
        if (tri->P1.Y > B1.Y)
          B1.Y = tri->P1.Y;
        if (tri->P2.Y > B1.Y)
          B1.Y = tri->P2.Y;
        if (tri->P0.Y < B0.Y)
          B0.Y = tri->P0.Y;
        if (tri->P1.Y < B0.Y)
          B0.Y = tri->P1.Y;
        if (tri->P2.Y < B0.Y)
          B0.Y = tri->P2.Y;

        if (tri->P0.Z > B1.Z)
          B1.Z = tri->P0.Z;
        if (tri->P1.Z > B1.Z)
          B1.Z = tri->P1.Z;
        if (tri->P2.Z > B1.Z)
          B1.Z = tri->P2.Z;
        if (tri->P0.Z < B0.Z)
          B0.Z = tri->P0.Z;
        if (tri->P1.Z < B0.Z)
          B0.Z = tri->P1.Z;
        if (tri->P2.Z < B0.Z)
          B0.Z = tri->P2.Z;
      }
    } /* End of 'GetBoundBox' function */
  }; /* End of 'obj' class */
} /* end of 'tp5' namespace */

#endif /* __obj_h_ */

/* END OF 'obj.h' FILE */
