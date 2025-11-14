#include "Application.h"
#include "Callbacks.h"
#include "SphereData.h"
#include "TreeData.h"
#include "BushData.h"

#include "Transform.h"
#include "Rotate.h"
#include "Translate.h"
#include "Scale.h"
#include "DynamicRotate.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdlib.h>

#include "Scene1.h"
#include "Scene2.h"
void Application::run() {
    initGLFW();
    initWindow();
    initGLEW();
    setupApp();
    mainLoop();
    cleanup();
}

void Application::initGLFW() {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }
    //Init correct GLFW version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

}

void Application::initWindow() {
    window = glfwCreateWindow(1000, 800, "ZPG", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }


    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, button_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

void Application::initGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "ERROR: could not start GLEW\n");
        exit(EXIT_FAILURE);
    }
    glEnable(GL_DEPTH_TEST);



}

void Application::setupApp() {
    scenes.push_back(new Scene1());
    scenes.push_back(new Scene2());

    currentScene = scenes[0];        
    currentScene->bindCallbacks();   


    glfwSetWindowUserPointer(window, this);

	//need to call those lines after binding camera to callbacks
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    window_size_callback(window, width, height);
}


void Application::mainLoop() {
    float lastPrintTime = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        if (currentScene)
            currentScene->drawAll();

        glfwSwapBuffers(window);
    }
}



void Application::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::switchScene(int index) {
    if (index < 0 || index >= scenes.size()) return;
    currentScene = scenes[index];
    currentScene->bindCallbacks();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    window_size_callback(window, width, height);
}