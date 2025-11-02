// Translate.cpp
#include "Translate.h"

Translate::Translate(const glm::vec3& offset)
    : offset(offset) {
}

glm::mat4 Translate::getMatrix() {
    return glm::translate(glm::mat4(1.0f), offset);
}
