/* PROJECT     : tp5-rt 
 * FILE NAME   : rt_win.h
 * PROGRAMMER  : Tim Peterson
 * LAST UPDATE : 16.07.2025
 * PURPOSE     : 'rt_win' class defenition file.
 * LICENSE     : MIT License
 */

#ifndef __rt_win_h_
#define __rt_win_h_

#include "win/win.h"
#include "rt_scene.h"

/* Base project namespace */
namespace tp5
{
  /* Ray tracing window representation type */
  class rt_win : public window
  {
  public:
    frame  Frm;   // frame for rendering to window
    camera Cam;   // Camera raytracing
    scene  Scene; // Scene to render

    /* 'rt_win' class constructor */
    rt_win( int W, int H );

    /* 'rt_win' class destructor */
    ~rt_win();

    /* Resize all local fields. 
     * ARGUMENTS:
     *   - new size:
     *       int NewW, int NewH;
     * RETURNS: None.
     */
    void Resize( int NewW, int NewH );

    /* Render to frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    void Render( void );

    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - new width and height of client area:
     *       int W, H;
     * RETURNS: None.
     */
    void OnSize( int W, int H ) override;

    /* WM_KEYDOWN window message handle function.
     * ARGUMENTS:
     *   - key:
     *       UINT Key;
     * RETURNS: None.
     */
    void OnKeyDown( SDL_Keysym KeySym ) override;

    /* Execute as fast as possible call-back method.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    void OnIdle( void ) override;  
  }; /* End of 'rt_win' class */
} /* end of 'tp5' namespace */

#endif /* __rt_win_h_ */

/* END OF 'rt_win.h' FILE */
