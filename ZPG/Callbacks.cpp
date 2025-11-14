#include "callbacks.h"
#include "SceneManager.h" // You might have this for scene switching
#include "Camera.h"       // Include the new unified Camera header

#include <iostream>
#include "Application.h"

// Global pointer to the single Camera object
static Camera* camera = nullptr;
static bool cursorLocked = false;

// Function to set the global camera
void setCameraCallbacks(Camera* cam) {
    camera = cam;
}

void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    
    if (action == GLFW_PRESS) {
        // получаем указатель на Application
        Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
        if (!app) return;

        // переключение сцен
        if (key == GLFW_KEY_1) app->switchScene(0);
        if (key == GLFW_KEY_2) app->switchScene(1);
        if (key == GLFW_KEY_3) app->switchScene(2);
        
        
        
        
        if (key == GLFW_KEY_F) app->getCurrentScene()->switchHeadLight();



    }

    // Handle camera movement input
    if ((action == GLFW_PRESS || action == GLFW_REPEAT) && camera) {

        // 1. Get the current position
        glm::vec3 pos = camera->getPosition();

        // 2. Calculate the new position based on key presses
        if (key == GLFW_KEY_W)
            pos += camera->speed * camera->front;

        // Log the new position (using the local 'pos' variable)
        std::cout << "Camera position: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;

        if (key == GLFW_KEY_S)
            pos -= camera->speed * camera->front;
        if (key == GLFW_KEY_A)
            pos -= glm::normalize(glm::cross(camera->front, camera->up)) * camera->speed;
        if (key == GLFW_KEY_D)
            pos += glm::normalize(glm::cross(camera->front, camera->up)) * camera->speed;

        // 3. Set the new position on the camera (this updates the view matrix)
        camera->setPosition(pos);
    }
}

void button_callback(GLFWwindow* window, int button, int action, int mods) {
    // Toggles cursor lock
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
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);

	window_size_callback(window, fbWidth, fbHeight); // Force update on focus
}

void window_iconify_callback(GLFWwindow* window, int iconified) {
    printf("window_iconify_callback\n");
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

    // Update the camera's aspect ratio
    if (camera && width > 0 && height > 0) {
        // Calculate new aspect ratio
        float aspect = (float)width / (float)height;

        // Re-set the perspective using the stored fov/near/far
        camera->setPerspective(45.0f, aspect, 0.1f, 100.0f);
    }
}

void cursor_callback(GLFWwindow* window, double x, double y) {
    static bool firstMouse = true;
    static double lastX = 0.0, lastY = 0.0;

    // Only rotate if cursor is locked and camera exists
    if (!cursorLocked || !camera) {
        firstMouse = true; 
        return;
    }
    if (firstMouse) {
        lastX = x;
        lastY = y;
        firstMouse = false;
        return;
    }

    // Calculate mouse delta
    float deltaX = static_cast<float>(x - lastX);
    float deltaY = static_cast<float>(lastY - y); // Y is inverted

    lastX = x;
    lastY = y;

    // Pass the delta to the camera's rotate function
    camera->rotate(deltaX, deltaY);
    printf("cursor_callback\n");
}