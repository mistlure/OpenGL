#pragma once

#include <vector>
#include "DrawableObject.h"
#include "Light.h"
#include "HeadLight.h"

#include "Camera.h"
#include "Callbacks.h"

#define MAX_LIGHTS 8
class Scene
{
private:
    std::vector<DrawableObject*> objects;
    Camera* camera = new Camera();
    HeadLight* headLight = new HeadLight(camera);
protected:
    //Light* light = new Light(glm::vec3(0.0f, 5.0f, 5.0f));
	std::vector<Light*> lights;
public:
	Scene();
    void drawAll();
	Camera* getCamera() { return camera; }
    void bindCallbacks()
    {
        setCameraCallbacks(camera);
	}
    void addObject(DrawableObject* obj);
    Light* addLight(Light* l);
    std::vector<Light*>* getLights() { return &lights; }
    void switchHeadLight();
};

