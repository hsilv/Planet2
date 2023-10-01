#ifndef SETSYS_H
#define SETSYS_H

#include <vector>
#include "glm/glm.hpp"
#include "../color/color.h"
#include "./planet.h"

Star setSystem(std::vector<glm::vec3> vertexes,
                std::vector<glm::vec3> originals,
                std::vector<glm::vec3> normals,
                float angle)
{
  Star sun;
  Planet earth;
  glm::vec3 translateSun = glm::vec3(0.0f, -0.25f, 0.0f);
  glm::vec3 scaleSun = glm::vec3(0.7f / 1.2f, 1.0f / 1.2f, 1.0f / 1.2f);
  glm::vec3 rotateSun = glm::vec3(0.0f, 1.0f, 0.0f);
  float angleSun = angle;
  uint16_t textIndex = 1;
  Color orbitColor = Color(0, 0, 255);
  sun = Star(textIndex, vertexes, originals, normals, translateSun, scaleSun, rotateSun, orbitColor, angle);
  glm::vec3 translateEarth = glm::vec3(0.0f, -0.25f, 0.0f);
  glm::vec3 scaleEarth = glm::vec3(0.7f / 2.5f, 1.0f / 2.5f, 1.0f / 2.5f);
  glm::vec3 rotateEarth = glm::vec3(0.0f, 1.0f, 0.0f);
  float angleEarth = angle;
  earth = Planet(textIndex, vertexes, originals, normals, translateEarth, scaleEarth, rotateEarth, orbitColor, angle);
  earth.axisX = 20.5f;
  earth.axisY = 27.0f;
  earth.angularSpeed = 0.025f;
  earth.setTranslation(sun.translate);
  earth.calculateLight(sun.translate);
  float angleMoonSat = angle + 0.5f;
  Color moonSatOrbitColor = Color(150, 100, 100);
  glm::vec3 scaleMoonSat = glm::vec3(0.63f / 5.0f, 1.0f / 5.0f, 1.0f / 5.0f);
  glm::vec3 rotateMoonSat = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 translateMoonSat = glm::vec3(0.0f * sin(0.05 * angle), 0.0f, 0.0f * cos(0.05 * angle)) + translateEarth;
  Satelite moonSat = Satelite(2, vertexes, originals, normals, translateMoonSat, scaleMoonSat, rotateMoonSat, moonSatOrbitColor, angleMoonSat);
  moonSat.axisX = 1.5f;
  moonSat.axisY = 2.0f;
  moonSat.angularSpeed = 0.2f;
  moonSat.setTranslation(translateEarth);
  moonSat.calculateLight(sun.translate);
  earth.satelites.push_back(moonSat);
  moonSatOrbitColor = Color(100, 150, 100);
  Satelite moonSat2 = Satelite(2, vertexes, originals, normals, translateMoonSat, scaleMoonSat * 0.5f, rotateMoonSat, moonSatOrbitColor, angleMoonSat);
  moonSat2.axisX = 3.5f;
  moonSat2.axisY = 4.4f;
  moonSat2.setTranslation(translateEarth);
  moonSat2.calculateLight(sun.translate);
  earth.satelites.push_back(moonSat2);
  sun.planets.push_back(earth);
  return sun;
}


#endif