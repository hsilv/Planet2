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
    glm::mat4 MVP = uniforms.projection * uniforms.view * uniforms.model.resultant;
    glm::vec4 transformedVertex = MVP * glm::vec4(vertex.position.x, vertex.position.y, vertex.position.z, 1.0f);

    /* ESTA ES LA CONDICIÓN QUE NO RENDERIZA DIRECTAMENTE LO QUE ESTÉ DEMASIADO CERCA O PASE DETRÁS DE LA CÁMARA POR LO QUE YA SE PODRÁ ACERCAR A CUALQUIER DISTANCIA SIN AFECTAR EN DEMASÍA EL RENDIMIENTO*/
    if (transformedVertex.w <= -2.0f)
    {
        return Vertex{
            glm::vec3(r.x / r.w, r.y / r.w, r.z * r.x),
            normal,
            vertex.position,
            vertex.color,
            true};
    }
    else
    {
        return Vertex{
            glm::vec3(r.x / r.w, r.y / r.w, r.z * r.x),
            normal,
            vertex.position,
            vertex.color,
            false};
    }
}

#endif