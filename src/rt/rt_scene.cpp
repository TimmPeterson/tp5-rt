/* PROJECT     : tp5-rt 
 * FILE NAME   : rt_scene.cpp
 * PROGRAMMER  : Tim Peterson
 * LAST UPDATE : 16.07.2025
 * PURPOSE     : 'scene' methods defenition file.
 * LICENSE     : MIT License
 */

#include <thread>

#include "rt_scene.h"

/* Trace ray function.
 * ARGUMENTS:
 *   - ray to trace:
 *       const ray &R;
 * RETURNS:
 *   (vec3) traced color.
 */
tp5::vec3 tp5::scene::Trace( const ray &R, int RecDepth )
{
  intr in;
  vec3 color;

  if (RecDepth > MaxRecDepth)
    return vec3(0);

  if (IsToBeStop)
     return vec3(0);

  if (Intersect(R, &in))
  {
    in.P  = R(in.T);
    in.Shp->GetNormal(&in);
    if (RecDepth > 3 || RecDepth < 0)
      printf("TEST");
    color = Shade(R, &in, RecDepth);
  }
  else
    color = BackgroundColor;
  return color;
} /* End of 'tp5::scene::Trace' function */

/* Shade single pixel function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &R;
 *   - data about intersection:
 *       intr *In;
 *   - depth of recoursion:
 *       int RecDepth;
 */
tp5::vec3 tp5::scene::Shade( const ray &R, intr *In, int RecDepth )
{
  /* Face forward */
  vec3 N = In->N;

  // N += vec3::RndN(N, In->Shp->Mtl.Matte);
  N.Normalize();

  double vn = R.Dir & N;
  bool IsEnter = true;
  if (vn > 0)
  {
    N = -N, vn = -vn;
    IsEnter = false;
  }
  /* Ray reflected vector */
  vec3 Ref = R.Dir.Reflect(N);

  /* Ambient color component */
  vec3 ambient = In->Shp->Mtl.Ka * AmbientColor;

  /* Diffuse color component */
  vec3 diffuse = vec3(0);
  vec3 Kd = In->Shp->Color(In);

  /* Specular color component */
  vec3 specular = vec3(0);

  /* Iterating through each light */
  for (auto lg : Lights)
  {    
    light_info li;
    double sh = lg->Shadow(In->P, &li);
    intr in;

    sh = min(max(0.0, sh), 1.0);

    vec3 diffuse0 = vec3(0.), specular0 = vec3(0.);

    if (double nl = N & li.Direction; nl > tp5::Trashold)
    {
      diffuse0 += Kd * li.Color * nl * sh;
 
      if (double rl = Ref & li.Direction; rl > Trashold)
        specular0 += In->Shp->Mtl.Ks * li.Color * pow(rl, In->Shp->Mtl.Ph) * sh;
    }

    diffuse += diffuse0;
    specular += specular0;
  }

  vec3 reflect = Trace(ray(In->P + N * Trashold, Ref), ++RecDepth) * In->Shp->Mtl.Kr;

  double eta = IsEnter ?
            In->Shp->Mtl.RefractionCoef / Air : Air / In->Shp->Mtl.RefractionCoef;

  double sq = 1 - (1 - (R.Dir & N) * (R.Dir & N));
  vec3 refract;
  if (sq > 0)
  {
    vec3 T = (R.Dir - N * (R.Dir & N)) * eta - N * sqrt(sq);

    refract = In->Shp->Mtl.Kt * Trace(ray(In->P + T * Trashold, T), RecDepth);
  }
  else
  {
    vec3 T = (R.Dir - N * (R.Dir & N)) * eta - N;

    refract = In->Shp->Mtl.Kt * Trace(ray(In->P + T * Trashold, T), RecDepth);
  }
  In->Shp->GetNormal(In);

  // return vec3(In->T) / 100.;//vec3(1) * (In->N.Normalizing() & vec3(1));
  // TODO:
  return ambient + diffuse + specular + reflect + refract;
} /* End of 'tp5::scene::Shade' function */

