/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_ray.h
 * PURPOSE     : Raytracing project.
 *               Ray class math module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_ray_h_
#define __mth_ray_h_

#include "mth_def.h"

/* Math library namespace */
namespace mth
{
  /* Ray representation type */
  template<typename Type>
    class ray
    {
    public:
      vec3<Type>
        Org, // Ray origin
        Dir; // Ray direction

      /* ray default constructor */
      ray( void )
      {
      } /* End of default ray constructor */

      /* ray constructor by two vectors.
       * ARGUMENTS:
       *   - origin:
       *       const vec3<Type> &Ro;
       *   - direction:
       *       const vec3<Type> &Rd;
       */
      ray( const vec3<Type> &Ro, const vec3<Type> &Rd ) : Org(Ro), Dir(Rd.Normalizing())
      {
      } /* End of ray constructor */

      /* Get point on vector function.
       * ARGUMENTS:
       *   - distance from origin:
       *       Type T;
       * RETURNS:
       *   (vec3<Type>) point radius vector.
       */
      vec3<Type> operator()( Type T ) const
      {
        return Org + Dir * T;
      } /* End of 'operator()' function */
    };
} /* end of 'mth' namespace */

#endif /* __mth_ray_h_ */

/* END OF 'ray.h' FILE */
