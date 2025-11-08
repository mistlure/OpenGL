// Transform.cpp
#include "Transform.h"

Transform* Transform::addTransform(TransformBase* transform) {
    transforms.push_back(transform);
    return this;
}

glm::mat4 Transform::getMatrix() {
    glm::mat4 outMatrix = glm::mat4(1.f);
    for (const auto& t : transforms) {
        outMatrix *= t->getMatrix();
    }
    return outMatrix;
}

