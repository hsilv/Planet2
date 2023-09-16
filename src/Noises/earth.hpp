#ifndef EARTH_H
#define EARTH_H

#include "../FastNoise/FastNoise.h"

long terrainSeed = random();
FastNoiseLite terrain;
FastNoiseLite warp;

void setTerrainNoise()
{
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
};

float getTerrainNoise(int x, int y){
    float newX = static_cast<float>(x);
    float newY = static_cast<float>(y);
    terrain.DomainWarp(newX, newY);
    return terrain.GetNoise(newX, newY);
}

#endif