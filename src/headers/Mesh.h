#pragma once

#include <vector>
#include "headers/vec3.h"
#include "headers/Object.h"
#include "headers/Ray.h"
#include "headers/Triangle.h"
#include "headers/MeshData.h"

class Mesh : public Object
{
public:

    float emittance;

    // Triangles
    Triangle* closest_tri = nullptr;
    std::vector<Triangle> tris;

    // Constructor
    Mesh(MeshData data, float emittance = 0.0f) : emittance(emittance) {
        // Construct and push tris
        for (size_t i = 0; i < data.faces.size(); i += 3) {
            unsigned int idx0 = data.faces[i];
            unsigned int idx1 = data.faces[i + 1];
            unsigned int idx2 = data.faces[i + 2];

            this->tris.push_back(Triangle(
                data.vertices.at(idx0), 
                data.vertices.at(idx1), 
                data.vertices.at(idx2)
            ));
        }
    }
    Mesh() = default;

    // Normal override
    vec3 normal(vec3 collision) override {
        return this->closest_tri->normal();
    };

    // Color override
    vec3 getColor() override {
        return this->closest_tri->color;
    };

    // Emittance override
    float getEmittance() override {
        return this->emittance;
    };

    // Intersection override
    bool intersects(Ray ray, vec3 &hit_pos, float &distance) override {
        bool hit_anything = false;
        float closest_t = 1e30f;

        for (auto& tri : this->tris) {
            vec3 edge1 = tri.p2 - tri.p1;
            vec3 edge2 = tri.p3 - tri.p1;
            vec3 h = math::cross(ray.dir, edge2);
            float a = math::dot(edge1, h);

            if (a > -1E-06 && a < 1E-06) continue; // Parallel

            float f = 1.0f / a;
            vec3 s = ray.origin - tri.p1;
            float u = f * math::dot(s, h);

            if (u < 0.0f || u > 1.0f) continue; 

            vec3 q = math::cross(s, edge1);
            float v = f * math::dot(ray.dir, q);

            if (v < 0.0f || u + v > 1.0f) continue; 

            // Calculate t
            float t = f * math::dot(edge2, q);

            if (t > 1E-04 && t < closest_t) {
                closest_t = t;
                hit_pos = ray.origin + (ray.dir * t);
                hit_anything = true;

                this->closest_tri = &tri;

                distance = t;
            }
        }

        return hit_anything;
    };

};
