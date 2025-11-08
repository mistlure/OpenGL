#include "SceneManager.h"


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



void SceneManager::handleMouseMovement(float deltaX, float deltaY) {
    printf("handle mouse moovement is NOT implemented\n");
}