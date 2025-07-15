/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : rt_def.h
 * PURPOSE     : Raytracing project.
 *               Ray tracing default defenitions header file.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __rt_def_h_
#define __rt_def_h_

#include <functional>

#include "def.h"
#include "img/img.h"
#include "mods/mods.h"

/* Base project namespace */
namespace tp5
{
  /* distance trashold */
  const double Trashold = 0.001;

  /* Forwrd declaration of shape class */
  class shape;

  /* Intersection for ray tracing representation type */
  class intr
  {
  public:
    double   T;     // Distance from ray origin
    shape *Shp;  // Intersected shape
    vec3  P;     // Intersection point
    vec3  N;     // Intersection normal
    int I[5];    // Additional integer data

    enum ENTER_TYPE
    {
      ENTER, // Ray entered shape after this intersection
      LEAVE, // Ray left    shape after this intersection
    } EnterFlag; // Intersection entering type

    /* Default intr cconstructor function */
    intr( void ) : T {}, Shp {}, P {}, N {}, I {}, EnterFlag {}
    {
    } /* End of 'intr' function */

    /* intr constructor function.
     * ARGUMENTS:
     *   - distance from ray origin:
     *       double Rt;
     *   - intersected shape:
     *       shape *Shp;
     *   - intersection point:
     *       vec3 Point;
     *   - intersection normal:
     *       vec3 Normal;
     */
    intr( double Rt, shape *Shape, vec3 Point, vec3 Normal ) : T(Rt), Shp(Shape), P(Point), N(Normal), I {}, EnterFlag {}
    {
    } /* End of 'intr' function */
  }; /* End of 'intr' class */

  /* Stock of intersetions representation type */
  typedef stock<intr> intr_list;

  /* Material representation structure */
  struct material
  {
  public:
    vec3 
      Ka,             // Ambient
      Kd,             // Diffuse
      Ks,             // Specular
      Kr,             // Reflect
      Kt;             // Refract
    double 
      Ph;             // Phong
    double 
      RefractionCoef;
    double
      Matte;          // Matteness
    int UsefullData;

    /* 'material' structure constructor function */
    material( const vec3 &A = vec3(0), const vec3 &D = vec3(0, 0.7, 0.7), const vec3 &S = vec3(0.5), double P = 90, const vec3 &R = vec3(0.5), const vec3 &T = vec3(0), double Refr = 1.1, double M = 0. ) :
      Ka(A), Kd(D), Ks(S), Ph(P), UsefullData(0), Kr(R), Kt(T), RefractionCoef(Refr), Matte(M)
    {
    } /* End of 'material' function */
  }; /* End of 'material' structure */

  /* Shape for ray tracing representation type */
  class shape
  {
  public:
    material Mtl;         // shape material
    stock<mods::mod *> Mods; // mods stock

    /* 'shape' class constructor by material.
     * ARGUMENTS:
     *   - material:
     *       const material &M;
     */
    shape( const material &M = material()) : Mtl(M), Mods {}
    {
    } /* End of 'shape' function */

    /* 'shape' class virtual destructor function */
    virtual ~shape( void )
    {
    } /* End of '~shape' function */

    /* Shape intersect virtual function.
     * ARGUMENTS:
     *   - ray to intersect with:
     *       const ray &R;
     *   - intersection structure:
     *       intr *Intr;
     * RETURNS:
     *   (bool) true if intersected, false otherwise.
     */
    virtual bool Intersect( const ray &R, intr *Intr )
    {
      return false;
    } /* End of 'Intersect' function */

    /* Get normal at intersection virtual function.
     * ARGUMENTS:
     *   - intersection:
     *       intr *Intr;
     * RETURNS: None.
     */
    virtual void GetNormal( intr *Intr )
    {
    } /* End of 'GetNormal' function */

    /* Check if point is inside the shape function. 
     * ARGUMENTS:
     *   - point to check:
     *       const vec3 &P;
     * RETURNS:
     *   (bool) true if is inside, false otherwise.
     */
    virtual bool IsInside( const vec3 &P )
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
    virtual int AllIntersections( const ray &R, intr_list &IL ) 
    {
      return 0;
    } /* End of 'AllIntersections' function */

    /* Get local shape color function.
     * ARGUMENTS:
     *   - intersection properties:
     *       intr *Intr;
     * RETURNS:
     *   (vec3) result color.
     */
    virtual vec3 Color( intr *Intr )
    {
      vec3 col = Mtl.Kd;
      for (auto mod : Mods)
      {
        col = (*mod)(mods::mod::mod_info{col, Intr->P, Intr->N});
      }
      return col;
    } /* End of 'Color' function */

    /* Apply modifier operator function.
     * ARGUMENTS:
     *   - modifier:
     *       modifier Mod;
     */
    shape & operator<<( mods::mod *Mod )
    {
      Mods << Mod;
      return *this;
    } /* End of 'operator<<' function */
  }; /* End of 'shape' class */
} /* end of 'tp5' namespace */

#endif /* __rt_def_h_ */

/* END OF 'rt_def.h' FILE */
