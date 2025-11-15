#include "HeadLight.h"
#include <iostream>
HeadLight::HeadLight(Camera* camera) : SpotLight(camera->getPosition(), camera->front, glm::vec3(1.0f, 1.0f, 1.0f), 12.5f, 17.5f), camera(camera)
{
	camera->attach(this);
}

void HeadLight::onNotify(ObservableSubjects subject)
{
	if (subject == ObservableSubjects::SCamera)
	{
		this->position = camera->getPosition();
		this->direction = camera->front;
	}

	notify(ObservableSubjects::SLight);
}