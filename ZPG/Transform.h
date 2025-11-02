#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "TransformBase.h"

class Transform {
public:
    Transform* addTransform(TransformBase* transform);
    glm::mat4 getMatrix();
	void clearTransforms();

private:
    glm::mat4 transformMatrix = glm::mat4(1.0f);
    std::vector<TransformBase*> transforms;
};
