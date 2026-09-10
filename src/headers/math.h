#include "vec3.h"
#include "mat3.h"

class math
{
public:
    // Dot product between two normalized vec3's
    inline static float dot(const vec3& a, const vec3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    // Transforms a vector based on a 3x3 transformation matrix
    inline static vec3 transform(const vec3& v, const mat3& m) {
        return vec3(
            m.data[0][0] * v.x + m.data[0][1] * v.y + m.data[0][2] * v.z,
            m.data[1][0] * v.x + m.data[1][1] * v.y + m.data[1][2] * v.z,
            m.data[2][0] * v.x + m.data[2][1] * v.y + m.data[2][2] * v.z
        );
    }
};