// ShaderProgram links multiple shaders into a complete GPU program.
// 
// It handles linking, validation, and activation of the program.

#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"

class ShaderProgram
{
public:
    ShaderProgram(const Shader& vertex, const Shader& fragment);
    ~ShaderProgram();

    void use();

    void setModelMatrix(const glm::mat4& matrix);
    
    // GLuint getID() const;

private:
    GLuint id;
};