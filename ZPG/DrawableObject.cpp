#include "DrawableObject.h"

DrawableObject::DrawableObject(const char* ShaderPair[2], Model* model, Camera* camera, Light* light)
    : model(model) {
    Shader vertexShader(GL_VERTEX_SHADER, ShaderPair[0]);
    Shader fragmentShader(GL_FRAGMENT_SHADER, ShaderPair[1]);
    shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
    camera->attach(shaderProgram);

    light->attach(shaderProgram);
	shaderProgram->useProgram();
    shaderProgram->setUniform("lightPos", light->getPosition());


}

void DrawableObject::draw(Camera* camera, Light* light)
{
    shaderProgram->useProgram();

    // set matrices
    shaderProgram->setUniform("modelMatrix", transform->getMatrix());
    /*shaderProgram->setUniform("viewMatrix", camera->getViewMatrix());
    shaderProgram->setUniform("projectMatrix", camera->getProjectionMatrix());*/

    // set camera and light positions
    shaderProgram->setUniform("viewPos", camera->getPosition());
    shaderProgram->setUniform("lightPos", light->getPosition());

    // set object color
    shaderProgram->setUniform("objectColor", glm::vec3(1.0f, 0.5f, 0.3f));

    // draw model
    model->draw();
}
