#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H

#include "../fragment/fragment.h"
#include "../color/color.h"
#include "../Noises/earth.hpp"
#include "../Noises/jupiter.hpp"

int moonWidthU = INT32_MIN;
int moonWidthD = INT32_MAX;
int moonHeightU = INT32_MIN;
int moonHeightD = INT32_MAX;
int moonDepthU = INT32_MIN;
int moonDepthD = INT32_MAX;

Fragment fragmentShader(Fragment &frag, uint8_t textIndex)
{
    Color color;
    if (textIndex == 2)
    {
        color = getMoonTexture(frag.original.x * 100, frag.original.y * 100, frag.original.z * 100);
        moonWidthD = moonWidthD < frag.position.x ? moonWidthD : floor(frag.position.x);
        moonWidthU = moonWidthU > frag.position.x ? moonWidthU : floor(frag.position.x);
        moonHeightD = moonHeightD < frag.position.y ? moonHeightD : floor(frag.position.y);
        moonHeightU = moonHeightU > frag.position.y ? moonHeightU : floor(frag.position.y);
        moonDepthD = moonDepthD < frag.position.z ? moonDepthD : floor(frag.position.z);
        moonDepthU = moonDepthU > frag.position.z ? moonDepthU : floor(frag.position.z);
    }
    else if (textIndex == 1)
    {
        color = getEarthTexture(frag.original.x * 75, frag.original.y * 75, frag.original.z * 75);
    }
    else if (textIndex == 3)
    {
        color = GetJupiterTexture(frag.original.x * 75, frag.original.y * 75, frag.original.z * 75);
    }
    else
    {
        color = Color(210, 210, 210);
    }
    frag.color = color * frag.intensity;
    return frag;
}

void resetDimens()
{
    moonWidthU = INT32_MIN;
    moonWidthD = INT32_MAX;
    moonHeightU = INT32_MIN;
    moonHeightD = INT32_MAX;
    moonDepthU = INT32_MIN;
    moonDepthD = INT32_MAX;
}

void setMoonOrbit()
{
    int x = floor(moonWidthD + ((moonWidthU - moonWidthD) / 2.0f));
    int y = floor(moonHeightD + ((moonHeightU - moonHeightD) / 2.0f));
    int z = floor(moonDepthD + ((moonDepthU - moonDepthD) / 2.0f));
    addMoonOrbitPoint(x, y, z);
}

#endif