#ifndef FRAGMENTSHADER_H
#define FRAGMENTSHADER_H

#include "../fragment/fragment.h"
#include "../color/color.h"
#include "../Noises/earth.hpp"
#include "../Noises/jupiter.hpp"
#include "../Noises/sun.hpp"
#include "../SolarSys/planet.h"
#include "../Noises/mars.hpp"

Fragment fragmentShader(Fragment &frag, Planet &planet)
{
    Color color;
    if (planet.textIndex == 2)
    {
        color = getMoonTexture(frag.original.x * 75, frag.original.y * 75, frag.original.z * 75);
        planet.setBoundings(frag);
    }
    else if (planet.textIndex == 1)
    {
        color = getEarthTexture(frag.original.x * 75 * 5, frag.original.y * 75 * 5, frag.original.z * 75 * 5);
        planet.setBoundings(frag);
    }
    else if (planet.textIndex == 3)
    {
        color = GetJupiterTexture(frag.original.x * 75 * 5, frag.original.y * 75 * 5, frag.original.z * 75 * 5);
        planet.setBoundings(frag);
    }
    else if (planet.textIndex == 5)
    {
        color = GetMarsTexture(frag.original.x * 75 * 5, frag.original.y * 75 * 5, frag.original.z * 75 * 5);
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
        color = getMoonTexture(frag.original.x * 100 * 5, frag.original.y * 100 * 5, frag.original.z * 100 * 5);
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
    else if (planet.textIndex == 5)
    {
        color = GetMarsTexture(frag.original.x * 75 * 20, frag.original.y * 75 * 20, frag.original.z * 75 * 20);
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
    Color color;
    if (planet.textIndex == 4)
    {
        color = getSunTexture(frag.original.x * 500, frag.original.y * 500, frag.original.z * 500);
        planet.setBoundings(frag);
    }
    else
    {
        color = Color(255, 133, 41);
    }
    frag.color = color * 1.4f;
    return frag;
}
#endif