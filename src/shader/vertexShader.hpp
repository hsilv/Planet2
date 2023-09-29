#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "../vertex/vertex3.h"
#include "../uniform/uniform.h"
#include <glm/glm.hpp>
#include "../matrixes/matrixes.hpp"

Vertex vertexShader(const Vertex &vertex, const Uniforms &uniforms)
{
    glm::vec4 r = uniforms.viewport * uniforms.projection * uniforms.view * uniforms.model.resultant * glm::vec4(vertex.position.x, vertex.position.y, vertex.position.z, 1);
    glm::vec4 n = uniforms.model.rotation * glm::vec4(vertex.normal.x, vertex.normal.y, vertex.normal.z, 1);
    glm::vec3 normal = glm::vec3(n.x, n.y, n.z);
    normal = glm::normalize(normal);
    return Vertex{
        glm::vec3(r.x / r.w, r.y / r.w, r.z * r.x),
        normal,
        vertex.position,
        vertex.color};
}

#endif