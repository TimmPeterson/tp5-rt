/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_camera.h
 * PURPOSE     : Raytracing project.
 *               Camera class math module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_camera_h_
#define __mth_camera_h_

#include "mth_def.h"

/* Math library namespace */
namespace mth
{
  /* Space camera handle class */
  template<typename Type>
    class camera
    {
    public:
      vec3<Type>
        Loc,            // camera location
        Dir, Up, Right, // basis camera directions
        At;             // camera pivot point    ...
      Type
        ProjDist,       // near project plane distance
        FarClip,        // far project plane distance
        Size,           // inner project plane rectangle size
        Wp, Hp;         // project plane size
      int
        FrameW, FrameH; // Camera frame size in pixels
      matr<Type>
        View,           // view matrix
        Proj,           // projection matrix
        VP;             // View and Proj matrix production
 
      /* Get ray directed from camera location to pixel:
       * ARGUMENTS:
       *   - pixel screen coordinates:
       *       Type Xs, Ys;
       * RETURNS:
       *   (ray<Type>) result ray.
       */
      ray<Type> FrameRay( Type Xs, Type Ys ) const
      {
        vec3<Type> Q =
          Dir * ProjDist +
          Right * ((Xs - FrameW / 2) * Wp / FrameW) +
          Up * ((FrameH / 2 - Ys) * Hp / FrameH);
 
        return ray(Loc + Q, Q);
      } /* End of 'FrameRay' function */

      /* camera default constructor */
      camera( void ) :
        Loc(0, 0, 5), Dir(0, 0, -1), Up(0, 1, 0), Right(1, 0, 0), At(0, 0, 0),
        ProjDist(0.1), FarClip(500), Size(0.1), FrameW(30), FrameH(30)
      {
        UpdateProj();
      } /* End of 'camera' function */
 
      /* Set camera projection properties function.
       * ARGUMENTS:
       *   - new projection size:
       *       Type NewSize;
       *   - new projection distance:
       *       Type NewProjDist;
       *   - new far clip distance:
       *       Type NewFarClip;
       * RETURNS:
       *   (camera &) self reference.
       */
      camera & SetProj( Type NewSize, Type NewProjDist, Type NewFarClip )
      {
        ProjDist = NewProjDist;
        Size = NewSize;
        FarClip = NewFarClip;
 
        UpdateProj();
        return *this;
      } /* End of 'SetProj' function */
 
      /* Resize camera properties function.
       * ARGUMENTS:
       *   - new frame size:
       *       int NewFrameW, int NewFrameH;
       * RETURNS:
       *   (camera &) self reference.
       */
      camera & Resize( int NewFrameW, int NewFrameH )
      {
        FrameW = NewFrameW;
        FrameH = NewFrameH;
 
        UpdateProj();
        return *this;
      } /* End of 'Resize' function */
 
      /* Set camera by location point, point of interest and up-looking vector function.
       * ARGUMENTS:
       *   - location:
       *       const vec3<Type> &L;
       *   - point of interest:
       *       const vec3<Type> &A;
       *   - up-looking vector:
       *       const vec3<Type> &U;
       */
      camera & SetLocAtUp( const vec3<Type> &L, const vec3<Type> &A, const vec3<Type> &U = vec3<Type>(0, 1, 0) )
      {
        Loc = L;
        At = A;
        Up = U;
 
        Dir = (At - Loc).Normalizing();
        Right = (Dir % Up).Normalizing();
        Up = Right % Dir;
 
        UpdateProj();
        return *this;
      } /* End of 'SetLocAtUp' function */
 
    private:
      /* Update projection properties of camera function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      void UpdateProj( void )
      {
        Type rx = Size / 2, ry = Size / 2;
 
        if (FrameW > FrameH)
          rx *= (Type)FrameW / FrameH;
        else
          ry *= (Type)FrameH / FrameW;
        Wp = rx * 2;
        Hp = ry * 2;
        Proj = matr<Type>::Frustum(-rx, rx, -ry, ry, ProjDist, FarClip);
      } /* End of 'UpdateProj' function */
    };
} /* end of 'mth' namespace */

#endif /* __mth_camera_h_ */

/* END OF 'camera.h' FILE */
