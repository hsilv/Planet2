#ifndef PLANET_H
#define PLANET_H
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include "../fragment/fragment.h"
#include "../color/color.h"
#include "tbb/tbb.h"

class Satelite
{
public:
    uint16_t textIndex;
    std::vector<Fragment> orbit;
    std::vector<glm::vec3> vertexes;
    std::vector<glm::vec3> originals;
    std::vector<glm::vec3> normals;
    glm::vec3 translate;
    glm::vec3 scale;
    glm::vec3 rotate;
    Color orbitColor;
    float angle;
    float axisX;
    float axisY;
    float axisAngle = 0.0f;
    float angularSpeed = 0.05f;
    glm::vec3 center;
    glm::vec3 L;

    int planetWidthU = INT32_MIN;
    int planetWidthD = INT32_MAX;
    int planetHeightU = INT32_MIN;
    int planetHeightD = INT32_MAX;
    int planetDepthU = INT32_MIN;
    int planetDepthD = INT32_MAX;

    Satelite(
        uint16_t textIndex,
        std::vector<glm::vec3> vertexes,
        std::vector<glm::vec3> originals,
        std::vector<glm::vec3> normals,
        glm::vec3 translate,
        glm::vec3 scale,
        glm::vec3 rotate,
        Color orbitColor,
        float angle) : textIndex(textIndex),
                       vertexes(vertexes),
                       originals(originals),
                       normals(normals),
                       translate(translate),
                       scale(scale),
                       rotate(rotate),
                       orbitColor(orbitColor),
                       angle(angle) {}

    std::vector<Fragment> getOrbit()
    {
        return orbit;
    }

    void calculateLight(glm::vec3 source)
    {
        L = translate - source;
        L = -L;
        L = glm::normalize(L);
    }

    void setTranslation(glm::vec3 fatherTrans)
    {
        translate = glm::vec3(axisX * sin(angularSpeed * angle), 0.0f, axisY * cos(angularSpeed * angle)) + fatherTrans;
    }

    void clearOrbit()
    {
        orbit.clear();
        orbit.shrink_to_fit();
    }

    void addOrbitPoint(int x, int y, int z)
    {
        if (orbit.size() >= 1500)
        {
            clearOrbit();
        };
        orbit.push_back(Fragment{glm::vec3(x, y, z), orbitColor, 0.1f, glm::vec3(x, y, z)});
        center = glm::vec3(x, y, z);
    }

    void setBoundings(Fragment frag)
    {
        planetWidthD = planetWidthD < frag.position.x ? planetWidthD : floor(frag.position.x);
        planetWidthU = planetWidthU > frag.position.x ? planetWidthU : floor(frag.position.x);
        planetHeightD = planetHeightD < frag.position.y ? planetHeightD : floor(frag.position.y);
        planetHeightU = planetHeightU > frag.position.y ? planetHeightU : floor(frag.position.y);
        planetDepthD = planetDepthD < frag.position.z ? planetDepthD : floor(frag.position.z);
        planetDepthU = planetDepthU > frag.position.z ? planetDepthU : floor(frag.position.z);
    }

    void resetBoundings()
    {
        planetWidthU = INT32_MIN;
        planetWidthD = INT32_MAX;
        planetHeightU = INT32_MIN;
        planetHeightD = INT32_MAX;
        planetDepthU = INT32_MIN;
        planetDepthD = INT32_MAX;
    }

    void setOrbit()
    {
        int x = floor(planetWidthD + ((planetWidthU - planetWidthD) / 2.0f));
        int y = floor(planetHeightD + ((planetHeightU - planetHeightD) / 2.0f));
        int z = floor(planetDepthD + ((planetDepthU - planetDepthD) / 2.0f));
        addOrbitPoint(x, y, z);
    }
};

class Planet
{
public:
    std::vector<Satelite> satelites;
    uint16_t textIndex;
    std::vector<Fragment> orbit;
    std::vector<glm::vec3> vertexes;
    std::vector<glm::vec3> originals;
    std::vector<glm::vec3> normals;
    glm::vec3 translate;
    glm::vec3 scale;
    glm::vec3 rotate;
    Color orbitColor;
    float angle;
    float axisX;
    float axisY;
    float angularSpeed;
    float axisAngle = 0.0f;
    glm::vec3 center;
    glm::vec3 L;

