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

    void setUniform(const std::string& name, const glm::mat4& matrix);
    void setUniform(const std::string& name, const glm::vec3& vector);
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, int value);
    
    // GLuint getID() const;

private:
    GLuint id;
};