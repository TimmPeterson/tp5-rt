/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mods_def.h
 * PURPOSE     : Raytracing project.
 *               Modifier class definition header file.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mods_def_h_
#define __mods_def_h_

/* Base project namespace */
namespace tp5
{
  /* Modificators namespace */
  namespace mods
  {
    /* Modifier representation type */
    class mod
    {
    public:
      /* Information needed for modificator representation structure */
      struct mod_info
      {
        vec3 
          Kd,   // Diffuse coefficient
          P,    // Position
          N;    // Normal
      }; /* End of 'mod_info' structure */

      /* 'mod' class virtual destructor function */
      virtual ~mod( void )
      {
      }

      /* Mod apply operator function.
       * ARGUMENTS:
       *   - shade information:
       *       mod_info *Mi;
       * RETURNS:
       *   (vec3) result color.
       */
      virtual vec3 operator()( const mod_info &Mi )
      {
        return vec3(0);
      }
    };
  } /* end of 'mods' namespace */
} /* end of 'tp5' namespace */

#endif /* __mods_def_h_ */

/* END OF 'mods_def.h' FILE */
