#ifndef __shape_h_
#define __shape_h_

#include "rt/rt_mtl.h"

namespace tp5
{
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

#endif /* __shape_h_ */

/* END OF 'shape.h' FILE */