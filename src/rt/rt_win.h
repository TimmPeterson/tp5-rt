/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : rt_win.h
 * PURPOSE     : Raytracing project.
 *               Ray tracing window class header file.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 20.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __rt_win_h_
#define __rt_win_h_

#include "win/win.h"
#include "rt_scene.h"

/* Base project namespace */
namespace tp5
{
  /* Ray tracing window representation type */
  class rt_win : public Window
  {
  public:
    frame  Frm;   // frame for rendering to window
    camera Cam;   // Camera raytracing
    scene  Scene; // Scene to render

    rt_win( int W, int H );

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
