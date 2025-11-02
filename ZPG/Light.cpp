#include "Light.h"

Light::Light(const glm::vec3& position)
    : position(position) {
}

void Light::setPosition(const glm::vec3& pos)
{
    position = pos;
    notifyObservers();
}

const glm::vec3& Light::getPosition() const
{
    return position;
}

void Light::addObserver(ILightObserver* observer)
{
    if (observer)
        observers.push_back(observer);
}

void Light::notifyObservers()
{
    for (auto o : observers)
        o->onLightUpdated(position);
}