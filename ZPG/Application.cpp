#include "Application.h"
#include "Callbacks.h"
#include "SphereData.h"
#include "TreeData.h"
#include "BushData.h"

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <stdlib.h>

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

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float)height;
    glViewport(0, 0, width, height);

    setCameraController(&cameraController);
    cameraController.bindCamera(&camera);
}

void Application::initGLEW() {
    glewExperimental = GL_TRUE;
    glewInit();
}

void Application::setupApp() {
    const char* vertex_shader =
        "#version 330 core\n"
        "layout(location = 0) in vec3 vp;\n"
        "layout(location = 1) in vec3 normal;\n"
        "uniform mat4 modelMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 projectMatrix;\n"
        "out vec3 FragPos;\n"
        "out vec3 Normal;\n"
        "void main () {\n"
        "    vec4 worldPos = modelMatrix * vec4(vp, 1.0);\n"
        "    FragPos = vec3(worldPos);\n"
        "    Normal = mat3(transpose(inverse(modelMatrix))) * normal;\n"
        "    gl_Position = projectMatrix * viewMatrix * worldPos;\n"
        "}\n";

    const char* fragment_shader =
        "#version 330 core\n"
        "in vec3 FragPos;\n"
        "in vec3 Normal;\n"
        "uniform vec3 lightPos;\n"
        "uniform vec3 viewPos;\n"
        "out vec4 finalColor;\n"
        "void main () {\n"
        "    vec3 norm = normalize(Normal);\n"
        "    vec3 lightDir = normalize(lightPos - FragPos);\n"
        "    float diff = max(dot(norm, lightDir), 0.0);\n"
        "    vec3 viewDir = normalize(viewPos - FragPos);\n"
        "    vec3 reflectDir = reflect(-lightDir, norm);\n"
        "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);\n"
        "    vec3 ambient = vec3(0.1);\n"
        "    vec3 diffuse = diff * vec3(0.5);\n"
        "    vec3 specular = spec * vec3(1.0);\n"
        "    vec3 result = ambient + diffuse + specular;\n"
        "    finalColor = vec4(result, 1.0);\n"
        "}\n";

    Shader vertexShader(GL_VERTEX_SHADER, vertex_shader);
    Shader fragmentShader(GL_FRAGMENT_SHADER, fragment_shader);
    shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
    shaderProgram->use();

    Light light(glm::vec3(0.0f, 0.0f, 0.0f));
    shaderProgram->setLightPosition(light.getPosition());
    shaderProgram->setUniform("lightPos", light.getPosition());
    shaderProgram->setUniform("viewPos", cameraController.position);

    camera.addObserver(shaderProgram);
    cameraController.position = glm::vec3(0.0f, 0.0f, 5.0f);
    cameraController.updateDirection();
    camera.setPerspective(45.0f, ratio, 0.1f, 100.0f);
    shaderProgram->setUniform("projectMatrix", camera.getProjectionMatrix());

    // Scene 1 — rotating triangle
    float triangle[] = {
        -0.3f, -0.3f, 0.0f,  1.0f, 0.0f, 0.0f,
         0.3f, -0.3f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.0f,  0.3f, 0.0f,  0.0f, 0.0f, 1.0f
    };
    Model* triangleModel = new Model(triangle, sizeof(triangle));
    DrawableObject* triangleObject = new DrawableObject(shaderProgram, triangleModel);
    rotatingTriangle = new Transformation();
    triangleObject->transform = rotatingTriangle;
    Scene* scene1 = new Scene();
    scene1->addObject(triangleObject);
    scenes.push_back(scene1);

    // Scene 2 — forest
    Scene* scene2 = new Scene();
    Model* treeModel = new Model(tree, treeSize);
    Model* bushModel = new Model(bush, bushSize);
    for (int i = 0; i < 50; ++i) {
        float x = ((rand() % 200) - 100) / 10.0f;
        float z = ((rand() % 200) - 100) / 10.0f;
        Transformation* t = new Transformation();
        t->setLocalTransform(glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z)));
        DrawableObject* obj = new DrawableObject(shaderProgram, treeModel);
        obj->transform = t;
        scene2->addObject(obj);
    }
    for (int i = 0; i < 50; ++i) {
        float x = ((rand() % 200) - 100) / 10.0f;
        float z = ((rand() % 200) - 100) / 10.0f;
        Transformation* t = new Transformation();
        t->setLocalTransform(glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z)));
        DrawableObject* obj = new DrawableObject(shaderProgram, bushModel);
        obj->transform = t;
        scene2->addObject(obj);
    }
    scenes.push_back(scene2);

    // Scene 3 — spheres
    Scene* scene3 = new Scene();
    Model* sphereModel = new Model(sphere, sphereSize);
    glm::vec3 positions[] = {
        glm::vec3(0.0f,  2.0f, 0.0f),
        glm::vec3(0.0f, -2.0f, 0.0f),
        glm::vec3(-2.0f, 0.0f, 0.0f),
        glm::vec3(2.0f, 0.0f, 0.0f)
    };
    for (int i = 0; i < 4; ++i) {
        Transformation* t = new Transformation();
        t->setLocalTransform(glm::translate(glm::mat4(1.0f), positions[i]));
        DrawableObject* obj = new DrawableObject(shaderProgram, sphereModel);
        obj->transform = t;
        scene3->addObject(obj);
    }
    scenes.push_back(scene3);

    // Scene 4 — solar system
    Scene* solarScene = new Scene();
    sun = new Transformation();
    earth = new Transformation();
    moon = new Transformation();

    sun->setLocalTransform(glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)));
    earth->setLocalTransform(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));
    moon->setLocalTransform(glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

    earth->setParent(sun);
    moon->setParent(earth);

    DrawableObject* sunObj = new DrawableObject(shaderProgram, sphereModel);
    DrawableObject* earthObj = new DrawableObject(shaderProgram, sphereModel);
    DrawableObject* moonObj = new DrawableObject(shaderProgram, sphereModel);

    sunObj->transform = sun;
    earthObj->transform = earth;
    moonObj->transform = moon;

    solarScene->addObject(sunObj);
    solarScene->addObject(earthObj);
    solarScene->addObject(moonObj);
    scenes.push_back(solarScene);

    SceneManager::get().setScenes(scenes);

    glEnable(GL_DEPTH_TEST);
}

void Application::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        rotatingTriangle->setLocalTransform(glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)));
        camera.setPosition(cameraController.position);
        cameraController.updateDirection();

        float time = static_cast<float>(glfwGetTime());

        if (currentSceneIndex == 3) {
            earth->setLocalTransform(glm::rotate(glm::mat4(1.0f), time, glm::vec3(0, 1, 0)) *
                glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

            moon->setLocalTransform(glm::rotate(glm::mat4(1.0f), time * 2.0f, glm::vec3(0, 1, 0)) *
                glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)) *
                glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

            sun->setLocalTransform(glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)));
        }

        SceneManager::get().getCurrent()->drawAll();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void Application::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}