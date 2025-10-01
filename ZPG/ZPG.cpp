//GLEW 
#include <GL/glew.h>

//  GLFW
#include <GLFW/glfw3.h>

//  GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Callbacks.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Model.h"

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



const char* vertex_shader =
"#version 330 core\n"
"layout(location = 0) in vec3 vp;\n"
"layout(location = 1) in vec3 color;\n"
"out vec3 fragColor;\n"
"void main () {\n"
"    gl_Position = vec4(vp, 1.0);\n"
"    fragColor = color;\n"
"}";



const char* fragment_shader =
"#version 330 core\n"
"in vec3 fragColor;\n"
"out vec4 finalColor;\n"
"void main () {\n"
"    finalColor = vec4(fragColor, 1.0);\n"
"}";
/*
const char* fragment_shader_ignorColor =
"#version 330 core\n"
"out vec4 finalColor;\n"
"void main () {\n"
"    finalColor = vec4(0.2, 0.8, 0.4, 1.0);\n"
"}";
*/






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

    ShaderProgram shaderProgram(vertexShader, fragmentShader);
    shaderProgram.use();






    Model model(points, sizeof(points));






    // Main rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear color and depth buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.use();
        
        model.bind();
        model.draw();

        // Update other events like input handling
        glfwPollEvents();
        // Put the stuff we’ve been drawing onto the display
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
