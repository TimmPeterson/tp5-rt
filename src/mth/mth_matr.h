/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_matr.h
 * PURPOSE     : Raytracing project.
 *               4x4 matrix class math module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_matr_h_
#define __mth_matr_h_

#include "mth_def.h"

#include <cstring>
#include <iostream>

namespace mth
{
  /* 4x4 matrix representation type */
  template<typename Type>
    class matr
    {
    private:
      Type A[4][4];          // Matrix components array
      mutable Type 
        Inversed[4][4];      // Inversed matrix
      mutable bool
        IsInversedEvaluated; // If inversed matrix's been evaluated

    public:
      /* Default matr constructor */
      matr( void ) : IsInversedEvaluated(false)
      {
      } /* End of default matr constructor */

      /* Percomponent matrix constructor.
       * ARGUMENTS: 
       *   - matrix elements:
       *       Type A00, A01, A02, A03,
       *            A10, A11, A12, A13,
       *            A20, A21, A22, A23,
       *            A30, A31, A32, A33;
       * RETURNS:
       *   (MATR) result matrix.
       */
      matr( Type A00, Type A01, Type A02, Type A03,
            Type A10, Type A11, Type A12, Type A13,
            Type A20, Type A21, Type A22, Type A23,
            Type A30, Type A31, Type A32, Type A33 ) :
        A {
            {A00, A01, A02, A03},
            {A10, A11, A12, A13},
            {A20, A21, A22, A23},
            {A30, A31, A32, A33},
          }, IsInversedEvaluated(false)
      {
      } /* End of 'matr' function */

      /* matr constructor by array.
       * ARGUMENTS:
       *   - array:
       *       Type Arr[4][4];
       */
      matr( Type Arr[4][4] ) : IsInversedEvaluated(false)
      {
        std::memcpy(A, Arr, 16);
      } /* End of matr constructor */

      /* Get identity matrix function. 
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) identity matrix.
       */
      static matr Identity( void )
      {
        static matr I = matr(1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1);
      
        return I;
      } /* End of 'Identity' function */

      /* Get translate matrix function
       * ARGUMENTS: 
       *   - translating vector:
       *       const vec3<Type> &T;
       * RETURNS:
       *   (matr) translate matrix.
       */
      static matr Translate( const vec3<Type> &T )
      {
        return 
          matr(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  T.X, T.Y, T.Z, 1);
      } /* End of 'MatrTranslate' function */

      /* Get scale matrix function
       * ARGUMENTS: 
       *   - scaling vector:
       *       const vec3<Type> &S;
       * RETURNS:
       *   (matr) scaling matrix.
       */
      static matr Scale( const vec3<Type> &S )
      {
        return 
          matr(S.X, 0, 0, 0,
               0, S.Y, 0, 0,
               0, 0, S.Z, 0,
               0, 0, 0, 1);
      } /* End of 'MatrScale' function */

      /* Get rotating arount the x axis matrix function
       * ARGUMENTS: 
       *   - angle:
       *       Type AngleInDegree;
       * RETURNS:
       *   (matr) rotating matrix.
       */
      static matr RotateX( Type AngleInDegree )
      {
        Type 
          a = D2R(AngleInDegree),
          c = std::cos(a),
          s = std::sin(a);
  
        return 
          matr(1, 0, 0, 0,
               0, c, s, 0,
               0, -s, c, 0,
               0, 0, 0, 1);
      } /* End of 'RotateX' function */

      /* Get rotating arount the y axis matrix function
       * ARGUMENTS: 
       *   - angle:
       *       Type AngleInDegree;
       * RETURNS:
       *   (matr) rotating matrix.
       */
      static matr RotateY( Type AngleInDegree )
      {
        Type
          a = D2R(AngleInDegree),
          c = std::cos(a),
          s = std::sin(a);
  
        return 
          matr(c, 0, -s, 0,
               0, 1, 0, 0,
               s, 0, c, 0,
               0, 0, 0, 1);
      } /* End of 'RotateY' function */

      /* Get rotating arount the z axis matrix function
       * ARGUMENTS: 
       *   - angle:
       *       Type AngleInDegree;
       * RETURNS:
       *   (matr) rotating matrix.
       */
      static matr RotateZ( Type AngleInDegree )
      {
        Type
          a = D2R(AngleInDegree),
          c = std::cos(a),
          s = std::sin(a);
  
        return 
          matr(c, -s, 0, 0,
               s, c, 0, 0,
               0, 0, 1, 0,
               0, 0, 0, 1);
      } /* End of 'RotateZ' function */

