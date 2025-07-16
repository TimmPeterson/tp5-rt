/* PROJECT     : tp5-rt 
 * FILE NAME   : win.h
 * PROGRAMMER  : Tim Peterson
 * LAST UPDATE : 16.07.2025
 * PURPOSE     : 'window' class defenition file.
 * LICENSE     : MIT License
 */

#ifndef __win_h_
#define __win_h_

#include <SDL2/SDL.h>

#include "def.h"

/* Base developer namespace */
namespace tp5 
{
  /* 'frame' class forward declaration */
  class frame;

  /* Abstract window representation class */
  class window 
  {
  protected:
    bool running;           // Is runnging flag

  private:          
    int                     // Reolution
      width,                
      height;               
    SDL_Window   *wnd;      // SDL window handle
    SDL_Renderer *renderer; // SDL render handle
    SDL_Texture  *texture;  // SDL texture handle
    
  public:
    /* 'window' class constructor.
     * ARGUMENTS:
     *   - resolution in pixels:
     *       int W, H; 
     */
    window( int W, int H );

    /* 'window' class destructor */
    ~window();

    /* Draw buffer of pixels to the window.
     * ARGUMENS:
     *   - buffer of pixels to draw:
     *       dword *Pixels;
     * RETURNS: None.
     */
    void DrawPixels( const dword *Pixels ) const;

    /* Draw pixels from frame to the window.
     * ARGUMENTS:
     *   - frame to be drawn:
     *       const frame &F;
     */
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

    /* On idle call-back virtual method.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual void OnIdle( void );
  };

}

#endif /* __win_h_ */

/* END OF 'win.h' FILE */
