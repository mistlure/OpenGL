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

// Bridge between C++ and GLSL that passes transformation data.
// It's universal and will be used for every object.
void ShaderProgram::setModelMatrix(const glm::mat4& matrix)
{
	// Get the location of the "modelMatrix".
    GLint location = glGetUniformLocation(id, "modelMatrix");
	// Location -1 means that the uniform variable was not found or is not used in the shader.
    if (location == -1)
    {
        std::cerr << "Uniform 'modelMatrix' not found!" << std::endl;
        return;
    }
	// Upload the 4x4 matrix to the GPU.
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

// GLuint ShaderProgram::getID() const {
//    return id;
// }
