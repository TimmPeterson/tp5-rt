/* PROJECT     : tp5-rt 
 * FILE NAME   : bound.h
 * PROGRAMMER  : Tim Peterson
 * LAST UPDATE : 16.07.2025
 * PURPOSE     : Bound shape defenition file.
 * LICENSE     : MIT License
 */

#ifndef __mods_def_h_
#define __mods_def_h_

#include "def.h"

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
