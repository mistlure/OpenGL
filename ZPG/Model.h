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
};
