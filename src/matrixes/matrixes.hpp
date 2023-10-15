#ifndef MATRIXES_H
#define MATRIXES_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "../uniform/uniform.h"

void printMatrix(glm::mat4 matrix)
{
    printf("Matriz: [ \n");
    printf("%lf, %lf, %lf, %lf \n", matrix[0][0], matrix[0][1], matrix[0][2], matrix[0][3]);
    printf("%lf, %lf, %lf, %lf \n", matrix[1][0], matrix[1][1], matrix[1][2], matrix[1][3]);
    printf("%lf, %lf, %lf, %lf \n", matrix[2][0], matrix[2][1], matrix[2][2], matrix[2][3]);
    printf("%lf, %lf, %lf, %lf \n", matrix[3][0], matrix[3][1], matrix[3][2], matrix[3][3]);
    printf("] \n");
}

modelMatrix createModelMatrix(glm::vec3 translateV, glm::vec3 scaleV, glm::vec3 rotationV, float rotationD)
{
    glm::mat4 translation = glm::mat4(1);
    translation = glm::translate(translation, translateV);

    glm::mat4 scale = glm::mat4(1);
    scale = glm::scale(scale, scaleV);

    glm::mat4 rotation = glm::mat4(1);
    rotation = glm::rotate(rotation, glm::radians(rotationD), rotationV);

    return modelMatrix{translation, scale, rotation, translation * scale * rotation};
}

glm::mat4 createViewMatrix(glm::vec3 eye, glm::vec3 lookPoint, glm::vec3 up)
{
    glm::mat4 viewMatrix;
    viewMatrix = glm::lookAtLH(eye, lookPoint, up);
    return viewMatrix;
}

glm::mat4 createProjectionMatrix(int wWidth, int wHeight)
{
    glm::mat4 perspective;
    float fovInDegrees = 45.0f;
    float aspectRatio = wWidth / wHeight;
    float nearClip = 0.1f;
    float farClip = 0.15f;

    perspective = glm::perspective(glm::radians(fovInDegrees), aspectRatio, nearClip, farClip);

    return perspective;
}

glm::mat4 createViewportMatrix(int wWidth, int wHeight)
{
    glm::mat4 viewport = glm::mat4(1);

    viewport = glm::scale(viewport, glm::vec3(wWidth/2.0f, wHeight/2.0f, 0.5f));
    viewport = glm::translate(viewport, glm::vec3(1.0f, 1.0f, 0.5f));

    return viewport;
}

#endif