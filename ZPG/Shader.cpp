#include "Shader.h"
#include <iostream>

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

Shader::~Shader()
{
    glDeleteShader(id);
}

//GLuint Shader::getID() const
//{
//    return id;
//}

