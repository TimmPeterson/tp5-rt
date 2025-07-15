#ifndef __def_h_
#define __def_h_

#include <cstdint>
#include <vector>

#include "mth/mth.h"


using dword = uint32_t;
using byte = unsigned char;

/* Project namespace */
namespace tp5
{
  inline double min( double A, double B )
  {
    return A < B ? A : B;
  }

  inline double max( double A, double B )
  {
    return A > B ? A : B;
  }
  
  inline double abs( double X )
  {
    return X > 0 ? X : -X;
  }

  // double clamp( double V, double A, double B )
  // {
  //   if (V < A) return A;
  //   if (V > B) return B;
  //   return V;
  // }

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