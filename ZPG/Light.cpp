#include "Light.h"

Light::Light(const glm::vec3& position)
    : position(position) {
}

void Light::setPosition(const glm::vec3& pos)
{
    position = pos;
    notify(position);
}

const glm::vec3& Light::getPosition() const
{
    return position;
}