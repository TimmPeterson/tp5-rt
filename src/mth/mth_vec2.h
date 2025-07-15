/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_vec2.h
 * PURPOSE     : Raytracing project.
 *               2 dimensional vector class math module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_vec2_h_
#define __mth_vec2_h_

#include "mth_def.h"

namespace mth
{
  /* Two dimensional vector representation type */
  template<typename Type>
    class vec2
    {
    public:
      Type X, Y; // Vector components

      /* vec2 default constructor */
      vec2() : X {}, Y {}
      {
      } /* End of default vec2 constructor */

      /* vec2 constructor by 2 components:
       * ARGUMENTS:
       *   - components:
       *       Type A, B;
       */
      vec2( Type A, Type B ) : X(A), Y(B)
      {
      } /* End of vec2 constructor */

      /* vec2 constructor by single value.
       * ARGUMENTS:
       *   - value:
       *       Type V;
       */
      explicit vec2( Type V ) : X(V), Y(V)
      {
      } /* End of vec2 constructor */

      /* Dot product evaluating operation function 
       * ARGUMTENTS:
       *   - rvalue vector:
       *       const vec2 &V;
       * RETURNS:
       *   (Type) dot product value.
       */
      Type operator&( const vec2 &V ) const
      {
        return X * V.X + Y * V.Y;
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
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator+( const vec2 &V ) const
      {
        return vec2(X + V.X, Y + V.Y);
      } /* End of 'operator+' function */

      /* Sum operation function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self reference.
       */
      vec2 & operator+=( const vec2 &V )
      {
        X += V.X, Y += V.Y;
        return *this;
      } /* End of 'operator

      /* Subtract operation function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator-( const vec2 &V ) const
      {
        return vec2(X - V.X, Y - V.Y);
      } /* End of 'operator-' function */

      /* Subtract operation function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2 &) self reference.
       */
      vec2 & operator-=( const vec2 &V )
      {
        X -= V.X, Y -= V.Y;
        return *this;
      } /* End of 'operator-' function */

      /* Percomponent multiplication function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator*( const vec2 &V ) const
      {
        return vec2(X * V.X, Y * V.Y);
      } /* End of 'operator-' function */

      /* Mulitply self by number function 
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec3 &N;
       * RETURNS:
       *   (vec3 &) reference to self.
       */
      vec2 & operator*=( const vec2 &R )
      {
        X *= R.X, Y *= R.Y;
        return *this;
      } /* End of 'operator*=' function */

      /* Percomponent division function.
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator/( const vec2 &V ) const
      {
        return vec2(X / V.X, Y / V.Y);
      } /* End of 'operator/' function */

      /* Mulitply self by number function 
       * ARGUMENTS:
       *   - rvalue vector:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) reference to this.
       */
      vec2 & operator/=( const vec2 &V )
      {
        X /= V.X, Y /= V.Y;
        return *this;
      } /* End of 'operator*=' function */

      /* Multiply by number function.
       * ARGUMENTS:
       *   - rvalue number:
       *       const vec2 &V;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator*( Type N ) const
      {
        return vec2(X * N, Y * N);
      } /* End of 'operator*' function */

      /* Mulitply self by number function 
       * ARGUMENTS:
       *   - rvalue number:
       *       Type N;
       * RETURNS:
       *   (vec2 &) reference to self.
       */
      vec2 & operator*=( Type N )
      {
        X *= N, Y *= N;
        return *this;
      } /* End of 'operator*=' function */

      /* Divide by number function.
       * ARGUMENTS:
       *   - rvalue number:
       *       Type N;
       * RETURNS:
       *   (vec2) result vector.
       */
      Type operator/( Type N ) const
      {
        return vec2(X / N, Y / N);
      } /* End of 'operator/' function */

      /* Divide self by number function 
       * ARGUMENTS:
       *   - rvalue number:
       *       Type N;
       * RETURNS:
       *   (vec2 &) reference to self.
       */
      vec2 & operator/=( Type N )
      {
        X /= N, Y /= N;
        return *this;
      } /* End of 'operator/=' function */

      /* Negative vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) negative vector.
       */
      vec2 operator-( void ) const
      {
        return vec2(-X, -Y);
      } /* End of 'operator-' function */

      /* Normalize THIS vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2 &) reference to this normalized vector.
       */
      vec2 & Normalize( void ) const
      {
        *this /= !*this;
        return *this;
      } /* End of 'Normalize' function */

      /* Get noramlized vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) normalized vector.
       */
      vec2 Normalizing( void ) const
      {
        return *this / !*this;
      } /* End of 'Normalizing' function */

      /* Get distance to another radius vector function.
       * ARGUMENTS:
       *   - second vector:
       *       const vec2 &P;
       * RETURNS:
       *   (Type) distance.
       */
      Type Distance( const vec2 &P ) const
      {
        return !(*this - P);
      } /* End of 'Distance' function */

      /* Get zero vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) zero vector.
       */
      static vec2 Zero( void )
      {
        return vec2(0);
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
        return Y;
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
        return Y;
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
       *   (vec2) random vector.
       */
      static vec2<Type> Rnd0( void )
      {
        return vec2<Type>(std::rand(), std::rand()) / Type(RAND_MAX);
      }  /* End of 'Rnd0' function */

      /* Random vector in range -1 to 1 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) random vector.
       */
      static vec2<Type> Rnd1( void )
      {
        return (vec2<Type>(std::rand(), std::rand()) / Type(RAND_MAX) - 0.5) * 2;
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
       std::ostream & operator<<( std::ostream &Stream, const vec2<Type> &V )
       {
         Stream << "vec2(" << V[0] << ", " << V[1] << ")" << std::endl;
         return Stream;
       } /* End of 'operator<<' function */
} /* end of 'mth' namespace */

#endif /* __mth_vec2_h_ */

/* END OF 'mth_vec2.h' FILE */
