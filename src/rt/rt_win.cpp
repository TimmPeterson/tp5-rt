/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_def.h
 * PURPOSE     : Raytracing project.
 *               Ray tracing window class methods defenition source file.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Timofei I. Petrov.
 * LAST UPDATE : 22.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>

#include "rt_win.h"

/* rt_win constructor function.
 * ARGUMENTS:
 *   - instance:
 *       HINSTANCE hInst;
 */
tp5::rt_win::rt_win( int W, int H ) : Window(W, H), Frm(W, H)
{
  Frm.Resize(W, H);
  Frm.Clear(0xFF0000FF);

  Cam.Resize(W, H);
  Cam.SetLocAtUp(vec3(27 * sin(-PI / 2 + -PI / 3), 15, 27 * cos(-PI / 2 + -PI / 3)), vec3(0));

  
#if 0
  for (int i = 0; i < 100; i++)
  {
    char buf[200];

    sprintf(buf, "ANY2ANY_ico_multi.exe bin/images/mov/frm-%i.tga bin/images/mov/jpg/frm-%i.jpg", i, i);
    std::system(buf);
  }
#endif /* 0 */  
} /* End of 'rt_win::rt_win' function */

/* 'rt_win' class destructor */
tp5::rt_win::~rt_win()
{
  if (this->Scene.IsRenderActive)
  {
    this->Scene.IsToBeStop = true;
    std::cout << "\nWait render thread finishing...\n";
    while (!this->Scene.IsReadyToFinish)
      ;
  }
  std::cout << "\nFinished\n";
} /* End of 'rt_win' destructor */

/* Resize all local fields. 
 * ARGUMENTS:
 *   - new size:
 *       int NewW, int NewH;
 * RETURNS: None.
 */
void tp5::rt_win::Resize( int NewW, int NewH )
{
  Frm.Resize(NewW, NewH);
  Cam.Resize(NewW, NewH);
} /* End of 'tp5::rt_win::Resize' function */

/* Render to frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void tp5::rt_win::Render( void )
{
  //Scene.Render(Cam, Frm);
} /* End of 'tp5::rt_win::Render' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - new width and height of client area:
 *       int W, H;
 * RETURNS: None.
 */
void tp5::rt_win::OnSize( int W, int H )
{
  Scene.IsToBeStop = true;
  Resize(W, H);
} /* End of 'tp5::rt_win::OnSize' function */

/* WM_KEYDOWN window message handle function.
 * ARGUMENTS:
 *   - key:
 *       UINT Key;
 * RETURNS: None.
 */
void tp5::rt_win::OnKeyDown( SDL_Keysym KeySym )
{ 
  Render();
  printf("KeyDown");
  
  switch(KeySym.sym)
  {
  case SDLK_ESCAPE:
    Window::running = false;
    return;
  case SDLK_r:
    if (!Scene.IsRenderActive)
    {
      Scene.IsRenderActive = true;
      Scene.IsToBeStop = false;
      Scene.IsReadyToFinish = false;
      std::cout << std::endl << "Start render scene" << std::endl;
      std::thread Th;
      Th = std::thread(
        [&]( void )
        {
          Scene.Render(Cam, Frm);
          Window::DrawFrame(Frm);
          
          clock_t tt = clock();
          tt = clock() - tt;
          int Seconds = (int)((double)tt / CLOCKS_PER_SEC);
 
          
          std::cout << "Render finish <~~~> Time: " << Seconds << "sssss" << std::endl;

          Scene.IsRenderActive = false;
          Scene.IsToBeStop = false;
          Scene.IsReadyToFinish = true;
        });
      Th.detach();
    }
    return;
  case SDLK_s:
    Frm.Save("output.png");
    return;
  case SDLK_0:
    Frm.Clear(0x00FF00FF);
    return;
  case SDLK_1:
    Frm.Clear(0x0000FFFF);
    return;
  }
} /* End of 'tp5::rt_win::OnKeyDown' function */

void tp5::rt_win::OnIdle( void )
{
  Window::DrawFrame(this->Frm);
}

// /* WM_KEYDOWN window message handle function.
//  * ARGUMENTS:
//  *   - key:
//  *       UINT Key;
//  * RETURNS: None.
//  */
// void tp5::rt_win::OnTimer( int Id )
// {
// } /* End of 'tp5::rt_win::OnTimer' function */

/* END OF 'rt_win.cpp' FILE */
