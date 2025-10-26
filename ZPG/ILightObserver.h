#pragma once
#include <glm/glm.hpp>

class ILightObserver {
public:
    virtual void onLightUpdated(const glm::vec3& position) = 0;
    virtual ~ILightObserver() = default;
};