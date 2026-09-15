#pragma once

#include <vector>
#include <memory>
#include "Object.h"

class Scene {
public:
    std::vector<std::shared_ptr<Object>> objects;

    // Constructor
    Scene(std::vector<std::shared_ptr<Object>> const& objs) : objects(objs) {}
    Scene() = default;
};
