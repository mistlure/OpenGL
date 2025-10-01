#pragma once
#include <GL/glew.h>
#include <string>

class ShaderProgram;

class Shader
{
    friend class ShaderProgram;
public:
    Shader(GLenum type, const std::string& source);
    ~Shader();

    // GLuint getID() const;

private:
    GLuint id;
};
