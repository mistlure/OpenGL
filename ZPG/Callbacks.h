﻿#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "CameraController.h"

void setCameraController(CameraController* controller);

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void button_callback(GLFWwindow* window, int button, int action, int mods);
void window_focus_callback(GLFWwindow* window, int focused);
void window_iconify_callback(GLFWwindow* window, int iconified);
void window_size_callback(GLFWwindow* window, int width, int height);
void cursor_callback(GLFWwindow* window, double x, double y);
