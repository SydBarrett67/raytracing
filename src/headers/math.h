#include "vec3.h"

class math
{
public:
    // Dot product between two normalized vec3's
    inline static float dot(const vec3& a, const vec3& b) {
        return a.get(0) * b.get(0) + a.get(1) * b.get(1) + a.get(2) * b.get(2);
    }
};