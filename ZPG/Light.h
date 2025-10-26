#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "ILightObserver.h"

class Light
{
public:
    Light(const glm::vec3& position);

    void setPosition(const glm::vec3& pos);
    const glm::vec3& getPosition() const;

    void addObserver(ILightObserver* observer);
    void notifyObservers();

private:
    glm::vec3 position;
    std::vector<ILightObserver*> observers;
};