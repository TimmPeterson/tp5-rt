/* PROJECT     : tp5-rt 
 * FILE NAME   : win.cpp
 * PROGRAMMER  : Tim Peterson
 * LAST UPDATE : 16.07.2025
 * PURPOSE     : 'window' methods defenition file.
 * LICENSE     : MIT License
 */

#include "win.h"
#include "frame/frame.h"

/* Base developer namespace */
namespace tp5
{
  /* 'window' class constructor.
   * ARGUMENTS:
   *   - resolution in pixels:
   *       int W, H; 
   */
  window::window( int W, int H ) : running(false), width(W), height(H)
  {
    SDL_Init(SDL_INIT_VIDEO);
    
    wnd =
      SDL_CreateWindow(
        "Pixel window", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
        width, height,
        SDL_WINDOW_SHOWN
      );

    renderer = 
      SDL_CreateRenderer(
        wnd, 
        -1, 
        SDL_RENDERER_ACCELERATED
      );
    
    texture =
      SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING, 
        width, 
        height
      );
  } /* End of 'window::window' function */

  /* 'window' class destructor */
  window::~window()
  {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(wnd);
    SDL_Quit();
  } /* End of 'window::~window' function */

  /* Draw buffer of pixels to the window.
   * ARGUMENS:
   *   - buffer of pixels to draw:
   *       dword *Pixels;
   * RETURNS: None.
   */
  void window::DrawPixels( const dword *Pixels ) const
  {
    SDL_UpdateTexture(texture, nullptr, Pixels, width * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  } /* End of 'window::DrawPixels' function */

  /* Draw pixels from frame to the window.
   * ARGUMENTS:
   *   - frame to be drawn:
   *       const frame &F;
   */
  void window::DrawFrame( const frame &F ) const
  {
    SDL_UpdateTexture(texture, nullptr, F.pixels, F.width * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  } /* End of 'window::DrawFrame' function */

  /* Window events dispatching method.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  void window::Run( void )
  {
    SDL_Event event;
    
    running = true;
    
    while (running) 
    {
      while (SDL_PollEvent(&event))
        switch (event.type)
        {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_KEYDOWN:
          this->OnKeyDown(event.key.keysym);
          break;
        case SDL_WINDOWEVENT:
          if (event.window.event == SDL_WINDOWEVENT_RESIZED) 
          {
            int new_w  = event.window.data1;
            int new_h = event.window.data2;
            this->OnSize(new_w, new_h);
          }
          break;
        }
        
      this->OnIdle();
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, texture, nullptr, nullptr);
      SDL_RenderPresent(renderer);
    }
  } /* End of 'window::Run' method */

  /* On key down call-back virtual method.
   * ARGUMENTS:
   *   - pressed key:
   *        SDL_Keysym KeySym;
   * NOTE:
   *   'KeySym.sym' for exact symbol;
   */
  void window::OnKeyDown( SDL_Keysym KeySym )
  {
  } /* End of 'OnKeyDown' method */

  /* On resize call-back virtual method.
   * ARGUMENTS:
   *   - new size:
   *        int NewW, NewH;
   */
  void window::OnSize( int NewW, int NewH )
  {
  } /* End of 'OnSize' method */

  /* Method that executes as fast as possible.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  void window::OnIdle( void )
  {
  } /* End of 'OnIdle' method */
} /* end of 'tp5' namespace */

/* END OF 'win.cpp' FILE */
