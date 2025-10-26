#include "Camera.h"

Camera::Camera()
    : position(0.0f, 0.0f, 5.0f), viewMatrix(1.0f), projectionMatrix(1.0f) {
}

void Camera::setPosition(const glm::vec3& pos) {
    position = pos;
}

void Camera::lookAt(const glm::vec3& target, const glm::vec3& up) {
    viewMatrix = glm::lookAt(position, target, up);
    notifyObservers();
}

void Camera::setPerspective(float fov, float aspect, float nearPlane, float farPlane) {
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

void Camera::setOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
}

const glm::mat4& Camera::getViewMatrix() const {
    return viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const {
    return projectionMatrix;
}

void Camera::addObserver(ICameraObserver* observer) {
    observers.push_back(observer);
}

void Camera::notifyObservers() {
    for (auto o : observers)
        o->onCameraUpdated(viewMatrix);
}
