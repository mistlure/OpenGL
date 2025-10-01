#include "Scene.h"

void Scene::addObject(DrawableObject* obj)
{
    objects.push_back(obj);
}

void Scene::drawAll()
{

    for (auto obj : objects)
    {
        obj->draw();
    }
}