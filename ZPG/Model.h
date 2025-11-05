// Model represents a 3D object’s geometry in OpenGL.
// 
// It stores vertex data in GPU memory using a VBO and configures ->
// -> how that data is interpreted using a VAO.
// 
// Once created, the model can be bound and drawn using standard OpenGL calls.

#pragma once
#include <GL/glew.h>

#include "tiny_obj_loader.h"
#include <iostream>
#include <stdexcept>

class Model
{
public:
    Model(float* data, size_t size);
    Model(const char* filename);
    ~Model();

    void bind() const;
	void unbind() const;
    void draw() const;

private:
    GLuint vao;
    GLuint vbo;

    GLsizei vertexCount;
};
