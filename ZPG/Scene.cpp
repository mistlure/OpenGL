#include "Scene.h"

// Adds a DrawableObject to the scene
void Scene::addObject(DrawableObject* obj)
{
    if (obj)
        objects.push_back(obj);
}

// Draws all objects in the scene
void Scene::drawAll()
{
    for (auto& obj : objects)
    {
        obj->draw(camera, light);
    }
}


// Clears all objects from the scene
void Scene::clear()
{
    objects.clear();
}