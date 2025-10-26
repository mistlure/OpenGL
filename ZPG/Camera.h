#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "CameraObserver.h"

class Camera {
public:
    Camera();

    void setPosition(const glm::vec3& pos);
    void lookAt(const glm::vec3& target, const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f));
    void setPerspective(float fov, float aspect, float nearPlane, float farPlane);
    void setOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);

    const glm::mat4& getViewMatrix() const;
    const glm::mat4& getProjectionMatrix() const;

    void addObserver(ICameraObserver* observer);
    void notifyObservers();

private:
    glm::vec3 position;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    std::vector<ICameraObserver*> observers;
};
