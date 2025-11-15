#pragma once
#include "SpotLight.h"
#include "Observer.h"
#include "EnumObservableSubjects.h"
#include "Camera.h"

class HeadLight : public SpotLight, public Observer
{
private:
	Camera* camera;
	void onNotify(ObservableSubjects subject) override;
public:
	HeadLight(Camera* camera);
};