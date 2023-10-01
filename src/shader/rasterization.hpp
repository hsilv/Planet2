#ifndef RASTERIZATION_H
#define RASTERIZATION_H

#include <vector>
#include "../fragment/fragment.h"
#include "../vertex/vertex3.h"
#include "triangle.hpp"
#include "../SolarSys/planet.h"

tbb::concurrent_vector<Fragment> rasterize(const std::vector<std::vector<Vertex>> &triangles, glm::vec3 L)
{
    tbb::concurrent_vector<Fragment> fragments;

    tbb::parallel_for(size_t(0), triangles.size(), [&](size_t i){
        std::vector<Vertex> triangleVertices = triangles[i];

        std::vector<Fragment> triangleFrags = triangle(
            triangleVertices[0],
            triangleVertices[1],
            triangleVertices[2],
            L);
        
        for (Fragment frag: triangleFrags){
            fragments.push_back(frag);
        }
    });
    return fragments;
}

#endif