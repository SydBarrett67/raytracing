#include "vec3.h"

class Ray {
private:
    vec3 origin;
    vec3 dir;

public:
    
    // Consutrctor
    Ray(vec3 origin, vec3 dir) : origin(origin), dir(dir) {};

};