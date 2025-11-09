#pragma once

#include <vector>
#include "DrawableObject.h"
#include "Light.h"

#include "Camera.h"
#include "Callbacks.h"

class Scene
{
private:
    std::vector<DrawableObject*> objects;
    Camera* camera = new Camera();

protected:
    Light* light = new Light(glm::vec3(0.0f, 5.0f, 5.0f));

public:
    void drawAll();
	Camera* getCamera() { return camera; }
    void bindCallbacks()
    {
        setCameraCallbacks(camera);
	}
    void addObject(DrawableObject* obj);


};

