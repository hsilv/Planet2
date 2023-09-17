#ifndef UNIFORM_H
#define UNIFORM_H

#include <glm/glm.hpp>

struct Uniforms {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 viewport;
};

#endif