      /* Get rotate matrix around a vector function.
       * ARGUMENTS:
       *   - angle:
       *       Type AngleInDegree;
       *   - vector:
       *       const vec3 &R;
       * RETURNS:
       *   (matr) result matrix.
       */
      matr Rotate( Type AngleInDegree, const vec3<Type> &R )
      {
        Type
          A = D2R(AngleInDegree),
          si = std::sin(A), co = std::cos(A);
        vec3<Type> V = R.Normalizing();

        return matr(co + V.X * V.X * (1 - co),
                    V.X * V.Y * (1 - co) + V.Z * si,
                    V.X * V.Z * (1 - co) - V.Y * si, 
                    0,

                    V.Y * V.X * (1 - co) - V.Z * si,
                    co + V.Y * V.Y * (1 - co),
                    V.Y * V.Z * (1 - co) + V.X * si, 
                    0,
                 
                    V.Z * V.X * (1 - co) + V.Y * si,
                    V.Z * V.Y * (1 - co) - V.X * si,
                    co + V.Z * V.Z * (1 - co), 
                    0,

                    0, 0, 0, 1);
      } /* End of 'Rotate' function */

      /* Matrix look-at viewer setup function.
       * ARGUMENTS:
       *   - viewer position, look-at point, approximate up direction:
       *       const vec3 &Loc, &At, &Up1;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr View( const vec3<Type> &Loc, const vec3<Type> &At, const vec3<Type> &Up1 )
      {
        vec3
          Dir =   (At - Loc).Normalizing(),
          Right = (Dir % Up1).Normalizing(),
          Up =    (Right % Dir).Normalizing();

        return matr(Right.X, Up.X, -Dir.X, 0, 
                    Right.Y, Up.Y, -Dir.Y, 0, 
                    Right.Z, Up.Z, -Dir.Z, 0,
                    -(Loc & Right), -(Loc & Up), (Loc & Dir), 1);
      } /* End of 'MatrView' function */

      /* Matrix ortho setup function.
       * ARGUMENTS:
       *   - left border:
       *       Type l;
       *   - right border:
       *       Type r;
       *   - bottom border:
       *       Type b;
       *   - top border:
       *       Type t;
       *   - projection distance:
       *       Type n;
       *   - far border:
       *       Type f;
       * RETURNS:
       *   (MATR) result matrix.
       */
      static matr Ortho( Type L, Type R, Type B, Type T, Type N, Type F )
      {
        return
          matr(2 / (R - L), 0, 0, 0,
               0, 2 / (T - B), 0, 0,
               0, 0, -2 / (F - N), 0,
               -(R + L) / (R - L), -(T + B) / (T - B), -(F + N) / (F - N), 1);
      } /* End of 'MatrOrtho' function */

      /* Matrix frustum setup function.
       * ARGUMENTS:
       *   - left border:
       *       Type l;
       *   - right border:
       *       Type r;
       *   - bottom border:
       *       Type b;
       *   - top border:
       *       Type t;
       *   - projection distance:
       *       Type n;
       *   - far border:
       *       Type f;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr Frustum( Type L, Type R, Type B, Type T, Type N, Type F )
      {
        return
          matr(2 * N / (R - L), 0, 0, 0,
               0, 2 * N / (T - B), 0, 0,
               (R + L) / (R - L), (T + B) / (T - B), -(F + N) / (F - N), -1,
               0, 0, -2 * N * F / (F - N), 0);
      } /* End of 'Frustum' function */

      /* Get transposed matrix function
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr &) self reference.
       */
      matr & Transpose( void )
      {
        *this = matr(A[0][0], A[1][0], A[2][0], A[3][0],
                     A[0][1], A[1][1], A[2][1], A[3][1],
                     A[0][2], A[1][2], A[2][2], A[3][2],
                     A[0][3], A[1][3], A[2][3], A[3][3]);
        return *this;
      } /* End of 'Transpose' function */

      /* Get transposed matrix function
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) transposed matrix.
       */
      matr Transposed( void ) const
      {
        return matr(A[0][0], A[1][0], A[2][0], A[3][0],
                    A[0][1], A[1][1], A[2][1], A[3][1],
                    A[0][2], A[1][2], A[2][2], A[3][2],
                    A[0][3], A[1][3], A[2][3], A[3][3]);
      } /* End of 'Transpose' function */

