#include "headers/RayTracer.h"
#include "headers/Ray.h"

void RayTracer::trace() {
    // Loop over every pixel
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {

            // Trace single ray
            this->pixels.at(i * j) = this->trace_ray(
                // Init ray from camera position and orientation
                Ray(
                    this->cam.position,
                    this->cam.orientation
                )
            );

        }
    }
}

vec3 RayTracer::trace_ray(Ray Ray) {

    

}