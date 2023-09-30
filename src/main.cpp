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

glm::vec3 eye = glm::vec3(0, 50.0f, 0.10f);
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

Planet earth;

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

void setPlanets(std::vector<glm::vec3> vertexes,
                std::vector<glm::vec3> originals,
                std::vector<glm::vec3> normals)
{
  glm::vec3 translateEarth = glm::vec3(0.0f, -0.25f, 0.0f);
  glm::vec3 scaleEarth = glm::vec3(0.7f / 2.5f, 1.0f / 2.5f, 1.0f / 2.5f);
  glm::vec3 rotateEarth = glm::vec3(0.0f, 1.0f, 0.0f);
  float angleEarth = angle;
  uint16_t textIndex = 1;
  Color orbitColor = Color(0, 0, 255);
  earth = Planet(textIndex, vertexes, originals, normals, translateEarth, scaleEarth, rotateEarth, orbitColor, angle);
  earth.axisX = 10.5f;
  earth.axisY = 14.0f;
  earth.angularSpeed = 0.025f;
  earth.setTranslation();
  glm::vec3 translateMoon = glm::vec3(moonAxisX * sin(0.05 * angle), 0.0f, moonAxisZ * cos(0.05 * angle)) + translateEarth;
  float angleMoon = angle + 0.5f;
  Color moonOrbitColor = Color(100, 100, 100);
  glm::vec3 scaleMoon = glm::vec3(0.63f / 5.0f, 1.0f / 5.0f, 1.0f / 5.0f);
  glm::vec3 rotateMoon = glm::vec3(0.0f, 1.0f, 0.0f);
  Satelite moon = Satelite(2, vertexes, originals, normals, translateMoon, scaleMoon, rotateMoon, moonOrbitColor, angleMoon);
  moon.axisX = 1.5f;
  moon.axisY = 2.0f;
  moon.angularSpeed = 0.2f;
  moon.setTranslation(translateEarth);
  earth.satelites.push_back(moon);
  Satelite moon2 = Satelite(2, vertexes, originals, normals, translateMoon, scaleMoon * 0.5f, rotateMoon, moonOrbitColor, angleMoon);
  moon2.axisX = 3.5f;
  moon2.axisY = 4.4f;
  moon2.setTranslation(translateEarth);
  earth.satelites.push_back(moon2);
}

void resetOrbits(){
  earth.clearOrbit();
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
  setPlanets(vertexes, originals, normals);

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
              clearMoonOrbit();
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

    earth.angle = angle;
    earth.setTranslation();
    uniform.model = createModelMatrix(earth.translate, earth.scale, earth.rotate, earth.angle + 0.5);
    uniform.view = createViewMatrix(eye, center, glm::vec3(0, 1, 0));
    uniform.projection = createProjectionMatrix(1200, 800);
    uniform.viewport = createViewportMatrix(1200, 800);

    render(vertexes, normals, originals, uniform, earth);

    for (int i = 0; i < earth.satelites.size(); i++)
    {
      Satelite satel = earth.satelites[i];
      satel.angle = angle;
      satel.setTranslation(earth.translate);
      uniform.model = createModelMatrix(satel.translate, satel.scale, satel.rotate, satel.angle);
      uniform.view = createViewMatrix(eye, center, glm::vec3(0, 1, 0));
      uniform.projection = createProjectionMatrix(1200, 800);
      uniform.viewport = createViewportMatrix(1200, 800);
      render(satel.vertexes, satel.normals, satel.originals, uniform, satel);
      earth.satelites[i] = satel;
    }

    renderBuffer(renderer);
    endFPS(window);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
