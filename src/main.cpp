#include <SDL2/SDL.h>
#include "window/window.h"
#include "fps/fps.h"
#include <sstream>
#include <stdio.h>
#include "FastNoise/FastNoise.h"
#include "Noises/earth.hpp"
#include <tbb/tbb.h>
#include <glm/glm.hpp>
#include "obj.h"
#include "uniform/uniform.h"
#include "matrixes/matrixes.hpp"
#include "framebuffer/framebuffer.h"

float angle = 3.14f / 3.0f;
Uniforms uniform;
std::vector<glm::vec3> vertexes;
std::vector<glm::vec3> normals;
std::vector<glm::vec3> originals;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

bool setup(uint16_t SCREEN_WIDTH, uint16_t SCREEN_HEIGHT)
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cerr << "Error: Failed to initialize SDL: " << SDL_GetError() << std::endl;
    return false;
  }

  window = SDL_CreateWindow("Software Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
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

int main(int argc, char *argv[])
{
  if (!setup(620, 480))
  {
    return 1;
  }
  setTerrainNoise(rand(), rand());
  loadObj("./models/sphere.obj", vertexes, normals, originals);
  bool running = true;
  while (running)
  {
    startFPS();

    uniform.model = createModelMatrix(glm::vec3(5.0f, 4.0f, 0.0f), glm::vec3(0.42f * 2.25, 0.5f * 2.25, 0.5f * 2.25), glm::vec3(0.0f, 1.0f, 0.0f), angle += 1);
    uniform.view = createViewMatrix(glm::vec3(0, 0, -5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    uniform.projection = createProjectionMatrix(620, 480);
    uniform.viewport = createViewportMatrix(620, 480);

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = false;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    clearFrameBuffer();
    SDL_RenderClear(renderer);
    renderTexture(renderer);
    renderBuffer(renderer);
    endFPS(window);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
