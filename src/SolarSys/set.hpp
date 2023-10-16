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
  glm::vec3 scaleSun = glm::vec3(1.0f / 0.25f, 1.0f / 0.25f, 1.0f / 0.25f);
  glm::vec3 globalRotate = glm::vec3(0.0f, 1.0f, 0.0f);
  float angleSun = angle;
  Color orbitColor = Color(237, 195, 104);
  sun = Star(4, vertexes, originals, normals, translateSun, scaleSun, globalRotate, orbitColor, angle);

  glm::vec3 globalTranslate = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 scaleEarth = glm::vec3(1.0f, 1.0f, 1.0f);
  earth = Planet(1, vertexes, originals, normals, globalTranslate, scaleEarth, globalRotate, Color(40, 60, 110), angle);
  earth.axisX = 20.0f;
  earth.axisY = 17.0f;
  earth.angularSpeed = 0.035f;
  earth.calculateLight(sun.translate);
  earth.setTranslation(sun.translate);

  glm::vec3 scaleMoon = glm::vec3(0.70f, 0.70f, 0.70f);

  Satelite earthMoon = Satelite(2, vertexes, originals, normals, globalTranslate, scaleMoon, globalRotate, Color(64, 64, 64), angle);
  earthMoon.axisX = 3.5f;
  earthMoon.axisY = 3.5f;
  earthMoon.angularSpeed = 0.240f;
  earthMoon.setTranslation(earth.translate);
  earthMoon.calculateLight(sun.translate);

  earth.satelites.push_back(earthMoon);

  sun.planets.push_back(earth);

  glm::vec3 scaleVenus = glm::vec3(0.8f, 0.8f, 0.8f);
  Planet venus = Planet(2, vertexes, originals, normals, globalTranslate, scaleVenus, globalRotate, Color(195, 102, 49), angle);
  venus.axisX = 10.25f;
  venus.axisY = 10.8f;
  venus.angularSpeed = 0.045f;
  venus.setTranslation(sun.translate);
  venus.calculateLight(sun.translate);

  glm::vec3 scaleVenusMoon = glm::vec3(0.50f, 0.50f, 0.50f);

  Satelite VenusMoon = Satelite(2, vertexes, originals, normals, globalTranslate, scaleVenusMoon, globalRotate, Color(100, 127, 131), angle);
  VenusMoon.axisX = 3.0f;
  VenusMoon.axisY = 3.0f;
  VenusMoon.angularSpeed = 0.30f;
  VenusMoon.setTranslation(venus.translate);
  VenusMoon.calculateLight(sun.translate);

  venus.satelites.push_back(VenusMoon);

  sun.planets.push_back(venus);

  glm::vec3 scaleJool = glm::vec3(2.0f, 2.0f, 2.0f);
  Planet Jool = Planet(2, vertexes, originals, normals, globalTranslate, scaleJool, globalRotate, Color(122, 173, 84), angle);
  Jool.axisX = 50.25f;
  Jool.axisY = 50.25f;
  Jool.angularSpeed = 0.01f;
  Jool.setTranslation(sun.translate);
  Jool.calculateLight(sun.translate);

  glm::vec3 scaleJoolSat1 = glm::vec3(1.0f, 1.0f, 1.0f);
  Satelite JoolSat1 = Satelite(2, vertexes, originals, normals, globalTranslate, scaleJoolSat1, globalRotate, Color(114, 101, 87), angle);
  JoolSat1.axisX = 3.0f;
  JoolSat1.axisY = 3.0f;
  JoolSat1.angularSpeed = 0.30f;
  JoolSat1.setTranslation(Jool.translate);
  JoolSat1.calculateLight(sun.translate);

  Jool.satelites.push_back(JoolSat1);

  glm::vec3 scaleJoolSat2 = glm::vec3(0.65f, 0.65f, 0.65f);
  Satelite JoolSat2 = Satelite(2, vertexes, originals, normals, globalTranslate, scaleJoolSat2, globalRotate, Color(178, 171, 153), angle);
  JoolSat2.axisX = 7.0f;
  JoolSat2.axisY = 9.0f;
  JoolSat2.angularSpeed = 0.064f;
  JoolSat2.setTranslation(Jool.translate);
  JoolSat2.calculateLight(sun.translate);

  Jool.satelites.push_back(JoolSat2);

  sun.planets.push_back(Jool);
  return sun;
}

#endif