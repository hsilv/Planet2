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
float stripeHeight = 35.0f;
float stripeHeight3 = 60.0f;

const int JUPWIDTH = 1200;
const int JUPHEIGHT = 800;

int maxY = 0;
int maxX = 0;

std::array<std::array<Color, JUPHEIGHT>, JUPWIDTH> tex;
std::array<std::array<glm::vec2, JUPHEIGHT>, JUPWIDTH> texI;

void SetJupiterNoise()
{
/*    Color base = {222, 224, 209};
    Color color = {153, 115, 69};
    std::array<Color, 800> vTex;
    std::array<glm::vec2, JUPHEIGHT> vIndex;
    std::fill(vTex.begin(), vTex.end(), base);
    std::fill(tex.begin(), tex.end(), vTex);
    std::fill(vIndex.begin(), vIndex.end(), glm::vec2(0.0f, 0.0f));
    std::fill(texI.begin(), texI.end(), vIndex);

    for (int x = 0; x < JUPHEIGHT; x++)
    {
        for (int y = 0; y < JUPWIDTH; y++)
        {
            float intens = 1 - abs(sin(y / stripeHeight));
            tex[x][y] = (color * intens) + (base * (1 - intens));
            int newX = x;
            int newY = y;
            texI[newX][newY] = glm::vec2(newX, newY);
        }
        
    }
    jupiter.SetNoiseType(FastNoiseLite::NoiseType_Value); */
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
    /* jupiter.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    jupiter.SetFrequency(0.020f);
    jupiter.SetFractalType(FastNoiseLite::FractalType_None); */
}

/* void disturbJupiterTexture()
{
    float bandFact = 0.3f;
    int numbands = 4;
    float Dscale = 8.0f;
    float amp = 15.0f;
    float DscaleY = Dscale * float(JUPHEIGHT) / float(JUPWIDTH);
    
    float dx1, dy1, dx2, dy2, du, dd, magx, magy, velocity, dx, dy;

    for (int x = 0; x < JUPWIDTH; x++)
    {
        for (int y = 0; y < JUPHEIGHT; y++)
        {
            dx = ((rand() % 100) * 0.005) - 0.25;
            dy = ((rand() % 100) * 0.005) - 0.25;
            dx1 = ((float(x - 1) + dx)) * Dscale;
            dy1 = ((float(y - 1) + dy)) * DscaleY;
            dx = ((rand() % 100) * 0.005) - 0.25;
            dy = ((rand() % 100) * 0.005) - 0.25;
            dx2 = ((float(x + 1) + dx)) * Dscale;
            dy2 = ((float(y + 1) + dy)) * DscaleY;

            du = (1+jupiter.GetNoise(dx1, dy1, 0.0f))/2;
            dd = (1+jupiter.GetNoise(dx2, dy1, 0.0f))/2;

            magy = -amp * (du - dd);

            dd = (1+jupiter.GetNoise(dx1, dy2, 0.0f))/2;

            magx = amp * (du - dd);

            float vx = magx + bandFact * cos(float(y) / (float(JUPHEIGHT) * numbands * M_PI));
            float vy = magy;

            glm::vec2 indexes = texI[x][y];
            indexes.x += vx;
            indexes.y += vy;
            texI[x][y] = indexes;
        }
    }
} */

Color GetJupiterTexture(float x, float y, float z)
{
    float newX = x;
    float newY = y;
    float newZ = z;
    float baseX = x*3;
    float baseY = x*10;
    float baseZ = z*3;


    Color base = {222, 224, 209};
    Color base2 = {222-50, 224-50, 209-50};
    Color color = {153, 115, 69};

    float intens = 1 - abs(sin(y / stripeHeight));
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

    color = (color * intens)+ (base2 * (1-intens));

    return color;
}

#endif