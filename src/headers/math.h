#pragma once

#include "vec3.h"
#include "mat3.h"

class math
{
public:
    // Dot product between two normalized vec3's
    inline static float dot(const vec3& a, const vec3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    inline static mat3 getRotationMatrix(float yaw, float pitch) {
        float cy = cos(yaw);
        float sy = sin(yaw);
        float cp = cos(pitch);
        float sp = sin(pitch);

        return mat3(
            cy, sy * sp, sy * cp,
            0,  cp,      -sp,
            -sy, cy * sp, cy * cp
        );
    }
};