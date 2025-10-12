#include "Camera.h"

// Initialize camera at (0,0,5) looking towards the origin.
Camera::Camera()
    : position(0.0f, 0.0f, 5.0f), viewMatrix(1.0f), projectionMatrix(1.0f) {
}

// Set the camera's position in world space.
void Camera::setPosition(const glm::vec3& pos)
{
    position = pos;
}

// Calculates the view matrix so the camera looks at a target point, using the given up direction.
// Also notifies all observers that the view matrix has changed.
void Camera::lookAt(const glm::vec3& target, const glm::vec3& up)
{
    viewMatrix = glm::lookAt(position, target, up);
	notifyObservers(); // Shader programs get updated view matrix.
}

// Set a perspective projection matrix.
void Camera::setPerspective(float fov, float aspect, float nearPlane, float farPlane)
{
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

// Set an orthographic projection matrix.
void Camera::setOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
}

// Get the current view matrix.
const glm::mat4& Camera::getViewMatrix() const
{
    return viewMatrix;
}

// Get the current projection matrix.
const glm::mat4& Camera::getProjectionMatrix() const
{
    return projectionMatrix;
}

// Register an observer to be notified of camera updates.
void Camera::addObserver(ICameraObserver* observer)
{
    observers.push_back(observer);
}

// Notify all registered observers of the updated view matrix.
void Camera::notifyObservers()
{
    for (auto o : observers)
        o->onCameraUpdated(viewMatrix);
}