#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <tbb/tbb.h>
#include <stdio.h>
#include <array>
#include <mutex>
#include "../fragment/fragment.h"
#include "../color/color.h"
#include <vector>
#include "../uniform/uniform.h"
#include "../vertex/vertex3.h"
#include "../shader/vertexShader.hpp"
#include "../shader/assembly.hpp"
#include "../shader/fragmentShader.hpp"
#include "SDL.h"

Color clearColor(0, 0, 0);
Color currentColor(0, 0, 0);
constexpr size_t SCREEN_WIDTH = 1200;
constexpr size_t SCREEN_HEIGHT = 800;
std::mutex pointMutex;

#include "../shader/triangle.hpp"
#include "../shader/rasterization.hpp"

struct BO
{
    Color color;
    long z;
};

BO cleared = {clearColor, LONG_MAX};

std::array<BO, SCREEN_WIDTH * SCREEN_HEIGHT> frameBuffer;
std::array<std::mutex, SCREEN_WIDTH * SCREEN_HEIGHT> mutexes;

void clearFrameBuffer()
{
    std::fill(frameBuffer.begin(), frameBuffer.end(), cleared);
}

void point(Fragment f)
{
    if (f.position.x >= 0 && f.position.x < SCREEN_WIDTH && f.position.y >= 0 && f.position.y < SCREEN_HEIGHT)
    {
        std::lock_guard<std::mutex> lock(mutexes[f.position.y * SCREEN_WIDTH + f.position.x]);
        if (f.position.z < frameBuffer[f.position.y * SCREEN_WIDTH + f.position.x].z)
        {
            frameBuffer[f.position.y * SCREEN_WIDTH + f.position.x] = BO{f.color, static_cast<long>(f.position.z)};
        }
    }
}

void render(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec3> &text, Uniforms &u, Planet &planet)
{
    std::vector<Fragment> globalFrag;

    std::vector<Vertex> transformed(vertices.size());

    tbb::parallel_for(size_t(0), vertices.size(), [&](size_t i)
                      {
        Vertex vertex = {vertices[i], normals[i], text[i], Color(0.6f, 0.6f, 0.6f)};
        transformed[i] = vertexShader(vertex, u); });

    std::vector<std::vector<Vertex>> triangles = primitiveAssembly(transformed);

    tbb::concurrent_vector<Fragment> frags = rasterize(triangles, planet.L);

    tbb::parallel_for(size_t(0), frags.size(), [&](size_t i)
                      {
        Fragment frag = fragmentShader(frags[i], planet);
        point(frag); });

    planet.setOrbit();

    planet.resetBoundings();

    std::vector<Fragment> orbit = planet.getOrbit();

    tbb::parallel_for(size_t(0), orbit.size(), [&](size_t i)
                      {
                        point(orbit[i]); });
}

void render(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec3> &text, Uniforms &u, Star &planet)
{
    std::vector<Fragment> globalFrag;

    std::vector<Vertex> transformed(vertices.size());

    tbb::parallel_for(size_t(0), vertices.size(), [&](size_t i)
                      {
        Vertex vertex = {vertices[i], normals[i], text[i], Color(0.6f, 0.6f, 0.6f)};
        transformed[i] = vertexShader(vertex, u); });

    std::vector<std::vector<Vertex>> triangles = primitiveAssembly(transformed);

    tbb::concurrent_vector<Fragment> frags = rasterize(triangles, planet.L);

    tbb::parallel_for(size_t(0), frags.size(), [&](size_t i)
                      {
        Fragment frag = fragmentShader(frags[i], planet);
        point(frag); });

    planet.setOrbit();

    planet.resetBoundings();

    std::vector<Fragment> orbit = planet.getOrbit();

    tbb::parallel_for(size_t(0), orbit.size(), [&](size_t i)
                      {
                        point(orbit[i]); });
}

void render(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec3> &text, Uniforms &u, Satelite &satelite)
{
    std::vector<Fragment> globalFrag;

    std::vector<Vertex> transformed(vertices.size());

    tbb::parallel_for(size_t(0), vertices.size(), [&](size_t i)
                      {
        Vertex vertex = {vertices[i], normals[i], text[i], Color(0.6f, 0.6f, 0.6f)};
        transformed[i] = vertexShader(vertex, u); });

    std::vector<std::vector<Vertex>> triangles = primitiveAssembly(transformed);

    tbb::concurrent_vector<Fragment> frags = rasterize(triangles, satelite.L);

    tbb::parallel_for(size_t(0), frags.size(), [&](size_t i)
                      {
        Fragment frag = fragmentShader(frags[i], satelite);
        point(frag); });

    satelite.setOrbit();

    satelite.resetBoundings();

    std::vector<Fragment> orbit = satelite.getOrbit();

    tbb::parallel_for(size_t(0), orbit.size(), [&](size_t i)
                      {
                        point(orbit[i]); });
}

tbb::concurrent_vector<Fragment> getRenderFrags(std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec3> &text, Uniforms &u, uint8_t textIndex)
{
    Planet planet;
    std::vector<Fragment> globalFrag;

    std::vector<Vertex> transformed(vertices.size());

    tbb::parallel_for(size_t(0), vertices.size(), [&](size_t i)
                      {
        Vertex vertex = {vertices[i], normals[i], text[i], Color(0.6f, 0.6f, 0.6f)};
        transformed[i] = vertexShader(vertex, u); });

    std::vector<std::vector<Vertex>> triangles = primitiveAssembly(transformed);

    tbb::concurrent_vector<Fragment> frags = rasterize(triangles, planet.L);

    return frags;
}

void renderBuffer(SDL_Renderer *renderer)
{
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);

    void *texturePixels;
    int pitch;
    SDL_LockTexture(texture, NULL, &texturePixels, &pitch);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    Uint32 format = SDL_PIXELFORMAT_ARGB8888;
    SDL_PixelFormat *mappingFormat = SDL_AllocFormat(format);

    Uint32 *texturePixels32 = static_cast<Uint32 *>(texturePixels);
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            int framebufferY = SCREEN_HEIGHT - y - 1; // Reverse the order of rows
            int index = y * (pitch / sizeof(Uint32)) + x;
            const Color &color = frameBuffer[framebufferY * SCREEN_WIDTH + x].color;
            texturePixels32[index] = SDL_MapRGBA(mappingFormat, color.getRed(), color.getGreen(), color.getBlue(), 255);
        }
    }

    SDL_UnlockTexture(texture);
    SDL_Rect textureRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, texture, NULL, &textureRect);
    SDL_DestroyTexture(texture);

    SDL_RenderPresent(renderer);
}

#endif