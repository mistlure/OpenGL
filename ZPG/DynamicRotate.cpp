// DynamicRotate.cpp
#include "DynamicRotate.h"

DynamicRotate::DynamicRotate(float speed, const glm::vec3& axis)
    : speed(speed), axis(axis) {
}

glm::mat4 DynamicRotate::getMatrix() {
    float time = static_cast<float>(glfwGetTime());
    return glm::rotate(glm::mat4(1.0f), time * speed, glm::normalize(axis));
}
