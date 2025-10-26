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
