#include "SceneManager.h"

SceneManager& SceneManager::get() {
    static SceneManager instance;
    return instance;
}

void SceneManager::setScenes(const std::vector<Scene*>& sceneList) {
    scenes = sceneList;
}

void SceneManager::setCurrent(int index) {
    if (index >= 0 && index < scenes.size())
        currentIndex = index;
}

Scene* SceneManager::getCurrent() {
    return scenes[currentIndex];
}

int SceneManager::getIndex() {
    return currentIndex;
}

void SceneManager::setCameraController(CameraController* controller) {
    cameraController = controller;
}

void SceneManager::handleMouseMovement(float deltaX, float deltaY) {
    if (cameraController)
        cameraController->rotate(deltaX, deltaY);
}