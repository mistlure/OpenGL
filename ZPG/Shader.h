// Shader is a small class that represents a single shader stage in OpenGL.
// 
// It takes raw GLSL source code, compiles it, and stores the resulting shader object.
// 
// This class doesn’t handle linking or usage — it just prepares ->
// -> one piece of the rendering pipeline.

#pragma once
#include <GL/glew.h>
#include <string>

class ShaderProgram;

class Shader
{
	// Allow ShaderProgram to access private members.
    friend class ShaderProgram;
public:
    Shader(GLenum type, const std::string& source);
    //Shader(GLenum type, const char* filepath);
    ~Shader();


    // GLuint getID() const;

private:
    GLuint id;

    void createShader(GLenum shaderType, const char* shaderCode);
    void createShaderFromFile(GLenum shaderType, const char* shaderFile);
};
