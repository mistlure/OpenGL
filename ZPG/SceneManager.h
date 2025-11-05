#pragma once
#include <vector>
#include "Scene.h"
#include "CameraController.h"

class SceneManager {
public:
    static SceneManager& get();

    void setScenes(const std::vector<Scene*>& sceneList);
    void setCurrent(int index);
    Scene* getCurrent();
    int getIndex();

    void setCameraController(CameraController* controller); 
    void handleMouseMovement(float deltaX, float deltaY);

private:
    std::vector<Scene*> scenes;
    int currentIndex = 0;

    CameraController* cameraController = nullptr;
};