      /* Calcualte 3x3 matrix determinator function.
       * ARGUMENTS: 
       *   - matrix elements:
       *       Type A11, A12, A12,
       *            A21, A22, A23,
       *            A31, A32, A33;
       * RETURNS:
       *   (Type) determinator.
       */
      static Type Determ3x3( Type A11, Type A12, Type A13,
                            Type A21, Type A22, Type A23,
                            Type A31, Type A32, Type A33 )
      {
        return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
               A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
      } /* End of 'Determ3x3' function */

      /* Calcualte 4x4 matrix determinator function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) determinator.
       */
      Type operator!( void ) const
      {
        return
          +A[0][0] * Determ3x3(A[1][1], A[1][2], A[1][3],
                               A[2][1], A[2][2], A[2][3],
                               A[3][1], A[3][2], A[3][3]) +
          -A[0][1] * Determ3x3(A[1][0], A[1][2], A[1][3],
                               A[2][0], A[2][2], A[2][3],
                               A[3][0], A[3][2], A[3][3]) +
          +A[0][2] * Determ3x3(A[1][0], A[1][1], A[1][3],
                               A[2][0], A[2][1], A[2][3],
                               A[3][0], A[3][1], A[3][3]) +
          -A[0][3] * Determ3x3(A[1][0], A[1][1], A[1][2],
                               A[2][0], A[2][1], A[2][2],
                               A[3][0], A[3][1], A[3][2]);
      } /* End of 'operator!' function */

      /* Get inverse matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) inverse matrix.
       */
      matr Inverse( void ) const
      {
        Type det = !*this;
        matr r;

        if (IsInversedEvaluated)
          return matr(Inversed);
        IsInversedEvaluated = true;

        if (det == 0)
        {
          r = Identity();
          std::memcpy(Inversed, r.A[0], 16 * sizeof(Type));
          return r;
        }
 
        r.A[0][0] =
          +Determ3x3(A[1][1], A[1][2], A[1][3],
                     A[2][1], A[2][2], A[2][3],
                     A[3][1], A[3][2], A[3][3]) / det;

        r.A[1][0] =
          -Determ3x3(A[1][0], A[1][2], A[1][3],
                     A[2][0], A[2][2], A[2][3],
                     A[3][0], A[3][2], A[3][3]) / det;
 
        r.A[2][0] =
          +Determ3x3(A[1][0], A[1][1], A[1][3],
                     A[2][0], A[2][1], A[2][3],
                     A[3][0], A[3][1], A[3][3]) / det;
 
        r.A[3][0] =
          -Determ3x3(A[1][0], A[1][1], A[1][2],
                     A[2][0], A[2][1], A[2][2],
                     A[3][0], A[3][1], A[3][2]) / det;
 
        r.A[0][1] =
          -Determ3x3(A[0][1], A[0][2], A[0][3],
                     A[2][1], A[2][2], A[2][3],
                     A[3][1], A[3][2], A[3][3]) / det;
 
        r.A[1][1] =
          +Determ3x3(A[0][0], A[0][2], A[0][3],
                     A[2][0], A[2][2], A[2][3],
                     A[3][0], A[3][2], A[3][3]) / det;
 
        r.A[2][1] =
          -Determ3x3(A[0][0], A[0][1], A[0][3],
                     A[2][0], A[2][1], A[2][3],
                     A[3][0], A[3][1], A[3][3]) / det;
 
        r.A[3][1] =
          +Determ3x3(A[0][0], A[0][1], A[0][2],
                     A[2][0], A[2][1], A[2][2],
                     A[3][0], A[3][1], A[3][2]) / det;
 
 
        r.A[0][2] =
          +Determ3x3(A[0][1], A[0][2], A[0][3],
                     A[1][1], A[1][2], A[1][3],
                     A[3][1], A[3][2], A[3][3]) / det;

        r.A[1][2] =
          -Determ3x3(A[0][0], A[0][2], A[0][3],
                     A[1][0], A[1][2], A[1][3],
                     A[3][0], A[3][2], A[3][3]) / det;
 
        r.A[2][2] =
          +Determ3x3(A[0][0], A[0][1], A[0][3],
                     A[1][0], A[1][1], A[1][3],
                     A[3][0], A[3][1], A[3][3]) / det;
 
        r.A[3][2] =
          -Determ3x3(A[0][0], A[0][1], A[0][2],
                     A[1][0], A[1][1], A[1][2],
                     A[3][0], A[3][1], A[3][2]) / det;

        r.A[0][3] =
          -Determ3x3(A[0][1], A[0][2], A[0][3],
                     A[1][1], A[1][2], A[1][3],
                     A[2][1], A[2][2], A[2][3]) / det;

        r.A[1][3] =
          +Determ3x3(A[0][0], A[0][2], A[0][3],
                     A[1][0], A[1][2], A[1][3],
                     A[2][0], A[2][2], A[2][3]) / det;

        r.A[2][3] =
          -Determ3x3(A[0][0], A[0][1], A[0][3],
                     A[1][0], A[1][1], A[1][3],
                     A[2][0], A[2][1], A[2][3]) / det;

        r.A[3][3] =
          +Determ3x3(A[0][0], A[0][1], A[0][2],
                     A[1][0], A[1][1], A[1][2],
                     A[2][0], A[2][1], A[2][2]) / det;
        
        std::memcpy(Inversed, r.A[0], 16 * sizeof(Type));
        return r;
      } /* End of 'Inverse' function */

