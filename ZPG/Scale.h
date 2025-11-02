// Scale.h
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformBase.h"

class Scale : public TransformBase {
public:
    Scale(const glm::vec3& scale);
    glm::mat4 getMatrix() override;

private:
    glm::vec3 scale;
};