/* Render whole scene function.
 * ARGUMENTS:
 *   - camera for rendering:
 *       const camera &Cam;
 *   - frame to render in:
 *       frame &Frm;
 * RETURNS: None.
 */
void tp5::scene::Render( const camera &Cam, frame &Frm )
{
  int n = std::thread::hardware_concurrency() - 1;
  std::cout << "Log Scene.Render\nN: " << n << "\n";
// #ifndef NDEBUG
//   n = 1;
// #endif /* NDEBUG */
  std::vector<std::thread> Ths;
  Ths.resize(n);
  StartRow = 0;
  for (int i = 0; i < n; i++)
  {
    Ths[i] = std::thread(
      [&]( void )
      {
        int y = 0;
        while (y < Frm.height)
        {
          y = StartRow++;
          for (int x = 0; x < Frm.width; x++)
          {
#if 1
            ray r = Cam.FrameRay(x + 0.5, y + 0.5);
            vec3 c = Trace(r, 0);
#else
            int sub = 4;
            double ss = 1.0 / sub;
            vec3 c = vec3(0);
            for (int i = 0; i < sub; i++)
              for (int j = 0; j < sub; j++)
              {
                ray r = Cam.FrameRay(x + 0.5 + ss * i, y + 0.5 + ss * j);
                c += Trace(r, 0);
              }
            c /= sub * sub;
            // c *= 255;
            /*
            ray r1 = Cam.FrameRay(x + 0.5 - 0.2, y + 0.5 - 0.2);
            ray r2 = Cam.FrameRay(x + 0.5 - 0.2, y + 0.5 + 0.2);
            ray r3 = Cam.FrameRay(x + 0.5 + 0.2, y + 0.5 - 0.2);
            ray r4 = Cam.FrameRay(x + 0.5 + 0.2, y + 0.5 + 0.2);
            vec3 c1 = Trace(r1, 0);
            vec3 c2 = Trace(r2, 0);
            vec3 c3 = Trace(r3, 0);
            vec3 c4 = Trace(r4, 0);
            vec3 c = (c1 + c2 + c3 + c4) / 4;
            */
#endif
            // Frm.PutPixel(x, y, frame::RGBA(c.X, c.Y, c.Z, 255));  
            auto clamp = 
              []( double Value ) -> byte
              {
                if (Value < 0)
                  return 0;
                if (Value > 1)
                  return 255;
                return Value * 255;
              };
            Frm.PutPixel(x, y, frame::RGBA(clamp(c.X), clamp(c.Y), clamp(c.Z)));
          }
        }
      });
  }
  for (int i = 0; i < n; i++)
    Ths[i].join();
  IsToBeStop = false;
} /* End of 'tp5::scene::Render' function */

/* Intersect all objects function.
 * ARGUMENTS:
 *   - ray to intersect with:
 *       const ray &R;
 *   - intersection properties object:
 *       intr *In;
 * RETURNS:
 *   (bool) true if intersected, false otherwise.
 */
bool tp5::scene::Intersect( const ray &R, intr *In )
{
  intr best_intr;
  best_intr.T = -1;
 
  for (auto shp : Shapes)
  {
    intr current_intr;
    if (shp->Intersect(R, &current_intr) &&
        (best_intr.T == -1 || (current_intr.T < best_intr.T && current_intr.T > 0)))
      best_intr = current_intr;
  }
  if (best_intr.T == -1)
    return false;
  *In = best_intr;
  return true;
} /* End of 'tp5::scene::Intersect' function */

/* Add shape to scene operator function.
 * ARGUMENTS:
 *   - pointer to shape to add:
 *       shape *Shape;
 */
tp5::scene & tp5::scene::operator<<( shape *Shape )
{
  Shapes << Shape;
  return *this;
} /* End of 'tp5::scene::operator<<' function */

/* Add light to scene operator function.
 * ARGUMENTS:
 *   - pointer to light to add:
 *        light *Light;
 */
tp5::scene & tp5::scene::operator<<( light *Light )
{
  Lights << Light;
  return *this;
} /* End of 'tp5::scene::operat  or<<' function */

/* END OF 'rt_scene.cpp' FILE */
