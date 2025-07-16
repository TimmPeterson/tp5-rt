/* PROJECT     : tp5-rt 
 * FILE NAME   : def.h
 * PROGRAMMER  : Tim Peterson
 * LAST UPDATE : 16.07.2025
 * PURPOSE     : General defenitions header.
 * LICENSE     : MIT License
 */

#ifndef __def_h_
#define __def_h_

#include <cstdint>
#include <vector>

#include "mth/mth.h"


/* Project namespace */
namespace tp5
{
  /* 4 byte pixel representation type */
  using dword = uint32_t;

  /* 1 byte representation type */
  using byte  = unsigned char;

  /* Some usefull comparing functions */
  using mth::min;
  using mth::max;
  using mth::abs;

  /* Project type defenitions */
  typedef mth::vec2<double>   vec2;
  typedef mth::vec3<double>   vec3;
  typedef mth::vec4<double>   vec4;
  typedef mth::matr<double>   matr;
  typedef mth::ray<double>    ray;
  typedef mth::camera<double> camera;

  /* Stock container representation type. */
  template<typename Type>
    class stock : public std::vector<Type>
    {
    public:
      /* Stock push back operation function.
       * ARGUMENTS:
       *   - element to add:
       *       const Type &X;
       * RETURNS:
       *   (stock &) self reference.
       */
      stock & operator<<( const Type &X )
      {
        this->push_back(X);
        return *this;
      } /* End of 'operator<<' function */

      /* Walk thorugh stock and execute 'Walk' for each eleement function. 
       * ARGUMENTS:
       *   - walk function or object:
       *       WalkType Walk;
       * RETURNS: None.
       */
      template<class WalkType>
        void Walk( WalkType Walk )
        {
          for (auto &x : *this)
            Walk(x);
        } /* End of 'Walk' function */
  }; /* End of 'stock' class */
}

#endif /* __def_h_ */

/* END OF 'def.h' FILE */
