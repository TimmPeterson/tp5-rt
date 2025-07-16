/* PROJECT     : tp5-rt 
 * FILE NAME   : rt_scene.h
 * PROGRAMMER  : Tim Peterson
 * LAST UPDATE : 16.07.2025
 * PURPOSE     : 'scene' class defenition file.
 * LICENSE     : MIT License
 */

#ifndef __rt_scene_h_
#define __rt_scene_h_

#include <atomic>

#include "rt/shapes/shapes.h"
#include "rt/lights/lights.h"
#include "rt/mods/mods.h"
#include "frame/frame.h"

/* Base project namespace */
namespace tp5
{
  /* Scene representation type */
  class scene
  {
  public:
    std::atomic_bool IsRenderActive  = false; // Sync flags
    std::atomic_bool IsToBeStop      = false; // Waiting for stop flag
    std::atomic_bool IsReadyToFinish = true;  // Waiting to finish program flag
    std::atomic_int  StartRow        = 0;     // Store rendering line
  private:
    stock<shape *> Shapes;      // Container with shapes
    stock<light *> Lights;      // Container with lights
    int            MaxRecDepth; // Max recoursion depth
  public:
    vec3
      BackgroundColor,  // Color of back ground
      AmbientColor;     // Scene abmient color
    double Air;         // Air density

    /* Trace ray function.
     * ARGUMENTS:
     *   - ray to trace:
     *       const ray &R;
     * RETURNS:
     *   (vec3) traced color.
     */
    vec3 Trace( const ray &R, int RecDepth );

    /* Shade intersection function.
     * ARGUMENTS:
     *   - shadeing ray for direction:
     *       const ray &R;
     *   - intersection for shadiing properties:
     *       intr *in;
     * RETURNS:
     *   (vec3) shaded color.
     */
    vec3 Shade( const ray &R, intr *In, int RecDepth );

  public:
    /* 'scene' class default constructor function */
    scene( void ) : BackgroundColor(0.0, 0.1, 0.0), AmbientColor(1, 1, 1), MaxRecDepth(2), Air(0.95)
    {
    } /* End of '' function */

    /* Render whole scene function.
     * ARGUMENTS:
     *   - camera for rendering:
     *       const camera &Cam;
     *   - frame to render in:
     *       frame &Frm;
     */
    void Render( const camera &Cam, frame &Frm );

    /* Intersect all objects function.
     * ARGUMENTS:
     *   - ray to intersect with:
     *       const ray &R;
     *   - intersection properties object:
     *       intr *In;
     * RETURNS:
     *   (bool) true if intersected, false otherwise.
     */
    bool Intersect( const ray &R, intr *In );

    /* Add shape to scene operator function.
     * ARGUMENTS:
     *   - pointer to shape to add:
     *       shape *Shape;
     */
    scene & operator<<( shape *Shape );

    /* Add light to scene operator function.
     * ARGUMENTS:
     *   - pointer to light to add:
     *        light *Light;
     */
    scene & operator<<( light *Light );
  };
} /* end of 'tp5' namespace */

#endif /* __rt_scene_h_ */

/* END OF 'rt_scene.h' FILE */
