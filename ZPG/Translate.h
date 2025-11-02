// Translate.h
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformBase.h"

class Translate : public TransformBase {
public:
    Translate(const glm::vec3& offset);
    glm::mat4 getMatrix() override;

private:
    glm::vec3 offset;
};
