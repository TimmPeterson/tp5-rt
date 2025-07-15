#ifndef __win_h_
#define __win_h_

#include <SDL2/SDL.h>

#include "def.h"

namespace tp5 
{
  class frame;

  class Window 
  {
  protected:
    bool running;

  private:
    int 
      width, 
      height;
    SDL_Window   *window;
    SDL_Renderer *renderer;
    SDL_Texture  *texture;
    
  public:
    Window( int W, int H );

    ~Window();

    void DrawPixels( dword *Pixels ) const;

    void DrawFrame( const frame &F ) const;

    /* Window events dispatching method.
    * ARGUMENTS: None.
    * RETURNS: None.
    */
    void Run( void );
    
    /* On key down call-back virtual method.
    * ARGUMENTS:
    *   - pressed key:
    *        SDL_Keysym KeySym;
    * NOTE:
    *   'KeySym.sym' for exact symbol;
    */
    virtual void OnKeyDown( SDL_Keysym KeySym );

    /* On resize call-back virtual method.
    * ARGUMENTS:
    *   - new size:
    *        int NewW, NewH;
    */
    virtual void OnSize( int NewW, int NewH );

    virtual void OnIdle( void );
  };

}

#endif /* __win_h_ */