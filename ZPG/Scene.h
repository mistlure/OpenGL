// Container class that manages multiple DrawableObject instances.
// 
// It allows you to add objects to the scene and render them all with a single call.
// 
// This class doesn’t own the objects — it stores pointers and calls their draw() methods.
// 
// It’s a clean way to organize rendering logic.

#pragma once

#include <vector>
#include "DrawableObject.h"

class Scene
{
public:
    void addObject(DrawableObject* obj);
    void drawAll();

private:
    std::vector<DrawableObject*> objects;
};

