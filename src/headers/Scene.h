#pragma once

#include <vector>

#include "headers/Sphere.h"

class Scene
{
public:

    std::vector<Sphere> objects;

    Scene() : objects() {};
    Scene(std::vector<Sphere> objects) : objects(objects) {};
};