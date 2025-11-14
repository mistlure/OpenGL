#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>

#include "Shader.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "DrawableObject.h"
#include "Scene.h"
#include "Camera.h"
#include "Light.h"
#include "SceneManager.h"
#include "Transform.h"

#include "EnumLightType.h"

class Application {
public:
    void run();
    void switchScene(int index);
	Scene* getCurrentScene() { return currentScene; }
private:
    void initGLFW();
    void initWindow();
    void initGLEW();
    void setupApp();
    void mainLoop();
    void cleanup();

    GLFWwindow* window = nullptr;
    float ratio = 1.0f;
   
    std::vector<Scene*> scenes;
    Scene* currentScene;
};
