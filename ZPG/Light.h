#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Subject.h"
#include "EnumLightType.h"

class Light : public Subject
{
public:
    Light(const glm::vec3& position);

    void setPosition(const glm::vec3& pos);
    const glm::vec3& getPosition() const;

private:
    glm::vec3 position;
};