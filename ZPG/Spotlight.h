#pragma once
#include "Light.h"
#include "EnumLightType.h"

#include <glm/gtc/matrix_transform.hpp>

class SpotLight : public Light
{
public:
    glm::vec3 position;
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    SpotLight(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& col, float cutDeg = 12.5f, float outerCutDeg = 17.5f);

};