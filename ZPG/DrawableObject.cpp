#include "DrawableObject.h"

DrawableObject::DrawableObject(ShaderProgram* shaderProgram, Model* model)
    : shaderProgram(shaderProgram), model(model) {
}

void DrawableObject::draw(Camera* camera, Light* light)
{
    shaderProgram->useProgram();

    // set matrices
    shaderProgram->setUniform("modelMatrix", transform->getMatrix());
    shaderProgram->setUniform("viewMatrix", camera->getViewMatrix());
    shaderProgram->setUniform("projectMatrix", camera->getProjectionMatrix());

    // set camera and light positions
    shaderProgram->setUniform("viewPos", camera->getPosition());
    shaderProgram->setUniform("lightPos", light->getPosition());

    // set object color
    shaderProgram->setUniform("objectColor", glm::vec3(1.0f, 0.5f, 0.3f));

    // draw model
    model->draw();
}
