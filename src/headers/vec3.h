#pragma once

#include <cmath>

class vec3 {
public:

    float data[3];

    // Constructor
    vec3(float x, float y, float z) { data[0] = x; data[1] = y; data[2] = z; }
    vec3(float x)                   { data[0] = x; data[1] = x; data[2] = x; }

    void normalize() {

        float sq_len = data[0]*data[0] + data[1]*data[1] + data[2]*data[2];

        // Check for null vector
        if (sq_len < 1e-8f) {
            data[0] = data[1] = data[2] = 0.0f;
            return;
        }

        float inv_len = 1.0f / std::sqrt(sq_len);
        data[0] *= inv_len; data[1] *= inv_len; data[2] *= inv_len;
    }

    // Getter
    float get(int index) const { return data[index]; }
    // Setter
    void set(int index, float value) { data[index] = value; }
};
