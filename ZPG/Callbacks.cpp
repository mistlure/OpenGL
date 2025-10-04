#include "callbacks.h"
#include "Scene.h"

#include <stdio.h>
#include <vector>

extern std::vector<Scene*> scenes;
extern int currentSceneIndex;

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

    if (action == GLFW_PRESS)
    {
        if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9)
        {
            int index = key - GLFW_KEY_1;
            if (index < scenes.size())
            {
                currentSceneIndex = index;
                printf("Switched to scene %d\n", index + 1);
            }
        }
    }
}

void window_focus_callback(GLFWwindow* window, int focused)
{
    printf("window_focus_callback \n");
}

void window_iconify_callback(GLFWwindow* window, int iconified)
{
    printf("window_iconify_callback \n");
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}

void cursor_callback(GLFWwindow* window, double x, double y)
{
    printf("cursor_callback \n");
}

void button_callback(GLFWwindow* window, int button, int action, int mode)
{
    printf("button_callback [%d,%d,%d]\n", button, action, mode);
}