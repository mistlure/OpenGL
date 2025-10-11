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

#include "SphereData.h"

std::vector<Scene*> scenes;
int currentSceneIndex = 0;

Transformation* rotatingTriangle = nullptr;

float points[] = {
    // X,Y,Z            // R,G,B

    // 🔺 Figure№1 
    -0.6f, -0.2f, 0.0f,   1.0f, 0.75f, 0.8f,
    -0.7f,  0.2f, 0.0f,   0.6f, 0.4f, 0.8f,
    -0.5f,  0.2f, 0.0f,   0.96f, 0.85f, 0.7f,


    // 🟥 Figure№2
     0.0f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,
     0.0f, -0.2f, 0.0f,   0.0f, 1.0f, 0.0f,
    -0.2f, -0.2f, 0.0f,   0.0f, 0.0f, 1.0f,

     0.0f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,
    -0.2f, -0.2f, 0.0f,   0.0f, 0.0f, 1.0f,
    -0.2f,  0.2f, 0.0f,   1.0f, 1.0f, 0.0f
};

// Vertex shader with transformation
const char* vertex_shader =
"#version 330 core\n"
"layout(location = 0) in vec3 vp;\n"
"layout(location = 1) in vec3 color;\n"
"uniform mat4 modelMatrix;\n"
"out vec3 fragColor;\n"
"void main () {\n"
"    gl_Position = modelMatrix * vec4(vp, 1.0);\n"
"    fragColor = color;\n"
"}";

const char* fragment_shader =
"#version 330 core\n"
"in vec3 fragColor;\n"
"out vec4 finalColor;\n"
"void main () {\n"
"    finalColor = vec4(fragColor, 1.0);\n"
"}";

const char* fragment_shaderIgnorColor =
"#version 330 core\n"
"out vec4 finalColor;\n"
"void main () {\n"
"    finalColor = vec4(0.2, 0.8, 0.4, 1.0);\n"
"}";
const char* fragment_shaderGreen =
"#version 330 core\n"
"out vec4 finalColor;\n"
"void main () {\n"
"    finalColor = vec4(0.2, 1.0, 0.2, 1.0);\n"
"}";




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



    Shader vertexShader(GL_VERTEX_SHADER, vertex_shader);
    Shader fragmentShader(GL_FRAGMENT_SHADER, fragment_shader);

    Shader fragmentGreen(GL_FRAGMENT_SHADER, fragment_shaderGreen);
    ShaderProgram shaderGreen(vertexShader, fragmentGreen);


    ShaderProgram shaderProgram(vertexShader, fragmentShader);
    shaderProgram.use();

    //Model model(points, sizeof(points));
    //DrawableObject object(&shaderProgram, &model);
    //Scene scene;
    //scene.addObject(&object);








    float triangle[] = {
    -0.3f, -0.3f, 0.0f,  1.0f, 0.0f, 0.0f,
     0.3f, -0.3f, 0.0f,  0.0f, 1.0f, 0.0f,
     0.0f,  0.3f, 0.0f,  0.0f, 0.0f, 1.0f
    };

	// Create models and drawable objects.
    Model* triangleModel = new Model(triangle, sizeof(triangle));
    DrawableObject* triangleObject = new DrawableObject(&shaderProgram, triangleModel);


    float square[] = {
    -0.1f, -0.1f, 0.0f,  1.0f, 1.0f, 0.0f,
     0.1f, -0.1f, 0.0f,  1.0f, 1.0f, 0.0f,
     0.1f,  0.1f, 0.0f,  1.0f, 1.0f, 0.0f,

    -0.1f, -0.1f, 0.0f,  1.0f, 1.0f, 0.0f,
     0.1f,  0.1f, 0.0f,  1.0f, 1.0f, 0.0f,
    -0.1f,  0.1f, 0.0f,  1.0f, 1.0f, 0.0f
    };
    Model* squareModel = new Model(square, sizeof(square));


	// Create a transformation for the triangle.
    rotatingTriangle = new Transformation();
    triangleObject->transform = rotatingTriangle;

    // Scenes
    Scene* scene1 = new Scene();
    Scene* scene2 = new Scene();
    Scene* scene3 = new Scene();

    scene1->addObject(triangleObject);

	// Add objects to scenes.
    scenes.push_back(scene1);
    scenes.push_back(scene2);
    scenes.push_back(scene3);















	// Sphere model.
    Model* sphereModel = new Model(sphere, sphereSize);

	// Centers for the spheres in scene2.
    glm::vec3 centers[] = {
        glm::vec3(0.6f, 0.0f, 0.0f),
        glm::vec3(-0.6f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.6f, 0.0f),
        glm::vec3(0.0f, -0.6f, 0.0f)
    };

    for (int i = 0; i < 4; ++i) {
        DrawableObject* ball = new DrawableObject(&shaderProgram, sphereModel);
        Transformation* t = new Transformation();

		// Scale and translate.
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f));
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), centers[i]);
        t->setLocalTransform(translate * scale);

        ball->transform = t;
        scene2->addObject(ball);
    }





    for (int i = 0; i < 10; ++i) {
		// Schere.
        DrawableObject* ball = new DrawableObject(&shaderProgram, sphereModel);
        Transformation* t = new Transformation();
        glm::vec3 pos = glm::vec3((i % 5) * 0.4f - 0.8f, (i / 5) * 0.4f - 0.4f, 0.0f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.2f));
        t->setLocalTransform(transform);
        ball->transform = t;
        scene3->addObject(ball);
    }

    for (int i = 0; i < 5; ++i) {
		// Triangle.
        DrawableObject* tri = new DrawableObject(&shaderGreen, triangleModel);
        Transformation* t = new Transformation();
        glm::vec3 pos = glm::vec3(-0.9f + i * 0.45f, 0.7f, 0.0f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos);
        t->setLocalTransform(transform);
        tri->transform = t;
        scene3->addObject(tri);
    }

    for (int i = 0; i < 5; ++i) {
		// Square.
        DrawableObject* sq = new DrawableObject(&shaderProgram, squareModel);
        Transformation* t = new Transformation();
        glm::vec3 pos = glm::vec3(0.9f - i * 0.45f, -0.7f, 0.0f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
        t->setLocalTransform(transform);
        sq->transform = t;
        scene3->addObject(sq);
    }


    // Main rendering loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (currentSceneIndex == 0 && rotatingTriangle) {
            float time = (float)glfwGetTime();
            glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0.0f, 0.0f, 1.0f));
            rotatingTriangle->setLocalTransform(rotation);
        }
        printf("Current scene: %d\n", currentSceneIndex);
        scenes[currentSceneIndex]->drawAll();

        //glm::mat4 M = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        //shaderProgram.setModelMatrix(M);

        // Update other events like input handling
        glfwPollEvents();
        // Put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}