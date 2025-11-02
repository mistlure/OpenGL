// Rotate.cpp
#include "Rotate.h"

Rotate::Rotate(float angle, const glm::vec3& axis)
    : angle(angle), axis(axis) {
}

glm::mat4 Rotate::getMatrix() {
    return glm::rotate(glm::mat4(1.0f), angle, glm::normalize(axis));
}
