#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "TransformBase.h"

class Transform : public TransformBase {
public:
    Transform* addTransform(TransformBase* transform);
    glm::mat4 getMatrix() override;

private:
    std::vector<TransformBase*> transforms;
};
