#include "Light.h"

Light::Light(LightType type, const glm::vec3& col)
    : type(type), color(col) {
}

Light::~Light() {}