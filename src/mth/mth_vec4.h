/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_vec4.h
 * PURPOSE     : Raytracing project.
 *               4 dimensional vector class math module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_vec4_h_
#define __mth_vec4_h_

#include "mth_def.h"

namespace mth
{
  /* Four dimensional vector representation type */
  template<typename Type>
    class vec4
    {
    public:
      Type X, Y, Z, W; // Vector components

      /* vec4 default constructor */
      vec4() : X {}, Y {}, Z {}, W {}
      {
      } /* End of default vec4 constructor */

      /* vec4 constructor by 4 components:
       * ARGUMENTS:
       *   - components:
       *       Type A, B, C;
       */
      vec4( Type A, Type B, Type C, Type D ) : X(A), Y(B), Z(C), W(D)
      {
      } /* End of vec4 constructor */

      /* vec4 constructor by single value.
       * ARGUMENTS:
       *   - value:
       *       Type V;
       */
      explicit vec4( Type V ) : X(V), Y(V), Z(V), W(V)
      {
      } /* End of vec4 constructor */

      /* Dot product evaluating operation function 
       * ARGUMTENTS:
       *   - rvalue vector:
       *       const vec4 &V;
       * RETURNS:
       *   (Type) dot product value.
       */
      Type operator&( const vec4 &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
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
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator+( const vec4 &V ) const
      {
        return vec4(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
      } /* End of 'operator+' function */

      /* Sum operation function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) self reference.
       */
      vec4 & operator+=( const vec4 &V )
      {
        X += V.X, Y += V.Y, Z += V.Z, W += V.W;
        return *this;
      } /* End of 'operator

      /* Subtract operation function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator-( const vec4 &V ) const
      {
        return vec4(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
      } /* End of 'operator-' function */

      /* Subtract operation function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) self reference.
       */
      vec4 & operator-=( const vec4 &V )
      {
        X -= V.X, Y -= V.Y, Z -= V.Z, W -= V.W;
        return *this;
      } /* End of 'operator-' function */

      /* Percomponent multiplication function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator*( const vec4 &V ) const
      {
        return vec4(X * V.X, Y * V.Y, Z * V.Z, Z * V.W);
      } /* End of 'operator-' function */

      /* Mulitply self by number function 
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec4 &N;
       * RETURNS:
       *   (vec4 &) reference to self.
       */
      vec4 & operator*=( const vec4 &R )
      {
        X *= R.X, Y *= R.Y, Z *= R.Z, W *= R.W;
        return *this;
      } /* End of 'operator*=' function */

      /* Percomponent division function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec4 operator/( const vec4 &V ) const
      {
        return vec4(X / V.X, Y / V.Y, Z / V.Z, W / V.W);
      } /* End of 'operator/' function */

      /* Mulitply self by number function 
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) reference to this.
       */
      vec4 & operator/=( const vec4 &V )
      {
        X /= V.X, Y /= V.Y, Z /= V.Z, W /= V.W;
        return *this;
      } /* End of 'operator*=' function */

      /* Multiply by number function.
       * ARGUMENTS:
       *   - rvalue number:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) result vector.
       */
      vec4 operator*( Type N ) const
      {
        return vec4(X * N, Y * N, Z * N, W * N);
      } /* End of 'operator*' function */

      /* Mulitply self by number function 
       * ARGUMENTS:
       *   - rvalue number:
       *       Type N;
       * RETURNS:
       *   (vec4 &) reference to self.
       */
      vec4 & operator*=( Type N )
      {
        X *= N, Y *= N, Z *= N, W *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* Divide by number function.
       * ARGUMENTS:
       *   - rvalue number:
       *       Type N;
       * RETURNS:
       *   (vec4) result vector.
       */
      Type operator/( Type N ) const
      {
        return vec4(X / N, Y / N, Z / N, W / N);
      } /* End of 'operator/' function */

      /* Divide self by number function 
       * ARGUMENTS:
       *   - rvalue number:
       *       Type N;
       * RETURNS:
       *   (vec4 &) reference to self.
       */
      vec4 & operator/=( Type N )
      {
        X /= N, Y /= N, Z /= N, W /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Negative vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) negative vector.
       */
      vec4 operator-( void ) const
      {
        return vec4(-X, -Y, -Z, -W);
      } /* End of 'operator-' function */

      /* Normalize THIS vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3 &) reference to this normalized vector.
       */
      vec4 & Normalize( void ) const
      {
        *this /= !*this;
        return *this;
      } /* End of 'Normalize' function */

      /* Get noramlized vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) normalized vector.
       */
      vec4 Normalizing( void ) const
      {
        return *this / !*this;
      } /* End of 'Normalizing' function */

      /* Get distance to another radius vector function.
       * ARGUMENTS:
       *   - second vector:
       *       const vec4 &P;
       * RETURNS:
       *   (Type) distance.
       */
      Type Distance( const vec4 &P ) const
      {
        return !(*this - P);
      } /* End of 'Distance' function */

      /* Get zero vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) zero vector.
       */
      static vec4 Zero( void )
      {
        return vec4(0);
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
        if (C == 2)
          return Z;
        return W;
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
        if (C == 2)
          return Z;
        return W;
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
       *   (vec4) random vector.
       */
      static vec4<Type> Rnd0( void )
      {
        return vec4<Type>(std::rand(), std::rand(), std::rand(), std::rand()) / Type(RAND_MAX);
      }  /* End of 'Rnd0' function */

      /* Random vector in range -1 to 1 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) random vector.
       */
      static vec4<Type> Rnd1( void )
      {
        return (vec4<Type>(std::rand(), std::rand(), std::rand(), std::rand()) / Type(RAND_MAX) - 0.5) * 2;
      }  /* End of 'Rnd1' function */
    };

    /* Out put to stream operator for vec3 function
     * ARGUMENTS:
     *   - stream:
     *       std::ostream &Stream;
     *   - matrix:
     *       const vec2<Type> V;
     */
     template<typename Type>
       std::ostream & operator<<( std::ostream &Stream, const vec4<Type> &V )
       {
         Stream << "vec4(" << V[0] << ", " << V[1] << ", " << V[2] << ", " << V[3] << ")" << std::endl;
         return Stream;
       } /* End of 'operator<<' function */
} /* end of 'mth' namespace */

#endif /* __mth_vec4_h_ */

/* END OF 'mth_vec4.h' FILE */
