#pragma once
#include <GL/glew.h>
#include "Shader.h"

class ShaderProgram {
public:
    ShaderProgram(const Shader& vertex, const Shader& fragment);
    ~ShaderProgram();

    void use();
    
    // GLuint getID() const;

private:
    GLuint id;
};