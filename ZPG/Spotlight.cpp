#include "Spotlight.h"

SpotLight::SpotLight(const glm::vec3& pos, const glm::vec3& dir, const glm::vec3& col,
    float cutDeg, float outerCutDeg)
    : Light(LightType::SPOT, col),
    position(pos), direction(dir)
{
    cutOff = glm::cos(glm::radians(cutDeg));
    outerCutOff = glm::cos(glm::radians(outerCutDeg));
}