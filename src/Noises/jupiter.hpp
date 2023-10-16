#ifndef JUPITER_H
#define JUPITER_H

#include "SDL.h"
#include "../FastNoise/FastNoise.h"
#include "../color/color.h"
#include <tbb/tbb.h>
#include "glm/glm.hpp"
#include <vector>
#include <array>

FastNoiseLite jupiter;
FastNoiseLite jupiterWarp;
FastNoiseLite jupiterBase;
FastNoiseLite jupiterBaseWarp;

FastNoiseLite gany;
FastNoiseLite ganyWarp;

Color ganyColor = {100, 127, 131};

float stripeHeight = 35.0f;
float stripeHeight3 = 120.0f;

const int JUPWIDTH = 1200;
const int JUPHEIGHT = 800;

int maxY = 0;
int maxX = 0;

std::array<std::array<Color, JUPHEIGHT>, JUPWIDTH> tex;
std::array<std::array<glm::vec2, JUPHEIGHT>, JUPWIDTH> texI;

void SetJupiterNoise()
{
    jupiter.SetFrequency(0.005f);
    jupiter.SetFractalType(FastNoiseLite::FractalType_FBm);
    jupiter.SetFractalOctaves(5);
    jupiter.SetFractalLacunarity(2.00f);
    jupiter.SetFractalGain(0.50f);
    jupiter.SetFractalWeightedStrength(0.20f);
    jupiterWarp.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2Reduced);
    jupiterWarp.SetDomainWarpAmp(145.0f);
    jupiterWarp.SetFrequency(0.010f);
    jupiterWarp.SetFractalType(FastNoiseLite::FractalType_DomainWarpProgressive);
    jupiterWarp.SetFractalOctaves(7);
    jupiterWarp.SetFractalLacunarity(1.40f);
    jupiterWarp.SetFractalGain(0.60f);
    jupiterBase.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
    jupiterBase.SetFrequency(0.015f);
    jupiterBase.SetFractalType(FastNoiseLite::FractalType_FBm);
    jupiterBase.SetFractalOctaves(5);
    jupiterBase.SetFractalLacunarity(2.00f);
    jupiterBase.SetFractalGain(0.50f);
    jupiterBase.SetFractalWeightedStrength(0.30f);
    jupiterBaseWarp.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2);
    jupiterBaseWarp.SetRotationType3D(FastNoiseLite::RotationType3D_ImproveXZPlanes);
    jupiterBaseWarp.SetDomainWarpAmp(60.0f);
    jupiterBaseWarp.SetFrequency(0.010f);
    jupiterBaseWarp.SetFractalType(FastNoiseLite::FractalType_DomainWarpIndependent);
    jupiterBaseWarp.SetFractalOctaves(5);
    jupiterBaseWarp.SetFractalLacunarity(1.10f);
    jupiterBaseWarp.SetFractalGain(1.00f);

    long seed = rand();
    gany.SetSeed(seed);
    gany.SetRotationType3D(FastNoiseLite::RotationType3D_ImproveXYPlanes);
    gany.SetFrequency(0.020f);
    gany.SetFractalType(FastNoiseLite::FractalType_FBm);
    gany.SetFractalOctaves(5);
    gany.SetFractalLacunarity(2.10f);
    gany.SetFractalGain(0.90f);
    gany.SetFractalWeightedStrength(0.50f);
    ganyWarp.SetSeed(seed);
    ganyWarp.SetDomainWarpType(FastNoiseLite::DomainWarpType_BasicGrid);
    ganyWarp.SetDomainWarpAmp(25.00f);
    ganyWarp.SetFrequency(0.010f);
}

Color GetJupiterTexture(float x, float y, float z)
{
    float newX = x;
    float newY = y;
    float newZ = z;
    float baseX = x * 3;
    float baseY = x * 10;
    float baseZ = z * 3;

    Color base = {222, 224, 209};
    Color base2 = {222 - 50, 224 - 50, 209 - 50};
    Color color = {153, 115, 69};
    float stripeThickness = 120.0f;

    float intens = pow(1 - abs(sin(y * (3.14159265359 / stripeThickness))), 0.6f);
    float intens2 = 1 - abs(sin(y / stripeHeight3));

    jupiterBaseWarp.DomainWarp(baseX, baseY, baseZ);
    float baseNoise = (1 + jupiterBase.GetNoise(baseX, baseY, baseZ)) / 4 + 0.4;
    base = base * baseNoise;
    base = (base * intens2) + (base2 * (1 - intens2));

    jupiterWarp.DomainWarp(newX, newY, newZ);
    float noise = (1 + jupiter.GetNoise(newX, newY, newZ)) / 2;
    color = color * noise;

    if (noise >= 0.35)
    {
        Color newColor = color;
        color = {72 + 50, 38 + 50, 20 + 50};
        color = (color * noise) + (newColor * (1 - noise));
    }
    else
    {
        Color newColor = color;
        color = {155 + 50, 38 + 50, 20 + 50};
        color = (color * noise) + (newColor * (1 - noise));
    }

    color = (color * intens) + (base2 * (1 - intens));

    return color;
}

Color GetGanyTexture(float x, float y, float z)
{
    ganyWarp.DomainWarp(x, y, z);
    float noise = (1 + gany.GetNoise(x, y, z)) / 1.0f;
    return (ganyColor * noise) + (Color(255, 255, 255) * (1.0f - noise));
}

#endif