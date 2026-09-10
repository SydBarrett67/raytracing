#pragma once

#include <cmath>

class vec3 {
public:

    float x, y, z;

    // Constructor
    vec3(float x, float y, float z) { x = x; y = y; z = z; }
    vec3(float x)                   { x = x; y = x; z = x; }

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
};
