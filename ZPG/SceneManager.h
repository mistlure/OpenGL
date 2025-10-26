#pragma once
#include <vector>
#include "Scene.h"

class SceneManager {
public:
    static SceneManager& get();

    void setScenes(const std::vector<Scene*>& sceneList);
    void setCurrent(int index);
    Scene* getCurrent();
    int getIndex();

private:
    std::vector<Scene*> scenes;
    int currentIndex = 0;
};
