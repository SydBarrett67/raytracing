#pragma once

#include "headers/mat3.h"

#include <cmath>

class vec3 {
public:

    float x, y, z;

    // Constructor
    vec3(float x, float y, float z) : x(x), y(y), z(z) {};
    vec3(float x)                   : x(x), y(x), z(x) {};

    void normalize() {

        float sq_len = x*x + y*y + z*z;

        // Check for null vector
        if (sq_len < 1e-8f) {
            x = y = z = 0.0f;
            return;
        }

        float inv_len = 1.0f / std::sqrt(sq_len);
        x *= inv_len; y *= inv_len; z *= inv_len;
    }

    // Transforms a vector based on a 3x3 transformation matrix
    vec3 transform(const mat3 m) {
        return vec3(
            m.data[0][0] * this->x + m.data[0][1] * this->y + m.data[0][2] * this->z,
            m.data[1][0] * this->x + m.data[1][1] * this->y + m.data[1][2] * this->z,
            m.data[2][0] * this->x + m.data[2][1] * this->y + m.data[2][2] * this->z
        );
    }

    std::string print() {
        return  "\nx: " + std::to_string(this->x) + 
                "\ny: " + std::to_string(this->y) +
                "\nz: " + std::to_string(this->z);
    }

    vec3 operator-(const vec3& other) const
    {
        return vec3(
            x - other.x,
            y - other.y,
            z - other.z
        );
    }
};
