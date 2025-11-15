// DynamicRotate.h
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "Rotate.h"
class DynamicRotate : public Rotate {
public:
    DynamicRotate(float speed, const glm::vec3& axis);
    glm::mat4 getMatrix() override;

private:
    float speed ;

};
