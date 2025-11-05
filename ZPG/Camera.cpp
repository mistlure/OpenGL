#include "Camera.h"

Camera::Camera()
    : position(0.0f, 0.0f, 5.0f), viewMatrix(1.0f), projectionMatrix(1.0f) {
}

// Sets the camera position and notifies observers of the change.
void Camera::setPosition(const glm::vec3& pos)
{
    position = pos;
    notify(viewMatrix);

}

// Updates the view matrix to look at a target.
void Camera::lookAt(const glm::vec3& target, const glm::vec3& up)
{
    viewMatrix = glm::lookAt(position, target, up);
    notify(viewMatrix);

}

// Sets the projection matrix to a perspective projection.
void Camera::setPerspective(float fov, float aspect, float nearPlane, float farPlane)
{
    projectionMatrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
}

// Sets the projection matrix to an orthographic projection.
void Camera::setOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    projectionMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
}

// Returns the current view matrix.
const glm::mat4& Camera::getViewMatrix() const
{
    return viewMatrix;
}

// Returns the current projection matrix.
const glm::mat4& Camera::getProjectionMatrix() const
{
    return projectionMatrix;
}
