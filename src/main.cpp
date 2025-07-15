#include <SDL2/SDL.h>

#include "tp5/rt.h"

const int WIDTH  = 1024;
const int HEIGHT = 512;

using namespace tp5;

int main( void ) 
{
  tp5::rt_win MyWin(WIDTH, HEIGHT);

  auto s  = new sphere(vec3(0, 0, 0), 5., material());
  auto p  = new plane(vec3(0, -10, 0), vec3(0, 1, 0), material(vec3(0), vec3(0.6)));
  auto t  = new torus(vec3(0), 5, 2);
  auto lw = new point_light(vec3(10), vec3(1));
  auto lg = new point_light(vec3(10, -10, -10), vec3(0, 0.5, 0));
  
  MyWin.Scene << t << p << lw << lg;
  
  MyWin.Run();

  if (MyWin.Scene.IsRenderActive)
  {
    MyWin.Scene.IsToBeStop = true;
    std::cout << "\nWait render thread finishing\n";
    while (!MyWin.Scene.IsReadyToFinish)
      ;
    std::cout << "\nAfter waiting\n";
  }
  std::cout << "\nFinish\n";

  return 0;
}
