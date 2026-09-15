#include "headers/vec3.h"
#include "headers/math.h"

class Triangle
{
public:

    vec3 p1, p2, p3;

    vec3 color;

    Triangle(vec3 p1, vec3 p2, vec3 p3, vec3 color = vec3(1.0f)) : p1(p1), p2(p2), p3(p3), color(color) {};
    
    // Get normal vector
    vec3 normal() const {
        vec3 e1 = p2 - p1;
        vec3 e2 = p3 - p1;

        return math::cross(e1, e2);
    }
};
