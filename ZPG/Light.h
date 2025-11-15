#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Subject.h"
#include "EnumLightType.h"

class Light : public Subject
{
public:
    Light(LightType type, const glm::vec3& color);
    virtual ~Light() = 0;
    glm::vec3 color;
	LightType type;
	bool isOn = true;
private:

};