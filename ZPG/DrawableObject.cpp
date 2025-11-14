#include "DrawableObject.h"

DrawableObject::DrawableObject(const char* ShaderPair[2], Model* model, Camera* camera, std::vector<Light*>* lights)
    : model(model) {
    Shader vertexShader(GL_VERTEX_SHADER, ShaderPair[0]);
    Shader fragmentShader(GL_FRAGMENT_SHADER, ShaderPair[1]);
    shaderProgram = new ShaderProgram(vertexShader, fragmentShader, camera, lights);

}

void DrawableObject::draw()
{
    shaderProgram->useProgram();

	// set transform matrix
    shaderProgram->setUniform("modelMatrix", transform->getMatrix());
   
    model->bind();

    glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount()); 

    glBindVertexArray(0);
    glUseProgram(0);
}
