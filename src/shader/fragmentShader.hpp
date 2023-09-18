#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H

#include "../fragment/fragment.h"
#include "../color/color.h"
#include "../Noises/earth.hpp"

Fragment fragmentShader(Fragment &frag, uint8_t textIndex)
{
    Color color;
    if (textIndex == 2)
    {
        color = getMoonTexture(frag.original.x * 100, frag.original.y * 100, frag.original.z * 100);
    }
    else
    {
        color = getEarthTexture(frag.original.x * 75, frag.original.y * 75, frag.original.z * 75);
    }
    frag.color = color * frag.intensity;
    return frag;
}

#endif