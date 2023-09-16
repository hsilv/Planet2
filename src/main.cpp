#include <SDL2/SDL.h>
#include "window/window.h"
#include "fps/fps.h"
#include <sstream>
#include <stdio.h>
#include "FastNoise/FastNoise.h"
#include "Noises/earth.hpp"
#include <tbb/tbb.h>

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
int a = 0;

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

  bool running = true;
  while (running)
  {
    a++;
    startFPS();
    printf("Número de núcleos %i \n", 5);

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = false;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    setTerrainNoise();
    for (int x = a; x < 620 + a; x++)
    {
      for (int y = a; y < 480 + a; y++)
      {
        float color = getTerrainNoise(x, y);
        SDL_SetRenderDrawColor(renderer, color*255, color*255, color*255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawPoint(renderer, x - a, y - a);
      }
    }
    SDL_RenderPresent(renderer);
    endFPS(window);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
