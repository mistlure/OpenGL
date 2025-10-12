#include "callbacks.h"
#include <iostream>

extern std::vector<Scene*> scenes;
extern int currentSceneIndex;

extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;
extern float cameraSpeed;

extern float yaw;
extern float pitch;

void updateCameraFront() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw));
    direction.y = 0.0f;
    direction.z = sin(glm::radians(yaw));
    cameraFront = glm::normalize(direction);
}

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

	// Switch scenes with number keys 1-9
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
    if (action == GLFW_PRESS || action == GLFW_REPEAT)
    {
        if (key == GLFW_KEY_W) 
        {
            cameraPos += cameraSpeed * cameraFront;
            std::cout << "Camera position: " << cameraPos.x << ", " << cameraPos.y << ", " << cameraPos.z << std::endl;
        }
        if (key == GLFW_KEY_S)
            cameraPos -= cameraSpeed * cameraFront;
        if (key == GLFW_KEY_A)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (key == GLFW_KEY_D)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
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

void button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {
            yaw -= 5.0f;
            updateCameraFront();
            printf("Rotated camera left to yaw = %.2f\n", yaw);
        }
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            yaw += 5.0f;
            updateCameraFront();
            printf("Rotated camera right to yaw = %.2f\n", yaw);
        }
    }
}