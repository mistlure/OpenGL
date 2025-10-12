#pragma once
#include <glm/glm.hpp>

class ICameraObserver
{
public:
    virtual void onCameraUpdated(const glm::mat4& viewMatrix) = 0;
    virtual ~ICameraObserver() = default;
};
