#include "headers/math.h"
#include "headers/Camera.h"

void Camera::update(mat3 transformation_matrix) {
    this->orientation = this->orientation.transform(transformation_matrix);
}