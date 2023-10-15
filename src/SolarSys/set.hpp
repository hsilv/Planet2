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
  glm::vec3 translateSun = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 scaleSun = glm::vec3(0.7f / 0.25f, 1.0f / 0.25f, 1.0f / 0.25f);
  glm::vec3 rotateSun = glm::vec3(0.0f, 1.0f, 0.0f);
  float angleSun = angle;
  uint16_t textIndex = 1;
  Color orbitColor = Color(0, 0, 255);
  sun = Star(4, vertexes, originals, normals, translateSun, scaleSun, rotateSun, orbitColor, angle);
  glm::vec3 translateEarth = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 scaleEarth = glm::vec3(0.7f / 0.75f, 1.0f / 0.75f, 1.0f / 0.75f);
  glm::vec3 rotateEarth = glm::vec3(0.0f, 1.0f, 0.0f);
  float angleEarth = angle;
  earth = Planet(textIndex, vertexes, originals, normals, translateEarth, scaleEarth, rotateEarth, orbitColor, angle);
  earth.axisX = 10.5f;
  earth.axisY = 17.0f;
  earth.angularSpeed = 0.025f;
  earth.setTranslation(sun.translate);
  earth.calculateLight(sun.translate);
  uint16_t textMoon = 2;
  float angleMoonSat = angle + 0.5f;
  Color moonSatOrbitColor = Color(150, 100, 100);
  glm::vec3 scaleMoonSat = glm::vec3(0.63f / 5.0f, 1.0f / 5.0f, 1.0f / 5.0f);
  glm::vec3 rotateMoonSat = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 translateMoonSat = glm::vec3(0.0f * sin(0.05 * angle), 0.0f, 0.0f * cos(0.05 * angle)) + translateEarth;
  Satelite moonSat = Satelite(textMoon, vertexes, originals, normals, translateMoonSat, scaleMoonSat, rotateMoonSat, moonSatOrbitColor, angleMoonSat);
  moonSat.axisX = 1.5f;
  moonSat.axisY = 2.0f;
  moonSat.angularSpeed = 0.2f;
  moonSat.setTranslation(translateEarth);
  moonSat.calculateLight(sun.translate);
  earth.satelites.push_back(moonSat);
  moonSatOrbitColor = Color(100, 150, 100);
  Satelite moonSat2 = Satelite(textMoon, vertexes, originals, normals, translateMoonSat, scaleMoonSat * 0.5f, rotateMoonSat, moonSatOrbitColor, angleMoonSat);
  moonSat2.axisX = 3.5f;
  moonSat2.axisY = 4.4f;
  moonSat2.setTranslation(translateEarth);
  moonSat2.calculateLight(sun.translate);
  earth.satelites.push_back(moonSat2);
  sun.planets.push_back(earth);
  glm::vec3 scaleVenus = glm::vec3(0.63f / 1.0f, 1.0f / 1.0f, 1.0f / 1.0f);
  glm::vec3 translateVenus = glm::vec3(10.25f * sin(0.045f * 150.0f), 0.0f, 15.5f * cos(0.045f * 150.0f)) + translateSun;
  Planet venus = Planet(2, vertexes, originals, normals, translateVenus, scaleVenus, rotateEarth, Color(140, 127, 69), angle);
  venus.axisX = 10.25f;
  venus.axisY = 15.5f;
  venus.angularSpeed = 0.045f;
  venus.setTranslation(sun.translate);
  venus.calculateLight(sun.translate);
  sun.planets.push_back(venus);
  return sun;
}

#endif