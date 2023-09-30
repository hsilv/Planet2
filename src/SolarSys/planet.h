#ifndef PLANET_H
#define PLANET_H
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include "../fragment/fragment.h"
#include "../color/color.h"

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
    float angularSpeed = 0.05f;

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

    void setTranslation()
    {
        translate = glm::vec3(axisX * sin(angularSpeed * angle), 0.0f, axisY * cos(angularSpeed * angle));
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

#endif