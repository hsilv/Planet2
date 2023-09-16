#include <SDL2/SDL.h>
#include "window/window.h"
#include "fps/fps.h"
#include <sstream>
#include <stdio.h>
#include "FastNoise/FastNoise.h"

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
  long terrainSeed = random();
  FastNoiseLite noise;
  noise.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
  noise.SetSeed(terrainSeed);
  noise.SetFrequency(0.010);
  noise.SetFractalType(FastNoiseLite::FractalType_None);
  noise.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
  noise.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);
  noise.SetCellularJitter(1.00f);
  noise.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2);
  noise.SetDomainWarpAmp(100.0f);
  noise.SetFractalType(FastNoiseLite::FractalType_DomainWarpIndependent);
  noise.SetFractalOctaves(8);
  noise.SetFractalLacunarity(2.20f);
  noise.SetFractalGain(0.60f);
  FastNoiseLite warp;
  while (running)
  {
    a++;
    startFPS();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        running = false;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    for (int x = 0; x < 620; x++)
    {
      for (int y = 0; y < 480; y++)
      {
        float newX = static_cast<float>(x);
        float newY = static_cast<float>(y);
        noise.DomainWarp(newX, newY);
        float color = noise.GetNoise(newX, newY);
        SDL_SetRenderDrawColor(renderer, color * 255, color * 255, color * 255, 0);
        SDL_RenderDrawPoint(renderer, x, y);
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
