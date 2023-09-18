#ifndef EARTH_H
#define EARTH_H

#include "SDL.h"
#include "../FastNoise/FastNoise.h"
#include "../color/color.h"
#include <tbb/tbb.h>

long terrainSeed;
long cloudSeed;
long moonSeed;
float minor;
float maxor;
float a = 0.0f;
FastNoiseLite terrain;
FastNoiseLite warp;
FastNoiseLite beach;
FastNoiseLite clouds;
FastNoiseLite cloudWarp;
FastNoiseLite moon;
FastNoiseLite moonWarp;
Color continent = {55, 125, 35};
Color beachColor = {111, 73, 52};
Color oceanColor = {40, 60, 110};
Color cloudColor = {255, 255, 255};

void setTerrainNoise(long terrSeed, long clSeed, long mnSeed)
{
    terrainSeed = terrSeed;
    cloudSeed = clSeed;
    moonSeed = mnSeed;
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
    cloudWarp.SetFractalType(FastNoiseLite::FractalType_DomainWarpProgressive);
    cloudWarp.SetFractalOctaves(6);
    cloudWarp.SetFractalLacunarity(2.00f);
    cloudWarp.SetFractalGain(0.60f);
    warp.SetSeed(terrainSeed);
    moon.SetSeed(moonSeed);
    moon.SetNoiseType(FastNoiseLite::NoiseType_Value);
    moon.SetFrequency(0.010f);
    moon.SetFractalType(FastNoiseLite::FractalType_FBm);
    moon.SetFractalOctaves(5);
    moon.SetFractalLacunarity(2.90f);
    moon.SetFractalGain(0.50f);
    moon.SetFractalWeightedStrength(0.20f);
    moonWarp.SetSeed(moonSeed);
    moonWarp.SetDomainWarpType(FastNoiseLite::DomainWarpType_BasicGrid);
    moonWarp.SetDomainWarpAmp(100.00f);
    moonWarp.SetFrequency(0.005f);
};

float getTerrainNoise(int x, int y, int z)
{
    float newX = static_cast<float>(x);
    float newY = static_cast<float>(y);
    float newZ = static_cast<float>(z);
    terrain.DomainWarp(newX, newY, newZ);
    return terrain.GetNoise(newX, newY, newZ);
}

float getBeachNoise(int x, int y, int z)
{
    float newX = static_cast<float>(x);
    float newY = static_cast<float>(y);
    float newZ = static_cast<float>(z);
    beach.DomainWarp(newX, newY, newZ);
    return beach.GetNoise(newX, newY, newZ);
}

float getCloudNoise(int x, int y, int z)
{
    float newX = static_cast<float>(x);
    float newY = static_cast<float>(y);
    float newZ = static_cast<float>(z);
    cloudWarp.DomainWarp(newX, newY, newZ);
    return clouds.GetNoise(newX, newY, newZ);
}

float getTerrainNoise(float x, float y, float z)
{
    terrain.DomainWarp(x, y, z);
    return terrain.GetNoise(x, y, z);
}

float getBeachNoise(float x, float y, float z)
{
    beach.DomainWarp(x, y, z);
    return beach.GetNoise(x, y, z);
}

float getCloudNoise(float x, float y, float z)
{
    cloudWarp.DomainWarp(x, y, z);
    return clouds.GetNoise(x, y, z);
}

Color getMoonTexture(float x, float y, float z)
{
    Color RenderColor = {255, 255, 255};
    moonWarp.DomainWarp(x, y, z);
    float noise = (1 + moon.GetNoise(x, y, z))/2.5f;
    return RenderColor * noise;
}

Color getMoonTexture(int x, int y, int z)
{
    return getMoonTexture(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
}

Color getMoonTexture(float x, float y)
{
    return getMoonTexture(x, y, 0.0f);
}

Color getMoonTexture(int x, int y)
{
    return getMoonTexture(x, y, 0);
}

Color getEarthTexture(int x, int y, int z)
{
    Color RenderColor;
    float color = getTerrainNoise(x, y, z);
    if (color * 255 < 0)
    {
        float clouds = (0.2 + getCloudNoise(x, y, z)) / 3.5;
        if (clouds < 0)
        {
            clouds = 0;
        }
        float beachNoise = getBeachNoise(x, y, z);
        Color Ncolor = continent + (beachColor * beachNoise) + (cloudColor * clouds);
        if (Ncolor.getGreen() < Ncolor.getBlue() || Ncolor.getGreen() < Ncolor.getRed())
        {
            Ncolor = Color(10, 89, 16);
        }
        RenderColor = Ncolor;
    }
    else
    {
        float clouds = (0.4 + getCloudNoise(x, y, z)) / 2.5;
        if (clouds < 0)
        {
            clouds = 0;
        }
        Color Ncolor = oceanColor;
        Ncolor = Ncolor + (cloudColor * clouds);
        RenderColor = Ncolor;
    }
    return RenderColor;
}

Color getEarthTexture(float x, float y, float z)
{
    Color RenderColor;
    float color = getTerrainNoise(x, y, z);
    if (color * 255 < 0)
    {
        float clouds = (0.2 + getCloudNoise(x, y, z)) / 3.5;
        if (clouds < 0)
        {
            clouds = 0;
        }
        float beachNoise = getBeachNoise(x, y, z);
        Color Ncolor = continent + (beachColor * beachNoise) + (cloudColor * clouds);
        if (Ncolor.getGreen() < Ncolor.getBlue() || Ncolor.getGreen() < Ncolor.getRed())
        {
            Ncolor = Color(10, 89, 16);
        }
        RenderColor = Ncolor;
    }
    else
    {
        float clouds = (0.4 + getCloudNoise(x, y, z)) / 2.5;
        if (clouds < 0)
        {
            clouds = 0;
        }
        Color Ncolor = oceanColor;
        Ncolor = Ncolor + (cloudColor * clouds);
        RenderColor = Ncolor;
    }
    return RenderColor;
}

Color getEarthTexture(int x, int y)
{
    return getEarthTexture(x, y, 0);
}

#endif