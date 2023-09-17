#ifndef OBJ_H
#define OBJ_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <array>
#include <string>
#include <glm/glm.hpp>

bool loadObj(const std::string &path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec3> &out_normals, std::vector<glm::vec3> &out_text)
{

    int counterV = 0;
    int counterF = 0;
    int counterT = 1;
    int counterN = 1;

    std::ifstream file(path);
    if (!file)
    {
        std::cout << "Failed to open the file: " << path << std::endl;
        return false;
    }

    std::string line;
    char buffer[128];

    while (std::getline(file, line))
    {
        line = line.substr(0, line.find("#"));
        line = line.substr(0, line.find("\r"));

        line = line.substr(0, sizeof(buffer) - 1);
        strncpy(buffer, line.c_str(), sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';

        char type[3];
        int result = sscanf(buffer, "%2s", type);

        if (result == 1)
        {
            if (strcmp(type, "v") == 0)
            {
                counterV++;
            }
            else if (strcmp(type, "f") == 0)
            {
                counterF++;
            }
            else if (strcmp(type, "vn") == 0)
            {
                counterN++;
            }
            else if (strcmp(type, "vt") == 0)
            {
                counterT++;
            }
        }
    }

    out_vertices.reserve(counterF * 3);
    out_normals.reserve(counterF * 3);
    out_text.reserve(counterF * 3);

    std::vector<glm::vec3> temp_vertices;
    temp_vertices.reserve(counterV);
    std::vector<glm::vec3> temp_normals;
    temp_normals.reserve(counterN);
    std::vector<glm::vec3> temp_text;
    temp_text.reserve(counterT);

    file.clear();
    file.seekg(0, std::ios::beg);

    while (std::getline(file, line))
    {
        line = line.substr(0, line.find("#"));
        line = line.substr(0, line.find("\r"));

        line = line.substr(0, sizeof(buffer) - 1);
        strncpy(buffer, line.c_str(), sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';

        char type[3];
        int result = sscanf(buffer, "%2s", type);

        if (result == 1)
        {
            if (strcmp(type, "v") == 0)
            {
                double x, y, z;
                if (sscanf(buffer, "v %lf %lf %lf", &x, &y, &z) == 3)
                {
                    glm::vec3 temp(x, y, z);
                    temp_vertices.push_back(temp);
                }
            }
            else if (strcmp(type, "f") == 0)
            {
                std::array<int, 3> face_indices;
                std::array<int, 3> face_indices2;
                std::array<int, 3> face_indices3;
                if (sscanf(buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d", &face_indices[0], &face_indices[1], &face_indices[2], &face_indices2[0], &face_indices2[1], &face_indices2[2], &face_indices3[0], &face_indices3[1], &face_indices3[2]) == 9)
                {
                    for (int i = 0; i < 3; i++)
                    {
                        face_indices[i] -= 1;
                        face_indices2[i] -= 1;
                        face_indices3[i] -= 1;
                    }
                    out_vertices.push_back(temp_vertices.at(face_indices[0]));
                    out_text.push_back(temp_text.at(face_indices[1]));
                    out_normals.push_back(temp_normals.at(face_indices[2]));
                    out_vertices.push_back(temp_vertices.at(face_indices2[0]));
                    out_text.push_back(temp_text.at(face_indices2[1]));
                    out_normals.push_back(temp_normals.at(face_indices2[2]));
                    out_vertices.push_back(temp_vertices.at(face_indices3[0]));
                    out_text.push_back(temp_text.at(face_indices3[1]));
                    out_normals.push_back(temp_normals.at(face_indices3[2]));
                }
            }
            else if (strcmp(type, "vn") == 0)
            {
                double x, y, z;
                if (sscanf(buffer, "vn %lf %lf %lf", &x, &y, &z) == 3)
                {
                    glm::vec3 temp(x, y, z);
                    temp_normals.push_back(temp);
                }
            }
            else if (strcmp(type, "vt") == 0)
            {
                double x, y;
                if (sscanf(buffer, "vt %lf %lf", &x, &y) == 2)
                {
                    glm::vec3 temp(x, y, 0);
                    temp_text.push_back(temp);
                }
            }
        }
    }

    temp_vertices.clear();
    temp_vertices.shrink_to_fit();
    temp_normals.clear();
    temp_normals.shrink_to_fit();
    temp_text.clear();
    temp_text.shrink_to_fit();
    
    printf("Vértices: %i, Caras: %i, Normales: %i \n", counterV, counterF, counterN);
    return true;
}

#endif