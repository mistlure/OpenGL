#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "TransformBase.h"
#include <cstdlib>

class RandomTranslation : public TransformBase {
private:
    glm::vec3 base;
    float range;

public:
    RandomTranslation(const glm::vec3& base, float range) : base(base), range(range) {}

    glm::mat4 getMatrix() override {
        float dx = ((rand() % 1000) / 1000.0f - 0.5f) * range;
        float dy = ((rand() % 1000) / 1000.0f - 0.5f) * range;
        float dz = ((rand() % 1000) / 1000.0f - 0.5f) * range;
        return glm::translate(glm::mat4(1.0f), base + glm::vec3(dx, dy, dz));
    }
};
