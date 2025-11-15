#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Subject.h"
#include "EnumObservableSubjects.h"
class Camera : public Subject {
public:
    Camera();

    void setPosition(const glm::vec3& pos);
    void setPerspective(float fov, float aspect, float nearPlane, float farPlane);
    void rotate(float deltaX, float deltaY);

    const glm::mat4& getViewMatrix() const { return viewMatrix; }
    const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
    const glm::vec3& getPosition() const { return position; }

    glm::vec3 front;
    glm::vec3 up;
    float speed;
    float yaw;
    float pitch;

private:
    glm::vec3 position;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    void updateViewMatrix();
};