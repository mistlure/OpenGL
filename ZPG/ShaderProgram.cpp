#include "ShaderProgram.h"
//#include "Shader.h"
#include <iostream>

// Constructor that links vertex and fragment shaders into a shader program
ShaderProgram::ShaderProgram(const Shader& vertex, const Shader& fragment)
{   
    // Create a new shader program object
    id = glCreateProgram();



    // Attach the compiled vertex&fragment shaders to the program
    // Safe access to internal shader ID
    glAttachShader(id, vertex.id);
    glAttachShader(id, fragment.id);
    // Combine vertex + fragment into one executable
    glLinkProgram(id);



    // Check if the linking was successful
    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);



	// Failure test
    if (!success)
    {
        GLint logLength;
        // Get the length of the error log
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);
        // Allocate memory for the log
        char* log = new char[logLength];
        // Retrieve the log content
        glGetProgramInfoLog(id, logLength, nullptr, log);
        // Print the error log
        std::cerr << "Shader program linking failed:\n" << log << std::endl;
        // Free the allocated memory
        delete[] log;
    }
}   

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(id);
}

void ShaderProgram::use()
{
    glUseProgram(id);
}

// GLuint ShaderProgram::getID() const {
//    return id;
// }
