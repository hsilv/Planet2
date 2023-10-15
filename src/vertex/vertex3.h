#ifndef VERTEX3_H
#define VERTEX3_H

#include <glm/glm.hpp>
#include "../color/color.h"

struct Vertex3 {
    float x, y, z;
    
    Vertex3(float xValue, float yValue, float zValue) : x(xValue), y(yValue), z(zValue) {}
};

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 originals;
    Color color;
    bool renderizable;
};

#endif