      /* Multiplicate two matrix function.
       * ARGUMENTS: 
       *   - second matrix:
       *       matr M2;
       * RETURNS:
       *   (matr) result matrix.
       */
      matr operator*( const matr &M2 ) const
      {
        return
          matr(A[0][0] * M2.A[0][0] + A[0][1] * M2.A[1][0] + A[0][2] * M2.A[2][0] + A[0][3] * M2.A[3][0],
               A[0][0] * M2.A[0][1] + A[0][1] * M2.A[1][1] + A[0][2] * M2.A[2][1] + A[0][3] * M2.A[3][1],
               A[0][0] * M2.A[0][2] + A[0][1] * M2.A[1][2] + A[0][2] * M2.A[2][2] + A[0][3] * M2.A[3][2],
               A[0][0] * M2.A[0][3] + A[0][1] * M2.A[1][3] + A[0][2] * M2.A[2][3] + A[0][3] * M2.A[3][3],
                                                                                    
               A[1][0] * M2.A[0][0] + A[1][1] * M2.A[1][0] + A[1][2] * M2.A[2][0] + A[1][3] * M2.A[3][0],
               A[1][0] * M2.A[0][1] + A[1][1] * M2.A[1][1] + A[1][2] * M2.A[2][1] + A[1][3] * M2.A[3][1],
               A[1][0] * M2.A[0][2] + A[1][1] * M2.A[1][2] + A[1][2] * M2.A[2][2] + A[1][3] * M2.A[3][2],
               A[1][0] * M2.A[0][3] + A[1][1] * M2.A[1][3] + A[1][2] * M2.A[2][3] + A[1][3] * M2.A[3][3],
                                                                                    
               A[2][0] * M2.A[0][0] + A[2][1] * M2.A[1][0] + A[2][2] * M2.A[2][0] + A[2][3] * M2.A[3][0],
               A[2][0] * M2.A[0][1] + A[2][1] * M2.A[1][1] + A[2][2] * M2.A[2][1] + A[2][3] * M2.A[3][1],
               A[2][0] * M2.A[0][2] + A[2][1] * M2.A[1][2] + A[2][2] * M2.A[2][2] + A[2][3] * M2.A[3][2],
               A[2][0] * M2.A[0][3] + A[2][1] * M2.A[1][3] + A[2][2] * M2.A[2][3] + A[2][3] * M2.A[3][3],
                                                                                    
               A[3][0] * M2.A[0][0] + A[3][1] * M2.A[1][0] + A[3][2] * M2.A[2][0] + A[3][3] * M2.A[3][0],
               A[3][0] * M2.A[0][1] + A[3][1] * M2.A[1][1] + A[3][2] * M2.A[2][1] + A[3][3] * M2.A[3][1],
               A[3][0] * M2.A[0][2] + A[3][1] * M2.A[1][2] + A[3][2] * M2.A[2][2] + A[3][3] * M2.A[3][2],
               A[3][0] * M2.A[0][3] + A[3][1] * M2.A[1][3] + A[3][2] * M2.A[2][3] + A[3][3] * M2.A[3][3]);
      } /* End of 'operator*' function */

      /* Multiplicate two matrix function.
       * ARGUMENTS: 
       *   - second matrix:
       *       matr M2;
       * RETURNS:
       *   (matr) result matrix.
       */
      matr & operator*=( const matr &M2 ) const
      {
        return *this = *this * M2;
      } /* End of 'operator*=' function */

      /* Get matrix component operation function.
       * ARGUMENTS:
       *   - row:
       *       int Row;
       * RETURNS:
       *   (Type *) pointer to the start of the row.
       */
      Type * operator[]( int Row )
      {
        if (Row < 0 || Row >= 4)
          return A[0];
        return A[Row];
      } /* End of 'operator[]' function */

