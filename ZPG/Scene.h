#pragma once

#include <vector>
#include "DrawableObject.h"
#include "Light.h"

#include "Camera.h"
class Scene
{
protected:
public:
    void drawAll();
    void clear();	
    Light* light = nullptr;
    void addObject(DrawableObject* obj);
    
    Camera* camera = new Camera();
    //CameraController* cameraController = nullptr;


private:
    std::vector<DrawableObject*> objects;
};