    int planetWidthU = INT32_MIN;
    int planetWidthD = INT32_MAX;
    int planetHeightU = INT32_MIN;
    int planetHeightD = INT32_MAX;
    int planetDepthU = INT32_MIN;
    int planetDepthD = INT32_MAX;

    Planet(){};

    Planet(
        uint16_t textIndex,
        std::vector<glm::vec3> vertexes,
        std::vector<glm::vec3> originals,
        std::vector<glm::vec3> normals,
        glm::vec3 translate,
        glm::vec3 scale,
        glm::vec3 rotate,
        Color orbitColor,
        float angle) : textIndex(textIndex),
                       vertexes(vertexes),
                       originals(originals),
                       normals(normals),
                       translate(translate),
                       scale(scale),
                       rotate(rotate),
                       orbitColor(orbitColor),
                       angle(angle) {}

    std::vector<Fragment> getOrbit()
    {
        return orbit;
    }

    void calculateLight(glm::vec3 source)
    {
        L = translate - source;
        L = -L;
        L = glm::normalize(L);
    }

    void setTranslation(glm::vec3 fatherTrans)
    {
        translate = glm::vec3(axisX * sin(angularSpeed * angle), 0.0f, axisY * cos(angularSpeed * angle)) + fatherTrans;
    }

    void clearOrbit()
    {
        orbit.clear();
        orbit.shrink_to_fit();
        for (int i = 0; i < satelites.size(); i++)
        {
            Satelite satel = satelites[i];
            satel.clearOrbit();
            satelites[i] = satel;
        }
    }

    void addOrbitPoint(int x, int y, int z)
    {
        if (orbit.size() >= 1500)
        {
            clearOrbit();
        };
        orbit.push_back(Fragment{glm::vec3(x, y, z), orbitColor, 0.1f, glm::vec3(x, y, z)});
        center = glm::vec3(x, y, z);
    }

    void addSatelite(Satelite satelite)
    {
        satelites.push_back(satelite);
    }

    void setBoundings(Fragment frag)
    {
        planetWidthD = planetWidthD < frag.position.x ? planetWidthD : floor(frag.position.x);
        planetWidthU = planetWidthU > frag.position.x ? planetWidthU : floor(frag.position.x);
        planetHeightD = planetHeightD < frag.position.y ? planetHeightD : floor(frag.position.y);
        planetHeightU = planetHeightU > frag.position.y ? planetHeightU : floor(frag.position.y);
        planetDepthD = planetDepthD < frag.position.z ? planetDepthD : floor(frag.position.z);
        planetDepthU = planetDepthU > frag.position.z ? planetDepthU : floor(frag.position.z);
    }

    void resetBoundings()
    {
        planetWidthU = INT32_MIN;
        planetWidthD = INT32_MAX;
        planetHeightU = INT32_MIN;
        planetHeightD = INT32_MAX;
        planetDepthU = INT32_MIN;
        planetDepthD = INT32_MAX;
    }

    void setOrbit()
    {
        int x = floor(planetWidthD + ((planetWidthU - planetWidthD) / 2.0f));
        int y = floor(planetHeightD + ((planetHeightU - planetHeightD) / 2.0f));
        int z = floor(planetDepthD + ((planetDepthU - planetDepthD) / 2.0f));
        addOrbitPoint(x, y, z);
    }
};

class Star
{
public:
    std::vector<Planet> planets;
    uint16_t textIndex;
    std::vector<Fragment> orbit;
    std::vector<glm::vec3> vertexes;
    std::vector<glm::vec3> originals;
    std::vector<glm::vec3> normals;
    glm::vec3 translate;
    glm::vec3 scale;
    glm::vec3 rotate;
    Color orbitColor;
    float angle = 0.0f;
    float axisX = 0.0f;
    float axisY = 0.0f;
    float angularSpeed = 0.0f;
    float axisAngle = 0.0f;
    glm::vec3 center;
    glm::vec3 L;

