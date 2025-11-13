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
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, button_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
}

void Application::initGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "ERROR: could not start GLEW\n");
        exit(EXIT_FAILURE);
    }
    glEnable(GL_DEPTH_TEST);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    window_size_callback(window, width, height);

}

void Application::setupApp() {

    scene = new Scene1(); // Start with scene 1
	scene->bindCallbacks();
    // 
    //scene = new Scene(); // Placeholder for scene 0
    //setCameraCallbacks(scene->getCamera());//!!! SWITCH ON SCENNE CHANGE
    //
    //Shader vertexShader(GL_VERTEX_SHADER, "shaders/vertex.glsl");
    //Shader fragmentShader(GL_FRAGMENT_SHADER, "shaders/fragment_phong.glsl");
    //
    //auto shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
    //shaderProgram->useProgram();
    //
    //scene->getCamera()->attach(shaderProgram);
    //auto light = new Light(glm::vec3(0.0f, 5.0f, 5.0f));
    //light->attach(shaderProgram);
    //shaderProgram->setUniform("lightPos", light->getPosition());
    //
    //float triangle[] = {
    //    // pos             // normal
    //    -0.3f, -0.3f, 0.0f,  0.0f, 0.0f, 1.0f,
    //     0.3f, -0.3f, -0.5f, 0.0f, 0.0f, 1.0f,
    //     0.0f,  0.3f, 0.0f,  0.0f, 0.0f, 1.0f
    //};
    //
    //Model* triangleModel = new Model(triangle, sizeof(triangle));
    //
    //
    //scene->addObject(new DrawableObject(shaderProgram, triangleModel)); // Placeholder object for scene 0
    //
    //
    //shaderProgram->setUniform("projectMatrix", scene->getCamera()->getProjectionMatrix());
    //
    //shaderProgram->setUniform("ambientColor", glm::vec3(0.25f));
    //shaderProgram->setUniform("ambientStrength", 0.5f);
    
}


void Application::mainLoop() {
    float lastPrintTime = 0.0f;
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwPollEvents();

        scene->drawAll();

        glfwSwapBuffers(window);
    }
}



void Application::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}