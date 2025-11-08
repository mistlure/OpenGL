// DynamicRotate.cpp
#include "DynamicRotate.h"

DynamicRotate::DynamicRotate(float speed, const glm::vec3& axis)
    : Rotate(0.f, glm::normalize(axis)) , speed(glm::radians(speed)) {
}

glm::mat4 DynamicRotate::getMatrix() {
	this->angle += speed; // Increment angle for continuous rotation

    return glm::rotate(glm::mat4(1.0f), angle, glm::normalize(axis));
}
