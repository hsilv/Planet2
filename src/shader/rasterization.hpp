#ifndef RASTERIZATION_H
#define RASTERIZATION_H

#include <vector>
#include "../fragment/fragment.h"
#include "../vertex/vertex3.h"
#include "triangle.hpp"

tbb::concurrent_vector<Fragment> rasterize(const std::vector<std::vector<Vertex>> &triangles)
{
    tbb::concurrent_vector<Fragment> fragments;

    tbb::parallel_for(size_t(0), triangles.size(), [&](size_t i){
        std::vector<Vertex> triangleVertices = triangles[i];

        std::vector<Fragment> triangleFrags = triangle(
            triangleVertices[0],
            triangleVertices[1],
            triangleVertices[2]);
        
        for (Fragment frag: triangleFrags){
            fragments.push_back(frag);
        }
    });
/*     for (const std::vector<Vertex> triangleVertices : triangles)
    {
        std::vector<Fragment> triangleFrags = triangle(
            triangleVertices[0],
            triangleVertices[1],
            triangleVertices[2]);

        for(Fragment frag: triangleFrags){
            fragments.push_back(frag);
        }
    } */
    return fragments;
}

#endif