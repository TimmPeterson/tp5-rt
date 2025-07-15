/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_vec3.h
 * PURPOSE     : Raytracing project.
 *               3 dimensional vector class math module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include "mth_def.h"

#include <iostream>

namespace mth
{
  /* Three dimensional vector representation type */
  template<typename Type>
    class vec3
    {
    public:
      Type X, Y, Z; // Vector components

      /* vec3 default constructor */
      vec3() : X {}, Y {}, Z {}
      {
      } /* End of default vec3 constructor */

      /* vec3 constructor by 3 components:
       * ARGUMENTS:
       *   - components:
       *       Type A, B, C;
       */
      vec3( Type A, Type B, Type C ) : X(A), Y(B), Z(C)
      {
      } /* End of vec3 constructor */

      /* vec3 constructor by single value.
       * ARGUMENTS:
       *   - value:
       *       Type V;
       */
      explicit vec3( Type V ) : X(V), Y(V), Z(V)
      {
      } /* End of vec3 constructor */

      /* Dot product evaluating operation function 
       * ARGUMTENTS:
       *   - rvalue vector:
       *       const vec3 &V;
       * RETURNS:
       *   (Type) dot product value.
       */
      Type operator&( const vec3 &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z;
      } /* End of 'operator&' function */

      /* Length evaluating operation function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) length.
       */
      Type operator!( void ) const
      {
        return std::sqrt(*this & *this);
      } /* End of 'operator!' function */

      /* Sum operation function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator+( const vec3 &V ) const
      {
        return vec3(X + V.X, Y + V.Y, Z + V.Z);
      } /* End of 'operator+' function */

      /* Sum operation function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) self reference.
       */
      vec3 & operator+=( const vec3 &V )
      {
        X += V.X, Y += V.Y, Z += V.Z;
        return *this;
      } /* End of 'operator' */

      /* Subtract operation function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator-( const vec3 &V ) const
      {
        return vec3(X - V.X, Y - V.Y, Z - V.Z);
      } /* End of 'operator-' function */

      /* Subtract operation function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) self reference.
       */
      vec3 & operator-=( const vec3 &V )
      {
        X -= V.X, Y -= V.Y, Z -= V.Z;
        return *this;
      } /* End of 'operator-' function */

      /* Percomponent multiplication function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator*( const vec3 &V ) const
      {
        return vec3(X * V.X, Y * V.Y, Z * V.Z);
      } /* End of 'operator-' function */

      /* Mulitply self by number function 
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec3 &N;
       * RETURNS:
       *   (vec3 &) reference to self.
       */
      vec3 & operator*=( const vec3 &R )
      {
        X *= R.X, Y *= R.Y, Z *= R.Z;
        return *this;
      } /* End of 'operator*=' function */

      /* Percomponent division function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator/( const vec3 &V ) const
      {
        return vec3(X / V.X, Y / V.Y, Z / V.Z);
      } /* End of 'operator/' function */

      /* Mulitply self by number function 
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) reference to this.
       */
      vec3 & operator/=( const vec3 &V )
      {
        X /= V.X, Y /= V.Y, Z /= V.Z;
        return *this;
      } /* End of 'operator*=' function */

      /* Multiply by number function.
       * ARGUMENTS:
       *   - rvalue number:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator*( Type N ) const
      {
        return vec3(X * N, Y * N, Z * N);
      } /* End of 'operator*' function */

