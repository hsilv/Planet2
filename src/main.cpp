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
#include "SolarSys/set.hpp"

float angle = 3.14f / 3.0f;
Uniforms uniform;
std::vector<glm::vec3> vertexes;
std::vector<glm::vec3> normals;
std::vector<glm::vec3> originals;

glm::vec3 eye = glm::vec3(0, 100.01f, -7.0f);
glm::vec3 center = glm::vec3(0, 0, 0);

std::vector<Fragment> stars;
int numStars = 1500;

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;

Star sun;

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

void resetOrbits()
{
  sun.clearOrbit();
}

int main(int argc, char *argv[])
{
  if (!setup(620, 480))
  {
    return 1;
  }
  loadObj("./models/sphere.obj", vertexes, normals, originals);

  setTextures();
  sun = setSystem(vertexes, originals, normals, angle);

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
    angle += 0.4f;

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
            resetOrbits();
            break;
          case SDLK_DOWN:
            eye.z -= 0.05f;
            center.z -= 0.05f;
            resetOrbits();
            break;
          case SDLK_RIGHT:
            eye.x -= 0.05f;
            center.x -= 0.05f;
            resetOrbits();
            break;
          case SDLK_LEFT:
            eye.x += 0.05f;
            center.x += 0.05f;
            resetOrbits();
            break;
          case SDLK_PAGEUP:
            eye.y += 0.05f;
            resetOrbits();
            break;
          case SDLK_PAGEDOWN:
            eye.y -= 0.05f;
            resetOrbits();
            break;
          case SDLK_i:
            if (eye.z + 0.05f == 0.0f)
            {
              eye.z == 0.01f;
              resetOrbits();
            }
            else
            {
              eye.z += 0.05f;
              resetOrbits();
            }
            break;
          case SDLK_k:
            if (eye.z - 0.05f == 0.0f)
            {
              eye.z == 0.01f;
              resetOrbits();
            }
            else
            {
              eye.z -= 0.05f;
              resetOrbits();
            }
            break;
          case SDLK_r:
            eye = glm::vec3(0, 10.0f, 0.10f);
            center = glm::vec3(0, 0, 0);
            resetOrbits();
            break;
          }
        }
      }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    clearFrameBuffer();
    SDL_RenderClear(renderer);

    sun.axisAngle += 1.0f;
    sun.angle = angle;
    sun.setTranslation();
    uniform.model = createModelMatrix(sun.translate, sun.scale, sun.rotate, sun.axisAngle);
    uniform.view = createViewMatrix(eye, center, glm::vec3(0, 1, 0));
    uniform.projection = createProjectionMatrix(1200, 800);
    uniform.viewport = createViewportMatrix(1200, 800);
    render(vertexes, normals, originals, uniform, sun);

    for (int i = 0; i < sun.planets.size(); i++)
    {
      Planet planet = sun.planets[i];
      planet.axisAngle += 1.0f;
      planet.angle = angle;
      planet.setTranslation(sun.translate);
      planet.calculateLight(sun.translate);
      uniform.model = createModelMatrix(planet.translate, planet.scale, planet.rotate, planet.axisAngle);
      uniform.view = createViewMatrix(eye, center, glm::vec3(0, 1, 0));
      uniform.projection = createProjectionMatrix(1200, 800);
      uniform.viewport = createViewportMatrix(1200, 800);

      render(vertexes, normals, originals, uniform, planet);

      for (int j = 0; j < planet.satelites.size(); j++)
      {
        Satelite satel = planet.satelites[j];
        satel.angle = angle;
        satel.axisAngle += 0.8f;
        satel.setTranslation(planet.translate);
        satel.calculateLight(sun.translate);
        uniform.model = createModelMatrix(satel.translate, satel.scale, satel.rotate, satel.axisAngle);
        uniform.view = createViewMatrix(eye, center, glm::vec3(0, 1, 0));
        uniform.projection = createProjectionMatrix(1200, 800);
        uniform.viewport = createViewportMatrix(1200, 800);
        render(satel.vertexes, satel.normals, satel.originals, uniform, satel);
        planet.satelites[j] = satel;
      }
      sun.planets[i] = planet;
    }
    renderBuffer(renderer);
    endFPS(window);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
