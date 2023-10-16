#ifndef MARS_H
#define MARS_H

#include "SDL.h"
#include "../FastNoise/FastNoise.h"
#include "../color/color.h"
#include <tbb/tbb.h>
#include <array>
#include <vector>
#include "glm/glm.hpp"
#include "../fragment/fragment.h"
#include "../tex/tex.h"
#include <map>

FastNoiseLite marsNoise;
FastNoiseLite marsNoiseWarp;

Color marsColor = {175, 104, 81};

void setMarsNoise()
{
    long seed = rand();
    marsNoise.SetSeed(seed);
    marsNoise.SetRotationType3D(FastNoiseLite::RotationType3D_ImproveXYPlanes);
    marsNoise.SetFrequency(0.020f);
    marsNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
    marsNoise.SetFractalOctaves(5);
    marsNoise.SetFractalLacunarity(2.10f);
    marsNoise.SetFractalGain(0.90f);
    marsNoise.SetFractalWeightedStrength(0.50f);
    marsNoiseWarp.SetSeed(seed);
    marsNoiseWarp.SetDomainWarpType(FastNoiseLite::DomainWarpType_BasicGrid);
    marsNoiseWarp.SetDomainWarpAmp(25.00f);
    marsNoiseWarp.SetFrequency(0.010f);
}

Color GetMarsTexture(float x, float y, float z)
{
    marsNoiseWarp.DomainWarp(x, y, z);
    float noise = (1 + marsNoise.GetNoise(x, y, z)) / 2.5f;
    return marsColor * noise;
}

#endif