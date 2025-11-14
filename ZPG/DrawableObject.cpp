#include "DrawableObject.h"

DrawableObject::DrawableObject(const char* ShaderPair[2], Model* model, Camera* camera, Light* light)
    : model(model) {
    Shader vertexShader(GL_VERTEX_SHADER, ShaderPair[0]);
    Shader fragmentShader(GL_FRAGMENT_SHADER, ShaderPair[1]);
    shaderProgram = new ShaderProgram(vertexShader, fragmentShader, camera, light);

	shaderProgram->useProgram();
    //shaderProgram->setUniform("lightPos", light->getPosition());

}

void DrawableObject::draw()
{
    shaderProgram->useProgram();

    // set matrices
    shaderProgram->setUniform("modelMatrix", transform->getMatrix());
   
    model->bind();

    glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount()); 

    glBindVertexArray(0);
    glUseProgram(0);
}
