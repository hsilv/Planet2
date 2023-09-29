#include <SDL2/SDL.h>
#include "window/window.h"
#include "fps/fps.h"
#include <sstream>
#include <stdio.h>
#include "Noises/earth.hpp"
#include "Noises/jupiter.hpp"
#include <tbb/tbb.h>
#include <glm/glm.hpp>
#include "obj.h"
#include "uniform/uniform.h"
#include "matrixes/matrixes.hpp"
#include "framebuffer/framebuffer.h"
#include "tex/tex.h"

float angle = 3.14f / 3.0f;
Uniforms uniform;
std::vector<glm::vec3> vertexes;
std::vector<glm::vec3> normals;
std::vector<glm::vec3> originals;
std::vector<glm::vec3> vertexes2;
std::vector<glm::vec3> normals2;
std::vector<glm::vec3> originals2;

glm::vec3 eye = glm::vec3(0, 10.0f, 0.10f);
glm::vec3 center = glm::vec3(0, 0, 0);

std::vector<Fragment> stars;
int numStars = 1500;

float moonAxisX = 1.5f;
float moonAxisZ = 2.0f;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

float minX = 0;
float maxX = 0;
float minY = 0;
float maxY = 0;

glm::vec3 translate = glm::vec3(0.0f, -0.25f, 0.0f);

bool setup(uint16_t SCREEN_WIDTH, uint16_t SCREEN_HEIGHT)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cerr << "Error: Failed to initialize SDL: " << SDL_GetError() << std::endl;
    return false;
  }

  window = SDL_CreateWindow("Software Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, 0);
  if (!window)
  {
    std::cerr << "Error: Failed to create SDL window: " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer)
  {
    std::cerr << "Error: Failed to create SDL renderer: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

void setTextures()
{
  setEarthSystemNoise(rand(), rand(), rand());
  SetJupiterNoise();
}

int main(int argc, char *argv[])
{
  if (!setup(620, 480))
  {
    return 1;
  }
  loadObj("./models/sphere.obj", vertexes, normals, originals);
  vertexes2 = vertexes;
  normals2 = normals;
  originals2 = originals;

  setTextures();

  for (int i = 0; i < numStars; i++)
  {
    float x = static_cast<float>(rand() % SCREEN_WIDTH);
    float y = static_cast<float>(rand() % SCREEN_HEIGHT);
    float z = INT16_MAX - 1;

    Color color(210, 210, 210);

    stars.push_back(Fragment{glm::vec3(x, y, z), color, 1.0f, glm::vec3(x, y, z)});
  }

  bool running = true;
  while (running)
  {
    startFPS();
    angle += 1;
    /*     eye.y += 0.05f; */

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = false;
      }
      else
      {
        switch (event.type)
        {
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym)
          {
          case SDLK_UP:
            eye.z += 0.05f;
            center.z += 0.05f;
            clearMoonOrbit();
            break;
          case SDLK_DOWN:
            eye.z -= 0.05f;
            center.z -= 0.05f;
            clearMoonOrbit();
            break;
          case SDLK_RIGHT:
            eye.x -= 0.05f;
            center.x -= 0.05f;
            clearMoonOrbit();
            break;
          case SDLK_LEFT:
            eye.x += 0.05f;
            center.x += 0.05f;
            clearMoonOrbit();
            break;
          case SDLK_PAGEUP:
            eye.y += 0.05f;
            clearMoonOrbit();
            break;
          case SDLK_PAGEDOWN:
            eye.y -= 0.05f;
            clearMoonOrbit();
            break;
          case SDLK_i:
            if (eye.z + 0.05f == 0.0f)
            {
              eye.z == 0.01f;
              clearMoonOrbit();
            }
            else
            {
              eye.z += 0.05f;
              clearMoonOrbit();
            }
            break;
          case SDLK_k:
            if (eye.z - 0.05f == 0.0f)
            {
              eye.z == 0.01f;
              clearMoonOrbit();
            }
            else
            {
              eye.z -= 0.05f;
              clearMoonOrbit();
            }
            break;
          case SDLK_r:
            eye = glm::vec3(0, 10.0f, 0.10f);
            center = glm::vec3(0, 0, 0);
            clearMoonOrbit();
            break;
          }
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    clearFrameBuffer();
    SDL_RenderClear(renderer);

    size_t degrees = 360*5;

/*     tbb::parallel_for(size_t(0), degrees, [&](size_t i)
                      { 
                        float angle =  i * (M_PI/45);
                        glm::vec3 pos = glm::vec3(floor(400.0f * cos(0.05 * angle)) + SCREEN_WIDTH/2.0f, floor(400.0f * sin(0.05 * angle)) + SCREEN_HEIGHT/2.0f, INT32_MAX-2.0f);
                        Fragment frag = Fragment{pos, Color(50, 50, 50), 0.1f, pos};
                        point(frag); }); */

    uniform.model = createModelMatrix(translate, glm::vec3(0.7f / 2.5f, 1.0f / 2.5f, 1.0f / 2.5f), glm::vec3(0.0f, 1.0f, 0.0f), angle + 0.5);
    uniform.view = createViewMatrix(eye, center, glm::vec3(0, 1, 0));
    uniform.projection = createProjectionMatrix(1200, 800);
    uniform.viewport = createViewportMatrix(1200, 800);

    render(vertexes, normals, originals, uniform, 1);

    uniform.model = createModelMatrix(glm::vec3(moonAxisX * sin(0.05 * angle), 0.0f, moonAxisZ * cos(0.05 * angle)) + translate, glm::vec3(0.63f / 5.0f, 1.0f / 5.0f, 1.0f / 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), angle);
    uniform.view = createViewMatrix(eye, center, glm::vec3(0, 1, 0));
    uniform.projection = createProjectionMatrix(1200, 800);
    uniform.viewport = createViewportMatrix(1200, 800);

    render(vertexes2, normals2, originals2, uniform, 2);

    renderBuffer(renderer);
    endFPS(window);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
