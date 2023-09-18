#ifndef ASSEMBLY_H
#define ASSEMBLY_H

#include <vector>
#include "../vertex/vertex3.h"
#include <tbb/tbb.h>

std::vector<std::vector<Vertex>> primitiveAssembly(const std::vector<Vertex> &transformedVertices)
{
    std::vector<std::vector<Vertex>> assembled(transformedVertices.size() / 3);


    tbb::parallel_for(size_t(0), transformedVertices.size() / 3, [&](size_t i){
        std::vector<Vertex> vertexGroup;
        vertexGroup.push_back(transformedVertices[3 * i]);
        vertexGroup.push_back(transformedVertices[3 * i + 1]);
        vertexGroup.push_back(transformedVertices[3 * i + 2]);
        assembled[i] = vertexGroup;
    });

    return assembled;
}

#endif