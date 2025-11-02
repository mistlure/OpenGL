// Rotate.h
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformBase.h"

class Rotate : public TransformBase {
public:
    Rotate(float angle, const glm::vec3& axis);
    glm::mat4 getMatrix() override;

private:
    float angle;
    glm::vec3 axis;
};
