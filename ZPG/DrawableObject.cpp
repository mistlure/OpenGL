#include "DrawableObject.h"

DrawableObject::DrawableObject(ShaderProgram* shader, Model* model)
    : shader(shader), model(model) {
}

void DrawableObject::draw()
{
    // Activate the shader program
    shader->use();
    // Bind the model's VAO
    model->bind();
    // Draw call
    model->draw();
}
