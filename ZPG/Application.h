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
#include "Transformation.h"
#include "CameraController.h"
#include "SceneManager.h"

class Application {
public:
    void run();

private:
    void initGLFW();
    void initWindow();
    void initGLEW();
    void setupApp();
    void mainLoop();
    void cleanup();

    GLFWwindow* window = nullptr;
    ShaderProgram* shaderProgram = nullptr;

    float ratio = 1.0f;

    Camera camera;
    CameraController cameraController;

    std::vector<Scene*> scenes;
    int currentSceneIndex = 0;

    Transformation* rotatingTriangle = nullptr;
    Transformation* sun = nullptr;
    Transformation* earth = nullptr;
    Transformation* moon = nullptr;
};