      /* Get matrix component operation function.
       * ARGUMENTS:
       *   - row:
       *       int Row;
       * RETURNS:
       *   (const Type *) pointer to the start of the row.
       */
      const Type * operator[]( int Row ) const
      {
        if (Row < 0 || Row >= 4)
          return A[0];
        return A[Row];
      } /* End of 'operator[]' function */

      
      /* Transform a vector with matrix function.
       * ARGUMENTS: 
       *   - vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) transformated vector.
       */
      vec3<Type> VectorTransform( const vec3<Type> &V ) const
      {
        return
          vec3(V.X * A[0][0] + V.Y * A[1][0] + V.Z * A[2][0],
               V.X * A[0][1] + V.Y * A[1][1] + V.Z * A[2][1],
               V.X * A[0][2] + V.Y * A[1][2] + V.Z * A[2][2]);
      } /* End of 'VectorTransform' function */

      /* Transform a point with matrix function.
       * ARGUMENTS:
       *   - radius vector of a point:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) radius vector of transforamted point.
       */
      vec3<Type> PointTransform( const vec3<Type> &V ) const
      {
        return
          vec3(V.X * A[0][0] + V.Y * A[1][0] + V.Z * A[2][0] + A[3][0],
               V.X * A[0][1] + V.Y * A[1][1] + V.Z * A[2][1] + A[3][1],
               V.X * A[0][2] + V.Y * A[1][2] + V.Z * A[2][2] + A[3][2]);
      } /* End of 'PointTransform' function */

      /* Multiplicate vector by matrix
       * ARGUMENTS: 
       *   - vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) transformated vector.
       */
      vec3<Type> Transform4x4( const vec3<Type> &V ) const
      {
        Type w = V.X * A[0][3] + V.Y * A[1][3] + V.Z * A[2][3] + A[3][3];

        return
          vec3<Type>((V.X * A[0][0] + V.Y * A[1][0] + V.Z * A[2][0] + A[3][0]) / w,
                     (V.X * A[0][1] + V.Y * A[1][1] + V.Z * A[2][1] + A[3][1]) / w,
                     (V.X * A[0][2] + V.Y * A[1][2] + V.Z * A[2][2] + A[3][2]) / w);
      } /* End of 'Transform4x4' function */

      /* Multiplicate vector by matrix
       * ARGUMENTS: 
       *   - vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) transformated vector.
       */
      vec4<Type> Transform4x4( const vec4<Type> &V ) const
      {
        return
          vec4<Type>(V.X * A[0][0] + V.Y * A[1][0] + V.Z * A[2][0] + A[3][0],
                     V.X * A[0][1] + V.Y * A[1][1] + V.Z * A[2][1] + A[3][1],
                     V.X * A[0][2] + V.Y * A[1][2] + V.Z * A[2][2] + A[3][2],
                     V.X * A[0][3] + V.Y * A[1][3] + V.Z * A[2][3] + A[3][3]);
      } /* End of 'Transform4x4' function */

      /* Multiplicate normal by matrix.
       * ARGUMENTS:
       *   - normal:
       *       const vec3 &N;
       * RETURNS:
       *   (vec3) transformed normal.
       */
      vec3<Type> TransformNormal( const vec3<Type> &N ) const
      {
        if (IsInversedEvaluated)
          return matr(Inversed).Transpose().VectorTransform(N);
        return (*this).Inverse().Transpose().VectorTransform(N);
      } /* End of 'TransformNormal' function */

    }; /* End of 'matr' class */

    /* Out put to stream operator for matrix function
     * ARGUMENTS:
     *   - stream:
     *       std::ostream &Stream;
     *   - matrix:
     *       const matr<Type> M;
     */
    template<typename Type>
      std::ostream & operator<<( std::ostream &Stream, const matr<Type> M )
      {
        Stream << "matr(" << M[0][0] << ", " << M[0][1] << ", " << M[0][2] << ", " << M[0][3] << "," << std::endl;
        Stream << "     " << M[1][0] << ", " << M[1][1] << ", " << M[1][2] << ", " << M[1][3] << "," << std::endl;
        Stream << "     " << M[2][0] << ", " << M[2][1] << ", " << M[2][2] << ", " << M[2][3] << "," << std::endl;
        Stream << "     " << M[3][0] << ", " << M[3][1] << ", " << M[3][2] << ", " << M[3][3] << ")" << std::endl;
        return Stream;
      } /* End of 'operator<<' function */

} /* end of 'mth' namespace */

#endif /* __mth_matr_h_ */

/* END OF 'mth_math.h' FILE */
