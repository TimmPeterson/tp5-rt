/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mods.h
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

#ifndef __mods_h_
#define __mods_h_

#include <functional>

#include "def.h"
#include "mods_def.h"
#include "../img/img.h"

/* Base project namespace */
namespace tp5
{
  /* Modificators namespace */
  namespace mods
  {
    /* Functional modificator representation type */
    class func : public mod
    {
    private:
      std::function<vec3(const mod_info &)> 
        Func; // Modificator func

    public:
      /* 'func' class constructor function.
       * ARGUMENTS:
       *   - modificator function:
       *       std::function<vec3(mod_info *)> F;
       */
      func( std::function<vec3(const mod_info &)> F ) : Func(F)
      {
      } /* End of 'func' function */

      /* Mod apply operator function.
       * ARGUMENTS:
       *   - shade information:
       *       mod_info *Mi;
       * RETURNS:
       *   (vec3) result color.
       */
      vec3 operator()( const mod_info &Mi )
      {
        return Func(Mi);
      } /* End of 'operator()' function */
    }; /* End of 'func' class */

    /* Checked texture modificator representation type */
    class tex : public mod
    {
    private:
      img Img;
    public:
      /* 'func' class constructor function.
       * ARGUMENTS:
       *   - modificator function:
       *       std::function<vec3(mod_info *)> F;
       */
      tex( const char *FileName ) : Img(FileName)
      {
        Img.ApplyMono();
      } /* End of 'func' function */

      /* Convert dword value to rgb vector function. 
       * ARGUMENTS:
       *   - dword RGB;
       * RETURNS:
       *   (vec3) result vector.
       */
      static vec3 ToVec3( dword RGB )
      {
        return vec3((RGB >> 16) & 0xFF, (RGB >> 8) & 0xFF, RGB & 0xFF) / 255.0;
      } /* End of 'ToVec3' function */

      /* Mod apply operator function.
       * ARGUMENTS:
       *   - shade information:
       *       mod_info *Mi;
       * RETURNS:
       *   (vec3) result color.
       */
      vec3 operator()( const mods::mod::mod_info &Mi )
      {
        vec3 Kd = Mi.Kd, P = Mi.P;
        P /= 12;
        vec3 g = -vec3(std::floor(P.X) - P.X, std::floor(P.Y + 0.5) - P.Y - 0.5, std::floor(P.Z) - P.Z) * vec3(Img.W, 0, Img.H);
        return ToVec3(Img.GetPixel((int)g.X, (int)g.Z));
      } /* End of 'operator()' function */
    }; /* End of 'tex' class */

    /* Gradient modificator representation type */
    class grad : public mod
    {
    public:
      /* Mod apply operator function.
       * ARGUMENTS:
       *   - shade information:
       *       mod_info *Mi;
       * RETURNS:
       *   (vec3) result color.
       */
      vec3 operator()( const mods::mod::mod_info &Mi )
      {
        vec3 Kd = Mi.Kd, P = Mi.P;
        P /= 5;
        vec3 g = -vec3(std::floor(P.X) - P.X, std::floor(P.Y + 0.5) - P.Y - 0.5, std::floor(P.Z) - P.Z);
        return vec3(g.X, g.Y, 1);
      } /* End of 'operator()' function */
    }; /* End of 'grad' class */

    /* Gradient modificator representation type */
    class check : public mod
    {
    private:
      vec3 C1, C2; // Check colors
    public:
      /* 'check' class constructor*/
      check( const vec3 &Color1, const vec3 &Color2 ) : C1(Color1), C2(Color2)
      {
      } /* End of 'check' funciton */

      /* Mod apply operator function.
       * ARGUMENTS:
       *   - shade information:
       *       mod_info *Mi;
       * RETURNS:
       *   (vec3) result color.
       */
      vec3 operator()( const mods::mod::mod_info &Mi )
      {
        vec3 Kd = Mi.Kd, P = Mi.P;
        if (((int(std::floor(P.X / 3)) % 2 == 0 && int(std::floor(P.Z / 3)) % 2 != 0) || (int(std::floor(P.X / 3)) % 2 != 0 && int(std::floor(P.Z / 3)) % 2 == 0)))
          return C1;
        return C2;
      } /* End of 'operator()' function */
    }; /* End of 'check' class */

    /* Normal modificator representation type */
    class norm : public mod
    {
    public:
      /* Mod apply operator function.
       * ARGUMENTS:
       *   - shade information:
       *       mod_info *Mi;
       * RETURNS:
       *   (vec3) result color.
       */
      vec3 operator()( const mods::mod::mod_info &Mi )
      {
        return Mi.N;
      } /* End of 'operator()' function */
    }; /* End of 'norm' class */
  } /* end of 'mods' namespace */
} /* end of 'tp5' namespace */

#endif /* __mods_h_ */

/* END OF 'mods.h' FILE */
