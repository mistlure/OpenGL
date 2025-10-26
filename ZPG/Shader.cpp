#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(GLenum type, const std::string& source)
{
	// Create the shader object of the given type
    id = glCreateShader(type);



    // Convert the C++ string to a C-style string for OpenGL
    const char* src = source.c_str();



    // Provide the shader source code to OpenGL
    glShaderSource(id, 1, &src, nullptr);
	// Compile the shader
    glCompileShader(id);


    
    // Check if the compilation was successful
    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    


	// Failure test
    if (!success)
    {
        GLint logLength;
        // Get the length of the error log
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
        // Allocate memory for the log
        char* log = new char[logLength];
        // Retrieve the log content
        glGetShaderInfoLog(id, logLength, nullptr, log);
        // Print the error log
        std::cerr << "Shader compilation failed:\n" << log << std::endl;
		// Free the allocated memory
        delete[] log;
    }
}

Shader::Shader(GLenum type, const char* filepath)
{
    createShaderFromFile(type, filepath);
}

Shader::~Shader()
{
    glDeleteShader(id);
}

//GLuint Shader::getID() const
//{
//    return id;
//}

void Shader::createShader(GLenum shaderType, const char* shaderCode)
{
    id = glCreateShader(shaderType);
    glShaderSource(id, 1, &shaderCode, nullptr);
    glCompileShader(id);

    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint logLength;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
        char* log = new char[logLength];
        glGetShaderInfoLog(id, logLength, nullptr, log);
        std::cerr << "Shader compilation failed:\n" << log << std::endl;
        delete[] log;
    }
}

void Shader::createShaderFromFile(GLenum shaderType, const char* shaderFile)
{
    std::ifstream file(shaderFile);
    if (!file.is_open())
    {
        std::cerr << "Unable to open shader file: " << shaderFile << std::endl;
        exit(-1);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string shaderCode = buffer.str();

    createShader(shaderType, shaderCode.c_str());
}
