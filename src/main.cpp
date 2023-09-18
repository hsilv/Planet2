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
std::vector<glm::vec3> vertexes2;
std::vector<glm::vec3> normals2;
std::vector<glm::vec3> originals2;

std::vector<Fragment> stars;
int numStars = 650;

float moonAxisX = 1.5;
float moonAxisZ = 1.5;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

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

int main(int argc, char *argv[])
{
  if (!setup(620, 480))
  {
    return 1;
  }
  setTerrainNoise(rand(), rand(), rand());
  loadObj("./models/sphere.obj", vertexes, normals, originals);
  vertexes2 = vertexes;
  normals2 = normals;
  originals2 = originals;

  for (int i = 0; i < numStars; i++)
  {
    float x = static_cast<float>(rand() % SCREEN_WIDTH);
    float y = static_cast<float>(rand() % SCREEN_HEIGHT);
    float z = INT16_MAX-1;

    Color color(210, 210, 210);

    stars.push_back(Fragment{glm::vec3(x, y, z), color, 1.0f, glm::vec3(x, y, z)});
  }

  bool running = true;
  while (running)
  {
    startFPS();
    angle += 1;

    uniform.model = createModelMatrix(glm::vec3(0.0f, -0.25f, 0.0f), glm::vec3(0.7f / 2.5f, 1.0f / 2.5f, 1.0f / 2.5f), glm::vec3(0.0f, 1.0f, 0.0f), angle + 0.5);
    uniform.view = createViewMatrix(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    uniform.projection = createProjectionMatrix(1200, 800);
    uniform.viewport = createViewportMatrix(1200, 800);

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

    render(vertexes, normals, originals, uniform, 0);

    uniform.model = createModelMatrix(glm::vec3(moonAxisX * sin(0.05 * angle), -0.25f, moonAxisZ * cos(0.05 * angle)), glm::vec3(0.63f / 8.0f, 1.0f / 8.0f, 1.0f / 8.0f), glm::vec3(0.0f, 1.0f, 0.0f), angle);
    uniform.view = createViewMatrix(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    uniform.projection = createProjectionMatrix(1200, 800);
    uniform.viewport = createViewportMatrix(1200, 800);

    render(vertexes2, normals2, originals2, uniform, 2);

    tbb::parallel_for(size_t(0), stars.size(), [&](size_t i)
                      { point(stars[i]); });

    renderBuffer(renderer);
    endFPS(window);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
