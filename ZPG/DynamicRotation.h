// DynamicRotate.h
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "TransformBase.h"

class DynamicRotate : public TransformBase {
public:
    DynamicRotate(float speed, const glm::vec3& axis);
    glm::mat4 getMatrix() override;

private:
    float speed;
    glm::vec3 axis;
};
