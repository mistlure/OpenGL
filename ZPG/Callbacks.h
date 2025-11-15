#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Forward-declare the Camera class
class Camera;

// Sets the camera instance for all callbacks to use
void setCameraCallbacks(Camera* cam);

// --- Callback function declarations ---
void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void button_callback(GLFWwindow* window, int button, int action, int mods);
void window_focus_callback(GLFWwindow* window, int focused);
void window_iconify_callback(GLFWwindow* window, int iconified);
void window_size_callback(GLFWwindow* window, int width, int height);
void cursor_callback(GLFWwindow* window, double x, double y);