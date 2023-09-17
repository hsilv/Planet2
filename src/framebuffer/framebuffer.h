#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdio.h>
#include <array>
#include <mutex>
#include "../fragment/fragment.h"
#include "../color/color.h"
#include "SDL.h"

Color clearColor(0, 0, 0);
Color currentColor(0, 0, 0);
constexpr size_t SCREEN_WIDTH = 620;
constexpr size_t SCREEN_HEIGHT = 480;

struct BO
{
    Color color;
    uint16_t z;
};

BO cleared = {clearColor, INT16_MAX};

std::array<BO, SCREEN_WIDTH * SCREEN_HEIGHT> frameBuffer;
std::array<std::mutex, SCREEN_WIDTH * SCREEN_HEIGHT> mutexes;

void clearFrameBuffer()
{
    std::fill(frameBuffer.begin(), frameBuffer.end(), cleared);
}

void point(Fragment f)
{
    std::lock_guard<std::mutex> lock(mutexes[f.position.y * SCREEN_WIDTH + f.position.x]);

    if (f.position.z < frameBuffer[f.position.y * SCREEN_WIDTH + f.position.x].z)
    {
        frameBuffer[f.position.y * SCREEN_WIDTH + f.position.x] = BO{f.color, static_cast<uint16_t>(f.position.z)};
    }
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