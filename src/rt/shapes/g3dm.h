/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : g3dm.h
 * PURPOSE     : Raytracing project.
 *               Box shape class defenition header.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 23.07.2024.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __g3dm_h_
#define __g3dm_h_

#include "rt/rt_def.h"
#include "triangle.h"

/* Base project namespace */
namespace tp5
{
  /* Box shape representation class */
  class g3dm : public shape
  {
  private:
    stock<triangle *> Tris;

    /* Single vertex representaiton structure */
    typedef struct tagtp5VERTEX
    {
      mth::vec3<float> P;  /* Vertex position */
      mth::vec3<float> T;  /* Vertex texture */
      mth::vec3<float> N;  /* Vertex normal */
      mth::vec3<float> C;  /* Vertex color */
    } tp5VERTEX;

  public:
    /* 'g3dm' class constructor function.
     * ARGUMENTS:
     *   - point on plane:
     *       const vec3 &P;
     *   - plane normal:
     *       const vec3 &N;
     */
    g3dm( const char *FileName ) : shape()
    {
      FILE *F;
      int flen, p, t, m;
      byte *mem, *ptr;
      dword Sign;
      dword NumOfPrims;
      dword NumOfMaterials;
      dword NumOfTextures;

      /* Open file */
      if ((F = fopen(FileName, "rb")) == NULL)
        return;

      /* Obtain file length */
      fseek(F, 0, SEEK_END);
      flen = ftell(F);
      rewind(F);

      /* Allocate memory and load whole file to memory */
      if ((mem = (byte *)malloc(flen)) == NULL)
      {
        fclose(F);
        return;
      }
      fread(mem, 1, flen, F);
      fclose(F);

      ptr = mem;
      /* Signature */
      Sign = *(dword *)ptr;
      ptr += 4;
      if (Sign != *(dword *)"G3DM")
      {
        free(mem);
        return;
      }
      NumOfPrims = *(dword *)ptr;
      ptr += 4;
      NumOfMaterials = *(dword *)ptr;
      ptr += 4;
      NumOfTextures = *(dword *)ptr;
      ptr += 4;

      /* Load primitives */
      for (p = 0; p < NumOfPrims; p++)
      {
        dword 
          NumOfVertexes,
          NumOfFacetIndexes,
          MtlNo;
        tp5VERTEX *V; /* Vertex array */
        dword *I;     /* Index array */

        NumOfVertexes = *(dword *)ptr;
        ptr += 4;

        NumOfFacetIndexes = *(dword *)ptr;
        ptr += 4;

        MtlNo = *(dword *)ptr;
        ptr += 4;

        V = (tp5VERTEX *)ptr;
        ptr += sizeof(tp5VERTEX) * NumOfVertexes;

        I = (dword *)ptr;
        ptr += sizeof(dword) * NumOfFacetIndexes;

        for (int i = 0; i < NumOfFacetIndexes; i += 3)
          Tris << new triangle(V[i].P, V[i + 1].P, V[i + 2].P);
      }

      free(mem);
      return;
    } /* End of 'g3dm' function */

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
  }; /* End of 'g3dm' class */
} /* end of 'tp5' namespace */

#endif /* __g3dm_h_ */

/* END OF 'g3dm.h' FILE */