    int planetWidthU = INT32_MIN;
    int planetWidthD = INT32_MAX;
    int planetHeightU = INT32_MIN;
    int planetHeightD = INT32_MAX;
    int planetDepthU = INT32_MIN;
    int planetDepthD = INT32_MAX;

    Star(){};

    Star(
        uint16_t textIndex,
        std::vector<glm::vec3> vertexes,
        std::vector<glm::vec3> originals,
        std::vector<glm::vec3> normals,
        glm::vec3 translate,
        glm::vec3 scale,
        glm::vec3 rotate,
        Color orbitColor,
        float angle) : textIndex(textIndex),
                       vertexes(vertexes),
                       originals(originals),
                       normals(normals),
                       translate(translate),
                       scale(scale),
                       rotate(rotate),
                       orbitColor(orbitColor),
                       angle(angle) {}

    std::vector<Fragment> getOrbit()
    {
        return orbit;
    }

    void setAura(Color auraColor, tbb::concurrent_vector<Fragment> &starFrags)
    {
        tbb::parallel_for(size_t(0), starFrags.size(), [&](size_t i)
                          {
                              float numY = (M_PI * starFrags[i].position.y + M_PI * ((planetHeightU - planetHeightD) / 2.0f));
                              float intensityY = abs(sin(numY / planetHeightU)) * M_PI;
                              intensityY = pow(intensityY, 1.0f);
                              float numX = (M_PI * starFrags[i].position.x + M_PI * ((planetWidthU - planetWidthD) / 2.0f));
                              float intensityX = abs(sin(numX / planetWidthU)) * M_PI;
                              intensityX = pow(intensityX, 1.0f);
                              float intensity = (intensityY+intensityX) / 2.0f;
                              intensity = intensity >= 1.0f ? 1.0f : intensity;
                              starFrags[i].color = auraColor * intensity + starFrags[i].color * (1.0f - intensity); });
    }

    void calculateLight(glm::vec3 source)
    {
        L = translate - source;
        L = -L;
        L = glm::normalize(L);
    }

    void setTranslation()
    {
        translate = glm::vec3(axisX * sin(angularSpeed * angle), 0.0f, axisY * cos(angularSpeed * angle));
    }

    void clearOrbit()
    {
        orbit.clear();
        orbit.shrink_to_fit();
        for (int i = 0; i < planets.size(); i++)
        {
            Planet planet = planets[i];
            planet.clearOrbit();
            planets[i] = planet;
        }
    }

    void addOrbitPoint(int x, int y, int z)
    {
        if (orbit.size() >= 1500)
        {
            clearOrbit();
        };
        orbit.push_back(Fragment{glm::vec3(x, y, z), orbitColor, 0.1f, glm::vec3(x, y, z)});
        center = glm::vec3(x, y, z);
    }

    void addPlanet(Planet planet)
    {
        planets.push_back(planet);
    }

    void setBoundings(Fragment frag)
    {
        planetWidthD = planetWidthD < frag.position.x ? planetWidthD : floor(frag.position.x);
        planetWidthU = planetWidthU > frag.position.x ? planetWidthU : floor(frag.position.x);
        planetHeightD = planetHeightD < frag.position.y ? planetHeightD : floor(frag.position.y);
        planetHeightU = planetHeightU > frag.position.y ? planetHeightU : floor(frag.position.y);
        planetDepthD = planetDepthD < frag.position.z ? planetDepthD : floor(frag.position.z);
        planetDepthU = planetDepthU > frag.position.z ? planetDepthU : floor(frag.position.z);
    }

    void resetBoundings()
    {
        planetWidthU = INT32_MIN;
        planetWidthD = INT32_MAX;
        planetHeightU = INT32_MIN;
        planetHeightD = INT32_MAX;
        planetDepthU = INT32_MIN;
        planetDepthD = INT32_MAX;
    }

    void setOrbit()
    {
        int x = floor(planetWidthD + ((planetWidthU - planetWidthD) / 2.0f));
        int y = floor(planetHeightD + ((planetHeightU - planetHeightD) / 2.0f));
        int z = floor(planetDepthD + ((planetDepthU - planetDepthD) / 2.0f));
        addOrbitPoint(x, y, z);
    }
};
#endif