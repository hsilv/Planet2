#ifndef sunNoise_H
#define sunNoise_H

#include "../FastNoise/FastNoise.h"
#include "../color/color.h"
#include "tbb/tbb.h"
#include "../fragment/fragment.h"

long sunNoiseSeed;
float increment = 0.1f;

FastNoiseLite sunNoise;
FastNoiseLite sunNoiseWarp;
float sunAuraAxisX;
float sunAuraAxisY;
float sunAuraAxisZ;
Color sunNoiseColor = {255, 133+30, 41+30};

void setSunNoise(long seed){
    sunNoiseSeed = seed;
    sunNoise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
    sunNoise.SetSeed(sunNoiseSeed);
    sunNoise.SetFrequency(0.020f);
    sunNoise.SetFractalType(FastNoiseLite::FractalType_FBm);
    sunNoise.SetFractalOctaves(5);
    sunNoise.SetFractalLacunarity(1.70f);
    sunNoise.SetFractalGain(0.60f);
    sunNoise.SetFractalWeightedStrength(0.20f);
    sunNoiseWarp.SetSeed(sunNoiseSeed);
    sunNoiseWarp.SetDomainWarpAmp(60.50f);
    sunNoiseWarp.SetFrequency(0.005f);
    sunNoiseWarp.SetDomainWarpType(FastNoiseLite::DomainWarpType_OpenSimplex2);
    sunNoiseWarp.SetFractalType(FastNoiseLite::FractalType_DomainWarpIndependent);
    sunNoiseWarp.SetFractalOctaves(7);
    sunNoiseWarp.SetFractalLacunarity(2.90f);
    sunNoiseWarp.SetFractalGain(0.30);
}

void incrementSunNoisePlane(){
    increment += 1.5f;
}

Color getSunTexture(float x, float y, float z){
    float newX = x;
    float newY = y;
    float newZ = z+increment;
    sunNoiseWarp.DomainWarp(newX, newY, newZ);
    float noise = (1 + sunNoise.GetNoise(newX, newY, newZ))/2.5f;
    return sunNoiseColor * noise;
}

#endif