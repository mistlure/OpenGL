#include "CameraController.h"
#include "Camera.h"

void CameraController::bindCamera(Camera* cam) {
    camera = cam;
}

void CameraController::updateDirection() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw));
    direction.y = 0.0f;
    direction.z = sin(glm::radians(yaw));
    front = glm::normalize(direction);

    if (camera)
        camera->lookAt(position + front, up);
}

void CameraController::rotate(float deltaX, float deltaY) {
    float sensitivity = 0.1f;
    yaw += deltaX * sensitivity;
    pitch -= deltaY * sensitivity;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);

    if (camera)
        camera->lookAt(position + front, up);
}