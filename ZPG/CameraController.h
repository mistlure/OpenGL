#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera;

class CameraController {
public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    float speed = 0.1f;
    float yaw = -90.0f;
    float pitch = 0.0f;

    void bindCamera(Camera* cam);
    void updateDirection();

private:
    Camera* camera = nullptr;
};
