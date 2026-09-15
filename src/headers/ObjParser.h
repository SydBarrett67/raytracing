#pragma once

#include <fstream>
#include <sstream>

#include "headers/vec3.h"
#include "headers/MeshData.h"

class ObjParser
{
public:

    MeshData inline static parse(std::string path) {
        std::vector<vec3> vertices;
        std::vector<unsigned int> faces;

        // Open file
        std::ifstream file(path, std::ios::in);

        if (!file.is_open()) {

            std::cout << "File not found." << std::endl;
            return MeshData();
        } 

        // Read file
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string type;

            // Get type
            ss >> type;

            // Vertex
            if (type == "v") {
                float x, y, z;
                ss >> x >> y >> z;

                vertices.push_back(vec3(x, y, z));
            }
            // Face
            else if (type == "f") {
                unsigned int x, y, z;
                ss >> x >> y >> z;

                faces.push_back(x - 1);
                faces.push_back(y - 1);
                faces.push_back(z - 1);
            }
        }

        return MeshData(vertices, faces);
    }
};
