#pragma once
#include <glm/glm.hpp>

class TransformBase
{
public:
    virtual glm::mat4 getMatrix() = 0;
};
