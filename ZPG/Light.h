#pragma once
#include <glm/glm.hpp>

class Light
{
public:
    Light(const glm::vec3& position);

    void setPosition(const glm::vec3& pos);
    const glm::vec3& getPosition() const;

private:
    glm::vec3 position;
};