#include "win.h"
#include "frame/frame.h"

namespace tp5
{

Window::Window( int W, int H ) : running(false), width(W), height(H)
  {
    SDL_Init(SDL_INIT_VIDEO);
    
    window =
      SDL_CreateWindow(
        "Pixel Window", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
        width, height,
        SDL_WINDOW_SHOWN
      );

    renderer = 
      SDL_CreateRenderer(
        window, 
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
  }

  Window::~Window()
  {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  void Window::DrawPixels( dword *Pixels ) const
  {
    SDL_UpdateTexture(texture, nullptr, Pixels, width * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  }

  void Window::DrawFrame( const frame &F ) const
  {
    SDL_UpdateTexture(texture, nullptr, F.pixels, F.width * sizeof(uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
  }

  /* Window events dispatching method.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  void Window::Run( void )
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
  } /* End of 'Run' method */

  /* On key down call-back virtual method.
   * ARGUMENTS:
   *   - pressed key:
   *        SDL_Keysym KeySym;
   * NOTE:
   *   'KeySym.sym' for exact symbol;
   */
  void Window::OnKeyDown( SDL_Keysym KeySym )
  {
  } /* End of 'OnKeyDown' method */

  /* On resize call-back virtual method.
   * ARGUMENTS:
   *   - new size:
   *        int NewW, NewH;
   */
  void Window::OnSize( int NewW, int NewH )
  {
  } /* End of 'OnSize' method */

  /* Method that executes as fast as possible.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  void Window::OnIdle( void )
  {
  } /* End of 'OnIdle' method */
} 