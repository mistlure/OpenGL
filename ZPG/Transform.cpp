// Transform.cpp
#include "Transform.h"

Transform* Transform::addTransform(TransformBase* transform) {
    transforms.push_back(transform);
    return this;
}

glm::mat4 Transform::getMatrix() {
    glm::mat4 outMatrix = transformMatrix;
    for (const auto& t : transforms) {
        outMatrix *= t->getMatrix();
    }
    return outMatrix;
}

void Transform::clearTransforms()
{
    for (auto* t : transforms)
        delete t;
    transforms.clear();
}

