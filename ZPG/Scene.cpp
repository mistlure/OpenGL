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
        obj->draw();
    }
}


Light* Scene::addLight(Light* light) {
	if (lights.size() >= MAX_LIGHTS) {
		std::cerr << "Cannot add more lights, maximum reached: " << MAX_LIGHTS << std::endl;
		delete light;
		return nullptr;
	}
	lights.push_back(light);
	return light;
}