// Model represents a 3D object’s geometry in OpenGL.
// 
// It stores vertex data in GPU memory using a VBO and configures ->
// -> how that data is interpreted using a VAO.
// 
// Once created, the model can be bound and drawn using standard OpenGL calls.

#pragma once
#include <GL/glew.h>

class Model
{
public:
    Model(float* data, size_t size);
    ~Model();

    void bind();
    void draw();

private:
    GLuint vao;
    GLuint vbo;

    GLsizei vertexCount;

};
