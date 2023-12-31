#ifndef FRAGMENT_H
#define FRAGMENT_H

#include <glm/glm.hpp>
#include "../color/color.h"


struct Fragment
{
    glm::vec3 position;
    Color color;
    float intensity;
    glm::vec3 original;
};

#endif