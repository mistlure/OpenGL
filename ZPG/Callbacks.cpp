#include "callbacks.h"
#include "SceneManager.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static CameraController* controller = nullptr;
static bool cursorLocked = false;

void setCameraController(CameraController* c) {
    controller = c;
}

void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (action == GLFW_PRESS) {
        if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9) {
            int index = key - GLFW_KEY_1;
            SceneManager::get().setCurrent(index);
            std::cout << "Switched to scene " << index << std::endl;
        }
    }

    if ((action == GLFW_PRESS || action == GLFW_REPEAT) && controller) {
        if (key == GLFW_KEY_W)
            controller->position += controller->speed * controller->front;
        std::cout << "Camera position: " << controller->position.x << ", " << controller->position.y << ", " << controller->position.z << std::endl;

        if (key == GLFW_KEY_S)
            controller->position -= controller->speed * controller->front;
        if (key == GLFW_KEY_A)
            controller->position -= glm::normalize(glm::cross(controller->front, controller->up)) * controller->speed;
        if (key == GLFW_KEY_D)
            controller->position += glm::normalize(glm::cross(controller->front, controller->up)) * controller->speed;
    }
}

void button_callback(GLFWwindow* window, int button, int action, int mods) {

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        cursorLocked = !cursorLocked;

        if (cursorLocked) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            std::cout << "Cursor locked\n";
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            std::cout << "Cursor unlocked\n";
        }
    }
}

void window_focus_callback(GLFWwindow* window, int focused) {
    printf("window_focus_callback\n");
}

void window_iconify_callback(GLFWwindow* window, int iconified) {
    printf("window_iconify_callback\n");
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    printf("resize %d, %d\n", width, height);
    glViewport(0, 0, width, height);
}

void cursor_callback(GLFWwindow* window, double x, double y) {
    static bool firstMouse = true;
    static double lastX = 0.0, lastY = 0.0;

    if (!cursorLocked || !controller) return;

    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
        return;
    }

    float deltaX = static_cast<float>(x - lastX);
    float deltaY = static_cast<float>(lastY - y); // инвертируем Y

    lastX = x;
    lastY = y;

    controller->rotate(deltaX, deltaY);
    printf("cursor_callback\n");
}