      /* Mulitply self by number function 
       * ARGUMENTS:
       *   - rvalue number:
       *       Type N;
       * RETURNS:
       *   (vec3 &) reference to self.
       */
      vec3 & operator*=( Type N )
      {
        X *= N, Y *= N, Z *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* Divide by number function.
       * ARGUMENTS:
       *   - rvalue number:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator/( Type N ) const
      {
        return vec3(X / N, Y / N, Z / N);
      } /* End of 'operator/' function */

      /* Divide self by number function 
       * ARGUMENTS:
       *   - rvalue number:
       *       Type N;
       * RETURNS:
       *   (vec3 &) reference to self.
       */
      vec3 & operator/=( Type N )
      {
        X /= N, Y /= N, Z /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Negative vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) negative vector.
       */
      vec3 operator-( void ) const
      {
        return vec3(-X, -Y, -Z);
      } /* End of 'operator-' function */

      /* Cross product operator function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec3 &R;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator%( const vec3 &R ) const
      {
        return vec3(Y * R.Z - Z * R.Y, Z * R.X - X * R.Z, X * R.Y - Y * R.X);
      } /* End of 'operator%' function */

      /* Normalize THIS vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3 &) reference to this normalized vector.
       */
      vec3 & Normalize( void )
      {
        *this /= !*this;
        return *this;
      } /* End of 'Normalize' function */

      /* Get noramlized vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) normalized vector.
       */
      vec3 Normalizing( void ) const
      {
        return *this / (!*this);
      } /* End of 'Normalizing' function */

      /* Get distance to another radius vector function.
       * ARGUMENTS:
       *   - second vector:
       *       const vec3 &P;
       * RETURNS:
       *   (Type) distance.
       */
      Type Distance( const vec3 &P ) const
      {
        return !(*this - P);
      } /* End of 'Distance' function */

      /* Get zero vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) zero vector.
       */
      static vec3 Zero( void )
      {
        return vec3(0);
      } /* End of 'Zero' function */

      /* Component getter function.
       * ARGUMENTS:
       *   - component number:
       * RETURNS:
       *   (Type &) reference to that component.
       */
      Type & operator[]( int C )
      {
        if (C == 0)
          return X;
        if (C == 1)
          return Y;
        return Z;
      } /* End of 'operator[]' function */

      /* Component getter function.
       * ARGUMENTS:
       *   - component number:
       * RETURNS:
       *   (Type &) reference to that component.
       */
      const Type & operator[]( int C ) const
      {
        if (C == 0)
          return X;
        if (C == 1)
          return Y;
        return Z;
      } /* End of 'operator[]' function */

      /* Type pointer casting redefinition function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type *) pointer to the first component.
       */
      operator Type *( void ) const
      {
        return &X;
      } /* End of 'operator Type *' function */

      /* Random vector in range 0 to 1 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) random vector.
       */
      static vec3 Rnd0( void )
      {
        return vec3(std::rand(), std::rand(), std::rand()) / Type(RAND_MAX);
      }  /* End of 'Rnd0' function */

      /* Random vector in range -1 to 1 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) random vector.
       */
      static vec3 Rnd1( void )
      {
        return (vec3(std::rand(), std::rand(), std::rand()) / Type(RAND_MAX) - vec3(0.5)) * 2;
      }  /* End of 'Rnd1' function */

      /* Random normalized vector. */
      static vec3 RndN( const vec3 &Direction, Type Angle )
      {
        vec3 r;

        do
        {
          r = Rnd1();
        }
        while ((r & r) < 1.);
        
        r.Normalize();
        
        vec3 N         = Direction.Normalizing();
        vec3 proj      = r - (N * (N & r));
        Type theta     = rand() / (Type)RAND_MAX * Angle;
        vec3 new_dir   = matr<Type>().Rotate(theta, proj).VectorTransform(N);

        return new_dir;
      } /* End of 'RndN' function */

      /* Random normalized vector. */
      static vec3 RndN0( void )
      {
        vec3 r;

        do
        {
          r = Rnd1();
        }
        while ((r & r) < 1.);
        
        r.Normalize();

        return r;
      } /* End of 'RndN' function */

      /* Reflect vector with respect to normal.
       * ARGUMENTS:
       *   - normal:
       *       const vec3 &N;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 Reflect( const vec3 &N ) const
      {
        return *this - N * (N & *this) * 2.0;
      } /* End of 'Reflect' function */
      
      /* Cast to double vector operator function */
      operator vec3<double>( void ) const
      {
        return vec3<double>((double)X, (double)Y, (double)Z);
      } /* End of 'vec3<double>' function */
    };
    
    /* Out put to stream operator for vec3 function
     * ARGUMENTS:
     *   - stream:
     *       std::ostream &Stream;
     *   - matrix:
     *       const vec3<Type> V;
     */
     template<typename Type>
       std::ostream & operator<<( std::ostream &Stream, const vec3<Type> &V )
       {
         Stream << "vec3(" << V[0] << ", " << V[1] << ", " << V[2] << ")" << std::endl;
         return Stream;
       } /* End of 'operator<<' function */

     
} /* end of 'mth' namespace */

#endif /* __mth_vec3_h_ */

/* END OF 'mth_vec3.h' FILE */
