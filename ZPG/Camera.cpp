#include "Camera.h"

Camera::Camera() :
    position(0.0f, 0.0f, 5.0f),
    front(0.0f, 0.0f, -1.0f),
    up(0.0f, 1.0f, 0.0f),
    speed(0.3f),
    yaw(-90.0f),
    pitch(0.0f)
{

    updateViewMatrix();
}

void Camera::setPosition(const glm::vec3& pos) {
    position = pos;
    updateViewMatrix();
}

void Camera::setPerspective(float fov, float aspect, float nearPlane, float farPlane) {
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

void Camera::rotate(float deltaX, float deltaY) {
    float sensitivity = 0.1f;
    yaw += deltaX * sensitivity;
    pitch += deltaY * sensitivity;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);

    updateViewMatrix();
}

void Camera::updateViewMatrix() {
    viewMatrix = glm::lookAt(position, position + front, up);
}