#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H

#include "../fragment/fragment.h"
#include "../color/color.h"
#include "../Noises/earth.hpp"
#include "../Noises/jupiter.hpp"
#include "../SolarSys/planet.h"

Fragment fragmentShader(Fragment &frag, Planet &planet)
{
    Color color;
    if (planet.textIndex == 2)
    {
        color = getMoonTexture(frag.original.x * 100, frag.original.y * 100, frag.original.z * 100);
        planet.setBoundings(frag);
    }
    else if (planet.textIndex == 1)
    {
        color = getEarthTexture(frag.original.x * 75, frag.original.y * 75, frag.original.z * 75);
        planet.setBoundings(frag);
    }
    else if (planet.textIndex == 3)
    {
        color = GetJupiterTexture(frag.original.x * 75, frag.original.y * 75, frag.original.z * 75);
        planet.setBoundings(frag);
    }
    else
    {
        color = Color(210, 210, 210);
    }
    frag.color = color * frag.intensity;
    return frag;
}

Fragment fragmentShader(Fragment &frag, Satelite &planet)
{
    Color color;
    if (planet.textIndex == 2)
    {
        color = getMoonTexture(frag.original.x * 100, frag.original.y * 100, frag.original.z * 100);
        planet.setBoundings(frag);
    }
    else if (planet.textIndex == 1)
    {
        color = getEarthTexture(frag.original.x * 75, frag.original.y * 75, frag.original.z * 75);
        planet.setBoundings(frag);
    }
    else if (planet.textIndex == 3)
    {
        color = GetJupiterTexture(frag.original.x * 75, frag.original.y * 75, frag.original.z * 75);
        planet.setBoundings(frag);
    }
    else
    {
        color = Color(210, 210, 210);
    }
    frag.color = color * frag.intensity;
    return frag;
}

Fragment fragmentShader(Fragment &frag, Star &planet)
{
    frag.color = Color(210, 210, 50) * 1.0f;
    return frag;
}
#endif