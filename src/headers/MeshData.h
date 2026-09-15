#pragma once

#include <vector>

#include "headers/vec3.h"

class MeshData
{
public:

    std::vector<vec3> vertices;
    std::vector<unsigned int> faces;

    MeshData() = default;

    MeshData(std::vector<vec3> vertices, std::vector<unsigned int> faces) : vertices(vertices), faces(faces) {};

    ~MeshData() = default;
};
