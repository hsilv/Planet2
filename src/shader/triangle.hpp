#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glm/glm.hpp>
#include <vector>
#include "../vertex/vertex3.h"
#include "../fragment/fragment.h"
#include "../framebuffer/framebuffer.h"
#include "../Noises/earth.hpp"

std::pair<float, float> barycentricCoordinates(const glm::ivec2 &P, const glm::vec3 &A, const glm::vec3 &B, const glm::vec3 &C)
{
    
    glm::vec3 bary = glm::cross(
        glm::vec3(C.x - A.x, B.x - A.x, A.x - P.x),
        glm::vec3(C.y - A.y, B.y - A.y, A.y - P.y));

    if (abs(bary.z) < 1)
    {
        return std::make_pair(-1, -1);
    }

    return std::make_pair(
        bary.y / bary.z,
        bary.x / bary.z);
}

std::vector<Fragment> triangle(Vertex a, Vertex b, Vertex c, const glm::vec3 &L)
{
    std::vector<Fragment> frags;
    glm::vec3 A = a.position;
    glm::vec3 B = b.position;
    glm::vec3 C = c.position;

    int minX = std::min(std::min(A.x, B.x), C.x);
    int minY = std::min(std::min(A.y, B.y), C.y);
    int maxX = std::max(std::max(A.x, B.x), C.x);
    int maxY = std::max(std::max(A.y, B.y), C.y);

    for (float y = minY; y <= maxY; y++)
    {
        for (float x = minX; x <= maxX; x++)
        {
            if (x < 0 || y < 0 || y > SCREEN_HEIGHT || x > SCREEN_WIDTH)
                continue;

            glm::vec3 P = {x, y, 0.0f};
            auto bar = barycentricCoordinates(P, A, B, C);

            float w = 1 - bar.first - bar.second;
            float v = bar.first;
            float u = bar.second;

            float minbar = 1e-50;

            if (w < minbar || v < minbar || u < minbar)
                continue;

            P.z = A.z * w + B.z * v + C.z * u;

            glm::vec3 fragNormal = a.normal * w + b.normal * v + c.normal * u;
            fragNormal = glm::normalize(fragNormal);

            float intensity = glm::dot(fragNormal, L);

            if (intensity <= 0.1)
                intensity = 0.1;

            Color fragColor = {255, 255, 255};

            glm::vec3 original = a.originals * w + b.originals * v + c.originals * u;

            frags.push_back(Fragment{P, fragColor, intensity, original});
            
        }
    }

    return frags;
}
#endif