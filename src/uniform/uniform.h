#ifndef UNIFORM_H
#define UNIFORM_H

#include <glm/glm.hpp>

struct modelMatrix {
    glm::mat4 translation;
    glm::mat4 scale;
    glm::mat4 rotation;
    glm::mat4 resultant;
};

struct Uniforms {
    modelMatrix model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 viewport;
};

#endif