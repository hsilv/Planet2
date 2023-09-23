#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H

#include "../fragment/fragment.h"
#include "../color/color.h"
#include "../Noises/earth.hpp"
#include "../Noises/jupiter.hpp"

Fragment fragmentShader(Fragment &frag, uint8_t textIndex)
{
    Color color;
    if (textIndex == 2)
    {
        color = getMoonTexture(frag.original.x * 100, frag.original.y * 100, frag.original.z * 100);
    }
    else if (textIndex == 1)
    {
        color = getEarthTexture(frag.original.x * 75, frag.original.y * 75, frag.original.z * 75);
    }
    else if (textIndex == 3)
    {
        color = GetJupiterTexture(frag.original.x*75, frag.original.y*75, frag.original.z*75);
    }
    else
    {
        color = Color(210, 210, 210);
    }
    frag.color = color * frag.intensity;
    return frag;
}

#endif