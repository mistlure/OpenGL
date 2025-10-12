// GLEW 
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "Callbacks.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "DrawableObject.h"
#include "Scene.h"
#include "Camera.h"

#include "SphereData.h"
#include "TreeData.h"
#include "BushData.h"

std::vector<Scene*> scenes;
int currentSceneIndex = 0;

Transformation* rotatingTriangle = nullptr;

// Vertex shader with transformation
const char* vertex_shader =
"#version 330 core\n"
"layout(location = 0) in vec3 vp;\n"
"layout(location = 1) in vec3 color;\n"
"uniform mat4 modelMatrix;\n"
"uniform mat4 viewMatrix;\n"
"uniform mat4 projectMatrix;\n"
"out vec3 fragColor;\n"
"void main () {\n"
"    gl_Position = projectMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);\n"
"    fragColor = color;\n"
"}";

const char* fragment_shader =
"#version 330 core\n"
"in vec3 fragColor;\n"
"out vec4 finalColor;\n"
"void main () {\n"
"    finalColor = vec4(fragColor, 1.0);\n"
"}";

// Camera global setup.
Camera camera;
glm::vec3 cameraPos(0.0f, 0.0f, 5.0f);
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
float cameraSpeed = 0.1f;

float yaw = -90.0f;
float pitch = 0.0f;

//GLM test                    (We'll use it later)

//// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
//glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);
//
//// Camera matrix
//glm::mat4 View = glm::lookAt(
//  glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
//  glm::vec3(0, 0, 0), // and looks at the origin
//  glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
//);
//// Model matrix : an identity matrix (model will be at the origin)
//glm::mat4 Model = glm::mat4(1.0f);
//

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    /*
    //Version initialization
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
    GLFW_OPENGL_CORE_PROFILE);
    */

    window = glfwCreateWindow(1000, 800, "ZPG", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    // Start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();
    // Get version info
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Renderer %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
    int major, minor, revision;
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    // Sets the key callback
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, button_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);



    ///

    Shader vertexShader(GL_VERTEX_SHADER, vertex_shader);
    Shader fragmentShader(GL_FRAGMENT_SHADER, fragment_shader);

    ShaderProgram shaderProgram(vertexShader, fragmentShader);
    shaderProgram.use();

    camera.addObserver(&shaderProgram);

    float triangle[] = {
    -0.3f, -0.3f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.3f, -0.3f, -0.5f,  0.0f, 1.0f, 0.0f,
     0.0f,  0.3f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    // Create models and drawable objects.
    Model* triangleModel = new Model(triangle, sizeof(triangle));
    DrawableObject* triangleObject = new DrawableObject(&shaderProgram, triangleModel);

    // Create a transformation for the triangle.
    rotatingTriangle = new Transformation();
    triangleObject->transform = rotatingTriangle;

    // Scenes
    Scene* scene1 = new Scene();

	// Add the triangle to the scene.
    scene1->addObject(triangleObject);

    // Add objects to scenes.
    scenes.push_back(scene1);

	// Camera setup.
    float cameraAngle = 0.0f;
    float cameraRadius = 5.0f;
    glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);

    camera.setPosition(glm::vec3(0.0f, 0.0f, 5.0f));
    camera.lookAt(glm::vec3(0.0f, 0.0f, 0.0f));
    camera.setPerspective(45.0f, ratio, 0.1f, 100.0f);

    //shaderProgram.setUniform("viewMatrix", camera.getViewMatrix());
    shaderProgram.setUniform("projectMatrix", camera.getProjectionMatrix());

    ///



    ///
    
    Scene* scene2 = new Scene();

    Model* treeModel = new Model(tree, treeSize);
    Model* bushModel = new Model(bush, bushSize);

    for (int i = 0; i < 50; ++i) {
        float x = ((rand() % 200) - 100) / 10.0f; // от -10 до +10
        float z = ((rand() % 200) - 100) / 10.0f;
        Transformation* transform = new Transformation();
        transform->setLocalTransform(glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z)));

        DrawableObject* treeObject = new DrawableObject(&shaderProgram, treeModel);
        treeObject->transform = transform;
        scene2->addObject(treeObject);
    }

    for (int i = 0; i < 50; ++i) {
        float x = ((rand() % 200) - 100) / 10.0f;
        float z = ((rand() % 200) - 100) / 10.0f;
        Transformation* transform = new Transformation();
        transform->setLocalTransform(glm::translate(glm::mat4(1.0f), glm::vec3(x, 0.0f, z)));

        DrawableObject* bushObject = new DrawableObject(&shaderProgram, bushModel);
        bushObject->transform = transform;
        scene2->addObject(bushObject);
    }

    scenes.push_back(scene2);

    ///



	// Enable depth test.
    glEnable(GL_DEPTH_TEST);

    // Main rendering loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Static triangle transformation (for testing).
        rotatingTriangle->setLocalTransform(glm::scale(glm::mat4(1.0f), glm::vec3(2.0f)));

		// Camera control.
        camera.setPosition(cameraPos);
        camera.lookAt(cameraPos + cameraFront, cameraUp);

		// Draw the current scene.
        scenes[currentSceneIndex]->drawAll();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}