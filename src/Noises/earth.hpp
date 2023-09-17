#ifndef EARTH_H
#define EARTH_H

#include "SDL.h"
#include "../FastNoise/FastNoise.h"
#include "../color/color.h"
#include "../framebuffer/framebuffer.h"

long terrainSeed;
long cloudSeed;
float minor;
float maxor;
float a = 0.0f;
FastNoiseLite terrain;
FastNoiseLite warp;
FastNoiseLite beach;
FastNoiseLite clouds;
FastNoiseLite cloudWarp;
Color continent = {55, 125, 35};
Color beachColor = {111, 73, 52};
Color oceanColor = {40, 60, 110};
Color cloudColor = {255, 255, 255};

void setTerrainNoise(long terrSeed, long clSeed)
{
    terrainSeed = terrSeed;
    cloudSeed = clSeed;
    terrain.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
    terrain.SetSeed(terrainSeed);
    terrain.SetFrequency(0.010);
    terrain.SetFractalType(FastNoiseLite::FractalType_None);
    terrain.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
    terrain.SetCellularReturnType(FastNoiseLite::CellularReturnType_CellValue);
    terrain.SetCellularJitter(1.00f);
    terrain.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2);
    terrain.SetDomainWarpAmp(100.0f);
    terrain.SetFractalType(FastNoiseLite::FractalType_DomainWarpIndependent);
    terrain.SetFractalOctaves(8);
    terrain.SetFractalLacunarity(2.20f);
    terrain.SetFractalGain(0.60f);
    beach.SetNoiseType(FastNoiseLite::NoiseType_Cellular);
    beach.SetSeed(terrainSeed);
    beach.SetFrequency(0.010);
    beach.SetFractalType(FastNoiseLite::FractalType_None);
    beach.SetCellularDistanceFunction(FastNoiseLite::CellularDistanceFunction_Hybrid);
    beach.SetCellularReturnType(FastNoiseLite::CellularReturnType_Distance);
    beach.SetCellularJitter(1.00f);
    beach.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2);
    beach.SetDomainWarpAmp(100.0f);
    beach.SetFractalType(FastNoiseLite::FractalType_DomainWarpIndependent);
    beach.SetFractalOctaves(8);
    beach.SetFractalLacunarity(2.20f);
    beach.SetFractalGain(0.60f);
    clouds.SetNoiseType(FastNoiseLite::NoiseType_Value);
    clouds.SetSeed(cloudSeed);
    clouds.SetFrequency(0.015f);
    clouds.SetFractalType(FastNoiseLite::FractalType_None);
    cloudWarp.SetDomainWarpType(FastNoiseLite::DomainWarpType_BasicGrid);
    cloudWarp.SetDomainWarpAmp(75.00f);
    cloudWarp.SetFrequency(0.005f);
    cloudWarp.SetSeed(cloudSeed);
    ;
    cloudWarp.SetFractalType(FastNoiseLite::FractalType_DomainWarpProgressive);
    cloudWarp.SetFractalOctaves(6);
    cloudWarp.SetFractalLacunarity(2.00f);
    cloudWarp.SetFractalGain(0.60f);
    warp.SetSeed(terrainSeed);
};

float getTerrainNoise(int x, int y)
{
    float newX = static_cast<float>(x);
    float newY = static_cast<float>(y);
    terrain.DomainWarp(newX, newY);
    return terrain.GetNoise(newX, newY, 0.0f);
}

float getBeachNoise(int x, int y)
{
    float newX = static_cast<float>(x);
    float newY = static_cast<float>(y);
    beach.DomainWarp(newX, newY);
    return beach.GetNoise(newX, newY, 0.0f);
}

float getCloudNoise(int x, int y)
{
    float newX = static_cast<float>(x);
    float newY = static_cast<float>(y);
    cloudWarp.DomainWarp(newX, newY);
    return clouds.GetNoise(newX, newY, 0.0f);
}

void renderTexture(SDL_Renderer *renderer)
{
    a += 5;
    Color RenderColor;
    for (int x = a; x < 620 + a; x++)
    {
        for (int y = a; y < 480 + a; y++)
        {
            float color = getTerrainNoise(x, y);
            if (color * 255 < 0)
            {
                float clouds = (0.2 + getCloudNoise(x, y)) / 3.5;
                if (clouds < 0)
                {
                    clouds = 0;
                }
                float beachNoise = getBeachNoise(x, y);
                Color Ncolor = continent + (beachColor * beachNoise) + (cloudColor * clouds);
                if (Ncolor.getGreen() < Ncolor.getBlue() || Ncolor.getGreen() < Ncolor.getRed())
                {
                    Ncolor = Color(10, 89, 16);
                }
                RenderColor = Ncolor;
                /* SDL_SetRenderDrawColor(renderer, Ncolor.getRed(), Ncolor.getGreen(), Ncolor.getBlue(), SDL_ALPHA_OPAQUE); */
            }
            else
            {
                float clouds = (0.4 + getCloudNoise(x, y)) / 2.5;
                if (clouds < 0)
                {
                    clouds = 0;
                }
                Color Ncolor = oceanColor;
                Ncolor = Ncolor + (cloudColor * clouds);
                RenderColor = Ncolor;
                /* SDL_SetRenderDrawColor(renderer, Ncolor.getRed(), Ncolor.getGreen(), Ncolor.getBlue(), SDL_ALPHA_OPAQUE); */
            }
            point(Fragment{glm::vec3(x - a, y - a, 0.0f), RenderColor});
            /* SDL_RenderDrawPoint(renderer, x - a, y - a); */
        }
    }
}

#endif