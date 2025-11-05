//#include "InputManager.h"
//#include <iostream>
//
//InputManager::InputManager(GLFWwindow* win, SceneManager* sceneManager)
//    : window(win), sceneManager(sceneManager), firstMouse(true), lastMousePos(0.0f) {
//
//    glfwSetWindowUserPointer(window, this);
//
//    glfwSetKeyCallback(window, key_callback);
//    glfwSetCursorPosCallback(window, cursor_callback);
//    glfwSetMouseButtonCallback(window, button_callback);
//    glfwSetWindowSizeCallback(window, window_size_callback);
//    glfwSetWindowFocusCallback(window, window_focus_callback);
//    glfwSetWindowIconifyCallback(window, window_iconify_callback);
//}
//
//void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
//    InputManager* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
//
//    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, GL_TRUE);
//
//    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
//        input->sceneManager->handleBtnPress(key);
//    }
//}
//
//void InputManager::cursor_callback(GLFWwindow* window, double x, double y) {
//    InputManager* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
//
//    if (input->firstMouse) {
//        input->lastMousePos = glm::vec2(x, y);
//        input->firstMouse = false;
//    }
//
//    float deltaX = static_cast<float>(x - input->lastMousePos.x);
//    float deltaY = static_cast<float>(input->lastMousePos.y - y); // inverted Y
//
//    input->lastMousePos = glm::vec2(x, y);
//
//    if (input->sceneManager && input->isCursorLocked)
//        input->sceneManager->handleMouseMovement(deltaX, deltaY);
//}
//
//void InputManager::button_callback(GLFWwindow* window, int button, int action, int mods) {
//    InputManager* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
//
//    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
//        input->isCursorLocked = !input->isCursorLocked;
//
//        if (input->isCursorLocked) {
//            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//            input->firstMouse = true;
//            std::cout << "Cursor locked\n";
//        }
//        else {
//            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//            std::cout << "Cursor unlocked\n";
//        }
//    }
//}
//
//void InputManager::window_size_callback(GLFWwindow* window, int width, int height) {
//    InputManager* input = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
//    input->sceneManager->handleScreenResize(width, height);
//    glViewport(0, 0, width, height);
//}
//
//void InputManager::window_focus_callback(GLFWwindow* window, int focused) {
//    std::cout << "Window focus changed\n";
//}
//
//void InputManager::window_iconify_callback(GLFWwindow* window, int iconified) {
//    std::cout << "Window iconify changed\n";
//}
